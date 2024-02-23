
/**
 *  @class  PRobotSimple PRobotSimple.cpp "PPlPRobotSimpleayer.cpp"
 *  @file   PRobotSimple.cpp
 *  @brief  Parchis Class: derived from PPlayer. Simple robot that decides ramdomly
 *
 *  ---------------------------------------------------------------------------
 */


//---------------------------------------------------------------------------

#include "PPlayer.h"

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Private Methods
#pragma mark-- Private: Class initialization

/**
 * Initialize the attributes and create all instances
 */
void PRobotSimple::initAttributes()
{
    dbg.setCallerName("Simple ");
    this->setType(PLAYER_ROBOT_SIMPLE);
    dbg.printF(4,
               "|  Constructor RobotSimple %-8s, idx(%2d)             |",
               getName().c_str(),
               getIndex());
}

//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Public Methods
#pragma mark-- Public Constructor/Destructor

//---------------------------------------------------------------------------

/**
 * Constructor of PRobotSimple
 *
 * It will default to name="RobotSimple" and Index=0
 */
PRobotSimple::PRobotSimple() : PPlayer()
{
    setName("RSimple");
    setIndex(0);
    initAttributes();
}

//---------------------------------------------------------------------------

/**
 * Constructor of PRobotSimple
 *
 * Constructor of the PRobotSimple with the option to assign parameters
 *
 * @param new_name The name you want to assign to this instance.
 * @param new_index Id of the Player, is the index in the allocated array of Players
 * @param new_dice Pointer PDice* to the dice assigned to this player
 */
PRobotSimple::PRobotSimple(std::string new_name, int new_index, PDice *new_dice)
    : PPlayer(new_name, new_index, new_dice)
{
    initAttributes();
}

//---------------------------------------------------------------------------

/**
 * Destructor of PRobotSimple
 *
 */
PRobotSimple::~PRobotSimple()
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
PPawn *PRobotSimple::getPawnToMove(PSnapshot **snap)
{
    int r, i, x;
    int canMove = 0;

    if (snap != (PSnapshot **)NULL)
    {
        // Find out the number of movable pawns
        for (i = 0; i < PBoard::pawnsPerPlayer(); i++)
        {
            if (pawns[i]->canMove())
                canMove++;
        }
        dbg.printF(
            3,
            "|  Number of pawns I can move: %2d                        |",
            canMove);

        // Select the pawn pointer
        if (canMove != 0)
        {

            // This robot's intelligence is pretty low, it just uses random
            r = (rand() % canMove);

            // Fetch the pointer to the selected Pawn
            for (i = 0, x = 0; (x <= r) && (i < PBoard::pawnsPerPlayer()); i++)
            {
                if (pawns[i]->canMove())
                {
                    if (x == r)
                    {
                        dbg.printF(3,
                                   "|  Robot has selected pawn: %-8s           "
                                   "          |",
                                   pawns[i]->getName().c_str());
                        return (pawns[i]);
                    }
                    x++;
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
