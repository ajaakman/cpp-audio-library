#include "./Oscillator.h"

#include "../Utilities.h"

#include <math.h>

namespace audio
{
	Oscillator::Oscillator(const double& dFrequency, const double& dAmplitude)
		: m_dFrequency(0), m_dAmplitude(0.0), m_dPhase(0.0), m_Wave(Sine)
	{
		SetFrequency(dFrequency);
		SetAmplitude(dAmplitude);
	}

	void Oscillator::CalcSample(std::array<double, CHANNELS> & dSample)
	{
		const double sine = sin(m_dFrequency * TWO_PI<double> * SampleTime() + (m_dPhase * TWO_PI<double>));
		double wave = 0.0;
		switch (m_Wave)
		{
		case audio::Oscillator::Sine:
			wave = sine;
			break;
		case audio::Oscillator::Square:
			wave = signbit(sine);
			break;
		case audio::Oscillator::Triangle:
			wave = asin(sine) * TWO_OVER_PI<double>;
			break;
		case audio::Oscillator::Saw:
			wave = -2 / PI<double> * atan(1.0 / tan(m_dFrequency * SampleTime() * PI<double> + (m_dPhase * PI<double>)));
			break;
		case audio::Oscillator::Noise:
			wave = 2.0 * ((double)rand() / (double)RAND_MAX) - 1.0;
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

	void Oscillator::SetAmplitude(const double& dNewAmplitude)
	{
		m_dAmplitude = Utilities::Clamp(dNewAmplitude, 0.0, 1.0);
	}

	const double& Oscillator::GetAmplitude() const
	{
		return m_dAmplitude;
	}

	void Oscillator::SetFrequency(const double& dNewFrequency)
	{
		m_dFrequency = Utilities::Clamp(dNewFrequency, 0.0, 20000.0);
	}

	const double& Oscillator::GetFrequency() const
	{
		return m_dFrequency;
	}

	void Oscillator::SetPhase(const double& dNewPhase)
	{
		double temp;
		m_dPhase = abs(modf(dNewPhase, &temp));
	}

	const double& Oscillator::GetPhase() const
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