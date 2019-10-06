#pragma once

#include "./Component.h"

namespace audio
{
	class MasterMixer final : public Component
	{
	public:
		MasterMixer(double* const& dTime);

		virtual void CalcSample(std::array<float, CHANNELS<size_t>>& dSample) override;
		virtual const bool SetOutput(Component* const& newOutput) override;
		virtual const Component* const GetOutput() const override;
		const std::array<float, CHANNELS<size_t>>& GetMasterOutput();

		void SetAmplitude(const float& dNewAmplitude);
		const float& GetAmplitude();

	private:
		float m_dAmplitude;
		float m_dAmpTarget;
	};
}
