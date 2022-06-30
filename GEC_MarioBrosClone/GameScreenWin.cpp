#include "GameScreenWin.h"

GameScreenWin::GameScreenWin(SDL_Renderer* renderer) : GameScreen(renderer) {

	SetupLevel();
}

GameScreenWin::~GameScreenWin() {
	delete titleText;
	titleText = NULL;
}

void GameScreenWin::Render() {
	titleText->Render(mRenderer,"You Win",SCREEN_WIDTH / 2 - 72,SCREEN_HEIGHT / 4);

	option1->Render(mRenderer,"Press 1 - Retry",SCREEN_WIDTH / 2 - 57,225);
	option2->Render(mRenderer,"Press 2 - Return to Menu",SCREEN_WIDTH / 2 - 57,275);
}

void GameScreenWin::Update(float deltaTime,SDL_Event e) {
	switch (e.type) {
		case SDL_KEYUP:
			switch (e.key.keysym.sym) {
				case SDLK_1:
					SetNextGameState(GAME_1);
					break;

				case SDLK_2:
					SetNextGameState(MENU_STATE);
					break;
			}
	}
}

bool GameScreenWin::SetupLevel() {
	titleText = new TextRenderer(30);

	option1 = new TextRenderer(15);
	option2 = new TextRenderer(15);

	copyright = new TextRenderer(8);

	SetGameState(WIN_STATE);
	SetNextGameState(WIN_STATE);

	AudioManager::Instance()->StopMusic();
	AudioManager::Instance()->LoadSFX("SFX/Win.wav");
	return true;
}
