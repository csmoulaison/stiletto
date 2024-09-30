#ifndef paths_h_INCLUDED
#define paths_h_INCLUDED

#ifdef __EMSCRIPTEN__

// Textures paths
#define PATH_ATLAS "textures/atlas.bmp"
#define PATH_ICON "textures/icon.bmp"
// Sound paths
#define PATH_SOUND_SELECT "sounds/select.wav"

#else

// Textures paths
#define PATH_ATLAS "resources/textures/atlas.bmp"
#define PATH_ICON "resources/textures/icon.bmp"
// Sound paths
#define PATH_SOUND_SELECT "resources/sounds/select.wav"

#endif

#endif // paths_h_INCLUDED
