#pragma once

#include <SDL.h>

#include "Commons.h"

#include "GameScreenLevel1.h"
#include "GameScreenMenu.h"
#include "GameScreenOver.h"
#include "GameScreenLevel2.h"
#include "GameScreenWin.h"

using namespace std;

class GameScreen;

class GameScreenManager
{
public:
	GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
	~GameScreenManager();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void ChangeScreen(SCREENS screen);

	GAMESTATE GetCurrentGameState();
	GAMESTATE GetNextGameState();

private:
	SDL_Renderer* mRenderer;
	GameScreen* mCurrentScreen;
};

