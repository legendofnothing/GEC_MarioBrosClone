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

	float GetCollisionRadius();
	Rect2D GetCollisionBox();

protected:
	virtual void Move(float deltaTime, float velocity);

	SDL_Renderer* mRenderer;
	Vector2D      mPosition;
	Texture2D*    mTexture;
	FACING		  mFacingDirection;

	bool		  mMovingLeft;
	bool		  mMovingRight;

	float		  mCollisionRadius;
};

