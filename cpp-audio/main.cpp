#include <iostream>

#include "audio.hpp"

using namespace std;

int main(int argc, char** argv)
{
	SDL_Log("Starting Main...");
	StartAudio();
	cout << GetAmplitude() << endl;
	SetAmplitude(0.5);
	cout << GetAmplitude() << endl;
	std::cin.get();
	return 0;
}