#include "./Component.h"
#include <iostream>
namespace audio
{
	double* Component::m_dTime = nullptr;

	Component::Component()
		: m_Output(nullptr), m_dOutSample(0.0)
	{}

	Component::~Component()
	{
		// Remove component from output.
		if (m_Output != nullptr)
			m_Output->RemoveInput(this);
		// Remove component from inputs.
		for (const auto& input : m_Inputs)
			input->SetOutput(nullptr);
	}

	const bool Component::AddInput(Component* const& input)
	{
		// Must not receive input from self.
		if (input == this) return false;
		// Prevent same input from being added multiple times.
		for (const auto& in : m_Inputs)		
			if (in == input) return false;		
		
		m_Inputs.push_back(input);
		return true;
	};

	const bool Component::RemoveInput(Component* const& input)
	{
		// AddInput ensures the inputs are unique so we only need to remove the first one encountered.		
		const auto it = std::find(m_Inputs.begin(), m_Inputs.end(), input);
		if (it != m_Inputs.end())
		{
			m_Inputs.erase(it);
			return true;
		}

		return false;
	};

	const bool Component::SetOutput(Component* const& newOuput)
	{
		// Must not output in to self.
		if (newOuput == this) return false;
		// Remove component from old output. 
		if (m_Output != nullptr)
			m_Output->RemoveInput(this);
		// Add component to new output.
		if (newOuput != nullptr)
			newOuput->AddInput(this);

		m_Output = newOuput;
		return true;
	};

	const std::vector<Component*>& Component::GetInputs() const
	{
		return m_Inputs;
	}

	const Component* const Component::GetOutput() const
	{
		return m_Output;
	}

	const double& Component::SampleTime()
	{
		return *m_dTime;
	}	

	double& Component::CombineInputs()
	{
		m_dOutSample = 0.0;
		
		for (const auto& input : m_Inputs)		
			m_dOutSample += input->FinalOutput();
		
		return m_dOutSample;
	}

	const double& Component::FinalOutput()
	{
		CombineInputs();
		CalcSample(m_dOutSample);
		return m_dOutSample;
	};

}