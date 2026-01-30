/*****************************************Task B-iii ***********************************************
Create a singleton class called SoundManager for loading and playing sounds in the game.
***********************************************************************************************/
#pragma once

#include <SFML/Audio.hpp>

class SoundManager {
	sf::SoundBuffer hitSoundBuffer; // store the sounds here so they do not get destroyed right after .play(
	sf::Sound hitSound;

	// In this private constructor load the hitSound ready for it to be played
	SoundManager() :
		hitSoundBuffer(std::string((std::filesystem::current_path() / "assets" / "hit.ogg").string())),
		hitSound(hitSoundBuffer)
	{
		std::cout << "SoundManager loaded hit.ogg";
	} // Private constructor


public:
	static SoundManager& Instance() {
		static SoundManager instance; // static var only initialised once.
		return instance;
	}

	void PlayHitSound() {
		hitSound.play();
	}
};