#include <config.h>
#include <time.h>
#include <stdio.h>
#include <ctime>
#include <chrono>

extern "C"
int main (int argc, char *argv[]) {
	using namespace std::chrono;

	int n = 100;
	int delay = 200;

    time_t tv_sec = 0;
    long tv_nsec = delay * 1000000;
    struct timespec delay_timespec;
    delay_timespec.tv_sec = tv_sec;
    delay_timespec.tv_nsec = tv_nsec;

    struct timespec rem;

	for (int i = 0; i < n; i++) {
		high_resolution_clock::time_point t0 = high_resolution_clock::now();
		nanosleep (&delay_timespec, &rem);
		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		duration<double> time_span = duration_cast<duration<double> >(t1 - t0);

		printf ("Step %4d: elapsed = %f\n", i, time_span.count());
	}
}
