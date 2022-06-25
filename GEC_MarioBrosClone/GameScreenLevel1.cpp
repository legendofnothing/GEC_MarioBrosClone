#include "GameScreenLevel1.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer) {
	
	SetupLevel();
}

GameScreenLevel1::~GameScreenLevel1() {

	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
}

void GameScreenLevel1::Render() {
	//Draw Background
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e) {

}

bool GameScreenLevel1::SetupLevel() {
	mBackgroundTexture = new Texture2D(mRenderer);

	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png")) {
		cout << "Failed to load background texture";
		return false;
	}

	return true;
}

