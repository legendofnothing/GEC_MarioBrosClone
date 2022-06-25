#pragma once

#include <iostream>

#include <SDL.h>

#include "Commons.h"
#include "GameScreen.h"
#include "Texture2D.h"
#include "CharacterMario.h"

using namespace std;

class Texture2D;
class CharacterMario;

class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

private:
	Texture2D* mBackgroundTexture;

	bool SetupLevel();

	CharacterMario* marioCharacter;
};

