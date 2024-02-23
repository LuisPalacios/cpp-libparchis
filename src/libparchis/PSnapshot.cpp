/**
 *  @class  PSnapshot PSnapshot.cpp "PSnapshot.cpp"
 *  @file   PSnapshot.cpp
 *  @brief  Parchis Class: Represents the overall status of the Game
 *
 *  ---------------------------------------------------------------------------
 */


//---------------------------------------------------------------------------

#include "PSnapshot.h"

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Private Methods
#pragma mark-- Class initialization

//---------------------------------------------------------------------------

/**
 * Initialize the attributes and create all instances
 */
void PSnapshot::initAttributes()
{

    // Prepare debug
    dbg.setCallerName(name);
    dbg.print(4, "| Constructor Snapshot                                   |");

    // initialize
    this->init();

    // Strings for all the states
    sStates.operator[](sNumPawnsMovable) = "sNumPawnsMovable";
    sStates.operator[](sNumPawnsCanEat) = "sNumPawnsCanEat";
    sStates.operator[](cv_movable) = "cv_movable";
    sStates.operator[](cv_eatable) = "cv_eatable";
    sStates.operator[](cv_colleagueEatable) = "cv_colleagueEatable";
    sStates.operator[](cv_atStart) = "cv_atStart";
    sStates.operator[](cv_colleagueAtStart) = "cv_colleagueAtStart";
    sStates.operator[](cv_atRamp) = "cv_atRamp";
    sStates.operator[](cv_colleagueAtRamp) = "cv_colleagueAtRamp";
    sStates.operator[](cv_atRampSafe) = "cv_atRampSafe";
    sStates.operator[](cv_colleagueAtRampSafe) = "cv_colleagueAtRampSafe";
    sStates.operator[](cv_enemyAtMyRampSafe) = "cv_enemyAtMyRampSafe";
    sStates.operator[](cv_destinationIsSafe) = "cv_destinationIsSafe";
    sStates.operator[](cv_colleagueDestinationIsSafe) =
        "cv_colleagueDestinationIsSafe";
    sStates.operator[](cv_destinationIsRamp) = "cv_destinationIsRamp";
    sStates.operator[](cv_colleagueDestinationIsRamp) =
        "cv_colleagueDestinationIsRamp";
    sStates.operator[](cv_eat) = "cv_eat";
    sStates.operator[](cv_colleagueEats) = "cv_colleagueEats";
    sStates.operator[](cv_destinationFinal) = "cv_destinationFinal";
    sStates.operator[](cv_colleagueDestinationFinal) =
        "cv_colleagueDestinationFinal";
    sStates.operator[](cv_destinationRampSafe) = "cv_destinationRampSafe";
    sStates.operator[](cv_colleagueDestinationRampSafe) =
        "cv_colleagueDestinationRampSafe";
    sStates.operator[](cv_aloneAtEnemyStart) = "cv_aloneAtEnemyStart";
    sStates.operator[](cv_colleagueAloneAtEnemyStart) =
        "cv_colleagueAloneAtEnemyStart";
    sStates.operator[](cv_atEnemyStartLast) = "cv_atEnemyStartLast";
    sStates.operator[](cv_colleagueAtEnemyStartLast) =
        "cv_colleagueAtEnemyStartLast";
    sStates.operator[](cv_atEnemyStartFirst) = "cv_atEnemyStartFirst";
    sStates.operator[](cv_colleagueAtEnemyStartFirst) =
        "cv_colleagueAtEnemyStartFirst";
    sStates.operator[](cv_atNormal) = "cv_atNormal";
    sStates.operator[](cv_colleagueAtNormal) = "cv_colleagueAtNormal";
    sStates.operator[](cv_destinationCreatesBarrier) =
        "cv_destinationCreatesBarrier";
    sStates.operator[](cv_colleagueDestinationCreatesBarrier) =
        "cv_colleagueDestinationCreatesBarrier";
    sStates.operator[](cv_movingBreaksSafeBarrier) =
        "cv_movingBreaksSafeBarrier";
    sStates.operator[](cv_colleagueMovingBreaksSafeBarrier) =
        "cv_colleagueMovingBreaksSafeBarrier";
    sStates.operator[](cv_destinationEatable) = "cv_destinationEatable";
    sStates.operator[](cv_colleagueDestinationEatable) =
        "cv_colleagueDestinationEatable";
    sStates.operator[](cv_leavesSafe) = "cv_leavesSafe";
    sStates.operator[](cv_destinationLeavesDanger) =
        "cv_destinationLeavesDanger";
    sStates.operator[](cv_colleagueDestinationLeavesDanger) =
        "cv_colleagueDestinationLeavesDanger";
    sStates.operator[](cv_atQ4) = "cv_atQ4";
    sStates.operator[](cv_colleagueAtQ4) = "cv_colleagueAtQ4";
    sStates.operator[](cv_destinationThreatsEnemy) =
        "cv_destinationThreatsEnemy";
    sStates.operator[](cv_colleagueDestinationThreatsEnemy) =
        "cv_colleagueDestinationThreatsEnemy";
    sStates.operator[](cv_movingBreaksNormalBarrier) =
        "cv_movingBreaksNormalBarrier";
    sStates.operator[](cv_colleagueMovingBreaksNormalBarrier) =
        "cv_colleagueMovingBreaksNormalBarrier";
}

