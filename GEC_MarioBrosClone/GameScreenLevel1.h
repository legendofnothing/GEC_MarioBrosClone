#pragma once

#include <iostream>
#include <vector>

#include <SDL.h>

#include "Commons.h"
#include "GameScreen.h"
#include "Texture2D.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "Collision.h"
#include "LevelMap.h"
#include "PowBlock.h"
#include "AudioManager.h"
#include "EnemyKoopa.h"

using namespace std;

class Texture2D;
class CharacterMario;
class CharacterLuigi;
class Collision;
class LevelMap;
class PowBlock;
class AudioManager;
class EnemyKoopa;

class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void DoScreenShake();

	void UpdatePowBlock();
	void UpdateScreenShake(float deltaTime);
	void UpdateEnemies(float deltaTime,SDL_Event e);

	void CreateKoopa(Vector2D position,FACING direction);

private:
	Texture2D* mBackgroundTexture;

	bool SetupLevel();

	CharacterMario* marioCharacter;
	CharacterLuigi* luigiCharacter;

	void SetLevelMap();

	LevelMap* mLevelMap;

	PowBlock* mPowBlock;

	EnemyKoopa* mKoopa;

	bool  mScreenShake;
	float mScreenShakeTime;
	float mWobble;
	float mBackgroundYPos;

	vector<EnemyKoopa*> mEnemies;
};

