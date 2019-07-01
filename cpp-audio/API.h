#pragma once

#ifndef EMSCRIPTEN
int StartAudio();
void SetAmplitude(double newAmplitude);
double GetAmplitude();
#endif

