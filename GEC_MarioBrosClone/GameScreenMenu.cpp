#include "GameScreenMenu.h"

GameScreenMenu::GameScreenMenu(SDL_Renderer* renderer) : GameScreen(renderer) {

	SetupLevel();
}

GameScreenMenu::~GameScreenMenu() {
	delete titleText;
	titleText = NULL;
}

void GameScreenMenu::Render() {
	titleText->Render(mRenderer,"MARIO GAME!",SCREEN_WIDTH / 4 - 50,SCREEN_HEIGHT / 4);
}

void GameScreenMenu::Update(float deltaTime,SDL_Event e) {
}

bool GameScreenMenu::SetupLevel() {
	titleText = new TextRenderer(50);
	return true;
}