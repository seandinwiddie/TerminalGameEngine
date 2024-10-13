#pragma once

namespace Engine
{
	class ISimulationEntity
	{
		friend class Simulation;
		//---------------------------------------------------------- Methods
	protected:
		virtual void Update() = 0;
		virtual ~ISimulationEntity() = default;
	};
}