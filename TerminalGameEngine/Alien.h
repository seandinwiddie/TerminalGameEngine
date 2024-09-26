#pragma once
#include "GameObject.h"
#include "AliensController.h"
#include "Event.h"

class Alien : public GameObject
{
friend class AliensController;

//------------------------------------------------------ Fields
public:
	Event<int, int> OnDestroy;

private:
	int xIndexInMatrix;
	int yIndexInMatrix;

protected:
	bool showFirstAnimFrame;
//------------------------------------------------------ Methods
public:
	Alien(int xPos, int yPos, int xIndexInMatrix, int yIndexInMatrix) : 
		GameObject(xPos, yPos), xIndexInMatrix(xIndexInMatrix), yIndexInMatrix(yIndexInMatrix) { }

public:
	virtual bool CanExitScreenSpace() const override { return false; }
	virtual size_t GetScore() const = 0;

protected:
	virtual double GetGravityScale() const override { return 0; }
	virtual void CALLED_BY_SIM_OnDestroy() override;

	virtual void Update();

	virtual void StepAnimation() = 0;

};