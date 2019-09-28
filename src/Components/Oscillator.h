#pragma once

#include "./Component.h"

namespace audio
{
	class Oscillator : public Component
	{
	public:
		Oscillator(const double& dFrequency, const double& dAmplitude);

		enum Wave {Sine, Square, Triangle, Saw, Noise};

		virtual void CalcSample(double & dSample) override;

		void SetAmplitude(const double& dNewAmplitude);
		const double& GetAmplitude() const;
		void SetFrequency(const double& dNewFrequency);
		const double& GetFrequency() const;
		void SetPhase(const double& dNewPhase);
		const double& GetPhase() const;
		void SetWave(const Wave& newWave);
		const Wave& GetWave() const;

	private:
		Wave m_Wave;
		double m_dFrequency;
		double m_dAmplitude;
		double m_dPhase;
	};
}

