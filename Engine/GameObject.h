#pragma once
#include "Config.h"
#include "GridDirection.h"
#include "ISimulationEntity.h"
#include "Terminal.h"
#include "Event.h"
#include "Vector2D.h"

#include <Windows.h>
#include <vector>

template<typename T> using vector = std::vector<T>;
using namespace GridDirection;
using Model = Vector2D<char>;

class GameObject : public ISimulationEntity
{
	friend class Simulation;

//---------------------------------------------------------- Fields
public:
	Event<GameObject*, Direction> OnMove;
	// generic on destroy event could be added

protected:
	bool canMove = true;

private:
	int xPos;
	int yPos;

	double xPosContinuous;
	double yPosContinuous;

	bool mustBeReprinted = true;
	const Model* model = nullptr;

//---------------------------------------------------------- Methods
public:
	GameObject(int xPos, int yPos);

	virtual int GetColor() const { return Terminal::WHITE; }
	void Init() { InitModel(); }
	int GetPosX() const { return xPos; }
	int GetPosY() const { return yPos; }
	int GetMaxPosX()const { return xPos + static_cast<int>(GetModelWidth()) - 1; }
	int GetMaxPosY()const { return yPos + static_cast<int>(GetModelHeight()) - 1; }
	int GetMidPosX() { return GetPosX() + static_cast<int>(GetModelWidth()) / 2; }
	int GetMidPosY() { return GetPosY() + static_cast<int>(GetModelHeight()) / 2; }
	size_t GetModelWidth()const { return model->GetSizeX(); };
	size_t GetModelHeight()const { return model->GetSizeY(); }
	const Model& GetModel()const { return *model; }
	virtual bool CanExitScreenSpace() const = 0;

protected:
	virtual void InitModel() = 0;
	virtual double GetGravityScale() const = 0;
	virtual void OnDestroy() {} // called by simulation
	virtual void TryMove(Direction direction, double moveSpeed);
	virtual void Update();
	Model CreteModelUsingChar(char modelChar, size_t sizeX, size_t sizeY) const;
	void SetModel(const Model& newModel);

private:
	void ResetPartialMovement() { xPosContinuous = xPos; yPosContinuous = yPos; }
	void ApplyGravity();
	void CALLED_BY_SIM_Move(Direction direction);
};