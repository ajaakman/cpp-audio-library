#define USING_SDL2

#include "API.h"

#ifdef USING_SDL2
#include "SDL2Audio.h"
SDL2Audio audio;
#endif


#ifdef EMSCRIPTEN
extern "C" {
#endif
	
int StartAudio() {
	return audio.StartAudio();
}

void SetAmplitude(double newAmplitude) {
	audio.SetAmplitude(newAmplitude);
}

double GetAmplitude() {
	return audio.GetAmplitude();
}

#ifdef EMSCRIPTEN
}
#endif