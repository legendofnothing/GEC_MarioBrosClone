#pragma once

#include <iostream>

#include <SDL.h>

#include "Commons.h"
#include "GameScreen.h"
#include "Texture2D.h"
#include "TextRenderer.h"
#include "GameScreenManager.h"

class Texture2D;
class TextRenderer;
class GameScreenManager;

class GameScreenOver : public GameScreen {
public:
	GameScreenOver(SDL_Renderer* renderer);
	~GameScreenOver();

	virtual void Render();
	virtual void Update(float deltaTime,SDL_Event e);

private:
	bool SetupLevel();

	TextRenderer* titleText;
	TextRenderer* option1;
	TextRenderer* option2;
	TextRenderer* copyright;
};