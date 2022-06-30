#include "GameScreenLevel1.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer) {
	
	SetupLevel();

}

GameScreenLevel1::~GameScreenLevel1() {

	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

	delete marioCharacter;
	marioCharacter = NULL;

	delete mPowBlock; 
	mPowBlock = NULL;

	mEnemies.clear();
}

void GameScreenLevel1::Render() {
	//Draw Background
	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);

	marioCharacter->Render();

	mPowBlock->Render();

	for (unsigned int i = 0; i < mEnemies.size(); i++) {
		mEnemies[i]->Render();
	}

	scoreDisplay->Render(mRenderer,"Level 1",240,20);

	scoreDisplay->Render(mRenderer,"Score",240,40);
	scoreDisplay->Render(mRenderer,ScoreSystem::Instance()->GetScore() ,275,40);
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e) {
	marioCharacter->Update(deltaTime, e);

	UpdatePowBlock();

	UpdateScreenShake(deltaTime);

	UpdateEnemies(deltaTime,e);

	if (mEnemies.empty()) {

		CreateKoopa(Vector2D(150,32),FACING_RIGHT);
		CreateKoopa(Vector2D(325,32),FACING_LEFT);
	}

	if (marioCharacter->HasWon()) {
		SetNextGameState(GAME_2);
	}
}

void GameScreenLevel1::UpdatePowBlock() {
	//Collision Check with PowBlock and Mario Character
	if (Collision::Instance()->Box(mPowBlock->GetCollisionBox(),marioCharacter->GetCollisionBox())) {
		if (mPowBlock != NULL) {
			if (marioCharacter->IsJumping()) {
				mPowBlock->TakeAHit();
				marioCharacter->CancelJump();

				DoScreenShake();

				ScoreSystem::Instance()->AddScore(5);
			}
		}
	}
}

void GameScreenLevel1::UpdateScreenShake(float deltaTime) {
	//Do Screen Shake if true
	if (mScreenShake) {
		AudioManager::Instance()->LoadSFX("SFX/HitPowBlock.wav");

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

					AudioManager::Instance()->LoadSFX("SFX/KoopaConsume.wav");

					ScoreSystem::Instance()->AddScore(15);
				}

				else if (marioCharacter->IsJumping()) {
					mEnemies[i]->TakeDamage();
				}

				else SetNextGameState(LOSE_STATE);
			}
		}

		if (enemyIndexToDelete != -1) {
			mEnemies.erase(mEnemies.begin() + enemyIndexToDelete);
		}
	}
}

bool GameScreenLevel1::SetupLevel() {

	SetGameState(GAME_1);
	SetNextGameState(GAME_1);

	mBackgroundTexture = new Texture2D(mRenderer);

	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png")) {
		cout << "Failed to load background texture";
		return false;
	}

	SetLevelMap();

	mPowBlock = new PowBlock(mRenderer, mLevelMap);

	marioCharacter = new CharacterMario(mRenderer,"Images/Mario.png",Vector2D(64,330),mLevelMap);

	mScreenShake = false;
	mBackgroundYPos = 0.0f;

	scoreDisplay = new TextRenderer(12);

	ScoreSystem::Instance()->ResetScore();

	AudioManager::Instance()->LoadMusic("Music/Mario.ogg");

	return true;
}

void GameScreenLevel1::SetLevelMap() {
	//0 blank, 1 wall, 2 win condition
	int map[MAP_HEIGHT][MAP_WIDTH] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
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




