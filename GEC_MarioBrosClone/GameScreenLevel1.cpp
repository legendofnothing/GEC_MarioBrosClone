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
}

void GameScreenLevel1::Render() {
	//Draw Background
	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);

	marioCharacter->Render();
	luigiCharacter->Render();
	mPowBlock->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e) {
	marioCharacter->Update(deltaTime, e);
	luigiCharacter->Update(deltaTime, e);

	//Collision Check with PowBlock and Mario Character
	if (Collision::Instance()->Box(mPowBlock->GetCollisionBox(), marioCharacter->GetCollisionBox())) {
		if (mPowBlock != NULL) {
			if (marioCharacter->IsJumping()) {
				mPowBlock->TakeAHit();
				marioCharacter->CancelJump();

				DoScreenShake();
			}	
		}
	}

	//Collision Check with PowBlock and Luigi Character
	if (Collision::Instance()->Box(mPowBlock->GetCollisionBox(), luigiCharacter->GetCollisionBox())) {
		if (mPowBlock != NULL) {
			if (luigiCharacter->IsJumping()) {
				mPowBlock->TakeAHit();
				luigiCharacter->CancelJump();

				DoScreenShake();
			}
		}
	}

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

bool GameScreenLevel1::SetupLevel() {

	mBackgroundTexture = new Texture2D(mRenderer);

	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png")) {
		cout << "Failed to load background texture";
		return false;
	}

	SetLevelMap();

	marioCharacter = new CharacterMario(mRenderer, "Images/MarioSprite.png", Vector2D(64, 330), mLevelMap);
	luigiCharacter = new CharacterLuigi(mRenderer, "Images/LuigiSprite.png", Vector2D(128, 330), mLevelMap);

	mPowBlock = new PowBlock(mRenderer, mLevelMap);

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
}



