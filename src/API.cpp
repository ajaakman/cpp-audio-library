#include "./API.h"
#include "./Globals.h"

namespace audio {
	static std::array<std::atomic<bool>, audio::CHANNELS<size_t>> clip_flag;

	void clipCallback(const size_t channel, const bool status) // TODO.
	{
		clip_flag[channel] = status;
	}
}

#ifdef EMSCRIPTEN

//----------------------------------------------------------------------------------------------
const int Master::initAudio() { return synth.initAudio(); }

void Master::setAmp(const float new_amp) { synth.masterMixer.setAmplitude(new_amp); }

const float Master::getAmp() { return synth.masterMixer.getAmplitude(); };

intptr_t Master::get() { return reinterpret_cast<intptr_t>(&synth.masterMixer); }

//----------------------------------------------------------------------------------------------
Osc::Osc() :osc() {}

void Osc::setAmp(const float new_amp) { osc.setAmplitude(new_amp); }

const float Osc::getAmp() { return osc.getAmplitude(); }

void Osc::setFreq(const float new_freq) { osc.setFrequency(new_freq); }

const float Osc::getFreq() { return osc.getFrequency(); }

void Osc::setPhase(const float new_phase) { osc.setPhase(new_phase); }

const float Osc::getPhase() { return osc.getPhase(); }

void Osc::setWave(const int new_wave) { osc.setWave(static_cast<audio::Oscillator::Wave>(new_wave)); }

const int Osc::getWave() { return static_cast<int>(osc.getWave()); }

void Osc::setOut(intptr_t new_out) { osc.setOutput(reinterpret_cast<audio::Component*>(new_out)); }

intptr_t Osc::get() { return reinterpret_cast<intptr_t>(&osc); }

//----------------------------------------------------------------------------------------------
LP::LP() :lp() {}

void LP::setCutoff(const float new_freq) { lp.setCutoff(new_freq); }

const float LP::getCutoff() { return lp.getCutoff(); }

void LP::setOut(intptr_t new_out) { lp.setOutput(reinterpret_cast<audio::Component*>(new_out)); }

intptr_t LP::get() { return reinterpret_cast<intptr_t>(&lp); }

//----------------------------------------------------------------------------------------------
EMSCRIPTEN_BINDINGS(my_module) {
	emscripten::class_<Master>("Master")
		.constructor<>()
		.function("initAudio", &Master::initAudio)
		.function("setAmp", &Master::setAmp)
		.function("getAmp", &Master::getAmp)
		.function("get", &Master::get);

	emscripten::class_<LP>("LP")
		.constructor<>()
		.function("setCutoff", &LP::setCutoff)
		.function("getCutoff", &LP::getCutoff)
		.function("setOut", &LP::setOut)
		.function("get", &LP::get);

	emscripten::class_<Osc>("Osc")
		.constructor<>()
		.function("setAmp", &Osc::setAmp)
		.function("getAmp", &Osc::getAmp)
		.function("setFreq", &Osc::setFreq)
		.function("getFreq", &Osc::getFreq)
		.function("setPhase", &Osc::setPhase)
		.function("getPhase", &Osc::getPhase)
		.function("setWave", &Osc::setWave)
		.function("getWave", &Osc::getWave)
		.function("setOut", &Osc::setOut)
		.function("get", &Osc::get);
}
#endif