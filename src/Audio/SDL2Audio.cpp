#include "./SDL2Audio.h"

namespace audio
{
    int processAudio(void* ptr)
    {
        SDL_SetThreadPriority(SDL_THREAD_PRIORITY_HIGH);
        SDL2Audio* const& parent = reinterpret_cast<SDL2Audio*>(ptr);

        // TODO. Add exit condition.
        while (!parent->m_shuttingDown)
        {
            if (parent->m_audioReadyFlag)
            {
                SDL_CondWait(parent->cvAudioThreadReady, parent->mtxAudioLock);
            }

            for (size_t i = 0; i < parent->m_buffer.size(); i += CHANNELS<size_t>)
            {
                auto out = parent->masterMixer.getMasterOutput();

                for (size_t j = 0; j < CHANNELS<size_t>; j++)
                {
                    parent->m_buffer[i + j] = out[j];
                }

                parent->m_time += 1.0 / SAMPLE_RATE<double>;

                if (parent->m_time > OSC_TUNE_ACC<double>)
                {
                    double intpart;
                    parent->m_time = modf(parent->m_time, &intpart);
                }
            }

            parent->m_audioReadyFlag = true;
            SDL_CondSignal(parent->cvAudioThreadReady);
        }
        return 0;
    }

	SDL2Audio::SDL2Audio()
		: masterMixer(&m_time)
        , m_device(NULL)
        , m_buffer{ 0 }
        , m_time(0.0f)
        , m_audioReadyFlag(false)
        , m_shuttingDown(false)
	{	}

	SDL2Audio::~SDL2Audio()
	{
        // Mark audio thread for shutdown and wait for it to finish.
        m_shuttingDown = true;

        int threadReturnValue;
        SDL_WaitThread(audioThread, &threadReturnValue);

        SDL_PauseAudioDevice(m_device, 1);

        SDL_Log("Audio thread returned value: %d", threadReturnValue);                

        SDL_DestroyCond(cvAudioThreadReady);
        SDL_DestroyMutex(mtxAudioLock);

        SDL_CloseAudioDevice(m_device);

		SDL_QuitSubSystem(SDL_INIT_AUDIO);
		SDL_Quit();
	}

	const int SDL2Audio::initAudio()
	{
		if (SDL_Init(SDL_INIT_AUDIO) != 0)
		{
			SDL_Log("Unable to initialize SDL: %s.", SDL_GetError());
			return 101;
		}

		SDL_AudioSpec specin;
		SDL_AudioSpec specout;

		SDL_memset(&specin, 0, sizeof(specin));
		SDL_memset(&specout, 0, sizeof(specout));

		specin.channels = CHANNELS<Uint8>;
		specin.freq = SAMPLE_RATE<int>;
		specin.format = AUDIO_F32;
		specin.samples = BUFFER_SIZE<Uint16>;
		specin.userdata = this;
		specin.callback = forwardAudioCallback;

		m_device = SDL_OpenAudioDevice(NULL, 0, &specin, &specout, 0);

		if (!m_device)
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

        cvAudioThreadReady = SDL_CreateCond();
        mtxAudioLock = SDL_CreateMutex();

        audioThread = SDL_CreateThread(audio::processAudio, "AudioThread", (void*)this);

        if (audioThread == NULL) {
            SDL_Log("SDL_CreateThread failed: %s\n", SDL_GetError());
            return 110;
        }

        if (!m_audioReadyFlag)
        {
            SDL_CondWait(cvAudioThreadReady, mtxAudioLock);
        }
        SDL_PauseAudioDevice(m_device, 0);

		return 0;
	}

	void SDL2Audio::lockAudioThread()
	{
		SDL_LockAudioDevice(m_device);
	}

	void SDL2Audio::unlockAudioThread()
	{
		SDL_UnlockAudioDevice(m_device);
	}

	void SDL2Audio::forwardAudioCallback(void* const userdata, Uint8* const stream, const int stream_length)
	{
		static_cast<SDL2Audio*>(userdata)->audioCallback(stream, stream_length);
	}

	void SDL2Audio::audioCallback(Uint8* const& stream, const int& stream_length)
	{
        if (!m_audioReadyFlag)
        {
            SDL_Log("Warning: Poor Audio Performance!!!");
            SDL_CondWait(cvAudioThreadReady, mtxAudioLock);
        }

		SDL_memcpy(stream, &m_buffer[0], stream_length);

        m_audioReadyFlag = false;
        SDL_CondSignal(cvAudioThreadReady);
	}
}
