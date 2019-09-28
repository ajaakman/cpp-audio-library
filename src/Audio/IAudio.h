#pragma once

namespace audio
{
	class IAudio
	{
	public:
		virtual ~IAudio() {};
		virtual const int InitAudio() = 0;
		virtual void LockAudioThread() = 0;
		virtual void UnlockAudioThread() = 0;
	};
}
