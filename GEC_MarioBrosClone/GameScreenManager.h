#pragma once

#include <SDL.h>

#include "Commons.h"

#include "GameScreenLevel1.h"

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

private:
	SDL_Renderer* mRenderer;
	GameScreen* mCurrentScreen;
};