//---------------------------------------------------------------------------

#pragma mark-- Setter

//---------------------------------------------------------------------------

/**
 * Set the value for "name"
 * @param new_var the new value for the attribute "name"
 */
void PSnapshot::setName(std::string new_var)
{
    name.assign(new_var);
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Public Methods
#pragma mark-- Constructor/Destructor

//---------------------------------------------------------------------------

/**
 * Constructor of PSnapshot
 *
 * @param new_var Name assigned to these rules
 */
PSnapshot::PSnapshot(std::string new_var)
{
    setName(new_var);
    initAttributes();
}

//---------------------------------------------------------------------------

/**
 * Destructor
 */
PSnapshot::~PSnapshot()
{
    dbg.print(4, "Destructor Snapshot");
}
//---------------------------------------------------------------------------


#pragma mark-- Getters and Setters

//---------------------------------------------------------------------------

/**
 * Get the name value
 * @return string with the name value
 */
std::string PSnapshot::getName()
{
    return name;
}

//---------------------------------------------------------------------------

/**
 * Sets one of the state to a new value
 *
 * @param new_state state to store in
 * @param new_value the value to use
 *
 */
void PSnapshot::setState(int new_state, int new_value)
{

    if (new_state >= (int)sStates.size())
    {
        if (dbg.getDebug())
        {
            oss.str("");
            oss << "WARNING: Snapshot::setStated(" << new_state << ", "
                << new_value << ") Called with new_state=" << new_state
                << " out of bounds.";
            dbg.print(1, oss.str());
        }
        return;
    }

    // Set the value
    iStates[new_state] = new_value;
}

//---------------------------------------------------------------------------

/**
 * gets one of the states
 * @return the numerical value
 */
int PSnapshot::getState(int new_index)
{
    return iStates[new_index];
}

//---------------------------------------------------------------------------

/**
 * Just for debug purposes, show the states values
 *
 */
void PSnapshot::showState()
{
    for (int i = 0; i < (int)sStates.size(); i++)
    {
        oss.str("");
        oss << "|  iStates[" << i << ":" << sStates[i] << "] = " << iStates[i];
        dbg.print(1, oss.str());
    }
}

//---------------------------------------------------------------------------

/**
 * Clears all the states
 */
void PSnapshot::init()
{
    // Debug information
    if (dbg.getDebug())
    {
        dbg.printF(4,
                   "|   Clearing all states for %-8s.                    |",
                   this->getName().c_str());
    }
    for (int i = 0; i < (int)sStates.size(); i++)
    {
        iStates[i] = 0;
    }
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
