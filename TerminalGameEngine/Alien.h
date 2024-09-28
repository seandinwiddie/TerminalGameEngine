#pragma once
#include "GameObject.h"
#include "AliensController.h"
#include "Event.h"

class Alien : public GameObject
{
friend class AliensController;

//------------------------------------------------------ Settings
private:
	static const size_t PROJECTILE_SPEED = 8;

//------------------------------------------------------ Fields
public:
	Event<GameObject*> OnDestroy;

private:
	size_t gridIndexX;
	size_t gridIndexY;

protected:
	bool showFirstAnimFrame;
//------------------------------------------------------ Methods
public:
	Alien(int xPos, int yPos, size_t xIndexInFormation, size_t yIndexInFormation) :
		GameObject(xPos, yPos), gridIndexX(xIndexInFormation), gridIndexY(yIndexInFormation) { }

public:
	virtual bool CanExitScreenSpace() const override { return false; }
	size_t GetIndexInGridX() { return gridIndexX; }
	size_t GetIndexInGridY() { return gridIndexY; }
	virtual size_t GetScore() const = 0;
	void Shot();

protected:
	virtual double GetGravityScale() const override { return 0; }
	virtual void CALLED_BY_SIM_OnDestroy() override;
	virtual void Update();
	virtual void StepAnimation() = 0;
};