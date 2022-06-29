#include "Character.h"

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) {
	
	mRenderer = renderer;
	mPosition = startPosition;

	mTexture = new Texture2D(renderer);
	mTexture->LoadFromFile(imagePath);

	mFacingDirection = FACING_RIGHT;

	mCollisionRadius = 15.0f;

	mCurrentMap = map;
}

Character::~Character() {
	
	mRenderer = NULL;
}

void Character::Render() {
	
	if (mFacingDirection == FACING_RIGHT) {
		mTexture->Render(mPosition, SDL_FLIP_NONE, 0);
	}

	else mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL, 0);
}

void Character::Update(float deltaTime, SDL_Event e, bool isKoopa) {
	//Collision Variables
	int topPosition      = (int)(mPosition.y + mTexture->GetHeight() - 32) / TILE_HEIGHT;
	int centralXPosition = (int)(mPosition.x + (mTexture->GetWidth() * 0.5f)) / TILE_WIDTH;
	int footPosition     = (mPosition.y + mTexture->GetHeight()) / TILE_HEIGHT;

	if (mCurrentMap->GetTileAt(footPosition, centralXPosition) == 0) {
		AddGravity(deltaTime);
	}

	else mCanJump = true;

	//Collision for Head
	if (mCurrentMap->GetTileAt(topPosition, centralXPosition) == 1) {
		CancelJump();
		mCanJump = false;
	}

	//Gradually increase playerSpeed
	if (mMovingLeft) {
		mVelocity += PLAYER_SPEED;

		MoveLeft(deltaTime);
	}

	else if (mMovingRight) {
		mVelocity += PLAYER_SPEED;

		MoveRight(deltaTime);
	}

	if (!isKoopa) {
		//Cap Player Speed
		if (mVelocity > PLAYER_SPEED_LIMIT) {
			mVelocity = PLAYER_SPEED_LIMIT;
		}

		else if (mVelocity < -PLAYER_SPEED_LIMIT) {
			mVelocity = -PLAYER_SPEED_LIMIT;
		}
	}

	else {
		if (mVelocity > 65.0f) {
			mVelocity = 65.0f;
		}

		else if (mVelocity < -65.0f) {
			mVelocity = -65.0f;
		}
	}


	//if character is jumping
	if (mJumping) {
		mCanJump = false;

		//adjusts position
		mPosition.y -= mJumpForce * deltaTime;

		//reduces jump force
		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

		//if jump force is 0 then character is no longer jumping
		if (mJumpForce <= 0.0f) {
			mJumping = false;
		}
	}
}

void Character::MoveLeft(float deltaTime) {
	mPosition.x -= mVelocity * deltaTime;
}

void Character::MoveRight(float deltaTime) {
	mPosition.x += mVelocity * deltaTime;
}

void Character::Jump() {
	if (!mJumping) {
		mJumpForce = INITIAL_JUMP_FORCE;
		mJumping = true;

		mCanJump = false;

		AudioManager::Instance()->LoadSFX("SFX/Jump.wav");
	}
}

void Character::SetPosition(Vector2D newPosition) {
	
	mPosition = newPosition;
}

Vector2D Character::GetPosition() {
	
	return mPosition;
}

float Character::GetCollisionRadius() {
	return mCollisionRadius;
}

Rect2D Character::GetCollisionBox() {
	return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth(), mTexture->GetHeight());
}

void Character::AddGravity(float deltaTime) {
	mPosition.y += GRAVITY * deltaTime;
}

bool Character::IsJumping() {
	return mJumping;
}

void Character::CancelJump() {
	mJumpForce = 0;
}

