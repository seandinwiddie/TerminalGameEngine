#pragma once
#include "Config.h"
#include "Singleton.h"

#include <array>
#include <SFML/Audio.hpp>

using namespace sf;
using string = std::string;

class AudioManager : public Singleton<AudioManager>
{
friend class Singleton;

//---------------------------------------------------------- Fields
private:
	static const size_t SOUND_SOURCES_SIZE = 6;
	std::array<Sound, SOUND_SOURCES_SIZE> sounds;
	std::array<SoundBuffer, SOUND_SOURCES_SIZE> buffers;
	Music music;

	const std::array<string,3> MUSIC_TRACKS =
	{ 
		"Resources/Music/Music-1.wav",
		"Resources/Music/Music-2.wav", 
		"Resources/Music/Music-3.wav"
	};

//---------------------------------------------------------- Methods
public:
	void PlayFx(const string& fileName, double randomPitch = 0.0);
	void PlayMusic(const string& fileName);
	void StopMusic();

private:
	AudioManager();
	bool TryGetBufferAndSound(SoundBuffer*& outBuffer, Sound*& outSound);
};