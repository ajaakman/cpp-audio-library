#pragma once

#define USING_SDL2

#ifdef USING_SDL2
#include "./Audio/SDL2Audio.h"
#endif

#include "./Components/Component.h"
#include "./Components/FilterLP.h"
#include "./Components/Oscillator.h"

namespace audio {
	void ClipCallback(const size_t channel, const bool status); // TODO.
}

#ifdef EMSCRIPTEN

#include <emscripten/bind.h>
#include <cstdint>

class Master {
public:
	Master() = default;
	const int InitAudio();
	void SetAmp(const float new_amp);
	const float GetAmp();
	intptr_t Get();
private:
#ifdef USING_SDL2
	audio::SDL2Audio synth;
#endif
};

class LP {
public:
	LP();
	void SetCutoff(const float new_freq);
	const float GetCutoff();
	void SetOut(intptr_t new_out);
	intptr_t Get();
	audio::FilterLP lp;
};

class Osc {
public:
	Osc();
	void SetAmp(const float new_amp);
	const float GetAmp();
	void SetFreq(const float new_freq);
	const float GetFreq();
	void SetPhase(const float new_phase);
	const float GetPhase();
	void SetWave(const int new_wave);
	const int GetWave();
	void SetOut(intptr_t new_out);
	intptr_t Get();
	audio::Oscillator osc;
};

#endif