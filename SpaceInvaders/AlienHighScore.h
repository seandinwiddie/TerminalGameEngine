#pragma once
#include "Alien.h"

namespace SpaceInvaders
{
	class AlienHighScore : public Alien
	{
	private:
		static const Model MODEL_1;
		static const Model MODEL_2;
		//------------------------------------------------------ Methods
	public:
		using Alien::Alien;

		virtual size_t GetScore() const { return 30; }
		virtual int GetColor() const override { return Engine::Terminal::MAGENTA; }

	protected:
		virtual void InitModel()
		{
			animationModel1 = &MODEL_1;
			animationModel2 = &MODEL_2;
			SetModel(MODEL_1);
		}
	};

	const Model AlienHighScore::MODEL_1
	(
		4,
		{
			'/', 'O',  'o',  '\\',
			'/', '\'', '\'', '\\'
		}
	);

	const Model AlienHighScore::MODEL_2
	(
		4,
		{
			'/', 'o', 'O', '\\',
			'|', '\'', '\'', '|'
		}
	);
}