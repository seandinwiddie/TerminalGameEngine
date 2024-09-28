#pragma once
#include <vector>

template <typename T> using vector = std::vector<T>;

class Alien;

class AliensFrontline
{
private:
	vector<Alien*> frontLine;
public:
	void Init(size_t size) { frontLine.resize(size); }
	Alien* GetAt(size_t pos) { return frontLine[pos]; }
	void Set(size_t pos, Alien* alien) {frontLine[pos] = alien; }
	size_t GetMinY();
	void ReplaceDestroyedElement(Alien* destroyedObj, const vector<vector<Alien*>>& aliensGrid);
};