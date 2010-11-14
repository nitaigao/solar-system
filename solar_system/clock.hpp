#ifndef CLOCK_HPP_DZSZC4DU
#define CLOCK_HPP_DZSZC4DU

#pragma comment "Included"

//#include <SDL/SDL.h>

float last_ticks = 0.0f;

float start_ticks()
{
  //SDL_Init(SDL_INIT_TIMER);
  //return SDL_GetTicks();
}

float get_ticks()
{
  return SDL_GetTicks();
}

float loop_delta()
{
  if (last_ticks == 0.0f)
  {
    last_ticks = start_ticks();
  }
  
  float ticks = get_ticks();
  float delta = (ticks - last_ticks) / 1000.0f;
  last_ticks = ticks;
  return delta;
}

#endif /* end of include guard: CLOCK_HPP_DZSZC4DU */
