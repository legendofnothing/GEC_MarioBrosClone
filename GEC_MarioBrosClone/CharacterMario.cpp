#include "CharacterMario.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map) {

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
			mMovingRight = false;

			mVelocity = 0.0f;
			break;

		case SDLK_a:
			mMovingLeft = false;

			mVelocity = 0.0f;
			break;
		}

	default:
		break;

	case SDL_KEYDOWN:

		switch (e.key.keysym.sym) {

		case SDLK_d:
			mMovingRight = true;
			mMovingLeft = false;
			mFacingDirection = FACING_RIGHT;

			break;
		case SDLK_a:
			mMovingLeft = true;
			mMovingRight = false;
			mFacingDirection = FACING_LEFT;

			break;

		case SDLK_w:
			if (mCanJump) {
				Character::Jump();
			}
			break;

	default:
			break;
		}
	}

	Character::Update(deltaTime, e, false);
}

