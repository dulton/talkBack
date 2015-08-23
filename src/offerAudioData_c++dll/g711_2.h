#ifndef G711_2_H
#define G711_2_H
#if 0
unsigned char
Snack_Lin2Alaw(
    short		pcm_val);	/* 2's complement (16-bit range) */

short
Snack_Alaw2Lin(
    unsigned char	a_val);

unsigned char
Snack_Lin2Mulaw(
    short		pcm_val);	/* 2's complement (16-bit range) */


short
Snack_Mulaw2Lin(
    unsigned char	u_val);


/* A-law to u-law conversion */
unsigned char
alaw2ulaw(
    unsigned char	aval);

unsigned char
ulaw2alaw(
    unsigned char	uval);
#else
unsigned char linear2alaw(int		pcm_val);	/* 2's complement (16-bit range) */
int alaw2linear(unsigned char	a_val);

unsigned char linear2ulaw(int pcm_val);	/* 2's complement (16-bit range) */
int ulaw2linear(unsigned char	u_val);

unsigned char alaw2ulaw(unsigned char	aval);
unsigned char ulaw2alaw(unsigned char	uval);

#endif
#endif // G711_2_H
