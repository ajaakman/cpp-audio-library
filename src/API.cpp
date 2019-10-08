#include "./API.h"
#include "./Globals.h"

namespace audio {
	static std::array<std::atomic<bool>, audio::CHANNELS<size_t>> clip_flag;

	void ClipCallback(const size_t channel, const bool status) // TODO.
	{
		clip_flag[channel] = status;
	}
}

#ifdef EMSCRIPTEN

//----------------------------------------------------------------------------------------------
const int Master::InitAudio() { return synth.InitAudio(); }

void Master::SetAmp(const float new_amp) { synth.masterMixer.SetAmplitude(new_amp); }

const float Master::GetAmp() { return synth.masterMixer.GetAmplitude(); };

intptr_t Master::Get() { return reinterpret_cast<intptr_t>(&synth.masterMixer); }

//----------------------------------------------------------------------------------------------
Osc::Osc() :osc() {}

void Osc::SetAmp(const float new_amp) { osc.SetAmplitude(new_amp); }

const float Osc::GetAmp() { return osc.GetAmplitude(); }

void Osc::SetFreq(const float new_freq) { osc.SetFrequency(new_freq); }

const float Osc::GetFreq() { return osc.GetFrequency(); }

void Osc::SetPhase(const float new_phase) { osc.SetPhase(new_phase); }

const float Osc::GetPhase() { return osc.GetPhase(); }

void Osc::SetWave(const int new_wave) { osc.SetWave(static_cast<audio::Oscillator::Wave>(new_wave)); }

const int Osc::GetWave() { return static_cast<int>(osc.GetWave()); }

void Osc::SetOut(intptr_t new_out) { osc.SetOutput(reinterpret_cast<audio::Component*>(new_out)); }

intptr_t Osc::Get() { return reinterpret_cast<intptr_t>(&osc); }

//----------------------------------------------------------------------------------------------
LP::LP() :lp() {}

void LP::SetCutoff(const float new_freq) { lp.SetCutoff(new_freq); }

const float LP::GetCutoff() { return lp.GetCutoff(); }

void LP::SetOut(intptr_t new_out) { lp.SetOutput(reinterpret_cast<audio::Component*>(new_out)); }

intptr_t LP::Get() { return reinterpret_cast<intptr_t>(&lp); }

//----------------------------------------------------------------------------------------------
EMSCRIPTEN_BINDINGS(my_module) {
	emscripten::class_<Master>("Master")
		.constructor<>()
		.function("InitAudio", &Master::InitAudio)
		.function("SetAmp", &Master::SetAmp)
		.function("GetAmp", &Master::GetAmp)
		.function("Get", &Master::Get);

	emscripten::class_<LP>("LP")
		.constructor<>()
		.function("SetCutoff", &LP::SetCutoff)
		.function("GetCutoff", &LP::GetCutoff)
		.function("SetOut", &LP::SetOut)
		.function("Get", &LP::Get);

	emscripten::class_<Osc>("Osc")
		.constructor<>()
		.function("SetAmp", &Osc::SetAmp)
		.function("GetAmp", &Osc::GetAmp)
		.function("SetFreq", &Osc::SetFreq)
		.function("GetFreq", &Osc::GetFreq)
		.function("SetPhase", &Osc::SetPhase)
		.function("GetPhase", &Osc::GetPhase)
		.function("SetWave", &Osc::SetWave)
		.function("GetWave", &Osc::GetWave)
		.function("SetOut", &Osc::SetOut)
		.function("Get", &Osc::Get);
}
#endif