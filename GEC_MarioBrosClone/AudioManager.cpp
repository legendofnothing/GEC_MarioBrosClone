#include "AudioManager.h"

AudioManager* AudioManager::mInstance = NULL;

AudioManager::AudioManager() {
}

AudioManager::~AudioManager() {
	Mix_FreeMusic(mMusic);
	mMusic = NULL;

	Mix_FreeChunk(mSFX);
	mSFX = NULL;
}

AudioManager* AudioManager::Instance() {
	if (mInstance == NULL) {
		mInstance = new AudioManager;
	}

	return mInstance;
}

void AudioManager::LoadMusic(string path) {
	mMusic = Mix_LoadMUS(path.c_str());

	if (mMusic == NULL) {
		cout << "Failed to Load music file. Error: " << Mix_GetError() << "\n";
	}

	Mix_PlayMusic(mMusic, -1);
}

void AudioManager::LoadSFX(string path) {
	mSFX = Mix_LoadWAV(path.c_str());

	if (!mSFX) {
		cout << "Failed to Load music file. Error: " << Mix_GetError() << "\n";
	}

	Mix_PlayChannel(-1, mSFX, 0);
}

void AudioManager::StopMusic() {
	Mix_HaltMusic();
}





