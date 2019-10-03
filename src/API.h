#pragma once

#include <cstdint>
#ifndef EMSCRIPTEN
#include <vector>

// Functions called here must lock the audio thread when accessing shared data.

const int InitAudio();

const intptr_t MasterComp();
void MasterSetAmp(const double dNewAmplitude);
const double MasterGetAmp();

void CompDelete(const intptr_t component);
const bool CompSetOut(const intptr_t component, const intptr_t output);

const intptr_t CompGetOut(const intptr_t component);
const std::vector<intptr_t> CompGetIn(const intptr_t component);

const intptr_t CompAddOsc();
void OscSetFreq(const intptr_t component, const double dNewFreq);
const double OscGetFreq(const intptr_t component);
void OscSetAmp(const intptr_t component, const double nNewAmplitude);
const double OscGetAmp(const intptr_t component);
void OscSetPhase(const intptr_t component, const double nNewPhase);
const double OscGetPhase(const intptr_t component);
void OscSetWave(const intptr_t component, const int nNewWave);
const int OscGetWave(const intptr_t component);

const intptr_t CompAddLP();
void LPSetCutoff(const intptr_t component, const double dNewCutoff);
const double LPGetCutoff(const intptr_t component);

#endif
