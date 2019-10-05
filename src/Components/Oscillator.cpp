#include "./Oscillator.h"

#include "../Utilities.h"

#include <math.h>

namespace audio
{
	Oscillator::Oscillator(const float& dFrequency, const float& dAmplitude)
		: m_dFrequency(0.0f), m_dAmplitude(0.0f), m_dPhase(0.0f), m_Wave(Sine)
	{
		SetFrequency(dFrequency);
		SetAmplitude(dAmplitude);
	}

	void Oscillator::CalcSample(std::array<float, CHANNELS> & dSample)
	{
		const float sine = sin(m_dFrequency * TWO_PI<float> * SampleTime() + (m_dPhase * TWO_PI<float>));
		float wave = 0.0f;
		switch (m_Wave)
		{
		case audio::Oscillator::Sine:
			wave = sine;
			break;
		case audio::Oscillator::Square:
			wave = signbit(sine);
			break;
		case audio::Oscillator::Triangle:
			wave = asin(sine) * TWO_OVER_PI<float>;
			break;
		case audio::Oscillator::Saw:
			wave = -2.0f / PI<float> * atan(1.0f / tan(m_dFrequency * SampleTime() * PI<float> + (m_dPhase * PI<float>)));
			break;
		case audio::Oscillator::Noise:
			wave = 2.0f * (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) - 1.0f;
			break;
		default:
			break;
		}

		for (size_t i = 0; i < dSample.size(); i++)
		{
			dSample[i] += wave;
			dSample[i] *= m_dAmplitude;
		}
	}

	void Oscillator::SetAmplitude(const float& dNewAmplitude)
	{
		m_dAmplitude = Utilities::Clamp(dNewAmplitude, 0.0f, 1.0f);
	}

	const float& Oscillator::GetAmplitude() const
	{
		return m_dAmplitude;
	}

	void Oscillator::SetFrequency(const float& dNewFrequency)
	{
		m_dFrequency = Utilities::Clamp(dNewFrequency, 0.0f, 20000.0f);
	}

	const float& Oscillator::GetFrequency() const
	{
		return m_dFrequency;
	}

	void Oscillator::SetPhase(const float& dNewPhase)
	{
		float temp;
		m_dPhase = abs(modf(dNewPhase, &temp));
	}

	const float& Oscillator::GetPhase() const
	{
		return m_dPhase;
	}

	void Oscillator::SetWave(const Wave& newWave)
	{
		m_Wave = newWave;
	}

	const Oscillator::Wave& Oscillator::GetWave() const {
		return m_Wave;
	}
}