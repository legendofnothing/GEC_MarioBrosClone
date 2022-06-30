/*
Set Additional Include Directory if missing
$(ProjectDir)SDL\image_include
$(ProjectDir)SDL\include
$(ProjectDir)SDL\mixer_include

Set Additional Lib in Linker if missing
$(ProjectDir)SDL
*/
#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "Constants.h"
#include "Commons.h"

#include "Texture2D.h"
#include "GameScreenManager.h"

using namespace std;

//Globals 
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

Texture2D* gTexture = NULL;

GameScreenManager* gameScreenManager;
Uint32 gOldTime;

//Function Prototype
bool InitSDL();
bool Update();

void CloseSDL();
void Render();

void LoadMusic(string path);

int main(int argc, char* args[])
{
	//Debug 
	if (InitSDL()) {
		bool quit = false;

		gameScreenManager = new GameScreenManager(gRenderer, SCREEN_MENU);

		gOldTime = SDL_GetTicks();

		while (!quit) {
			Render();
			quit = Update();
		}
	}

	CloseSDL();

	return 0;
}

//Update Function, like Unity Update();
bool Update() {
	
	Uint32 newTime = SDL_GetTicks();

	//Event Handler
	SDL_Event e;

	//Get Events
	SDL_PollEvent(&e);

	//Handle Event
	switch (e.type) {
	case SDL_QUIT:
		return true;
		break;
	}

	gameScreenManager->Update((float)(newTime - gOldTime) / 1000.0f, e);

	gOldTime = newTime;

	return false;
}

//Setup SDL
bool InitSDL() {
	//If failed to Initialize
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "Failed to Init SDL. Error: " << SDL_GetError() << "\n";
		return false;
	}

	//If Sucesss
	else {
		//Create Window
		gWindow = SDL_CreateWindow("MarioBrosClone", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN); 
		
		//Create renderer
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

		//Check if Window is null
		if (gWindow == NULL) {
			cout << "Failed to create Window, Error: " << SDL_GetError() << "\n";
			return false;
		}

		//Check if renderer is null;
		if (gRenderer == NULL) {
			cout << "Failed to create Renderer, Error " << SDL_GetError() << "\n";
			return false;
		}

		//Set Texture
		else {
			int imageFlags = IMG_INIT_PNG;

			if (!(IMG_Init(imageFlags)) && imageFlags) {
				cout << "Failed to load SDL_Image, Error " << SDL_GetError() << "\n";
				return false;
			}
		}

		//Create Mixer
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
			cout << "Mixer could not initialise. Error: " << Mix_GetError();
			return false;
		}

		if (TTF_Init() < 0) {
			cout << "Error: " << TTF_GetError() << endl;
			return false;
		}
	}

	return true;
}

//Close SDL
void CloseSDL() {
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	IMG_Quit();
	SDL_Quit();

	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	delete gTexture;
	gTexture = NULL;

	delete gameScreenManager;
	gameScreenManager = NULL;
}

//Render 
void Render() {
	//Clear Screen
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gRenderer);
	
	//Render Texture to Screen
	gameScreenManager->Render();

	//Update Screen
	SDL_RenderPresent(gRenderer);
}

