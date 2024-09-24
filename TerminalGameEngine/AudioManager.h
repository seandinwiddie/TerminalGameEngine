#pragma once

#include "Config.h"
#include "Singleton.h"
#include <SFML/Audio.hpp>

using namespace sf;
using string = std::string;

class AudioManager : public Singleton<AudioManager>
{
	friend class Singleton;

//---------------------------------------------------------- Fields
private:
	static const size_t SOUND_SOURCES_SIZE = 6;
	const std::vector<string> MUSIC_TRACKS = { "music-1.wav","music-2.wav", "music-3.wav" };
	std::vector<Sound> sounds;
	std::vector<SoundBuffer> buffers;
	Music music;

//---------------------------------------------------------- Methods
public:
	void PlayFx(const string& fileName, double randomPitch = 0.0);
	void PlayRandomMusic();
	void StopMusic();

private:
	AudioManager();
	bool TryGetBufferAndSound(SoundBuffer*& outBuffer, Sound*& outSound);
};