#include "TextRenderer.h"

TextRenderer::TextRenderer(int fontsize) {

	font = TTF_OpenFont("arial.ttf",fontsize);

	color = { 255, 255, 255, 255 };
}

TextRenderer::~TextRenderer() {
	text = NULL;
}


void TextRenderer::Render(SDL_Renderer* renderer,const char* message,int x,int y) {

	if (text != NULL) {
		SDL_DestroyTexture(text);
	}

	textSurface = TTF_RenderText_Solid(font,message,color);
	text = SDL_CreateTextureFromSurface(renderer,textSurface);

	textRect.x = x;
	textRect.y = y;

	SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
	SDL_RenderCopy(renderer,text,NULL,&textRect);


	SDL_FreeSurface(textSurface);
	textSurface = nullptr;
}

void TextRenderer::Render(SDL_Renderer* renderer,int score,int x,int y) {
	char Buffer[256];
	sprintf_s(Buffer,"%i",score);

	if (text != NULL) {
		SDL_DestroyTexture(text);
	}

	textSurface = TTF_RenderText_Solid(font,Buffer,color);
	text = SDL_CreateTextureFromSurface(renderer,textSurface);

	textRect.x = x;
	textRect.y = y;

	SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
	SDL_RenderCopy(renderer,text,NULL,&textRect);


	SDL_FreeSurface(textSurface);
	textSurface = nullptr;
}
