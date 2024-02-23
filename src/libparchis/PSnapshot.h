/**
 *  @class  PSnapshot PSnapshot.h "PSnapshot.h"
 *  @brief  Parchis Class: Represents the overall status of the Game
 *
 *  Belongs to the Library: "Parchis Engine C++ library"
 *
 *  @author  Luis Palacios
 *  @version 0.1
 *  @date    8/Sep/09
 *
 *  @par Description
 *
 *  Class that represents the overall status of the Game and can
 *  be used by Robots to make its calculations.
 *
 *  This class represents the Snapshot of Pawn in the current turn,
 *  for example, can eat, is eatable, can move, its coleagues are
 *  in danger, etc... It is used by Game to inform the Robots
 *  (at every turn) about the actual rationale, situation
 *  and conditions of each Pawn at the board in the current turn.
 *  This will allow the robots to make their decisions
 *
 */

#ifndef SNAPSHOT_H
#define SNAPSHOT_H

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#pragma mark ====== DEFINES

//---------------------------------------------------------------------------

#define NUM_STATES 45 // Maximum number of states analysed by the robots

//---------------------------------------------------------------------------

#pragma mark ====== INCLUDES

//---------------------------------------------------------------------------

// My Includes
#include "PDebug.h"

// Standard includes
#include <iostream>
#include <map>
#include <sstream>
#include <string>

//---------------------------------------------------------------------------


#pragma mark ====== CLASS PSnapshot

//---------------------------------------------------------------------------

class PSnapshot
{

#pragma mark ====== PRIVATE INSTANCE MEMBERS
private:
    // DEBUGGING purposes

    PDebug dbg;             //!< To be able to send Log messages
    std::ostringstream oss; //!< Construct complex strings

    // PRIVATE ATTRIBUTES

    std::string name; //!< Name assigned to this object
    int iStates
        [NUM_STATES]; //!< Array of integers to store each of the states values.
    std::map<int, std::string>
        sStates; //!< Associate each of the "states" with a string


#pragma mark ====== PRIVATE INSTANCE METHODS

    // PRIVATE METHODS

    void initAttributes();             // Initialize the attributes
    void setName(std::string new_var); // Set the name assigned to this object


#pragma mark ====== PUBLIC INSTANCE METHODS
public:
    // CONSTRUCTOR/DESTRUCTOR

    PSnapshot(std::string new_var); // Constructors/Destructors
    virtual ~PSnapshot();           // Destructor


    // PUBLIC METHODS

    std::string getName(); // Get the name of the object
    void setState(int new_state, int new_value);
    int getState(int new_index);
    void showState();
    void init();


    //! PUBLIC STATES
    /*! More detailed description of the information or states stored in the snapshot */
    enum States
    {
        sNumPawnsMovable, /*!<  Number of pawns that are movable */
        sNumPawnsCanEat,  /*!<  Number of pawns that can eat */
        cv_movable,       /*!<  I'm movable */
        cv_eatable,       /*!<  I'm eatable at my current position */
        cv_colleagueEatable, /*!<  Colleague is threatend at his position (can be eated in a future turn) */
        cv_atStart,          /*!<  I'm at my SPACE_START space */
        cv_colleagueAtStart, /*!<  Colleague is at his SPACE_START space */
        cv_atRamp,           /*!<  I'm in one of the spaces of the final Ramp */
        cv_colleagueAtRamp,  /*!<  Colleague is at the Ramp */
        cv_atRampSafe,       /*!<  I'm in the safe just before my ramp */
        cv_colleagueAtRampSafe, /*!<  Colleague is at safe just before the ramp */
        cv_enemyAtMyRampSafe, /*!<  For future implementation: enemy is at my ramp safe */
        cv_destinationIsSafe, /*!<  If I move, then I go into a Safe */
        cv_colleagueDestinationIsSafe, /*!<  If Colleague moves, then he goes into a Safe */
        cv_destinationIsRamp, /*!<  If I move, then I go into the Ramp */
        cv_colleagueDestinationIsRamp, /*!<  If Colleague moves, then he goes into the Ramp */
        cv_eat,              /*!<  I do eat with the current tossed dice */
        cv_colleagueEats,    /*!<  Colleague eats with current tossed dice */
        cv_destinationFinal, /*!<  If I move, then I go into the Final space */
        cv_colleagueDestinationFinal, /*!<  If colleague moves, then he goes into the Final space */
        cv_destinationRampSafe, /*!<  If I move then I go into the Ramp Safe space */
        cv_colleagueDestinationRampSafe, /*!<  If colleague moves then he goes into the Ramp Safe space */
        cv_aloneAtEnemyStart, /*!<  I'm alone at enemy's start space. It's no yet a threat :-) */
        cv_colleagueAloneAtEnemyStart, /*!<  Colleague is alone at enemy's start space. */
        cv_atEnemyStartLast, /*!<  I'm at enemy's start paired with someone else, and I was the last one to arrive. Enemy eats me with a 5. */
        cv_colleagueAtEnemyStartLast, /*!<  Colleague is at enemy's start paired with someone else, but colleague was last to arrive, so threatened. */
        cv_atEnemyStartFirst, /*!<  I'm at enemy's start paired with someone else, but I was first to arrive, so no threat */
        cv_colleagueAtEnemyStartFirst, /*!<  Colleague at enemy's start paired with someone else, but he was first to arrive, so no threat */
        cv_atNormal,                   /*!<  I'm in a normal space */
        cv_colleagueAtNormal,          /*!<  Colleague is in a normal space */
        cv_destinationCreatesBarrier, /*!<  If I move, then I create a barrier */
        cv_colleagueDestinationCreatesBarrier, /*!<  If my colleague moves, then he creates a barrier */
        cv_movingBreaksSafeBarrier, /*!<  If I move then I break my own barrier in a Safe space. */
        cv_colleagueMovingBreaksSafeBarrier, /*!<  If colleague moves then he breaks his barrier in a Safe Space */
        cv_destinationEatable, /*!<  If I move to my destination then I'll be exposed. */
        cv_colleagueDestinationEatable, /*!<  If colleague moves then he will get exposed. */
        cv_leavesSafe, /*!<  If I move then I leave a Safe space */
        cv_destinationLeavesDanger, /*!<  If I move then I run away from a dangerous situation */
        cv_colleagueDestinationLeavesDanger, /*!<  If my colleague moves then he leaves a dangerous situation */
        cv_atQ4, /*!<  I'm actually at Q4 quadrant (last 25% of my path to the Final space) */
        cv_colleagueAtQ4, /*!<  Colleague is actually at Q4 quadrant */
        cv_destinationThreatsEnemy, /*!<  If I move then I'll threatened an enemy */
        /*!<  Make another one but without movin, so inform "If I don't move do I threat an enemy?" */
        cv_colleagueDestinationThreatsEnemy, /*!<  If colleague moves then he'll threatened an enemy */
        cv_movingBreaksNormalBarrier, /*!<  If I move then I'll break a normal barrier (a barrier that is not in a Safe space) */
        cv_colleagueMovingBreaksNormalBarrier /*!<  If I colleague moves then he'll break a normal barrier (a barrier that is not in a Safe space) */
    };
};

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#endif // SNAPSHOT_H
