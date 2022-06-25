#include "CharacterMario.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition) : Character(renderer, imagePath, startPosition) {

	mRenderer = renderer;
	mPosition = startPosition;

	mTexture = new Texture2D(renderer);
	mTexture->LoadFromFile(imagePath);

	mFacingDirection = FACING_RIGHT;
}

CharacterMario::~CharacterMario() {
	mRenderer = NULL;
}

void CharacterMario::Update(float deltaTime, SDL_Event e) {
	switch (e.type) {
	
	case SDL_KEYUP:
		switch (e.key.keysym.sym) {
		
		case SDLK_d:
			mMoving = false;

			mVelocity = 0.0f;
			break;

		case SDLK_a:
			mMoving = false;

			mVelocity = 0.0f;
			break;
		}

	default:
		break;

	case SDL_KEYDOWN:

		switch (e.key.keysym.sym) {

		case SDLK_d:
			mMoving = true;
			mFacingDirection = FACING_RIGHT;

			mVelocity += PLAYER_SPEED;

			break;
		case SDLK_a:
			mMoving = true;
			mFacingDirection = FACING_LEFT;

			mVelocity -= PLAYER_SPEED;

			break;

	default:
			break;
		}
	}

	if (mMoving && mVelocity != 0) {
		Move(deltaTime, mVelocity);
	}

	//Cap Player Speed
	if (mVelocity > PLAYER_SPEED_LIMIT) {
		mVelocity = PLAYER_SPEED_LIMIT;
	}

	else if (mVelocity < -PLAYER_SPEED_LIMIT) {
		mVelocity = -PLAYER_SPEED_LIMIT;
	}
}

