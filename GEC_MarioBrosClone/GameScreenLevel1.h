#pragma once

#include <iostream>

#include <SDL.h>

#include "Commons.h"
#include "GameScreen.h"
#include "Texture2D.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "Collision.h"
#include "LevelMap.h"
#include "PowBlock.h"

using namespace std;

class Texture2D;
class CharacterMario;
class CharacterLuigi;
class Collision;
class LevelMap;
class PowBlock;

class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void DoScreenShake();

private:
	Texture2D* mBackgroundTexture;

	bool SetupLevel();

	CharacterMario* marioCharacter;
	CharacterLuigi* luigiCharacter;

	void SetLevelMap();

	LevelMap* mLevelMap;

	PowBlock* mPowBlock;

	bool  mScreenShake;
	float mScreenShakeTime;
	float mWobble;
	float mBackgroundYPos;
};

