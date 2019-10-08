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

		void SetAmplitude(const float dNewAmplitude);
		const float GetAmplitude() const;
		void SetFrequency(const float dNewFrequency);
		const float GetFrequency() const;
		void SetPhase(const float dNewPhase);
		const float GetPhase() const;
		void SetWave(const Wave newWave);
		const Wave GetWave() const;
	private:
		const float SineWave() const;

	private:
		std::atomic<Wave> m_Wave;
		std::atomic<float> m_dFrequency;
		std::atomic<float> m_dAmplitude;
		std::atomic<float> m_dPhase;
	};
}
