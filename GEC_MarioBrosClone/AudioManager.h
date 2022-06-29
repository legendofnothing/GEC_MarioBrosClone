#pragma once

#include <iostream>
#include <string>

#include <SDL_mixer.h>

using namespace std;
using std::string;

class AudioManager {
public:
	AudioManager();
	~AudioManager();

	void LoadMusic(string path);
	void LoadSFX(string path);

	void StopMusic();

	static AudioManager* Instance();
private:

	Mix_Music* mMusic;
	Mix_Chunk* mSFX;

	static AudioManager* mInstance;
};

