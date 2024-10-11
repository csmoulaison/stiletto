#ifndef dialogue_h_INCLUDED
#define dialogue_h_INCLUDED

#define MAX_MSG_CHARS 128
#define MAX_DIALOGUE_MSGS 8

struct {
	char string[MAX_MSG_CHARS];
} Message;

struct {
	Message messages[MAX_DIALOGUE_MSGS];
	uint8_t messages_len;
	uint8_t current_message;
	uint8_t current_message_char;
} typedef Dialogue;

void update_dialogue(Dialogue* dialogue, DrawContext* draw, AudioContext* audio, Input* input, double dt);

#endif // dialogue_h_INCLUDED
