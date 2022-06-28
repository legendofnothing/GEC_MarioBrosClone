#include "CharacterLuigi.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map) {

	mRenderer = renderer;
	mPosition = startPosition;

	mTexture = new Texture2D(renderer);
	mTexture->LoadFromFile(imagePath);

	mFacingDirection = FACING_LEFT;
}

CharacterLuigi::~CharacterLuigi() {
	mRenderer = NULL;
}

void CharacterLuigi::Update(float deltaTime, SDL_Event e) {
	switch (e.type) {

	case SDL_KEYUP:
		switch (e.key.keysym.sym) {

		case SDLK_RIGHT:
			mMovingRight = false;

			mVelocity = 0.0f;
			break;

		case SDLK_LEFT:
			mMovingLeft = false;

			mVelocity = 0.0f;
			break;
		}

	default:
		break;

	case SDL_KEYDOWN:

		switch (e.key.keysym.sym) {

		case SDLK_RIGHT:
			mMovingRight = true;
			mMovingLeft = false;
			mFacingDirection = FACING_LEFT;

			break;
		case SDLK_LEFT:
			mMovingLeft = true;
			mMovingRight = false;
			mFacingDirection = FACING_RIGHT;

			break;

		case SDLK_UP:
			if (mCanJump) {
				Character::Jump();
			}
			break;

		default:
			break;
		}
	}

	Character::Update(deltaTime, e);
}