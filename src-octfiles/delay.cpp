#include <stdio.h>

#include <chrono>
#include <ctime>

#include <octave/oct.h>

DEFUN_DLD (delay, args, /* nargout */,
"USAGE: delay (OPT)\n"
"   OPT = 0 : nanosleep\n"
"   OPT = 1 : octave::sleep (0.2, true)\n"
"   OPT = 2 : octave::sleep (0.2, false)\n"
)
{
  int nargin = args.length ();

  int option = 0;
  if (nargin == 1)
    {
      option = args(0).int_value ();
    }

  octave_value_list retval;

  using namespace std::chrono;

  int n = 100;
  int delay = 200;
  double delay_s = double (delay) / 1000;

  time_t tv_sec = 0;
  long tv_nsec = delay * 1000000;
  struct timespec delay_timespec;
  delay_timespec.tv_sec = tv_sec;
  delay_timespec.tv_nsec = tv_nsec;

  struct timespec rem;

  if (option == 1)
    {
      printf ("Using octave::sleep (%f, true)\n", delay_s);
    }
  else if (option == 2)
    {
      printf ("Using octave::sleep (%f, false)\n", delay_s);
    }
  else
    {
      printf ("Using nanosleep (&delay_timespec, &rem);\n");
    }

  int dot_was_last = 0;
  for (int i = 0; i < n; i++)
    {
      high_resolution_clock::time_point t0 = high_resolution_clock::now();

      if (option == 1)
        {
          octave::sleep (delay_s, true);
        }
      else if (option == 2)
        {
          octave::sleep (delay_s, false);
        }
      else
        {
          nanosleep (&delay_timespec, &rem);
        }

      high_resolution_clock::time_point t1 = high_resolution_clock::now();
      duration<double> time_span = duration_cast<duration<double> >(t1 - t0);
      double elapsed_s = time_span.count();

      if (elapsed_s > delay_s * 2)
        {
          if (dot_was_last)
            printf ("\n");
          printf ("Step %4d: elapsed = %f\n", i, elapsed_s);
          dot_was_last = 0;
        }
      else 
        {
          printf (".");
          fflush (0);
          dot_was_last = 1;
        }
    }
    printf ("\n");

  return retval;
}
