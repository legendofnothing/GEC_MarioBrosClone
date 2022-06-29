#include "EnemyKoopa.h"

EnemyKoopa::EnemyKoopa(SDL_Renderer* renderer,std::string imagePath,Vector2D startPosition,LevelMap* map,FACING startFacing,float movementSpeed) : Character(renderer,imagePath,startPosition,map) {

	mFacingDirection = startFacing;
	mVelocity        = movementSpeed;
	mPosition        = startPosition;

	mInjured = false;
	
	mSingleSpriteWidth  = mTexture->GetWidth() / 2;
	mSingleSpriteHeight = mTexture->GetHeight();
}

EnemyKoopa::~EnemyKoopa() {

	delete mTexture;
	mTexture = NULL;
}

void EnemyKoopa::TakeDamage() {

	mInjured     = true;
	mInjuredTime = INJURED_TIME;
	Jump();
}

void EnemyKoopa::Jump() {
	if (!mJumping) {

		mJumpForce = JUMP_FORCE_INITIAL_SMALL;
		mJumping = true;
		mCanJump = false;
	}
}

void EnemyKoopa::FlipWayUp() {
	int left = 0.0f;

	if (mInjured) {
		left = mSingleSpriteWidth;
	}

	SDL_Rect portionOfSpriteSheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };

	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	if (mFacingDirection == FACING_RIGHT) {

		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
	}

	else if (mFacingDirection == FACING_LEFT) {

		mTexture->Render(portionOfSpriteSheet, destRect,SDL_FLIP_HORIZONTAL);
	}
}

void EnemyKoopa::Update(float deltaTime,SDL_Event e) {
	if (!mInjured) {

		if (mFacingDirection == FACING_LEFT) {
			mMovingLeft = true;
			mMovingRight = false;
		}

		else if (mFacingDirection == FACING_RIGHT) {
			mMovingLeft = false;
			mMovingRight = true;
		}
	}

	else {

		mMovingLeft = false;
		mMovingRight = false;

		mInjuredTime -= deltaTime;

		if (mInjuredTime <= 0.0) {
			FlipWayUp();
		}
	}

}
