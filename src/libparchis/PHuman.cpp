
/**
 *  @class  PHuman PHuman.cpp "PHuman.cpp"
 *  @file   PHuman.cpp
 *  @brief  Parchis Class: Derived from PPlayer, represents a Human player..
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
void PHuman::initAttributes()
{

    dbg.setCallerName("Human  ");

    this->setType(PLAYER_HUMAN);
    dbg.printF(4,
               "|  Constructor Human %-8s, idx(%2d)               |",
               getName().c_str(),
               getIndex());
}

//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Public Methods
#pragma mark-- Public Constructor/Destructor

//---------------------------------------------------------------------------

/**
 * Constructor of PHuman
 *
 * It will default to name="Human" and Index=0
 */
PHuman::PHuman() : PPlayer()
{
    setName("Human");
    setIndex(0);
    initAttributes();
}

//---------------------------------------------------------------------------

/**
 * Constructor of PHuman
 *
 * Constructor of the PHuman with the option to assign parameters
 *
 * @param new_name The name you want to assign to this instance.
 * @param new_index Id of the Player, is the index in the allocated array of Players
 * @param new_dice Pointer PDice* to the dice assigned to this player
 */
PHuman::PHuman(std::string new_name, int new_index, PDice *new_dice)
    : PPlayer(new_name, new_index, new_dice)
{
    initAttributes();
}

//---------------------------------------------------------------------------

/**
 * Destructor of PHuman
 *
 */
PHuman::~PHuman()
{
    oss.str("");
    oss << "|  Destructor for HUMAN '" << getName() << "'' called";
    dbg.print(4, oss.str());
}

//---------------------------------------------------------------------------

#pragma mark-- Public methods

//---------------------------------------------------------------------------

/**
 * This method overloads the one from the Base class "Player". Here, the derived class "Human",
 * should get the input from the Human about which Pawns decides to move.
 *
 *  @par NOTE about implementations:
 *  @verbatim

    In QT (qtPFormImpl.cpp) this method is not called, so never used.

    In Cocoa (PENDING)
 @endverbatim
 *
 * @return NULL. As of today this method is not called.
 */
PPawn *PHuman::getPawnToMove()
{

    // Not used, so it would allways return NULL
    return ((PPawn *)NULL);
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
