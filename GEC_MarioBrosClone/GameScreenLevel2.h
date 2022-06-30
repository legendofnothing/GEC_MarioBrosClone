#pragma once
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
#include "TextRenderer.h"
#include "ScoreSystem.h"
#include "LivesSystem.h"
#include "Coin.h"

using namespace std;

class GameScreenLevel2 : GameScreen {
	public:
		GameScreenLevel2(SDL_Renderer* renderer);
		~GameScreenLevel2();

		virtual void Render();
		virtual void Update(float deltaTime,SDL_Event e);

		void DoScreenShake();

		void UpdatePowBlock();
		void UpdateScreenShake(float deltaTime);
		void UpdateEnemies(float deltaTime,SDL_Event e);

		void CreateKoopa(Vector2D position,FACING direction);
		void CreateCoin(Vector2D position);

	private:
		Texture2D* mBackgroundTexture;

		bool SetupLevel();

		CharacterMario* marioCharacter;
		CharacterLuigi* luigiCharacter;

		void SetLevelMap();

		LevelMap* mLevelMap;

		PowBlock* mPowBlock;

		EnemyKoopa* mKoopa;
		Coin* mCoin;

		TextRenderer* scoreDisplay;

		bool  mScreenShake;
		float mScreenShakeTime;
		float mWobble;
		float mBackgroundYPos;

		vector<EnemyKoopa*> mEnemies;
		vector<Coin*> mCoins;
	};

