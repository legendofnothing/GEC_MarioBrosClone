#pragma once

#include <SDL.h>
#include "Commons.h"

class GameScreen
{
public:
	
	GameScreen(SDL_Renderer* renderer);
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	GAMESTATE GetGameState() { return mCurrentGameState; };
	GAMESTATE GetNextGameState() { return mNextGameState; };

private:

protected:

	SDL_Renderer* mRenderer;

	GAMESTATE mCurrentGameState;
	GAMESTATE mNextGameState;

	void SetGameState(GAMESTATE state);
	void SetNextGameState(GAMESTATE state);
};

