#pragma once

#include <iostream>
#include <string>

#include <SDL.h>

#include "Commons.h"
#include "Texture2D.h"	

using namespace std;

class Texture2D;

class Character
{
public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();

protected:
	virtual void Move(float deltaTime);
	virtual void SlowDown(float deltaTime);

	SDL_Renderer* mRenderer;
	Vector2D      mPosition;
	Texture2D*    mTexture;
	FACING		  mFacingDirection;

	bool		  mMoving;

	float		  mVelocity;
	float		  mSlowdownVelocity;
};

