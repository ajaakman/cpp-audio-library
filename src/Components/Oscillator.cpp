#include "./Oscillator.h"

#include "../Utilities.h"

#include <cmath>

namespace audio
{
	Oscillator::Oscillator(const MasterMixer& masterMixer)
		: Component(masterMixer)
        , m_frequency(0.0f)
        , m_amplitude(0.0f)
        , m_phase(0.0f)
        , m_wave(Sine)
	{}

	void Oscillator::writeSamples(std::array<float, CHANNELS<size_t>>& samples)
	{
		float wave = 0.0f;
		switch (m_wave)
		{
		case audio::Oscillator::Sine:
			wave = sineWave();
			break;
		case audio::Oscillator::Square:
			wave = signbit(sineWave());
			break;
		case audio::Oscillator::Triangle:
			wave = asin(sineWave()) * TWO_OVER_PI<float>;
			break;
		case audio::Oscillator::Saw:
			wave = -2.0f / PI<float> * atan(1.0f / tan(m_frequency * getTime() * PI<float> +(m_phase * PI<float>)));
			break;
		case audio::Oscillator::Noise:
			wave = 2.0f * (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) - 1.0f;
			break;
		default:
			break;
		}

		for (auto& sample : samples)
		{
			sample += wave;
			sample *= m_amplitude;
		}
	}

	const float Oscillator::sineWave()
	{
		return sin(m_frequency * TWO_PI<float> * getTime() + (m_phase * TWO_PI<float>));
	}

	void Oscillator::setAmplitude(const float new_amplitude)
	{
		m_amplitude = std::clamp(new_amplitude, 0.0f, 1.0f);
	}

	const float Oscillator::getAmplitude() const
	{
		return m_amplitude;
	}

	void Oscillator::setFrequency(const float new_frequency)
	{
		m_frequency = roundf(std::clamp(new_frequency, 0.0f, 20000.0f) * OSC_TUNE_ACC<float>) / OSC_TUNE_ACC<float>;
	}

	const float Oscillator::getFrequency() const
	{
		return m_frequency;
	}

	void Oscillator::setPhase(const float new_phase)
	{
		float temp;
		m_phase = abs(modf(new_phase, &temp));
	}

	const float Oscillator::getPhase() const
	{
		return m_phase;
	}

	void Oscillator::setWave(const Wave new_wave)
	{
		m_wave = new_wave;
	}

	const Oscillator::Wave Oscillator::getWave() const
	{
		return m_wave;
	}
}