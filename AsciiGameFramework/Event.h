#pragma once

#include <vector>
#include <functional>

template <typename... Args>
class Event
{
    using EventHandler = std::function<void(Args...)>;
    
//---------------------------------------------------------- Fields
private:
    std::vector<EventHandler> handlers;

//---------------------------------------------------------- Methods
public:
    void Subscribe(EventHandler handler)
    { 
        handlers.push_back(handler);
    }

    void Notify(Args... args)
    {
        for (auto& handler : handlers)
            handler(args...);
    }

    void Clear() { 
        handlers.clear();
    }
};