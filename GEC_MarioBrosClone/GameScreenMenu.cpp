#include "GameScreenMenu.h"

TextRenderer* loadLevel1;
TextRenderer* loadLevel2;

GameScreenMenu::GameScreenMenu(SDL_Renderer* renderer) : GameScreen(renderer) {

	SetupLevel();
}

GameScreenMenu::~GameScreenMenu() {
	delete titleText;
	titleText = NULL;

	delete copyrightText;
	copyrightText = NULL;

	delete loadLevel1;
	loadLevel1 = NULL;

	delete loadLevel2;
	loadLevel2 = NULL;
}

void GameScreenMenu::Render() {
	titleText->Render(mRenderer,"Inferior Mario Bros", 100, 100);
	copyrightText->Render(mRenderer,"Copyrighted by a pineapple pizza",159 ,400);

	loadLevel1->Render(mRenderer,"Press 1 to Enter Level 1",146,225);
	loadLevel2->Render(mRenderer,"Press 2 to Enter Level 2",146,275);
}

void GameScreenMenu::Update(float deltaTime, SDL_Event e) {
	switch (e.type) {
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym) {
				case SDLK_1:
					SetNextGameState(GAME_LVL1);
					cout << "hit";
					break;
				case SDLK_2:
					SetNextGameState(GAME_LVL2);
					break;
				default:
					break;
			}
	}
}

bool GameScreenMenu::SetupLevel() {
	SetGameState(MENU_STATE);
	SetNextGameState(GAME_LVL1);

	titleText = new TextRenderer(16);
	copyrightText = new TextRenderer(6);

	loadLevel1 = new TextRenderer(9);
	loadLevel2 = new TextRenderer(9);

	return true;
}
