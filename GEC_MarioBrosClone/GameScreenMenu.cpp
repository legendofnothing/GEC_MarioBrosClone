#include "GameScreenMenu.h"

GameScreenMenu::GameScreenMenu(SDL_Renderer* renderer) : GameScreen(renderer) {

	SetupLevel();
}

GameScreenMenu::~GameScreenMenu() {
	delete titleText;
	titleText = NULL;
}

void GameScreenMenu::Render() {
	titleText->Render(mRenderer,"Bario Mros",SCREEN_WIDTH / 2 - 72 ,SCREEN_HEIGHT / 4);

	option1->Render(mRenderer,"Press 1 - Level 1",SCREEN_WIDTH / 2 - 57, 225);
	option2->Render(mRenderer,"Press 2 - Level 2",SCREEN_WIDTH / 2 - 57, 275);

	copyright->Render(mRenderer,"Copyrighted by Pineapple Pizza lovers",SCREEN_WIDTH / 2 - 63, 400);
}

void GameScreenMenu::Update(float deltaTime,SDL_Event e) {
	switch (e.type) {
		case SDL_KEYUP:
			switch (e.key.keysym.sym) 
			{
				case SDLK_ESCAPE:
					SetNextGameState(EXIT_STATE);
					break;

				case SDLK_1:
					SetNextGameState(GAME_1);
					break;

				case SDLK_2:
					SetNextGameState(GAME_2);
					break;
			}
	}
}

bool GameScreenMenu::SetupLevel() {
	titleText = new TextRenderer(30);

	option1 = new TextRenderer(15);
	option2 = new TextRenderer(15);

	copyright = new TextRenderer(8);
	
	SetGameState(MENU_STATE);
	SetNextGameState(MENU_STATE);
	return true;
}