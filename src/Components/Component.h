#pragma once

#include "../Globals.h"

#include <vector>
#include <array>
#include <atomic>

namespace audio
{
	class Component
	{
	public:
		Component();
		virtual ~Component();
		Component(const Component&) = delete; // TODO
		Component(Component&&) = delete;
		Component& operator=(const Component&) = delete;
		Component& operator=(Component&&) = delete;

		virtual const bool SetOutput(Component* const newOuput);

	protected:
		virtual const bool AddInput(Component* const& input);
		virtual const bool RemoveInput(Component* const& input);
		virtual const std::vector<Component*>& GetInputs() const;
		virtual const Component* const GetOutput() const;

		static const float SampleTime();

	private:
		// CalcSample() runs for every audio sample and should assign a new value to the dSample input parameter variable.
		virtual void CalcSample(std::array<float, CHANNELS<size_t>>& dSample) = 0;

		friend class MasterMixer;

		const std::array<float, CHANNELS<size_t>>& FinalOutput();
		std::array<float, CHANNELS<size_t>>& CombineInputs();

	private:
		static double* m_dTime;
		std::array<float, CHANNELS<size_t>> m_OutSample;

		std::vector<Component*> m_Inputs; // TODO. Change to stack allocated array.
		Component* m_Output; // TODO. Make Atomic.
	};
}