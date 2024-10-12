#pragma once
#include "vector"

template<typename T> using vector = std::vector<T>;

/// <summary>
/// Implementation of a 2D vector using monodimensional vector for
/// better performance (cache)
/// </summary>
/// <typeparam name="T"></typeparam>
template<typename T>
class Vector2D
{
private:
	size_t width = 0;
	vector<T> vector;

public:
	Vector2D() : Vector2D(0) {};
	Vector2D(size_t width) : width(width) { vector.resize(width); }

	size_t GetSizeX() const { return width; }
	size_t GetSizeY() const { return width == 0 ? 0 : vector.size() / width; }

	void IncreaseSizeY() { vector.resize(vector.size() + width); }
	void Resize(size_t width, size_t height)
	{
		this->width = width;
		vector.resize(width * height);
	}

	void Set(T value, size_t x, size_t y) { vector[width * y + x] = value; }
	T Get(size_t x, size_t y) const { return vector[width * y + x]; }
};