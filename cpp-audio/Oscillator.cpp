#include "Oscillator.h"

#include "Utilities.h"

#include <math.h>

namespace audio
{
	Oscillator::Oscillator(const double& dFrequency, const double& dAmplitude)
		: m_dFrequency(0), m_dAmplitude(0.0)
	{
		SetFrequency(dFrequency);
		SetAmplitude(dAmplitude);
	}

	void Oscillator::CalcSample(double & dSample)
	{
		dSample += sin(m_dFrequency * 2.0 * acos(-1.0) * SampleTime());
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
}