#include "Character.h"

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition) {
	
	mRenderer = renderer;
	mPosition = startPosition;

	mTexture = new Texture2D(renderer);
	mTexture->LoadFromFile(imagePath);

	mFacingDirection = FACING_RIGHT;

	mCollisionRadius = 15.0f;
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

void Character::Move(float deltaTime, float velocity) {
	mPosition.x += velocity * deltaTime;
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

