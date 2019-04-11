#ifndef __GRADER_H__
#define __GRADER_H__

#ifdef __cplusplus
extern "C" {
#endif

int GetBestPosition(int, int, int, int *, int *, int *);

typedef int (*GetBestPositionFunction)(int, int, int, int *, int *, int *);

#ifdef __cplusplus
}
#endif

#endif /* __GRADER_H__ */
