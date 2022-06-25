#pragma once

struct Vector2D {
	float x;
	float y;

	Vector2D() {
		x = 0.0f;
		y = 0.0f;
	};

	Vector2D(float a, float b) {
		x = a;
		y = b;
	}
};

enum SCREENS {
	SCREEN_INTRO = 0,
	SCREEN_MENU,
	SCREEN_LVL1,
	SCREEN_LVL2,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORE
};
