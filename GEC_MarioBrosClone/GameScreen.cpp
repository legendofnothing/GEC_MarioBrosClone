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

void GameScreen::SetGameState(GAMESTATE state) {
	mCurrentGameState = state;
}

void GameScreen::SetNextGameState(GAMESTATE state) {
	mNextGameState = state;
}
