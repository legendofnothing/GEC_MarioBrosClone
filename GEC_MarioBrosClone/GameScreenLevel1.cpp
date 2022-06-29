#include "GameScreenLevel1.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer) {
	
	SetupLevel();

}

GameScreenLevel1::~GameScreenLevel1() {

	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

	delete marioCharacter;
	marioCharacter = NULL;

	delete luigiCharacter;
	luigiCharacter = NULL;

	delete mPowBlock; 
	mPowBlock = NULL;

	mEnemies.clear();
}

void GameScreenLevel1::Render() {
	//Draw Background
	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);

	marioCharacter->Render();
	luigiCharacter->Render();

	mPowBlock->Render();

	for (unsigned int i = 0; i < mEnemies.size(); i++) {
		mEnemies[i]->Render();
	}
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e) {
	marioCharacter->Update(deltaTime, e);
	luigiCharacter->Update(deltaTime, e);

	UpdatePowBlock();

	UpdateScreenShake(deltaTime);

	UpdateEnemies(deltaTime,e);
}

void GameScreenLevel1::UpdatePowBlock() {
	//Collision Check with PowBlock and Mario Character
	if (Collision::Instance()->Box(mPowBlock->GetCollisionBox(),marioCharacter->GetCollisionBox())) {
		if (mPowBlock != NULL) {
			if (marioCharacter->IsJumping()) {
				mPowBlock->TakeAHit();
				marioCharacter->CancelJump();

				DoScreenShake();
			}
		}
	}

	//Collision Check with PowBlock and Luigi Character
	if (Collision::Instance()->Box(mPowBlock->GetCollisionBox(),luigiCharacter->GetCollisionBox())) {
		if (mPowBlock != NULL) {
			if (luigiCharacter->IsJumping()) {
				mPowBlock->TakeAHit();
				luigiCharacter->CancelJump();

				DoScreenShake();
			}
		}
	}
}

void GameScreenLevel1::UpdateScreenShake(float deltaTime) {
	//Do Screen Shake if true
	if (mScreenShake) {
		mScreenShakeTime -= deltaTime;
		mWobble++;

		mBackgroundYPos = sin(mWobble);
		mBackgroundYPos *= 3.0f;

		if (mScreenShakeTime <= 0) {
			mScreenShake = false;
			mBackgroundYPos = 0.0f;
		}
	}
}

void GameScreenLevel1::UpdateEnemies(float deltaTime,SDL_Event e) {
	if (!mEnemies.empty()) {

		int enemyIndexToDelete = -1;

		for (unsigned int i = 0; i < mEnemies.size(); i++) {
			
			if (mEnemies[i]->GetPosition().y > 360.0f) {

				if (mEnemies[i]->GetPosition().x < (float)(-mEnemies[i]->GetCollisionBox().width * 0.5f) || mEnemies[i]->GetPosition().x < SCREEN_WIDTH - (float)(-mEnemies[i]->GetCollisionBox().width * 0.55f)) {
					enemyIndexToDelete = i;
				}
			}

			mEnemies[i]->Update(deltaTime,e);

			if (Collision::Instance()->Box(mEnemies[i]->GetCollisionBox(), marioCharacter->GetCollisionBox())) {
				if (mEnemies[i]->GetInjured()) {
					enemyIndexToDelete = i;
				}

				else cout << "Die 4 now";
			}

			if (Collision::Instance()->Box(mEnemies[i]->GetCollisionBox(), luigiCharacter->GetCollisionBox())) {
				if (mEnemies[i]->GetInjured()) {
					enemyIndexToDelete = i;
				}

				else cout << "Die 4 now";
			}
		}

		if (enemyIndexToDelete != -1) {
			mEnemies.erase(mEnemies.begin() + enemyIndexToDelete);
		}
	}
}

bool GameScreenLevel1::SetupLevel() {

	mBackgroundTexture = new Texture2D(mRenderer);

	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png")) {
		cout << "Failed to load background texture";
		return false;
	}

	SetLevelMap();

	marioCharacter = new CharacterMario(mRenderer, "Images/Mario.png", Vector2D(64, 330), mLevelMap);
	luigiCharacter = new CharacterLuigi(mRenderer, "Images/Luigi.png", Vector2D(128, 330), mLevelMap);

	mPowBlock = new PowBlock(mRenderer, mLevelMap);

	CreateKoopa(Vector2D(150,32), FACING_RIGHT);
	CreateKoopa(Vector2D(325,32), FACING_LEFT);

	mScreenShake = false;
	mBackgroundYPos = 0.0f;

	AudioManager::Instance()->LoadMusic("Music/Mario.mp3");

	return true;
}

void GameScreenLevel1::SetLevelMap() {
	//0 blank, 1 wall
	int map[MAP_HEIGHT][MAP_WIDTH] = {
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		{0,1,1,1,1,1,0,0,0,0,1,1,1,1,1,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	//Clear up any old map
	if (mLevelMap != NULL)
	{
		delete mLevelMap;

	}

	//Set up the new one
	mLevelMap = new LevelMap(map);
}

void GameScreenLevel1::DoScreenShake() {
	mScreenShake = true;
	mScreenShakeTime = 0.4f;
	mWobble = 0.0f;

	for (unsigned int i = 0; i < mEnemies.size(); i++) {
		mEnemies[i]->TakeDamage();
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction) {

	mKoopa = new EnemyKoopa(mRenderer,"Images/Koopa.png",position,mLevelMap,direction);

	mEnemies.push_back(mKoopa);
}




