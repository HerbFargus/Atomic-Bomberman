/**
 *
 * Classname / filename: Update / update.h
 *
 * Author: gm m
 *
 * Version: 0.1
 *
 */

/***************************************************************************
 *                                                                         *
 *   This program(class) is free software; you can redistribute it and/or  *
 *   modify it under the terms of the GNU General Public License as        *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/

#ifndef INPUT_UPDATE_H
#define INPUT_UPDATE_H

#include <functional>
using namespace std;

#include "input.h"
using input::Input;

#include <SDL/SDL.h>

namespace input
{
/**
 * Update
 */
    class Update : public unary_function < Input*, void >
    {
    public:
        explicit Update(const SDL_Event& event);

        typedef Input* PInput;
        void operator()(PInput& pInput);

    private:
        SDL_Event m_event;

    };
}

#endif // INPUT_UPDATE_H
