#include <errno.h>
#include <stdio.h>

#if defined(__MINGW32__)
#define EWOULDBLOCK EAGAIN
#endif

int main()
{
	const int err = EWOULDBLOCK;
	errno = err;
	perror("EWOULDBLOCK");
	return 0;
}
