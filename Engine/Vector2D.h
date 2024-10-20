#pragma once
#include "vector"

namespace Engine
{
    template<typename T> using vector = std::vector<T>;

    /// <summary>
    /// Implementation of a 2D vector using monodimensional vector for
    /// better performance (cache)
    /// </summary>
    /// <typeparam name="T"></typeparam>
    template<typename T>
    class Vector2D
    {
        // -------------------------------------------------------------------- Fields
    private:
        size_t width = 0;
        vector<T> vector;

        // -------------------------------------------------------------------- Methods
    public:
        Vector2D() : Vector2D(0) {};
        Vector2D(size_t width) : width(width) { vector.resize(width); }

        Vector2D(size_t width, const std::vector<T>& vect) : width(width)
        {
            vector = vect;
        }

        size_t GetSizeX() const { return width; }
        size_t GetSizeY() const { return width == 0 ? 0 : vector.size() / width; }

        void IncreaseSizeY() { vector.resize(vector.size() + width); }
        void Resize(size_t width, size_t height)
        {
            this->width = width;
            vector.resize(width * height);
        }
        void Clear() { vector.clear(); }

        const T& Get(size_t x, size_t y) const { return vector[width * y + x]; }
        T& Get(size_t x, size_t y) { return vector[width * y + x]; }

        // -------------------------------------------------------------------- Iterator
        class Iterator
        {
        private:
            typename std::vector<T>::iterator it;
        public:
            Iterator(typename std::vector<T>::iterator it) : it(it) {}

            T& operator*() { return *it; }
            Iterator& operator++() { ++it; return *this; }
            Iterator operator++(int) { Iterator temp = *this; ++it; return temp; }
            bool operator==(const Iterator& other) const { return it == other.it; }
            bool operator!=(const Iterator& other) const { return it != other.it; }
        };
        Iterator begin() { return Iterator(vector.begin()); }
        Iterator end() { return Iterator(vector.end()); }
    };
}
