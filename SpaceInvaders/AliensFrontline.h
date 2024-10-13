#pragma once
#include <vector>
#include "RandomUtils.h"
#include "Vector2D.h"

namespace SpaceInvaders
{
	template <typename T> using vector = std::vector<T>;
	template <typename T> using Vector2D = Engine::Vector2D<T>;

	class Alien;

	class AliensFrontline
	{
	private:
		vector<Alien*> frontLine;
	public:
		void Init(size_t size) { frontLine.resize(size); }
		Alien* GetAt(size_t pos) { return frontLine.size() > 0 ? frontLine[pos] : nullptr; }
		Alien* GetRandom();
		void Set(size_t pos, Alien* alien) { frontLine[pos] = alien; }
		size_t GetMinY();
		void ReplaceDestroyedElement(Alien* destroyedAlien, const Vector2D<Alien*>& aliensGrid);
	};
}