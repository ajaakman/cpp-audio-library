#include "./Component.h"
#include "./MasterMixer.h"

namespace audio
{
	Component::Component(const MasterMixer& masterMixer)
		: m_time(masterMixer.getTimeRef()), m_output(nullptr), m_outSamples()
	{
		m_inputs.reserve(20);
	}

	Component::~Component()
	{
		// Remove component from output.
		if (m_output != nullptr)
		{
			m_output->removeInput(this);
		}
		// Remove component from inputs.
		std::for_each(m_inputs.begin(), m_inputs.end(),
			[](const auto& input) { input->setOutput(nullptr); });
	}

	const bool Component::addInput(Component* const input)
	{
		// Must not receive input from self.
		if (input == this) return false;
		// Prevent same input from being added multiple times.

		if (std::find(m_inputs.begin(), m_inputs.end(), input) != m_inputs.end())
		{
			return false;
		}

		m_inputs.push_back(input);
		return true;
	};

	const bool Component::removeInput(Component* const input)
	{
		// AddInput ensures the inputs are unique so we only need to remove the first one encountered.
				
		if (const auto it = std::find(m_inputs.begin(), m_inputs.end(), input); 
			it != m_inputs.end())
		{
			m_inputs.erase(it);
			return true;
		}

		return false;
	};

	const bool Component::setOutput(Component* const new_output)
	{
		// Must not output in to self.
		if (new_output == this) return false;
		// Remove component from old output.
		if (m_output != nullptr)
		{
			m_output->removeInput(this);
		}
		// Add component to new output.
		if (new_output != nullptr)
		{
			new_output->addInput(this);
		}

		m_output = new_output;
		return true;
	};

	const std::vector<Component*>& Component::getInputs() const
	{
		return m_inputs;
	}

	const Component* const Component::getOutput() const
	{
		return m_output;
	}

	float Component::getTime()
	{
		return static_cast<float>(m_time);
	}

	std::array<float, CHANNELS<size_t>>& Component::combineInputs()
	{
		std::fill(m_outSamples.begin(), m_outSamples.end(), 0.0f);

		for (const auto& input : m_inputs)
		{
			auto out = input->finalOutput();
			for (size_t i = 0; i < out.size(); ++i)
			{
				m_outSamples[i] += out[i];
			}
		}

		return m_outSamples;
	}

	const std::array<float, CHANNELS<size_t>>& Component::finalOutput()
	{
		combineInputs();
		writeSamples(m_outSamples);
		return m_outSamples;
	};
}