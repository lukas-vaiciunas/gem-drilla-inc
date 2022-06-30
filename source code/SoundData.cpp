#include "SoundData.h"
#include <fstream>

SoundData::SoundData() :
	soundBuffers_(),
	musicPaths_(),
	sounds_(8, sf::Sound()),
	music_(),
	currentMusicId_(0)
{
	this->loadSoundBuffers_("data/sound-buffers.txt");
	this->loadMusicPaths_("data/music.txt");
}

SoundData &SoundData::getInstance()
{
	static SoundData instance;

	return instance;
}

void SoundData::playSound(uint8_t id)
{
	for (sf::Sound &sound : sounds_)
	{
		if (sound.getStatus() == sf::SoundSource::Status::Stopped)
		{
			sound.setBuffer(soundBuffers_[id]);
			sound.play();
			break;
		}
	}
}

void SoundData::playMusic(uint8_t id)
{
	if (currentMusicId_ == id) return;

	this->stopMusic();
	music_.openFromFile(musicPaths_[id]);
	music_.setLoop(true);
	music_.setVolume(50);
	music_.play();

	currentMusicId_ = id;
}

void SoundData::stopMusic()
{
	music_.stop();
}

void SoundData::loadSoundBuffers_(const std::string &dataPath)
{
	std::ifstream in(dataPath, std::ios_base::in);

	if (!in.is_open())
	{
		printf("Failed to open %s in SoundData!", dataPath.c_str());
		return;
	}

	uint16_t numSoundBuffers;
	uint16_t id;
	std::string path;

	in >> numSoundBuffers;

	while (numSoundBuffers--)
	{
		in >> id >> path;

		sf::SoundBuffer soundBuffer;

		soundBuffer.loadFromFile(path);

		soundBuffers_.emplace(static_cast<uint8_t>(id), std::move(soundBuffer));
	}

	in.close();
}

void SoundData::loadMusicPaths_(const std::string &dataPath)
{
	std::ifstream in(dataPath, std::ios_base::in);

	if (!in.is_open())
	{
		printf("Failed to open %s in SoundData!", dataPath.c_str());
		return;
	}

	uint16_t numMusicTracks;
	uint16_t id;
	std::string path;

	in >> numMusicTracks;

	while (numMusicTracks--)
	{
		in >> id >> path;

		musicPaths_.emplace(static_cast<uint8_t>(id), path);
	}

	in.close();
}