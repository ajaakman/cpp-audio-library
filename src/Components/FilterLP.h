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

		virtual void writeSamples(std::array<float, CHANNELS<size_t>>& samples) override;

		void setCutoff(const float new_cutoff);
		const float getCutoff() const;
	private:
		std::array<float, CHANNELS<size_t>> m_prev_samples;
		std::atomic<float> m_cutoff;
	};
}
