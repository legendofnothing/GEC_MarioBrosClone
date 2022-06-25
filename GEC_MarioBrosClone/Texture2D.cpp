#include "Texture2D.h"

#include <iostream>

#include <SDL_image.h>

using namespace std;

Texture2D::Texture2D(SDL_Renderer* renderer) {
	mRenderer = renderer;
	mTexture  = NULL;

	mWidth = 0;
	mHeight = 0;
}

Texture2D::~Texture2D() {
	Free();

	mRenderer = NULL;
}

//Free Textures
void Texture2D::Free() {
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
	}

	mWidth  = 0;
	mHeight = 0;
}

//Render Texture
void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, double angle) {
	//Clear Screen
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(mRenderer);

	//Render Location
	SDL_Rect renderLocation = { newPosition.x, newPosition.y, mWidth, mHeight};

	//Render To Screen
	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocation, angle, NULL, flip);

	//Update Screen
	SDL_RenderPresent(mRenderer);
}

//Load Image from File
bool Texture2D::LoadFromFile(string path) {
	//Free Texture
	Free();

	SDL_Texture* mTexture = NULL;

	//Load Image
	SDL_Surface* pSurface = IMG_Load(path.c_str());

	if (pSurface != NULL) {
		mTexture = SDL_CreateTextureFromSurface(mRenderer, pSurface);

		//Set Transparent ColorKey
		SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0, 0xFF, 0xFF)); //Set Black as ColorKey

		//Set mWidth and mHeight to pSurface
		mWidth  = pSurface->w;
		mHeight = pSurface->h;

		if (mTexture == NULL) {
			cout << "Failed to create texture from surface, Error: " << SDL_GetError() << "\n";
		}

		SDL_FreeSurface(pSurface);
	}

	else cout << "Failed to create texture from surface, Error: " << IMG_GetError() << "\n";

	return mTexture != NULL;
}