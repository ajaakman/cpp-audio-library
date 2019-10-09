emcc -std=c++17 \
"src/Utilities.cpp" \
"src/API.cpp" \
"src/Components/FilterLP.cpp" \
"src/Components/MasterMixer.cpp" \
"src/Components/Oscillator.cpp" \
"src/Components/Component.cpp" \
"src/Audio/SDL2Audio.cpp" \
-s USE_SDL=2 \
--bind \
-s WASM=1 \
-o "../react-audio/public/audio.js" \
-s ENVIRONMENT=web \
-O3 \
-s ASSERTIONS=1