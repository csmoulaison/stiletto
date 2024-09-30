#include "audio.h"

#include "paths.h"
#include <stdio.h>

void audio_init(AudioContext* audio) {
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 1024);

	load_sound(&audio->sound_select, PATH_SOUND_SELECT);
}

void load_sound(Sound* sound, const char* path) {
	sound->audio = Mix_LoadWAV(PATH_SOUND_SELECT);
}

void play_sound(Sound* sound) {
	Mix_PlayChannel(-1, sound->audio, 0);
}
