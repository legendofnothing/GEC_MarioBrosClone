#include "Character.h"

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition) {
	
	mRenderer = renderer;
	mPosition = startPosition;

	mTexture = new Texture2D(renderer);
	mTexture->LoadFromFile(imagePath);

	mFacingDirection = FACING_RIGHT;
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

void Character::Update(float deltaTime, SDL_Event e) {
	

}

void Character::Move(float deltaTime) {
	mPosition.x += mVelocity * deltaTime;
}

void Character::SlowDown(float deltaTime) {
	mPosition.x += mSlowdownVelocity * deltaTime;
}

void Character::SetPosition(Vector2D newPosition) {
	
	mPosition = newPosition;
}

Vector2D Character::GetPosition() {
	
	return mPosition;
}

