#pragma once

#include "./Component.h"

namespace audio
{
	class MasterMixer final : public Component
	{
	public:
		MasterMixer(double* const& dTime);

		virtual void CalcSample(double& dSample) override;
		virtual const bool SetOutput(Component* const& newOutput) override;
		virtual const Component* const GetOutput() const override;
		const double& GetMasterOutput();

		void SetAmplitude(const double& dNewAmplitude);
		const double& GetAmplitude();

	private:
		double m_dAmplitude;
		double m_dAmpTarget;
	};
}
