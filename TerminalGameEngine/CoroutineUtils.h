#pragma once
#include <iostream>
#include <coroutine>
#include <thread>
#include <chrono>
#include <future>

struct SleepAwaitable
{
    std::chrono::milliseconds duration;

    bool await_ready() const noexcept { return false; }
    void await_suspend(std::coroutine_handle<> handle) const
    {
        std::thread([handle, this]()
            {
                std::this_thread::sleep_for(duration);
                handle.resume();
            }).detach();
    }
    void await_resume() const noexcept {}
};

inline SleepAwaitable sleep_for(std::chrono::milliseconds duration)
{
    return SleepAwaitable{ duration };
}

struct Task
{
    struct promise_type
    {
        std::promise<void> promise;

        Task get_return_object()
        {
            return Task{ promise.get_future() };
        }

        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() { promise.set_value(); }
        void unhandled_exception() { promise.set_exception(std::current_exception()); }
    };

    std::future<void> future;
    explicit Task(std::future<void> fut) : future(std::move(fut)) {}
};