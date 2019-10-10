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

		virtual const bool setOutput(Component* const new_output);

	protected:
		virtual const bool addInput(Component* const input);
		virtual const bool removeInput(Component* const input);
		virtual const std::vector<Component*>& getInputs() const;
		virtual const Component* const getOutput() const;

		static const float getTime();

	private:
		// writeSamples() runs for every audio sample and should assign a new value to the dSample input parameter variable.
		virtual void writeSamples(std::array<float, CHANNELS<size_t>>& samples) = 0;

		friend class MasterMixer;

		const std::array<float, CHANNELS<size_t>>& finalOutput();
		std::array<float, CHANNELS<size_t>>& combineInputs();

	private:
		static double* m_time;
		std::array<float, CHANNELS<size_t>> m_outSamples;

		std::vector<Component*> m_inputs; // TODO. Change to stack allocated array.
		Component* m_output; // TODO. Make Atomic.
	};
}