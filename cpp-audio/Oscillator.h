#pragma once

#include "Component.h"

namespace audio
{
	class Oscillator : public Component
	{
	public:
		Oscillator(const double& dFrequency, const double& nAmplitude);

		virtual void CalcSample(double & dSample) override;

		void SetAmplitude(const double& dNewAmplitude);
		const double& GetAmplitude() const;
		void SetFrequency(const double& dNewFrequency);
		const double& GetFrequency() const;

	private:
		double m_dFrequency;
		double m_dAmplitude;
	};
}

