#include "GameScreenLevel2.h"

GameScreenLevel2::GameScreenLevel2(SDL_Renderer* renderer) : GameScreen(renderer) {

	SetupLevel();

}

GameScreenLevel2::~GameScreenLevel2() {

	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

	delete marioCharacter;
	marioCharacter = NULL;

	delete mPowBlock;
	mPowBlock = NULL;

	mEnemies.clear();
	mCoins.clear();
}

void GameScreenLevel2::Render() {
	//Draw Background
	mBackgroundTexture->Render(Vector2D(0,mBackgroundYPos),SDL_FLIP_NONE);

	marioCharacter->Render();
	luigiCharacter->Render();

	mPowBlock->Render();

	for (unsigned int i = 0; i < mEnemies.size(); i++) {
		mEnemies[i]->Render();
	}

	for (unsigned int i = 0; i < mCoins.size(); i++) { 
		mCoins[i]->Render();
	}

	scoreDisplay->Render(mRenderer,"Level 2",240,20);

	scoreDisplay->Render(mRenderer,"Score",240,40);
	scoreDisplay->Render(mRenderer,ScoreSystem::Instance()->GetScore(),275,40);

	scoreDisplay->Render(mRenderer,"Mario Lives: ",80,40);
	scoreDisplay->Render(mRenderer,LivesSystem::Instance()->GetMarioHP(),150,40);

	scoreDisplay->Render(mRenderer,"Luigi Lives: ", 350,40);
	scoreDisplay->Render(mRenderer,LivesSystem::Instance()->GetLuigiHP(), 415,40);
}

void GameScreenLevel2::Update(float deltaTime,SDL_Event e) {
	marioCharacter->Update(deltaTime,e);
	luigiCharacter->Update(deltaTime,e);

	UpdatePowBlock();

	UpdateScreenShake(deltaTime);

	UpdateEnemies(deltaTime,e);

	if (mEnemies.empty()) {

		CreateKoopa(Vector2D(150,32),FACING_RIGHT);
		CreateKoopa(Vector2D(325,32),FACING_LEFT);
	}

	if (!mCoins.empty()) {

		int enemyIndexToDelete = -1;
		
		for (int i = 0; i < mCoins.size(); i++){

			mCoins[i]->Update(deltaTime,e);

			if (Collision::Instance()->Box(mCoins[i]->GetCollisionBox(),luigiCharacter->GetCollisionBox())) {
				enemyIndexToDelete = i;

				AudioManager::Instance()->LoadSFX("SFX/KoopaConsume.wav");

				ScoreSystem::Instance()->AddScore(15);
			}

			if (Collision::Instance()->Box(mCoins[i]->GetCollisionBox(),marioCharacter->GetCollisionBox())) {
				enemyIndexToDelete = i;

				AudioManager::Instance()->LoadSFX("SFX/KoopaConsume.wav");

				ScoreSystem::Instance()->AddScore(15);
			}
		}

		if (enemyIndexToDelete != -1) {
			mCoins.erase(mCoins.begin() + enemyIndexToDelete);
		}
	}

	if (marioCharacter->HasWon() && luigiCharacter->HasWon()) {
		AudioManager::Instance()->StopMusic();

		SetNextGameState(WIN_STATE);
	}

	if (LivesSystem::Instance()->GetMarioHP() <= 0 || LivesSystem::Instance()->GetLuigiHP() <= 0) {
		SetNextGameState(LOSE_STATE);
	}
}

void GameScreenLevel2::UpdatePowBlock() {
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

	if (Collision::Instance()->Box(mPowBlock->GetCollisionBox(),luigiCharacter->GetCollisionBox())) {
		if (mPowBlock != NULL) {
			if (luigiCharacter->IsJumping()) {
				mPowBlock->TakeAHit();
				luigiCharacter->CancelJump();

				DoScreenShake();

				ScoreSystem::Instance()->AddScore(5);
			}
		}
	}
}

