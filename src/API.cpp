#define USING_SDL2
#include "./API.h"

#include "./Components/Component.h"
#include "./Components/Oscillator.h"
#include "./Components/FilterLP.h"

using namespace audio;

#ifdef USING_SDL2
#include "./Audio/SDL2Audio.h"
SDL2Audio synth;
#endif

#ifdef EMSCRIPTEN
extern "C" {
#endif

	const int InitAudio()
	{
		return synth.InitAudio();
	}

	void MasterSetAmp(const float dNewAmplitude)
	{
		synth.LockAudioThread();
		synth.masterMixer.SetAmplitude(dNewAmplitude);
		synth.UnlockAudioThread();
	}

	const bool IsOutClipping()
	{
		synth.LockAudioThread();
		volatile bool result = false;
		for (const auto& channel : synth.masterMixer.IsOutClipping())
		{
			if (channel) result = true;
		}
		synth.UnlockAudioThread();
		return result;
	}

	void ClipCallback(const size_t channel, const bool status)
	{
		// std::cout << channel << " " << status << std::endl; // TODO. Finish Callback.
	}

	const intptr_t MasterComp()
	{
		synth.LockAudioThread();
		const volatile intptr_t masterMixer = reinterpret_cast<intptr_t>(&synth.masterMixer);
		synth.UnlockAudioThread();

		return masterMixer;
	}

	const float MasterGetAmp()
	{
		synth.LockAudioThread();
		volatile float amplitude = synth.masterMixer.GetAmplitude();
		synth.UnlockAudioThread();

		return amplitude;
	}

	void CompDelete(const intptr_t component)
	{
		synth.LockAudioThread();
		delete reinterpret_cast<Component*>(component);
		synth.UnlockAudioThread();
	}

	const bool CompSetOut(const intptr_t component, const intptr_t output)
	{
		synth.LockAudioThread();
		volatile bool result = reinterpret_cast<Component*>(component)->SetOutput(reinterpret_cast<Component*>(output));
		synth.UnlockAudioThread();
		return result;
	}

	const intptr_t CompGetOut(const intptr_t component)
	{
		synth.LockAudioThread();
		const volatile Component* comp = reinterpret_cast<Component*>(component)->GetOutput();
		synth.UnlockAudioThread();
		return reinterpret_cast<intptr_t>(comp);
	}

	// New components get inserted here with python script.

	const intptr_t CompAddOsc()
	{
		return reinterpret_cast<intptr_t>(new Oscillator);
	}

	void OscSetFreq(const intptr_t component, const float dNewFrequency)
	{
		synth.LockAudioThread();
		reinterpret_cast<Oscillator*>(component)->SetFrequency(dNewFrequency);
		synth.UnlockAudioThread();
	}

	const float OscGetFreq(const intptr_t component)
	{
		synth.LockAudioThread();
		volatile float freq = reinterpret_cast<Oscillator*>(component)->GetFrequency();
		synth.UnlockAudioThread();

		return freq;
	}

	void OscSetAmp(const intptr_t component, const float dNewAmplitude)
	{
		synth.LockAudioThread();
		reinterpret_cast<Oscillator*>(component)->SetAmplitude(dNewAmplitude);
		synth.UnlockAudioThread();
	}

	const float OscGetAmp(const intptr_t component)
	{
		synth.LockAudioThread();
		volatile float amp = reinterpret_cast<Oscillator*>(component)->GetAmplitude();
		synth.UnlockAudioThread();

		return amp;
	}

	void OscSetPhase(const intptr_t component, const float dNewPhase)
	{
		synth.LockAudioThread();
		reinterpret_cast<Oscillator*>(component)->SetPhase(dNewPhase);
		synth.UnlockAudioThread();
	}

	const float OscGetPhase(const intptr_t component)
	{
		synth.LockAudioThread();
		volatile float phase = reinterpret_cast<Oscillator*>(component)->GetPhase();
		synth.UnlockAudioThread();

		return phase;
	}

	void OscSetWave(const intptr_t component, const int dNewWave)
	{
		synth.LockAudioThread();
		reinterpret_cast<Oscillator*>(component)->SetWave(static_cast<Oscillator::Wave>(dNewWave));
		synth.UnlockAudioThread();
	}

	const int OscGetWave(const intptr_t component)
	{
		synth.LockAudioThread();
		volatile int wave = reinterpret_cast<Oscillator*>(component)->GetWave();
		synth.UnlockAudioThread();

		return wave;
	}

	const intptr_t CompAddLP()
	{
		return reinterpret_cast<intptr_t>(new FilterLP());
	}

	void LPSetCutoff(const intptr_t component, const float dNewCutoff)
	{
		synth.LockAudioThread();
		reinterpret_cast<FilterLP*>(component)->SetCutoff(dNewCutoff);
		synth.UnlockAudioThread();
	}

	const float LPGetCutoff(const intptr_t component)
	{
		synth.LockAudioThread();
		volatile float cutoff = reinterpret_cast<FilterLP*>(component)->GetCutoff();
		synth.UnlockAudioThread();

		return cutoff;
	}

#ifdef EMSCRIPTEN
}
#endif

const std::vector<intptr_t> CompGetIn(const intptr_t component)
{
	std::vector<intptr_t> result;

	synth.LockAudioThread();
	result.reserve(reinterpret_cast<Component*>(component)->GetInputs().size());
	for (const auto& input : reinterpret_cast<Component*>(component)->GetInputs())
	{
		result.push_back(reinterpret_cast<intptr_t>(input));
	}
	synth.UnlockAudioThread();

	return result;
}