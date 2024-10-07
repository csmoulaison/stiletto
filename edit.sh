SOURCE="src/*.c"
OUT="build/editor"

echo "Building editor (linux)"
gcc -o $OUT $SOURCE `sdl2-config --cflags --libs` -lSDL2_mixer -D __EDITOR__ -g
if [ $? -eq 0 ]; then
	echo "Build succeeded. Running editor..."
	(cd build && ./editor)
else
	echo "Build failed"
fi
