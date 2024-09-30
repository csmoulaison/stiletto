if [ "$1" = "em" ]; then
	bash ./build.sh
	if [ $? -eq 0 ]; then
		echo "Serving program via html..."
		emrun build/game.html
	fi
else
	bash ./build.sh
	if [ $? -eq 0 ]; then
		echo "Running program executable..."
		(cd build && ./stiletto)
	fi
fi
