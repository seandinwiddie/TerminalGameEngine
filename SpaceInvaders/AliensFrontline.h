#pragma once
#include "RandomUtils.h"
#include "Vector2D.h"
#include <vector>

namespace SpaceInvaders
{
	template <typename T> using vector = std::vector<T>;
	template <typename T> using Vector2D = Engine::Vector2D<T>;
	template<typename T> using shared_ptr = std::shared_ptr<T>;
	template<typename T> using weak_ptr = std::weak_ptr<T>;

	class Alien;

	class AliensFrontline
	{
	private:
		vector<shared_ptr<Alien>> frontLine;
	public:
		void Init(size_t size) { frontLine.resize(size); }
		shared_ptr<Alien> GetAt(size_t pos) { return frontLine.size() > 0 ? frontLine[pos] : nullptr; }
		shared_ptr<Alien> GetRandom();
		void Set(size_t pos, shared_ptr<Alien> alien) { frontLine[pos] = alien; }
		size_t GetMinY();
		void ReplaceDestroyedElement(shared_ptr<Alien> destroyedAlien, const Vector2D<weak_ptr<Alien>>& aliensGrid);
	};
}