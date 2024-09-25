#pragma once
#include "GameObject.h"

class Alien : public GameObject
{
//------------------------------------------------------------------- Fields
private:
	Model model;

//------------------------------------------------------------------- Methods
public:
	Alien(int xPos, int yPos) : GameObject(xPos, yPos){}

	virtual bool CanExitScreenSpace() const override { return false; }
	virtual double GetGravityScale() const override { return 0; }
	virtual int GetColor() const { return Terminal::YELLOW; }

protected:
	virtual void OnCollisionEnter(GameObject* other, Direction collisionDir) override{}
	virtual void InitModel()
	{
		if (model.size() == 0)
			model = CreteModelUsingChar(-37, size_t(4), size_t(2));
		SetModel(model);
	}
};