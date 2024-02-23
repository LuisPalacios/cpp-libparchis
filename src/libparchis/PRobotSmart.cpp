
/**
 *  @class  PRobotSmart PRobotSmart.cpp "PRobotSmart.cpp"
 *  @file   PRobotSmart.cpp
 *  @brief  Parchis Class: Derived from "Player", smarter robot decides based on weights.
 *
 *  ---------------------------------------------------------------------------
 */


//---------------------------------------------------------------------------

#include "PPlayer.h"

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Static Attributes


/**
 *  Table of weight's with the value assigned to each of them
 */
const int PRobotSmart::weight[NUM_STATES] = {
    2, // cv_movable;                                  // I'm movable
    3, // cv_eatable;                                  // I'm eatable at my current position
    1, // cv_colleagueEatable;                         // Colleague is threatend at his position (can be eated in a future turn)
    0, // cv_atStart;                                  // I'm at my SPACE_START space
    1, // cv_colleagueAtStart;                         // Colleague is at his SPACE_START space
    2, // cv_atRamp;                                   // I'm in one of the spaces of the final Ramp
    1, // cv_colleagueAtRamp;                          // Colleague is at the Ramp
    0, // cv_atRampSafe;                               // I'm in the safe just before my ramp
    2, // cv_colleagueAtRampSafe;                      // Colleague is at safe just before the ramp
    2, // cv_enemyAtMyRampSafe;                        // For future implementation: enemy is at my ramp safe
    2, // cv_destinationIsSafe;                        // If I move, then I go into a Safe
    1, // cv_colleagueDestinationIsSafe;               // If Colleague moves, then he goes into a Safe
    2, // cv_destinationIsRamp;                        // If I move, then I go into the Ramp
    1, // cv_colleagueDestinationIsRamp;               // If Colleague moves, then he goes into the Ramp
    3, // cv_eat;                                      // I do eat with the current tossed dice
    1, // cv_colleagueEats;                            // Colleague eats with current tossed dice
    2, // cv_destinationFinal;                         // If I move, then I go into the Final space
    1, // cv_colleagueDestinationFinal;                // If colleague moves, then he goes into the Final space
    3, // cv_destinationRampSafe;                      // If I move then I go into the Ramp Safe space
    1, // cv_colleagueDestinationRampSafe;             // If colleague moves then he goes into the Ramp Safe space
    1, // cv_aloneAtEnemyStart;                        // I'm alone at enemy's start space. It's no yet a threat :-)
    2, // cv_colleagueAloneAtEnemyStart;               // Colleague is alone at enemy's start space.
    2, // cv_atEnemyStartLast;                         // I'm at enemy's start paired with someone else, and I was the last one to arrive. Enemy eats me with a 5.
    1, // cv_colleagueAtEnemyStartLast;                // Colleague is at enemy's start paired with someone else, but colleague was last to arrive, so threatened.
    -1, // cv_atEnemyStartFirst;                        // I'm at enemy's start paired with someone else, but I was first to arrive, so no threat
    1, // cv_colleagueAtEnemyStartFirst;               // Colleague at enemy's start paired with someone else, but he was first to arrive, so no threat
    2, // cv_atNormal;                                 // I'm in a normal space
    0, // cv_colleagueAtNormal;                        // Colleague is in a normal space
    2, // cv_destinationCreatesBarrier;                // If I move, then I create a barrier
    1, // cv_colleagueDestinationCreatesBarrier;       // If my colleague moves, then he creates a barrier
    -1, // cv_movingBreaksSafeBarrier;                  // If I move then I break my own barrier in a Safe space.
    2, // cv_colleagueMovingBreaksSafeBarrier;         // If colleague moves then he breaks his barrier in a Safe Space
    -1, // cv_destinationEatable;                       // If I move to my destination then I'll be exposed.
    2, // cv_colleagueDestinationEatable;              // If colleague moves then he will get exposed.
    -1, // cv_leavesSafe;                               // If I move then I leave a Safe space
    3, // cv_destinationLeavesDanger;                  // If I move then I run away from a dangerous situation
    1, // cv_colleagueDestinationLeavesDanger;         // If my colleague moves then he leaves a dangerous situation
    2, // cv_atQ4;                                     // I'm actually at Q4 quadrant (last 25% of my path to the Final space)
    1, // cv_colleagueAtQ4;                            // Colleague is actually at Q4 quadrant
    2, // cv_destinationThreatsEnemy;                  // If I move then I'll threatened an enemy
    // Make another one but without movin, so inform "If I don't move do I threat an enemy?"
    1, // cv_colleagueDestinationThreatsEnemy;         // If colleague moves then he'll threatened an enemy
    0, // cv_movingBreaksNormalBarrier;                // If I move then I'll break a normal barrier (a barrier that is not in a Safe space)
    2 // cv_colleagueMovingBreaksNormalBarrier        // If I colleague moves then he'll break a normal barrier (a barrier that is not in a Safe space)
};


