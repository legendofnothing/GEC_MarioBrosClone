#include "GameScreen.h"

GameScreen::GameScreen(SDL_Renderer* renderer) {
	mRenderer = renderer;
}

GameScreen::~GameScreen() {
	mRenderer = NULL;
}

void GameScreen::Render() {

}

void GameScreen::Update(float deltaTime, SDL_Event e) {

}

void GameScreen::SetGameState(GAMESTATE gamestate) {
	mCurrentGameState = gamestate;
}

void GameScreen::SetNextGameState(GAMESTATE gamestate) {
	mNextGameState = gamestate;
}

GAMESTATE GameScreen::GetGameState() {
	return mCurrentGameState;
}

GAMESTATE GameScreen::GetNextGameState() {
	return mNextGameState;
}