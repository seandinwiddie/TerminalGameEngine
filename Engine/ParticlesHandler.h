#pragma once
#include "Particle.h"
#include <list>

template<typename T> using list = std::list<T>;

class ParticlesHandler
{
private:
	list<Particle> particles;

};