/**
 * PCmd.cpp class.
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
 * Extends Parchis in Standalone mode
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

#include "PCmd.h"
#include <math.h>


/**
 * class PCmd
 *
 * This class is derived from Parchis (responsible for instantiating
 * the BOARD, PLAYERS and RULES and connect them)
 * This class is responsible for playing in terminal mode, runs in
 * standalone mode.
 *
 */


// ======================================================
//
// PRIVATE METHODS
//
// ======================================================


/**
 *
 * initAttributes()
 *
 * Initialize the attributes, called from the Constructor
 *
 */
void PCmd::initAttributes()
{
    // Debug purposes
    dbg.setCallerName("PCmd   ");
    dbg.print(3, "Constructor PCmd");
}


// ======================================================
//
// PUBLIC METHODS
//
// ======================================================


// CONSTRUCTOR/DESTRUCTOR
/////////////////////////////////////////////////////////
PCmd::PCmd() : PParchis()
{
    initAttributes();
}
PCmd::~PCmd()
{
}


// PUBLIC METHODS
/////////////////////////////////////////////////////////
/**
 * run()
 *
 * Start the game and play it standalone till finished
 */
void PCmd::run(int iNumGames)
{
    int i;
    int stat[4] = {0, 0, 0, 0};
    double percentage[4];
    PGame *g = board->getGame(); // The game
    int sum = 0;

    // Set the option that start games with 2 pawns already out on START
    g->setOptionStartTwoOut(true);

    for (int i = 0; i < iNumGames; i++)
    {

        dbg.print(3, "PCmd starts running");

        // Start a new Game
        dbg.print(1, "Starting a new game");
        g->newGame();
        tossDice = 0;
        // Main loop that controls a selfplayed game
        while (g->isRunning() && g->getNumColorWinner() < 0)
        {

            // PLAYER HAS FINISHED ??
            // If this player has finished (all its pawns are at "Final space")
            // then we change the turn and continue
            if (g->isPlayerFinished())
            {
                newTurn();
                continue;
            }

            // GAME CONTROL
            // Ask the "game" to Toss the Dice and process it
            g->playerTossDice(tossDice);
            tossDice = 0;

            // THIRD SIX ??
            // If player got 3x6's then I represent an animation sending its
            // last moved pawn to it Home.
            if (g->isFlagThirdSix())
            {

                // Send last Pawn moved home
                g->sendLastMovedHome();

                // If animation enabled then animate return home
                // this.animaLaVueltaACasa();

                // Change turn
                newTurn();

                // continue
                continue;
            }

            // EXECUTE THE RULES
            // Check the rules engine, which will determine the movable pawns,
            // which ones can eat, etc.
            dbg.print(
                2,
                "| Checking the rules                                     |");
            g->execRules();


            // NO MOVABLE PAWNS ??
            // If we don't have any movable pawns, then ask to change the turn and continue
            if (!g->movablePawns())
            {
                // Change the turn
                newTurn();
                // continue
                continue;
            }

            // ASK ROBOT TO SELECT PAWN AND MOVE IT
            g->selectPawn();
            g->movePawn();

            // Change turn
            newTurn();
        }

        // Statistics
        // cout << "Rounds: " << g->getNumRound() << ". Num 3x6: " << g->getNumThreeSixes() << ". WINNER: " << g->getNumColorWinner() << endl;
        stat[g->getNumColorWinner()]++;

        // Sum the number of games played
        sum++;
        if ((sum % 10) == 0)
        {
            std::cout << ".";
            std::cout.flush();
        }
    }

    for (i = 0; i < 4; i++)
    {
        percentage[i] = (double)stat[i] / (double)sum;
    }
    std::cout << std::endl;
    std::cout << "Yellow: " << stat[0] << " (" << percentage[0] * 100 << "%)"
              << " "
              << "Blue:" << stat[1] << " (" << percentage[1] * 100 << "%)"
              << " "
              << "Red: " << stat[2] << " (" << percentage[2] * 100 << "%)"
              << " "
              << "Green: " << stat[3] << " (" << percentage[3] * 100 << "%)"
              << std::endl;
}


/**
 * newTurn()
 *
 * Ask the Game to change the turn
 */
void PCmd::newTurn()
{
    PGame *g = board->getGame();

    if (g->isRunning())
    {
        // Ask the game to change the turn. It will take care of pending count 10, 20 or
        // situations where turn doesn't change, as in a color moving 2 pawns out of home.
        bool changedTurn = g->newTurn();

        // If didn't change turn analyse the cause
        if (!changedTurn)
        {
            if (g->isFlagPawnEated())
            {
                // Force a dice of 20
                tossDice = 20;
            }
            if (g->isFlagPawnGotFinal())
            {
                // Force a dice of 10
                tossDice = 10;
            }
            if (g->isFlagTwoGoOutHome())
            {
                // Force a dice of 5 again.
                tossDice = 5;
            }
            //            if ( g->getLastDice() == 6 ) {
            //                dbg.print(3, "Player plays again");
            //            }
        }
    }
}
