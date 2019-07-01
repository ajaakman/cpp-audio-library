#pragma once

#include <SDL.h>
#include "IAudio.h"

class SDL2Audio : public IAudio
{
public:

	virtual int StartAudio() override
	{
		if (SDL_Init(SDL_INIT_AUDIO) != 0) {
			SDL_Log("Unable to initialize SDL: %s.", SDL_GetError());
			return 101;
		}

		SDL_AudioSpec specin;
		SDL_AudioSpec specout;

		SDL_memset(&specin, 0, sizeof(specin));
		SDL_memset(&specout, 0, sizeof(specout));

		specin.channels = 1;
		specin.freq = 44100;
		specin.format = AUDIO_S16SYS;
		specin.samples = 4096;
		specin.callback = MyAudioCallback;

		device = SDL_OpenAudioDevice(NULL, 0, &specin, &specout, 0);

		if (!device)
		{
			SDL_Log("Failed to initialize audio device!!! %s.", SDL_GetError());
			return 102;
		}

		if (specin.freq != specout.freq)
		{
			SDL_Log("Requested fequency {%i} does not match received frequency: {%i}.", specin.freq, specout.freq);
			return 103;
		}

		if (specin.format != specout.format)
		{
			SDL_Log("Requested format does not match received format");
			return 104;
		}

		if (specin.channels != specout.channels)
		{
			SDL_Log("Requested channels {%i} does not match received channels: {%i}.", specin.channels, specout.channels);
			return 105;
		}

		if (specin.silence != specout.silence)
		{
			SDL_Log("Requested silence {%i} does not match received silence: {%i}.", specin.silence, specout.silence);
			return 106;
		}

		if (specin.samples != specout.samples)
		{
			SDL_Log("Requested samples {%i} does not match received samples: {%i}.", specin.samples, specout.samples);
			return 107;
		}

		if (specin.callback != specout.callback)
		{
			SDL_Log("Requested callback does not match received callback.");
			return 108;
		}

		if (specin.userdata != specout.userdata)
		{
			SDL_Log("Requested userdata does not match received userdata.");
			return 109;
		}

		SDL_PauseAudioDevice(device, 0);

		return 0;
	}

	void SetAmplitude(double newAmplitude)
	{
		if (newAmplitude > 1.0)	newAmplitude = 1.0;
		else if (newAmplitude < 0.0) newAmplitude = 0.0;

		SDL_LockAudioDevice(device);
		dAmpSlider = newAmplitude;
		SDL_UnlockAudioDevice(device);
	}

	double GetAmplitude()
	{
		return dAmpSlider;
	}

private:

	static void MyAudioCallback(void* userdata, Uint8* stream, int streamLength)
	{
		for (int i = 0; i < streamLength / 2; ++i)
		{
			if (dAmplitude < dAmpSlider - dSmoothingFactor || dAmplitude > dAmpSlider + dSmoothingFactor)
				dAmplitude += dAmplitude < dAmpSlider ? dSmoothingFactor : -dSmoothingFactor;

			if (dAmplitude < dSmoothingFactor) dAmplitude = 0.0;
			else if (dAmplitude > 1.0 - dSmoothingFactor) dAmplitude = 1.0;

			((Sint16*)stream)[i] = Sint16(sin(440.0 * 6.28318530 * dTime) * 32767.0 * dAmplitude);
			dTime += 1.0 / 44100.0;
		}
	}

public:

private:
	static double dTime;
	static double dAmpSlider;
	static double dAmplitude;
	static double dSmoothingFactor;
	SDL_AudioDeviceID device = NULL;

};