//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Private Methods
#pragma mark-- Private: Class initialization

/**
 * Initialize the attributes and create all instances
 */
void PRobotSmart::initAttributes()
{
    dbg.setCallerName("Smart  ");
    dbg.printF(4,
               "|  Constructor RobotSmart %-8s, idx(%2d)          |",
               getName().c_str(),
               getIndex());
    this->setType(PLAYER_ROBOT_SMART);
}

//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Public Methods
#pragma mark-- Public Constructor/Destructor

//---------------------------------------------------------------------------

/**
 * Constructor of PRobotSmart
 *
 * It will default to name="PRobotSmart" and Index=0
 */
PRobotSmart::PRobotSmart() : PPlayer()
{
    setName("RSmart");
    setIndex(0);
    initAttributes();
}

//---------------------------------------------------------------------------

/**
 * Constructor of PRobotSmart
 *
 * Constructor of the PRobotSmart with the option to assign parameters
 *
 * @param new_name The name you want to assign to this instance.
 * @param new_index Id of the Player, is the index in the allocated array of Players
 * @param new_dice Pointer PDice* to the dice assigned to this player
 */
PRobotSmart::PRobotSmart(std::string new_name, int new_index, PDice *new_dice)
    : PPlayer(new_name, new_index, new_dice)
{
    initAttributes();
}

//---------------------------------------------------------------------------

/**
 * Destructor of PRobotSmart
 *
 */
PRobotSmart::~PRobotSmart()
{
    dbg.printF(4,
               "|  Destructor del Robot: %-8s                        |",
               getName().c_str());
}

//---------------------------------------------------------------------------

#pragma mark-- Public methods overriden

//---------------------------------------------------------------------------

/**
 * This method overloads the one from the Base class "Player". Here, the derived class "RobotSimple",
 * implements its specific inteligence to determine which Pawns this robot decides to move.
 *
 * @param snap is a pointer to the PSnapshot of the game for this robot to decide which pawn to move
 * @return the pointer to the PPawn that this Robot has decided to move
 */
PPawn *PRobotSmart::getPawnToMove(PSnapshot **snap)
{
    int r, i;
    int canMove = 0;
    int sumas[4] = {0, 0, 0, 0};
    int nmax = 0;   // Fichas con valor máximo de suma
    int max = -100; // Máxima suma devuelta por el vector

    // Analize which Pawn to move only if I'm passed a valid Snapshot
    if (snap != (PSnapshot **)NULL)
    {

        // Analize each Pawn
        for (i = 0; i < PBoard::pawnsPerPlayer(); i++)
        {

            // Sum of "weight's" for this Pawn
            sumas[i] = 0;

            // Is this pawn movable?
            if (pawns[i]->canMove())
            {
                canMove++;

                // Sum each weight for all the "states" where its value == 1
                for (int n = 0, x = PSnapshot::cv_movable;
                     x <= PSnapshot::cv_colleagueMovingBreaksNormalBarrier;
                     x++, n++)
                {
                    // Only sum where state > 0
                    if (snap[i]->getState(x) > 0)
                    {
                        sumas[i] += weight[n];
                    }
                }

                // Special cases where I influence the sum :-)
                // BARRIER AT HOME START: Subtrac -1
                if (snap[i]->getState(PSnapshot::cv_atStart) &&
                    snap[i]->getState(PSnapshot::cv_movingBreaksSafeBarrier))
                {
                    sumas[i]--;
                }

                oss.str("");
                oss << pawns[i]->getName() << "| suma: " << sumas[i];
                dbg.print(3, oss.str());
            }
            else
            {

                // Pawn is not movable, so ficticious very negative sum of weight's.
                sumas[i] = -100;
            }
        }

        // Now that I have all the sum's of weight's, let's find which one is the highest
        max = sumas[0];
        for (i = 0; i < PBoard::pawnsPerPlayer(); i++)
        {
            if (sumas[i] > max)
            {
                max = sumas[i];
            }
        }


        // Clean all sum's lower than the maximum value
        for (i = 0; i < PBoard::pawnsPerPlayer(); i++)
        {
            if (sumas[i] == max)
            {
                nmax++;
            }
        }

        // If I have move than 1 pawn with the same maximum value, then use the random
        if (nmax > 1)
        {
            r = (rand() % nmax);
            for (i = 0; i < PBoard::pawnsPerPlayer(); i++)
            {
                if (sumas[i] == max && (r-- == 0))
                {
                    return (pawns[i]);
                }
            }
        }
        else
        {

            // We got a winner !!
            for (i = 0; i < PBoard::pawnsPerPlayer(); i++)
            {
                if (sumas[i] == max)
                {
                    return (pawns[i]);
                }
            }
        }
    }

    // Should never happen because getPawnToMove() is called when
    // the Player has at least one Pawn that can be moved.
    oss.str("");
    oss << "WARNING: " << getName() << " getPawnToMove() returns NULL";
    dbg.print(3, oss.str());
    return ((PPawn *)NULL);
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
