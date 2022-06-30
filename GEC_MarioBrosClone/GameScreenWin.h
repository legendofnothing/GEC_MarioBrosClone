#pragma once

#include "Commons.h"
#include "GameScreen.h"
#include "Texture2D.h"
#include "TextRenderer.h"
#include "GameScreenManager.h"

class Texture2D;
class TextRenderer;
class GameScreenManager;

class GameScreenWin : public GameScreen {
public:
	GameScreenWin(SDL_Renderer* renderer);
	~GameScreenWin();

	virtual void Render();
	virtual void Update(float deltaTime,SDL_Event e);

private:
	bool SetupLevel();

	TextRenderer* titleText;
	TextRenderer* option1;
	TextRenderer* option2;
	TextRenderer* copyright;
};
