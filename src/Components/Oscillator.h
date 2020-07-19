#pragma once

#include "./Component.h"

namespace audio
{
	class Oscillator final : public Component
	{
	public:
		Oscillator(const MasterMixer& masterMixer);
		~Oscillator() = default;
		Oscillator(const Oscillator&) = delete;
		Oscillator(Oscillator&&) = delete;
		Oscillator& operator=(const Oscillator&) = delete;
		Oscillator& operator=(Oscillator&&) = delete;

		enum Wave { Sine, Square, Triangle, Saw, Noise };

		virtual void writeSamples(std::array<float, CHANNELS<size_t>>& samples) override;

		void setAmplitude(const float new_amplitude);
		const float getAmplitude() const;
		void setFrequency(const float new_frequency);
		const float getFrequency() const;
		void setPhase(const float new_phase);
		const float getPhase() const;
		void setWave(const Wave new_wave);
		const Wave getWave() const;
	private:
		const float sineWave();

	private:
		std::atomic<Wave> m_wave;
		std::atomic<float> m_frequency;
		std::atomic<float> m_amplitude;
		std::atomic<float> m_phase;
	};
}
