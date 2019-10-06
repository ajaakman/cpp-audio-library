#pragma once

#include "./Component.h"

namespace audio
{
	class FilterLP final : public Component
	{
	public:
		FilterLP();
		virtual void CalcSample(std::array<float, CHANNELS<size_t>>& dSample) override;

		void SetCutoff(const float& dNewCutoff);
		const float& GetCutoff() const;
	private:
		std::array<float, CHANNELS<size_t>> m_dPrevSample;
		float m_dCutoff;
	};
}
