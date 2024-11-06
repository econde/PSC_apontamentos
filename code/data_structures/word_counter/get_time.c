#include <time.h>

unsigned get_time() {
	struct timespec time_point;
	timespec_get(&time_point, TIME_UTC);
	return time_point.tv_sec * 1000 + time_point.tv_nsec / 1000000;
}
