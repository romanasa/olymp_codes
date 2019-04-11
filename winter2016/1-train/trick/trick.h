#ifndef _TRICK_H
#define _TRICK_H

#ifdef __cplusplus
extern "C" {
#endif

void Initialize();
void Assistant(int r, int n, int *hand, int *cards);
int Magician(int n, int assistant1[2], int assistant2[2]);

#ifdef __cplusplus
}
#endif

#endif // _TRICK_H
