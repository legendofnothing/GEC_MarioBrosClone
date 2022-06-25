#pragma once

#include "Character.h"

using namespace std;

class Character;

class Collision
{
public:
	~Collision();
	static Collision* Instance();

	bool Circle(Character* character1, Character* character2);
	bool Box(Rect2D rect1, Rect2D rect2);

private:
	Collision();

	static Collision* mInstance;
};

