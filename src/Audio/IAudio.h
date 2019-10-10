#pragma once

namespace audio
{
	class IAudio
	{
	public:
		virtual ~IAudio() = default;
		virtual const int initAudio() = 0;
		virtual void lockAudioThread() = 0;
		virtual void unlockAudioThread() = 0;
	};
}
