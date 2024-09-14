#include "AudioManager.h"

void AudioManager::PlayFx(const string& fileName, const float randomPitch)
{
	string completeFileName = "Sounds/" + fileName;

	Sound* sound = nullptr;
	SoundBuffer* buffer = nullptr;

	if (TryGetBufferAndSound(buffer, sound) == false)
		return;

	if (!buffer->loadFromFile(completeFileName))
		return;

	float pitch = 1;
	if (randomPitch != 0.0)
		pitch += RandomUtils::GetRandomFloatBetween(1 - randomPitch, 1 + randomPitch);

	sound->setPitch(pitch);
	sound->play();
}

void AudioManager::PlayRandomMusic()
{
	StopMusic();
	string randomMusicFile = MUSIC_TRACKS[RandomUtils::GetRandomIntBetween(0, MUSIC_TRACKS.size() - 1)];
	randomMusicFile = "Music/" + randomMusicFile;
	if (music.openFromFile(randomMusicFile) == false)
		return;

	music.play();
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

