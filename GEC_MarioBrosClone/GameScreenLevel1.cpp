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
}

void GameScreenLevel1::Render() {
	//Draw Background
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);

	marioCharacter->Render();
	luigiCharacter->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e) {
	marioCharacter->Update(deltaTime, e);
	luigiCharacter->Update(deltaTime, e);
}

bool GameScreenLevel1::SetupLevel() {
	mBackgroundTexture = new Texture2D(mRenderer);

	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png")) {
		cout << "Failed to load background texture";
		return false;
	}

	marioCharacter = new CharacterMario(mRenderer, "Images/Mario.png", Vector2D(64, 330));
	luigiCharacter = new CharacterLuigi(mRenderer, "Images/Luigi.png", Vector2D(128, 330));

	return true;
}

