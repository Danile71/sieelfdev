#ifndef _NOTIFY_H_
#define _NOTIFY_H_

void Play_Sound(const char * filename);

extern GBSTMR VibraTimer;
void StartVibra(GBSTMR*);
void StopVibra(GBSTMR*);

#endif
