#include "GameScreenManager.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen) {

	mRenderer      = renderer;
	mCurrentScreen = NULL;

	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager() {

	mRenderer = NULL;

	delete mCurrentScreen;
	mCurrentScreen = NULL;
}

void GameScreenManager::Render() {

	mCurrentScreen->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e) {

	mCurrentScreen->Update(deltaTime, e);

	if (mCurrentScreen->GetScreenToChange() != NULL) {
		ChangeScreen(mCurrentScreen->GetScreenToChange());
	}

}

void GameScreenManager::ChangeScreen(SCREENS screen) {
	//Clear old screen
	if (mCurrentScreen != NULL) {
		delete mCurrentScreen;
	}

	GameScreenLevel1* level1;
	GameScreenMenu* menu;

	switch (screen)
	{
	case SCREEN_INTRO:
		break;
	case SCREEN_MENU:
		menu = new GameScreenMenu(mRenderer);
		mCurrentScreen = (GameScreen*)menu;
		menu = NULL;
		break;
	case SCREEN_LVL1:

		level1         = new GameScreenLevel1(mRenderer);
		mCurrentScreen = (GameScreen*)level1;
		level1	       = NULL;
		break;
	case SCREEN_LVL2:
		break;
	case SCREEN_GAMEOVER:
		break;
	case SCREEN_HIGHSCORE:
		break;
	default:
		break;
	}
}
