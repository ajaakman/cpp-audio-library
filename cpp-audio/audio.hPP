#ifndef AUDIO_H
#define AUDIO_H
#include <SDL.h>

#ifndef EMSCRIPTEN
int StartAudio();
void SetAmplitude(double newAmplitude);
double GetAmplitude();
#endif

#endif /* AUDIO_H */