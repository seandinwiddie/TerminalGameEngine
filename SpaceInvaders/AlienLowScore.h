#pragma once
#include "Alien.h"

namespace SpaceInvaders
{
	class AlienLowScore : public Alien
	{
	private:
		static const Model MODEL_1;
		static const Model MODEL_2;
		//------------------------------------------------------ Methods
	public:
		using Alien::Alien;

		virtual size_t GetScore() const { return 10; }
		int GetColor() const override { return Engine::Terminal::YELLOW_DARK; }

	protected:
		virtual void InitModel()
		{
			animationModel1 = &MODEL_1;
			animationModel2 = &MODEL_2;
			SetModel(MODEL_1);
		}

	};

	const Model AlienLowScore::MODEL_1
	(
		4,
		{
			'[', ':', ':', ']',
			'/', '"', '"', '\\'
		}
	);

	const Model AlienLowScore::MODEL_2
	(
		4,
		{
			'[', '.', '.', ']',
			'\\', '"', '"', '/'
		}
	);
}