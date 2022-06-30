#pragma once

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>
#include <unordered_map>

class SoundData
{
public:
	SoundData(const SoundData &) = delete;
	SoundData &operator=(const SoundData &) = delete;

	static SoundData &getInstance();

	void playSound(uint8_t id);
	void playMusic(uint8_t id);
	void stopMusic();
private:
	SoundData();
	~SoundData() {}

	std::unordered_map <uint8_t, sf::SoundBuffer> soundBuffers_;
	std::unordered_map<uint8_t, std::string> musicPaths_;
	std::vector<sf::Sound> sounds_;
	sf::Music music_;

	uint8_t currentMusicId_;

	void loadSoundBuffers_(const std::string &dataPath);
	void loadMusicPaths_(const std::string &dataPath);
};