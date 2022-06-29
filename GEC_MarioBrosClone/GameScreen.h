#pragma once

#include <SDL.h>

#include "Commons.h"

class GameScreen
{
public:
	
	GameScreen(SDL_Renderer* renderer);
	~GameScreen();

	SCREENS GetScreenToChange() { return mScreenToChange; };

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

private:

protected:

	SDL_Renderer* mRenderer;

	SCREENS mScreenToChange;
};

