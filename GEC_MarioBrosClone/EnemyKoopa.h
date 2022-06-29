#pragma once
#include "Character.h"

class EnemyKoopa : public Character {
public:
	EnemyKoopa(SDL_Renderer* renderer, string imagePath, Vector2D startPosition,LevelMap* map,FACING startFacing);
	~EnemyKoopa();

	void Update(float deltaTime,SDL_Event e);
	void Render();

	void TakeDamage();
	void Jump();

	bool GetInjured();
	void SetInjured(bool condition);

private:
	void FlipWayUp();

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	bool  mInjured;
	float mInjuredTime;
};

