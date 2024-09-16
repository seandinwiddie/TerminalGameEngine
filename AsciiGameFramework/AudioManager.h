#pragma once

#include "Config.h"
#include "RandomUtils.h"
#include "Singleton.h"
#include <windows.h>
#include <string>
#include <SFML/Audio.hpp>
#include <vector>

#pragma comment(lib,"winmm.lib")

using namespace sf;
using string = std::string;

class AudioManager : public Singleton<AudioManager>
{
	friend class Singleton;

//---------------------------------------------------------- Fields
private:
	static const uint SOUND_SOURCES_SIZE = 6;
	const std::vector<string> MUSIC_TRACKS = { "music-1.wav","music-2.wav", "music-3.wav" };
	std::vector<Sound> sounds;
	std::vector<SoundBuffer> buffers;
	Music music;

//---------------------------------------------------------- Methods
public:
	void PlayFx(const string& fileName, const float randomPitch = 0.0);
	void PlayRandomMusic();
	void StopMusic();

private:
	bool TryGetBufferAndSound(SoundBuffer*& outBuffer, Sound*& outSound);
	AudioManager()
	{
		sounds.resize(SOUND_SOURCES_SIZE);
		buffers.resize(SOUND_SOURCES_SIZE);
		for (int i = 0; i < sounds.size(); ++i)
		{
			sounds[i].setBuffer(buffers[i]);
			sounds[i].stop();
		}
	}
};