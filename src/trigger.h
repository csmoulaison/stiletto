#ifndef trigger_h_INCLUDED
#define trigger_h_INCLUDED

enum TriggerId {
	DEFAULT,
	UNLOCK_STILETTO
};

struct {
	TriggerId id;
	int16_t x;
	int16_t y;
	int16_t w;
	int16_t h;
} typedef Trigger;

void triggers_check(Trigger* triggers, uint8_t triggers_len, Ana* ana);

#endif // trigger_h_INCLUDED
