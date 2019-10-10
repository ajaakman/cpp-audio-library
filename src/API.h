#pragma once

#define USING_SDL2

#ifdef USING_SDL2
#include "./Audio/SDL2Audio.h"
#endif

#include "./Components/Component.h"
#include "./Components/FilterLP.h"
#include "./Components/Oscillator.h"

namespace audio {
	void clipCallback(const size_t channel, const bool status); // TODO.
}

#ifdef EMSCRIPTEN

#include <emscripten/bind.h>
#include <cstdint>

class Master {
public:
	Master() = default;
	const int initAudio();
	void setAmp(const float new_amp);
	const float getAmp();
	intptr_t get();
private:
#ifdef USING_SDL2
	audio::SDL2Audio synth;
#endif
};

class LP {
public:
	LP();
	void setCutoff(const float new_freq);
	const float getCutoff();
	void setOut(intptr_t new_out);
	intptr_t get();
	audio::FilterLP lp;
};

class Osc {
public:
	Osc();
	void setAmp(const float new_amp);
	const float getAmp();
	void setFreq(const float new_freq);
	const float getFreq();
	void setPhase(const float new_phase);
	const float getPhase();
	void setWave(const int new_wave);
	const int getWave();
	void setOut(intptr_t new_out);
	intptr_t get();
	audio::Oscillator osc;
};

#endif