#include "./MasterMixer.h"

#include "../Utilities.h"

namespace audio
{
	MasterMixer::MasterMixer(double* const& dTime)
		: m_dAmpTarget(0.0f), m_dAmplitude(0.0f)
	{
		m_dTime = dTime;
	}

	void MasterMixer::CalcSample(std::array<float, CHANNELS<size_t>> & dSample)
	{
		for (size_t i = 0; i < dSample.size(); ++i)
		{
			// Lerp the master amplitude before applying it to the final ouput to prevent audio clicks.
			dSample[i] *= Utilities::Lerp(m_dAmplitude, m_dAmpTarget, 0.0005f, 0.0f, 1.0f);
		}
	}

	const bool MasterMixer::SetOutput(Component* const& newOutput)
	{
		return false;
	}

	const Component* const MasterMixer::GetOutput() const
	{
		return nullptr;
	}

	const std::array<float, CHANNELS<size_t>> & MasterMixer::GetMasterOutput()
	{
		return FinalOutput();
	}

	void MasterMixer::SetAmplitude(const float& dNewAmplitude)
	{
		m_dAmpTarget = std::clamp(dNewAmplitude, 0.0f, 1.0f);
	}

	const float& MasterMixer::GetAmplitude()
	{
		return m_dAmpTarget;
	}
}