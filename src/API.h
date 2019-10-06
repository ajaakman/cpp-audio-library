#pragma once

#include <cstdint>
#ifndef EMSCRIPTEN
#include <vector>

// Functions called here must lock the audio thread when accessing shared data.

const int InitAudio();
const bool IsOutClipping();

const intptr_t MasterComp();
void MasterSetAmp(const float dNewAmplitude);
const float MasterGetAmp();

void CompDelete(const intptr_t component);
const bool CompSetOut(const intptr_t component, const intptr_t output);

const intptr_t CompGetOut(const intptr_t component);
const std::vector<intptr_t> CompGetIn(const intptr_t component);

const intptr_t CompAddOsc();
void OscSetFreq(const intptr_t component, const float dNewFreq);
const float OscGetFreq(const intptr_t component);
void OscSetAmp(const intptr_t component, const float nNewAmplitude);
const float OscGetAmp(const intptr_t component);
void OscSetPhase(const intptr_t component, const float nNewPhase);
const float OscGetPhase(const intptr_t component);
void OscSetWave(const intptr_t component, const int nNewWave);
const int OscGetWave(const intptr_t component);

const intptr_t CompAddLP();
void LPSetCutoff(const intptr_t component, const float dNewCutoff);
const float LPGetCutoff(const intptr_t component);

#endif
