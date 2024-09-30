#ifndef audio_h_INCLUDED
#define audio_h_INCLUDED

#include <SDL_mixer.h>

struct {
	Mix_Chunk* audio;
} typedef Sound;

struct {
	Sound sound_select;
} typedef AudioContext;

void audio_init(AudioContext* audio);
void load_sound(Sound* sound, const char* path);
void play_sound(Sound* sound);

#endif // audio_h_INCLUDED
