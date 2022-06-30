#include "ScoreSystem.h"

ScoreSystem* ScoreSystem::mInstance = NULL;

ScoreSystem* ScoreSystem::Instance() {
	if (mInstance == NULL) {
		mInstance = new ScoreSystem;
	}

	return mInstance;
}

ScoreSystem::ScoreSystem() {
	mCurrentScore = 0;
}

ScoreSystem::~ScoreSystem() {

}

void ScoreSystem::ResetScore() {
	mCurrentScore = 0;
}

void ScoreSystem::AddScore(int score) {
	mCurrentScore += score;
}