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

	void Oscillator::CalcSample(double& dSample)
	{
		const double sine = sin(m_dFrequency * 2.0 * acos(-1.0) * SampleTime() + (m_dPhase * 2.0 * acos(-1.0)));
		switch (m_Wave)
		{
		case audio::Oscillator::Sine:
			dSample += sine;
			break;
		case audio::Oscillator::Square:
			dSample += signbit(sine);
			break;
		case audio::Oscillator::Triangle:
			dSample += asin(sine) * 2.0 / acos(-1.0);
			break;
		case audio::Oscillator::Saw:
			dSample += -2 / acos(-1.0) * atan(1.0 / tan(m_dFrequency * SampleTime() * acos(-1.0) + (m_dPhase * acos(-1.0))));
			break;
		case audio::Oscillator::Noise:
			dSample += 2.0 * ((double)rand() / (double)RAND_MAX) - 1.0;
			break;
		default:
			break;
		}
		dSample *= m_dAmplitude;
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