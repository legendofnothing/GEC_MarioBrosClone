#include "LivesSystem.h"

LivesSystem* LivesSystem::mInstance = NULL;

LivesSystem* LivesSystem::Instance() {
	if (mInstance == NULL) {
		mInstance = new LivesSystem;
	}

	return mInstance;
}

LivesSystem::LivesSystem() {
	mMarioHP = 3;
	mLuigiHP = 3;
}

LivesSystem::~LivesSystem() {

}

void LivesSystem::ReduceHP(bool isMario, bool isLuigi){
	if (isMario) {
		mMarioHP -= 1;
	}

	if (isLuigi) {
		mLuigiHP -= 1;
	}
}

void LivesSystem::ResetHP() {
	mMarioHP = 3;
	mLuigiHP = 3;
}