#pragma once
#include "Character.h"

class Texture2D;
class Coin : public Character {
public:
	Coin(SDL_Renderer* renderer,std::string imagePath,Vector2D startPosition,LevelMap* map);
	~Coin();
	void Update(float deltaTime,SDL_Event e);
	void Render();

private:
	int   mCurrentFrame;

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	float mMovementSpeed;
	float mFrameDelay;
};
