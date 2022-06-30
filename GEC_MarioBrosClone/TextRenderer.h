#pragma once
#include <stdio.h>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;
using std::string;

class TextRenderer {
public:
	TextRenderer(int fontsize);
	~TextRenderer();

	void Render(SDL_Renderer* renderer,const char* message,int x,int y);

private:
	TTF_Font*    font;
	SDL_Color    color;
	SDL_Surface* textSurface;
	SDL_Texture* text;
	SDL_Rect     textRect;
};

