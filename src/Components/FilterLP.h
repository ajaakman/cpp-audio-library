#pragma once

#include "./Component.h"

namespace audio
{
	class FilterLP : public Component
	{
	public:
		FilterLP();
		virtual void CalcSample(double& dSample) override;

		void SetCutoff(const double& dNewCutoff);
		const double& GetCutoff() const;
	private:
		double m_dPrevSample;
		double m_dCutoff;
	};

}

