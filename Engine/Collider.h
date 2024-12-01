#pragma once
#include "GameObject.h"
#include <unordered_set>
#include <array>
#include <memory>	

namespace Engine
{
	template<typename T> using uset = std::unordered_set<T>;
	template<typename T> using weak_ptr = std::weak_ptr<T>;
	template<typename T> using list = std::list<T>;

	class Collider : public GameObject
	{
		friend class Simulation;

		//---------------------------------------------------------- Fields

	protected:
		std::array<list<weak_ptr<Collider>>, 4> collisions;

		//---------------------------------------------------------- Methods
	public:
		using GameObject::GameObject;

	protected:

		virtual void OnCollisionEnter(shared_ptr<Collider> other, Direction collisionDir) {}
		virtual void OnCollisionExit(Direction endingCollisionDir) {}

	private:
		void CALLED_BY_SIM_NotifyCollisionEnter(uset<shared_ptr<Collider>>collidingObjects, Direction collisionDir);
		void CALLED_BY_SIM_NotifyCollisionEnter(shared_ptr<Collider> collidingObject, Direction collisionDir);
		void CALLED_BY_SIM_UpdateEndedCollisions(const std::array<uset<shared_ptr<Collider>>, 4>& newCollisions);
	};
}