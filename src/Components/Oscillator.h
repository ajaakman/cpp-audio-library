#pragma once

#include "./Component.h"

namespace audio
{
	class Oscillator final : public Component
	{
	public:
		Oscillator();
		~Oscillator() = default;
		Oscillator(const Oscillator&) = delete;
		Oscillator(Oscillator&&) = delete;
		Oscillator& operator=(const Oscillator&) = delete;
		Oscillator& operator=(Oscillator&&) = delete;

		enum Wave { Sine, Square, Triangle, Saw, Noise };

		virtual void CalcSample(std::array<float, CHANNELS<size_t>>& dSample) override;

		void SetAmplitude(const float& dNewAmplitude);
		const float& GetAmplitude() const;
		void SetFrequency(const float& dNewFrequency);
		const float& GetFrequency() const;
		void SetPhase(const float& dNewPhase);
		const float& GetPhase() const;
		void SetWave(const Wave& newWave);
		const Wave& GetWave() const;
	private:
		const float SineWave() const;

	private:
		Wave m_Wave;
		float m_dFrequency;
		float m_dAmplitude;
		float m_dPhase;
	};
}
