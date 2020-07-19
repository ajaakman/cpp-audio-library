#pragma once

#include "./Component.h"

namespace audio
{
	class MasterMixer final : public Component
	{
	public:
		MasterMixer(const double& time);
		~MasterMixer() = default;
		MasterMixer(const MasterMixer&) = delete;
		MasterMixer(MasterMixer&&) = delete;
		MasterMixer& operator=(const MasterMixer&) = delete;
		MasterMixer& operator=(MasterMixer&&) = delete;

        const double& getTimeRef() const { return m_globalTime; }

		virtual void writeSamples(std::array<float, CHANNELS<size_t>>& samples) override;
		virtual const bool setOutput(Component* const new_output) override;
		const std::array<float, CHANNELS<size_t>>& getMasterOutput();
		const std::array<std::atomic<bool>, CHANNELS<size_t>>& isOutClipping();

		void setAmplitude(const float new_amplitude);
		const float getAmplitude();
	protected:
		virtual const Component* const getOutput() const override;
	private:
		void setChannelClip(size_t channel, bool value);

	private:
		float m_amplitude;
        const double& m_globalTime;
		std::atomic<float> m_amp_target;
		std::array<std::atomic<bool>, CHANNELS<size_t>> m_channel_clip;
		std::array<unsigned, CHANNELS<size_t>> m_clip_timer;
	};
}
