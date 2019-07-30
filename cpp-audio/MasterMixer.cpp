#include "MasterMixer.h"

#include "Utilities.h"

namespace audio
{
	MasterMixer::MasterMixer(double* const& dTime)
		: m_dAmpTarget(0.0), m_dAmplitude(0.0)
	{ 	
		m_dTime = dTime;
	}

	void MasterMixer::CalcSample(double & dSample)
	{
		// Lerp the master amplitude before applying it to the final ouput to prevent audio clicks.	
		dSample *= Utilities::Lerp(m_dAmplitude, m_dAmpTarget, 0.0005, 0.0, 1.0);
		// Hard clip final output.
		dSample = Utilities::Clamp(dSample, -1.0, 1.0);
	}

	const bool MasterMixer::SetOutput(Component* const& newOutput)
	{
		return false;
	}

	const Component* const MasterMixer::GetOutput() const
	{
		return nullptr;
	}

	const double& MasterMixer::GetMasterOutput()
	{
		return FinalOutput();
	}	
	
	void MasterMixer::SetAmplitude(const double & dNewAmplitude)
	{
		m_dAmpTarget = Utilities::Clamp(dNewAmplitude, 0.0, 1.0);
	}

	const double& MasterMixer::GetAmplitude()
	{
		return m_dAmpTarget;
	}
}