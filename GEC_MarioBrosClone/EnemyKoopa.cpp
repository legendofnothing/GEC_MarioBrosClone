#include "EnemyKoopa.h"

EnemyKoopa::EnemyKoopa(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing) : Character(renderer, imagePath, startPosition, map) {
	mFacingDirection = startFacing;
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

	mInjured = false;
	Jump();
	if (mFacingDirection == FACING_RIGHT) {

		mFacingDirection = FACING_LEFT;
	}
	else if (mFacingDirection == FACING_LEFT) {

		mFacingDirection = FACING_RIGHT;
	}
}

void EnemyKoopa::Update(float deltaTime,SDL_Event e) {
	if (!mInjured) {

		if (mFacingDirection == FACING_LEFT) {
			mMovingLeft = true;
			mMovingRight = false;
		}

		else if (mFacingDirection == FACING_RIGHT) {
			mMovingRight = true;
			mMovingLeft = false;
		}
	}

	else {
		mInjuredTime -= deltaTime;

		if (mInjuredTime <= 0.0) {
			FlipWayUp();
		}

		mVelocity = 0;
	}

	if (mPosition.y < 350) {

		if (mMovingLeft && mPosition.x < 0) {

			mFacingDirection = FACING_RIGHT;
		}
		else if (mMovingRight && (mPosition.x + mSingleSpriteWidth) > SCREEN_WIDTH) {

			mFacingDirection = FACING_LEFT;
		}
	}

	Character::Update(deltaTime,e,true);
}

void EnemyKoopa::Render() {
	int left = 0.0f;

	if (mInjured) {
		left = mSingleSpriteWidth;
	}

	SDL_Rect portionOfSpriteSheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };

	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	if (mFacingDirection == FACING_RIGHT) {

		mTexture->Render(portionOfSpriteSheet,destRect,SDL_FLIP_NONE);
	}

	else if (mFacingDirection == FACING_LEFT) {

		mTexture->Render(portionOfSpriteSheet,destRect,SDL_FLIP_HORIZONTAL);
	}
}

bool EnemyKoopa::GetInjured() {
	return mInjured;
}

void EnemyKoopa::SetInjured(bool condition) {
	mInjured = condition;
}