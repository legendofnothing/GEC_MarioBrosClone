#pragma once

#include <iostream>
#include <string>

#include <SDL.h>

#include "Commons.h"
#include "Texture2D.h"	
#include "LevelMap.h"
#include "AudioManager.h"

using namespace std;

class Texture2D;
class LevelMap;
class AudioManager;

class Character
{
public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();

	float GetCollisionRadius();
	Rect2D GetCollisionBox();

	bool IsJumping();
	void CancelJump();

	void AddGravity(float deltaTime);
	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);
	void Jump();

private:
	int footPosition;
	int centralXPosition;
	int topPosition;

	LevelMap* mCurrentMap;

	bool  mJumping;
	float mJumpForce;

protected: 
	SDL_Renderer* mRenderer;
	Vector2D      mPosition;
	Texture2D*    mTexture;
	FACING		  mFacingDirection;

	bool		  mMovingLeft;
	bool		  mMovingRight;
	bool		  mCanJump;

	float		  mCollisionRadius;
	float		  mVelocity;
};