void GameScreenLevel2::UpdateScreenShake(float deltaTime) {
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

void GameScreenLevel2::UpdateEnemies(float deltaTime,SDL_Event e) {
	if (!mEnemies.empty()) {

		int enemyIndexToDelete = -1;

		for (unsigned int i = 0; i < mEnemies.size(); i++) {

			if (mEnemies[i]->GetPosition().y > 360.0f) {

				if (mEnemies[i]->GetPosition().x < (float)(-mEnemies[i]->GetCollisionBox().width * 0.5f) || mEnemies[i]->GetPosition().x < SCREEN_WIDTH - (float)(-mEnemies[i]->GetCollisionBox().width * 0.55f)) {
					enemyIndexToDelete = i;
				}
			}

			mEnemies[i]->Update(deltaTime,e);

			if (Collision::Instance()->Box(mEnemies[i]->GetCollisionBox(),marioCharacter->GetCollisionBox())) {
				if (mEnemies[i]->GetInjured()) {
					enemyIndexToDelete = i;

					AudioManager::Instance()->LoadSFX("SFX/Coin.wav");

					ScoreSystem::Instance()->AddScore(15);
				}

				else if (marioCharacter->IsJumping()) {
					mEnemies[i]->TakeDamage();
				}

				else {
					DoScreenShake();
					LivesSystem::Instance()->ReduceHP(true, false);
					marioCharacter->SetPosition(Vector2D(64,330));

					ScoreSystem::Instance()->AddScore(-15);
				}
			}

			if (Collision::Instance()->Box(mEnemies[i]->GetCollisionBox(),luigiCharacter->GetCollisionBox())) {
				if (mEnemies[i]->GetInjured()) {
					enemyIndexToDelete = i;

					AudioManager::Instance()->LoadSFX("SFX/Coin.wav");

					ScoreSystem::Instance()->AddScore(15);
				}

				else if (luigiCharacter->IsJumping()) {
					mEnemies[i]->TakeDamage();
				}

				else {
					DoScreenShake();
					LivesSystem::Instance()->ReduceHP(false,true);
					luigiCharacter->SetPosition(Vector2D(396,330));

					ScoreSystem::Instance()->AddScore(-15);
				}
			}
		}

		if (enemyIndexToDelete != -1) {
			mEnemies.erase(mEnemies.begin() + enemyIndexToDelete);
		}
	}
}

bool GameScreenLevel2::SetupLevel() {

	SetGameState(GAME_2);
	SetNextGameState(GAME_2);

	mBackgroundTexture = new Texture2D(mRenderer);

	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png")) {
		cout << "Failed to load background texture";
		return false;
	}

	SetLevelMap();

	mPowBlock = new PowBlock(mRenderer,mLevelMap);

	marioCharacter = new CharacterMario(mRenderer,"Images/Mario.png",Vector2D(64,330),mLevelMap);
	luigiCharacter = new CharacterLuigi(mRenderer,"Images/Luigi.png",Vector2D(396,330),mLevelMap);

	CreateCoin(Vector2D(160,128));
	CreateCoin(Vector2D(224,128));
	CreateCoin(Vector2D(288,128));

	mScreenShake = false;
	mBackgroundYPos = 0.0f;

	scoreDisplay = new TextRenderer(12);

	ScoreSystem::Instance()->ResetScore();

	AudioManager::Instance()->LoadMusic("Music/Mario2.ogg");

	LivesSystem::Instance()->ResetHP();

	return true;
}

void GameScreenLevel2::SetLevelMap() {
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
	if (mLevelMap != NULL) {
		delete mLevelMap;

	}

	//Set up the new one
	mLevelMap = new LevelMap(map);
}

void GameScreenLevel2::DoScreenShake() {
	mScreenShake = true;
	mScreenShakeTime = 0.4f;
	mWobble = 0.0f;

	for (unsigned int i = 0; i < mEnemies.size(); i++) {
		mEnemies[i]->TakeDamage();
	}
}

void GameScreenLevel2::CreateKoopa(Vector2D position,FACING direction) {

	mKoopa = new EnemyKoopa(mRenderer,"Images/Koopa.png",position,mLevelMap,direction);

	mEnemies.push_back(mKoopa);
}

void GameScreenLevel2::CreateCoin(Vector2D position) {
	mCoin = new Coin(mRenderer,"Images/Coin.png",position,mLevelMap);
	mCoins.push_back(mCoin);
}
