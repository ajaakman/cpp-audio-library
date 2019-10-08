#pragma once

#include "./Component.h"

namespace audio
{
	class MasterMixer final : public Component
	{
	public:
		MasterMixer(double* const& dTime);
		~MasterMixer() = default;
		MasterMixer(const MasterMixer&) = delete;
		MasterMixer(MasterMixer&&) = delete;
		MasterMixer& operator=(const MasterMixer&) = delete;
		MasterMixer& operator=(MasterMixer&&) = delete;

		virtual void CalcSample(std::array<float, CHANNELS<size_t>>& dSample) override;
		virtual const bool SetOutput(Component* const newOutput) override;
		const std::array<float, CHANNELS<size_t>>& GetMasterOutput();
		const std::array<std::atomic<bool>, CHANNELS<size_t>>& IsOutClipping();

		void SetAmplitude(const float& dNewAmplitude);
		const float GetAmplitude();
	protected:
		virtual const Component* const GetOutput() const override;
	private:
		void SetChannelClip(size_t channel, bool value);

	private:
		float m_dAmplitude;
		std::atomic<float> m_dAmpTarget;
		std::array<std::atomic<bool>, CHANNELS<size_t>> m_bChannelClip;
		std::array<unsigned, CHANNELS<size_t>> m_bClipTimer;
	};
}
