// v0.1 by gm (created)

#include "powerupdata.h"

PowerupData::PowerupData()
{
    reset();
}

PowerupData::~PowerupData()
{

}

void
PowerupData::reset()
{
    m_nTriggerBombs = 0;
    m_tbombIDs.clear();
}

void
PowerupData::set_trigger_bombs(int number)
{
    m_nTriggerBombs = number;
}

void
PowerupData::inc_trigger_bombs(int offset)
{
    m_nTriggerBombs += offset;
}

int
PowerupData::trigger_bombs() const
{
    return m_nTriggerBombs;
}

void
PowerupData::add_bomb_id (UINT bomb_id)
{
    m_tbombIDs.push_back(bomb_id);
}

UINT
PowerupData::remove_next_bomb_id()
{
    if (m_tbombIDs.size() > 0)
    {
        UINT id = m_tbombIDs.front();
        m_tbombIDs.pop_front();
        return id;
    }
    else
    {
        return 0;
    }
}
