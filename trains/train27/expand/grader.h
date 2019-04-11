#ifndef __grader_h__
#define __grader_h__

typedef struct
{
	int cnt;
	char c;
} request_t;

void solve(const char*, int, const request_t*, char*);

#endif
