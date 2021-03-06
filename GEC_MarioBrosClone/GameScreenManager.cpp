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
}

void GameScreenManager::ChangeScreen(SCREENS screen) {
	//Clear old screen
	if (mCurrentScreen != NULL) {
		delete mCurrentScreen;
	}

	GameScreenLevel1* level1;
	GameScreenLevel2* level2;
	GameScreenMenu* menu;
	GameScreenOver* gameover;
	GameScreenWin* win;

	switch (screen)
	{
	case SCREEN_MENU:

		menu           = new GameScreenMenu(mRenderer);
		mCurrentScreen = (GameScreen*)menu;
		menu           = NULL;
		break;

	case SCREEN_LVL1:

		level1         = new GameScreenLevel1(mRenderer);
		mCurrentScreen = (GameScreen*)level1;
		level1	       = NULL;
		break;

	case SCREEN_LVL2:

		level2         = new GameScreenLevel2(mRenderer);
		mCurrentScreen = (GameScreen*)level2;
		level2         = NULL;
		break;

	case SCREEN_GAMEOVER:

		gameover       = new GameScreenOver(mRenderer);
		mCurrentScreen = (GameScreen*)gameover;
		gameover       = NULL;
		break;

	case SCREEN_WIN:

		win            = new GameScreenWin(mRenderer);
		mCurrentScreen = (GameScreen*)win;
		win            = NULL;
		break;
	default:
		break;
	}
}

GAMESTATE GameScreenManager::GetCurrentGameState() {
	return mCurrentScreen->GetGameState();
}

GAMESTATE GameScreenManager::GetNextGameState() {
	return mCurrentScreen->GetNextGameState();
}
