#include "Coin.h"

Coin::Coin(SDL_Renderer* renderer,std::string imagePath,Vector2D startPosition,LevelMap* map) : Character(renderer,imagePath,startPosition,map) {
	mPosition = startPosition;

	mSingleSpriteWidth = mTexture->GetWidth() / 3;
	mSingleSpriteHeight = mTexture->GetHeight();
}

Coin::~Coin() {
	delete mTexture;
	mTexture = NULL;
}

void Coin::Render() {
	int left = mSingleSpriteWidth * mCurrentFrame;

	SDL_Rect portionOfSpriteSheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };

	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	mTexture->Render(portionOfSpriteSheet,destRect,SDL_FLIP_NONE);
}

void Coin::Update(float deltaTime,SDL_Event e) {
	mFrameDelay -= deltaTime;

	if (mFrameDelay <= 0.0f) {
		mFrameDelay = 0.15f;

		mCurrentFrame++;

		if (mCurrentFrame > 2) {
			mCurrentFrame = 0;
		}
	}
}
