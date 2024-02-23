/**
 * PCmd.h class
 *
 * class PCmd
 *
 * This class is derived from Parchis (responsible for instantiating
 * the BOARD, PLAYERS and RULES and connect them)
 * This class is responsible for playing in terminal mode, runs in
 * standalone mode.
 *
 * Created on September 2009.
 * Copyright (c) 2009 Luis Palacios
 * All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */


#ifndef PCMD_H
#define PCMD_H


// Forward declaration of classes
// class Parchis;
// class Game;

// My includes
#include "PDebug.h"
// #include "PParchis.h"

// Standard includes
#include <iostream>
#include <string>
//using namespace std;


/**
 * class PCmd
 *
 * This class is derived from Parchis (responsible for instantiating
 * the BOARD, PLAYERS and RULES and connect them)
 * This class is responsible for playing in terminal mode, runs in
 * standalone mode.
 *
 */

class PCmd : public PParchis
{

private:
    // DEBUGGING purposes
    /////////////////////////////////////////////////////////
    PDebug dbg;
    std::ostringstream oss;


    // PRIVATE ATTRIBUTES
    /////////////////////////////////////////////////////////
    int tossDice; // Stores the value of the dice being tossed


    // PRIVATE METHODS
    /////////////////////////////////////////////////////////
    void initAttributes(); // Initialize the attributes, called from Constructor
    void newTurn();        // Method to run when a new Turn happens at run()


public:
    // CONSTRUCTORS/DESTRUCTOR
    /////////////////////////////////////////////////////////
    PCmd();          // Constructor
    virtual ~PCmd(); // Destructor


    // PUBLIC METHODS
    /////////////////////////////////////////////////////////
    void run(
        int iNumGames); // Start a game and play it standalone till finished
};

#endif // PCMD_H
