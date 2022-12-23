#ifndef _ADPCM_H_
#define _ADPCM_H_

void encode(short *indata, char *outdata, int len);
void decode(short *indata, char *outdata, int len);
#endif
