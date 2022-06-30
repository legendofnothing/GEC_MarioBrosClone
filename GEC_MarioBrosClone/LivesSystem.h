#pragma once
#include <iostream>

class LivesSystem {
public:
	LivesSystem();
	~LivesSystem();

	void ReduceHP(bool isMario, bool isLuigi);
	int GetMarioHP() { return mMarioHP; }
	int GetLuigiHP() { return mLuigiHP; }
	void ResetHP();

	static LivesSystem* Instance();

private:
	static LivesSystem* mInstance;

	int mMarioHP;
	int mLuigiHP;
};

