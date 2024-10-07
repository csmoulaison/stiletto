SOURCE="src/*.c"

LEVEL_PATH="build/resources/levels/@resources/levels"
TEXTURE_PATH="build/resources/textures/@resources/textures"
SOUND_PATH="build/resources/sounds/@resources/sounds"
SAVE_INIT_PATH="build/resources/save/@resources/save"

if [ "$1" = "em" ]; then
	echo "Building program (emscripten)"
	OUT="build/game.html"
	emcc -o $OUT $SOURCE -sUSE_SDL=2 -sUSE_SDL_MIXER=2 --embed-file=$TEXTURE_PATH --embed-file=$SOUND_PATH --embed-file=$LEVEL_PATH -- embed-file=$SAVE_INIT_PATH -D __EMSCRIPTEN__
	if [ $? -eq 0 ]; then
		echo "Build succeeded"
	else
		echo "Build failed"
	fi
else
	echo "Building program (linux)"
	OUT="build/stiletto"
	gcc -o $OUT $SOURCE `sdl2-config --cflags --libs` -lSDL2_mixer -g
	if [ $? -eq 0 ]; then
		echo "Build succeeded"
	else
		echo "Build failed"
	fi
fi
