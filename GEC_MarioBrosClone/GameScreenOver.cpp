#include "GameScreenOver.h"

GameScreenOver::GameScreenOver(SDL_Renderer* renderer) : GameScreen(renderer) {

	SetupLevel();
}

GameScreenOver::~GameScreenOver() {
	delete titleText;
	titleText = NULL;
}

void GameScreenOver::Render() {
	titleText->Render(mRenderer,"You Failed",SCREEN_WIDTH / 2 - 72,SCREEN_HEIGHT / 4);

	option1->Render(mRenderer,"Press 1 - Retry",SCREEN_WIDTH / 2 - 57,225);
	option2->Render(mRenderer,"Press 2 - Return to Menu",SCREEN_WIDTH / 2 - 57,275);

	copyright->Render(mRenderer,"haha u failed lmao",SCREEN_WIDTH / 2 - 63,400);
}

void GameScreenOver::Update(float deltaTime,SDL_Event e) {
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

bool GameScreenOver::SetupLevel() {
	titleText = new TextRenderer(30);

	option1 = new TextRenderer(15);
	option2 = new TextRenderer(15);

	copyright = new TextRenderer(8);

	SetGameState(LOSE_STATE);
	SetNextGameState(LOSE_STATE);

	AudioManager::Instance()->StopMusic();
	AudioManager::Instance()->LoadSFX("SFX/GameOver.wav");
	return true;
}