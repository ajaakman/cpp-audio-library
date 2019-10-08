#pragma once

#include "./Component.h"

namespace audio
{
	class FilterLP final : public Component
	{
	public:
		FilterLP();
		~FilterLP() = default;
		FilterLP(const FilterLP&) = delete;
		FilterLP(FilterLP&&) = delete;
		FilterLP& operator=(const FilterLP&) = delete;
		FilterLP& operator=(FilterLP&&) = delete;

		virtual void CalcSample(std::array<float, CHANNELS<size_t>>& dSample) override;

		void SetCutoff(const float dNewCutoff);
		const float GetCutoff() const;
	private:
		std::array<float, CHANNELS<size_t>> m_dPrevSample;
		std::atomic<float> m_dCutoff;
	};
}
