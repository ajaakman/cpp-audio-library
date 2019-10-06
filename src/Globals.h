#pragma once

namespace audio
{
	template<typename T>
	constexpr T CHANNELS = T(2);
	
	template<typename T>
	constexpr T SAMPLE_RATE = T(44100);

	template<typename T>
	constexpr T BUFFER_SIZE = T(4096); // Must be power of 2.

	template<typename T>
	constexpr T PI = T(3.141592653589793238463L);

	template<typename T>
	constexpr T TWO_PI = T(6.283185307179586476926L);

	template<typename T>
	constexpr T TWO_OVER_PI = T(0.636619772367581343076L);

	template<typename T>
	constexpr T OSC_TUNE_ACC = T(10);
}