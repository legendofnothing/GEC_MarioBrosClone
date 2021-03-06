#pragma once

#include <string>
#include <iostream>

#include <SDL.h>

#include "Commons.h"
#include "Texture2D.h"
#include "LevelMap.h"
#include "AudioManager.h";

using namespace std;
using std::string;

class Texture2D;
class AudioManager;

class PowBlock
{
public:
	PowBlock(SDL_Renderer* renderer, LevelMap* map);
	~PowBlock();
	void   Render();
	Rect2D GetCollisionBox();
	void   TakeAHit();
	bool   IsAvailable() { return mNumberOfHitsLeft > 0; };

	void   DoScreenShake();

private:
	SDL_Renderer* mRenderer;
	Vector2D      mPosition;
	Texture2D*    mTexture;
	LevelMap*     mLevelMap;
	AudioManager* mAudioManager;

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	int   mNumberOfHitsLeft;
};

