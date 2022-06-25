#pragma once

#include "Character.h"

class CharacterMario : public Character
{
public:
	CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition);
	~CharacterMario();

	void Update(float deltaTime, SDL_Event e);

private:
	float mVelocity;
};

