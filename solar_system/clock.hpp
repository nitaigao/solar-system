#include <sys/time.h>

typedef long long int64;
static  struct timeval start_time;

class ClockT
{
  
public:

  ClockT() 
    : last_time(0)
    { }
  
  float delta()
  {
     int64 now = time();
     float delta_time = (now - last_time) / 1000000.0;
     last_time = now;
     return delta_time;
  } 
 
  void init() 
  {
    gettimeofday(&start_time, NULL);
  }

private:

  int64 time() 
  {
    struct timeval t;
    gettimeofday(&t, NULL);
    return (int64) (t.tv_sec - start_time.tv_sec) * 1000000 + (t.tv_usec - start_time.tv_usec);
  }

private:
  
  int64 last_time;  
};
