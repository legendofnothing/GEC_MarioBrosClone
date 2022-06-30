#pragma once

#include <iostream>

class ScoreSystem {
public:
	ScoreSystem();
	~ScoreSystem();

	void AddScore(int score);
	void ResetScore();
	int GetScore() { return mCurrentScore; };

	static ScoreSystem* Instance();
private:
	static ScoreSystem* mInstance;

	int mCurrentScore;
};

