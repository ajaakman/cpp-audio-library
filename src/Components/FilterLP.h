#pragma once

#include "./Component.h"

namespace audio
{
	class FilterLP final : public Component
	{
	public:
		FilterLP();
		virtual void CalcSample(std::array<double, CHANNELS>& dSample) override;

		void SetCutoff(const double& dNewCutoff);
		const double& GetCutoff() const;
	private:
		std::array<double, CHANNELS> m_dPrevSample;
		double m_dCutoff;
	};
}
