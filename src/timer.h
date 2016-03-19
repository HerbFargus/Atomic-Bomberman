// v0.9  by gm, mm (created)
// v0.95 by gm (frame time restriction added)

#ifndef TIMER_H
#define TIMER_H

#include "typedefs.h"

class Timer
{
public:
    Timer ();
    virtual ~Timer ();

    /**
     * Zeit seit dem der Timer laeuft in seconds
     */
    double time();

    /**
     * Dauer des 'letzten' Frames in seconds
     * will not be greater than VAL_MAX_TIME_PER_FRAME
     */
    double frame_time();

    /**
     * muss vor jedem Frame aufgerufen werden
     */
    void refresh();

private:
    double  m_time;
    double   m_frame_time;
    UINT    m_last_ticks;
};

#endif // TIMER_H
