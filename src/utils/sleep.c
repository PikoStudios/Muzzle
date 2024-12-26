#include "utils/sleep.h"

#ifdef MUZZLE_SLEEP_USE_NANOSLEEP
	#include <time.h>
#endif

void mz_sleep(float seconds)
{
	if (seconds <= 0.f)
	{
		return;
	}

#ifdef MUZZLE_SLEEP_USE_NANOSLEEP
	struct timespec ts = (struct timespec){.tv_nsec = seconds * 1000000000L};
	nanosleep(&ts, NULL);
#else
	double end = glfwGetTime() + seconds;
	while (glfwGetTime() < end) {}
#endif
}

void mz_sleep_ms(int milliseconds)
{
	if (milliseconds <= 0)
	{
		return;
	}
	
#ifdef MUZZLE_SLEEP_USE_NANOSLEEP
	struct timespec ts = (struct timespec){.tv_nsec = milliseconds * 1000000L};
	nanosleep(&ts, NULL);
#else
	double end = glfwGetTime() + (milliseconds / 1000.f);
	while (glfwGetTime() < end) {}
#endif
}
