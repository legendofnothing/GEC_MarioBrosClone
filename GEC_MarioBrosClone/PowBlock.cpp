#include "PowBlock.h"

PowBlock::PowBlock(SDL_Renderer* renderer, LevelMap* levelMap)
{
	string imagePath = "Images/PowBlock.png";
	mTexture = new Texture2D(renderer);

	if (!mTexture->LoadFromFile(imagePath.c_str())) {

		cout << "Failed to load texture" << imagePath << std::endl;
		return;
	}

	mLevelMap = levelMap;

	mSingleSpriteWidth  = mTexture->GetWidth() / 3;
	mSingleSpriteHeight = mTexture->GetHeight();
	mNumberOfHitsLeft   = 3;

	mPosition = Vector2D((SCREEN_WIDTH * 0.5f) - mSingleSpriteWidth * 0.5f, 260);
}

PowBlock::~PowBlock() {
	mRenderer = NULL;
	delete mTexture;

	mTexture  = NULL;
	mLevelMap = NULL;
}

void PowBlock::TakeAHit() {

	mNumberOfHitsLeft--;

	if (mNumberOfHitsLeft <= 0) {

		mNumberOfHitsLeft = 0;

		mLevelMap->ChangeTileAt(8, 7, 0);
		mLevelMap->ChangeTileAt(8, 8, 0);
	}
}

void PowBlock::Render() {

	if (mNumberOfHitsLeft > 0) {
		//Get the portion of the spritesheet want to draw
		int left = mSingleSpriteWidth * (mNumberOfHitsLeft - 1);

		//{XPos, YPos, WidthOfSingleSprite, HeightOfSingleSprite}
		SDL_Rect portionOfSpriteSheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };

		//Determine where want to drawn
		SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

		//Then draw it
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
	}

	//If cannot hit left then move the sprite up to 1337 (idk how to destroy it)
	else mPosition.x = 1337;
}

Rect2D PowBlock::GetCollisionBox() {

	return Rect2D(mPosition.x, mPosition.y, mSingleSpriteWidth, mTexture->GetHeight());
}