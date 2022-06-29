#pragma once

#include <iostream>
#include <vector>

#include <SDL.h>

#include "Commons.h"
#include "GameScreen.h"
#include "Texture2D.h"
#include "TextRenderer.h"
#include "GameScreenManager.h"

class Texture2D;
class TextRenderer;
class GameScreenManager;

class GameScreenMenu : public GameScreen {
public:
	GameScreenMenu(SDL_Renderer* renderer);
	~GameScreenMenu();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

private:
	bool SetupLevel();

	TextRenderer* titleText;
	TextRenderer* copyrightText;
};

