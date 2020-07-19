emcc -std=c++17 \
src/Utilities.cpp \
src/API.cpp \
src/Components/*.cpp \
src/Audio/*.cpp \
-I src/Components \
-I src/Audio \
-s USE_SDL=2 \
-s USE_PTHREADS=1 \
-s PROXY_TO_PTHREAD=1 \
--bind \
-s WASM=1 \
-o "../react-audio/public/audio.js" \
-s ENVIRONMENT=web,worker \
-O3 \
-s ASSERTIONS=1