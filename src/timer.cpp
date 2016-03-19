// v0.9  by gm, mm (created)
// v0.95 by gm (frame time restriction added)

#include "timer.h"
#include "SDL/SDL.h"

#include "globals.h"
#include "valuelist.h"

Timer::Timer () :
    m_time(0),
    m_frame_time(0),
    m_last_ticks(SDL_GetTicks())
{

}

Timer::~Timer ()
{

}

void
Timer::refresh()
{
    UINT time = SDL_GetTicks();
    m_frame_time = (time - m_last_ticks) / 1000.0;
    m_last_ticks = time;

    double maxtime = Globals::values().get(VAL_MAX_TIME_PER_FRAME) / 1000.0;
    if (m_frame_time > maxtime)
        m_frame_time = maxtime;

    m_time += m_frame_time;
}

double
Timer::time()
{
    return m_time;
}

double
Timer::frame_time()
{
    return m_frame_time;
}
