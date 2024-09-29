#include "Config.h"
#include "AudioManager.h"
#include "RandomUtils.h"

AudioManager::AudioManager()
{
#if ALLOW_SOUNDS
	sounds.resize(SOUND_SOURCES_SIZE);
	buffers.resize(SOUND_SOURCES_SIZE);
	for (int i = 0; i < sounds.size(); ++i)
	{
		sounds[i].setBuffer(buffers[i]);
		sounds[i].stop();
	}
#endif
}

void AudioManager::PlayFx(const string& fileName, const double randomPitch)
{
#if ALLOW_SOUNDS
	string completeFileName = "Sounds/" + fileName;
	Sound* sound = nullptr;
	SoundBuffer* buffer = nullptr;

	//if all sound sources are already playing, sound is not played
	if (TryGetBufferAndSound(buffer, sound) == false)
		return;

	if (!buffer->loadFromFile(completeFileName))
		return;

	float pitch = 1;
	if (randomPitch != 0.0)
		pitch += static_cast<float>(RandomUtils::GetRandomDoubleBetween(1.0 - randomPitch, 1.0 + randomPitch));

	sound->setPitch(pitch);
	sound->play();
#endif
}

void AudioManager::PlayRandomMusic()
{
#if ALLOW_SOUNDS
	StopMusic();
	int randomIndex = RandomUtils::GetRandomInt(0, static_cast<int>(MUSIC_TRACKS.size()) - 1);
	string randomMusicFile = "Music/" + MUSIC_TRACKS[randomIndex];
	if (music.openFromFile(randomMusicFile) == false)
		return;
	music.play();
#endif
}

bool AudioManager::TryGetBufferAndSound(SoundBuffer*& outBuffer, Sound*& outSound)
{
	for (int i = 0; i < SOUND_SOURCES_SIZE; ++i)
	{
		if (sounds[i].getStatus() == SoundSource::Status::Stopped)
		{
			outBuffer = &buffers[i];
			outSound = &sounds[i];
			return true;
		}
	}
	return false;
}

void AudioManager::StopMusic()
{
#if ALLOW_SOUNDS
	if (music.getStatus() == sf::SoundSource::Playing)
		music.stop();
#endif
}
