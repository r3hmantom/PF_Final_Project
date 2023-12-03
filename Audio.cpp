#include <iostream>
#include <SFML/Audio.hpp>
using namespace std;

void playMoveSound() {
	static	sf::SoundBuffer moveBuffer;
	if (!moveBuffer.loadFromFile("assets/moveBead.wav")) {
		cout << "Error loading audio";
	}
	static	sf::Sound moveSound;
	moveSound.setBuffer(moveBuffer);
	moveSound.play();
}

void playKillSound() {

	static sf::SoundBuffer killBuffer;
	if (!killBuffer.loadFromFile("assets/killBead.wav")) {
		cout << "Error loading audio";
	}
	static sf::Sound killSound;
	killSound.setBuffer(killBuffer);
	killSound.play();
}


