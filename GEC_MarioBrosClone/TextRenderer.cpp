#include "TextRenderer.h"

TextRenderer::TextRenderer(int fontsize) {

	font = TTF_OpenFont("fonts.ttf",fontsize);

	color = { 255, 255, 255, 255 };
}

TextRenderer::~TextRenderer() {
	text = NULL;
}


void TextRenderer::Render(SDL_Renderer* renderer,const char* message,int x,int y) {

	textSurface = TTF_RenderText_Solid(font,message,color);
	text = SDL_CreateTextureFromSurface(renderer,textSurface);

	textRect.x = x;
	textRect.y = y;

	SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
	SDL_RenderCopy(renderer,text,NULL,&textRect);


	SDL_DestroyTexture(text);
	SDL_FreeSurface(textSurface);
	textSurface = nullptr;
}