
/**
 *  @class  PSpace PSpace.cpp "PSpace.cpp"
 *  @file   PSpace.cpp
 *  @brief  Parchis Class: represents each of the Spaces in the Parchis game
 *
 *  ---------------------------------------------------------------------------
 */


//---------------------------------------------------------------------------

#include "PSpace.h"

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Private Methods
#pragma mark-- Private: Class initialization

/**
 * Initialize the attributes and create all instances
 */
void PSpace::initAttributes()
{
    dbg.setCallerName("Space  ");
    dbg.printF(3,
               "|   %-8s (idx:%3d) Role: %2d (%-7s) Orient: %2d     |",
               getName().c_str(),
               getIndex(),
               getRole(),
               board->getColorName(getColor()),
               orientation);


    // This flag is only usefull if this space is a HOME space. Anyway set it to false allways.
    // Indicates if the player has used the option to get 2 pawns out of HOME with the first 5.
    bUsedFirstTwoGoOut = false;
    bCanGetOutOtherPawn = false;

    // Initialize attributes
    numPawns = 0;
}

//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Public Methods
#pragma mark-- Public Constructor/Destructor

//---------------------------------------------------------------------------

/**
 * Constructor of PSpace
 *
 * Creates a space instance, passing several parameters
 *
 * @param new_board is the pointer to the PBoard where this space will stay
 * @param new_name is the internal name assigned to this space
 * @param new_role is the role of this space
 * @param new_index represents the space id, it's the index inside the array of all space
 * @param new_num is the space number
 * @param new_color is the color this space belongs to
 * @param new_orientation is the orientation horizontal or veritcal of the space
 */
PSpace::PSpace(PBoard *new_board,
               std::string new_name,
               int new_role,
               int new_index,
               int new_num,
               int new_color,
               int new_orientation)
{
    board = new_board;

    // Set the name
    name.assign(new_name);

    // Set the Role
    role = new_role;
    if (role == PBoard::spaceTypeFinal() || role == PBoard::spaceTypeHome())
        this->setNumMaxPawns(PBoard::pawnsPerPlayer());
    else
        this->setNumMaxPawns(2);

    // Set the color
    color = new_color;

    // Set the Index
    index = new_index;

    // Set the number
    number = new_num;

    // Set the orientation
    if (new_orientation < SPACE_NOORIENTATION ||
        new_orientation > SPACE_VERTICAL)
        orientation = SPACE_NOORIENTATION;
    else
        orientation = new_orientation;

    initAttributes();
}

//---------------------------------------------------------------------------

/**
 * Destructor of the space
 *
 */
PSpace::~PSpace()
{
    dbg.printF(4,
               "|  Destructor Pspace: %-8s                           |",
               getName().c_str());
}

//---------------------------------------------------------------------------


#pragma mark-- General methods, getters and setters

//---------------------------------------------------------------------------

/**
 * Initilialize attributes because a new game has been requested
 */
void PSpace::newGame()
{
    this->bUsedFirstTwoGoOut = false;
}

//---------------------------------------------------------------------------

/**
 * For debugging purposes, shows information about this Space
 */
void PSpace::showInfo()
{
    unsigned int i;
    for (i = 0; i < vPawns.size(); i++)
    {
        dbg.printF(4,
                   "|   %-8s, position %d: %-8s                       |",
                   this->getName().c_str(),
                   i,
                   vPawns[i]->getName().c_str());
    }
}

//---------------------------------------------------------------------------

/**
 * Get the value of index
 * @return the value of index
 */
int PSpace::getIndex()
{
    return index;
}

//---------------------------------------------------------------------------

/**
 * Get the real number associated to this Space
 * @return the value of number
 */
int PSpace::getNumber()
{
    return number;
}

//---------------------------------------------------------------------------

/**
 * Get the value of name
 * @return the value of name
 */
std::string PSpace::getName()
{
    return name;
}


/**
 * setName()
 *
 * Set the value of name
 * @param new_name the value of name
 */
void PSpace::setName(std::string new_name)
{
    this->name.assign(new_name);
}

//---------------------------------------------------------------------------

/**
 * Get the value of color if any or nocolor
 * @return the value of color
 */
int PSpace::getColor()
{
    return color;
}

//---------------------------------------------------------------------------

/**
 * Get the value of orientation
 * @return int, value of orientation
 */
int PSpace::getOrientation()
{
    return orientation;
}

//---------------------------------------------------------------------------

/**
 * Get the value of role/type
 * @return the value of role
 */
int PSpace::getRole()
{
    return role;
}

//---------------------------------------------------------------------------

/**
 * Specify to which Quadrant (Q1-Q4) this space belongs
 * from the perspective of the color.
 * @param new_color specifies the color
 * @param new_var specifies the new_var
 */
void PSpace::setQuadrant(int new_color, int new_var)
{
    cQuadrant[new_color] = new_var;
}

//---------------------------------------------------------------------------

/**
 * Return which Quadrant (Q1-Q4) this space belongs
 * from the perspective of the color.
 *
 */
int PSpace::getQuadrant(int new_color)
{
    return cQuadrant[new_color];
}

//---------------------------------------------------------------------------

/**
 * Return information about the type of Space
 *
 * @return bool true if Horizontal, false otherwise
 */
bool PSpace::isHorizontal()
{
    if (orientation == SPACE_HORIZONTAL)
        return true;
    return false;
}

//---------------------------------------------------------------------------

/**
 * Return information about the type of Space
 *
 * @return bool true if Vertical, false otherwise
 */
bool PSpace::isVertical()
{
    if (orientation == SPACE_VERTICAL)
        return true;
    return false;
}

//---------------------------------------------------------------------------

/**
 * True is this Space is of type: NORMAL
 *
 * @return bool true or false
 */
bool PSpace::isNormal()
{
    if (this->getRole() == PBoard::spaceTypeNormal())
        return true;
    return false;
}

//---------------------------------------------------------------------------

/**
 * True is this Space is of type: SAFE, START or RAMPSAFE
 *
 * @return bool true or false
 */
bool PSpace::isSafe()
{
    if (this->getRole() == PBoard::spaceTypeSafe() ||
        this->getRole() == PBoard::spaceTypeStart() ||
        this->getRole() == PBoard::spaceTypeRampSafe())
        return true;
    return false;
}

//---------------------------------------------------------------------------

/**
 * True is this Space is of type: RAMP
 *
 * @return bool true or false
 */
bool PSpace::isRamp()
{
    if (this->getRole() == PBoard::spaceTypeRamp())
        return true;
    return false;
}

//---------------------------------------------------------------------------

/**
 * True is this Space is of type: FINAL
 *
 * @return bool true or false
 */
bool PSpace::isFinal()
{
    if (this->getRole() == PBoard::spaceTypeFinal())
        return true;
    return false;
}

//---------------------------------------------------------------------------

/**
 * True is this Space is of type: HOME
 *
 * @return bool true or false
 */
bool PSpace::isHome()
{
    if (this->getRole() == PBoard::spaceTypeHome())
        return true;
    return false;
}

//---------------------------------------------------------------------------

/**
 * True is this Space is of type: START
 *
 * @return bool true or false
 */
bool PSpace::isStart()
{
    if (this->getRole() == PBoard::spaceTypeStart())
        return true;
    return false;
}

//---------------------------------------------------------------------------

/**
 * True is this Space is of type: RAMPSAFE
 *
 * @return bool true or false
 */
bool PSpace::isRampSafe()
{
    if (this->getRole() == PBoard::spaceTypeRampSafe())
        return true;
    return false;
}


/**
 * isBarrier()
 *
 * Find out if we have a Barrier of two pawns same color in my space
 *
 * @return bool true if barrier exist or false otherwise
 */
bool PSpace::isBarrier()
{
    if (this->getNumPawns() == 2)
    {
        if (vPawns[0]->getColor() == vPawns[1]->getColor())
            return true;
    }
    return false;
}

//---------------------------------------------------------------------------

/**
 * Set the maximum number of Pawns allowed to reside in this space
 * @param new_var the new value for numMaxPawns
 */
void PSpace::setNumMaxPawns(int new_var)
{
    numMaxPawns = new_var;
}

//---------------------------------------------------------------------------

/**
 * Get the maximum number of Pawns allowd in my space
 * @return the value of numPawns
 */
int PSpace::getNumMaxPawns()
{
    return numMaxPawns;
}

//---------------------------------------------------------------------------

/**
 * Set the value of numPawns (number of Pawns in this space)
 * @param new_var the new value for numPawns
 */
void PSpace::setNumPawns(int new_var)
{
    numPawns = new_var;
}

//---------------------------------------------------------------------------

/**
 * Get the number of Pawns actually living in my space
 * @return the value of numPawns
 */
int PSpace::getNumPawns()
{
    return numPawns;
}

//---------------------------------------------------------------------------

/**
 * getPawn: get Pawn living in my Space
 * @param new_index is the index of the Pawn wanted inside the vector
 */
PPawn *PSpace::getPawn(int new_index)
{
    return vPawns[new_index];
}

//---------------------------------------------------------------------------

/**
 * Return the pawn that can be eated, which is any of
 * the pawns living in my space different from the one in the param.
 *
 * I start looking from the back of the stack, this will ensure the
 * case of eating the last one that arrived into my START when I'm
 * going out from home.
 *
 * @param new_pawn that eats
 * @return return the pawn eated
 */
PPawn *PSpace::getEatedPawn(PPawn *new_pawn)
{
    for (int i = (int)(vPawns.size() - 1); i >= 0; i--)
    {
        if (vPawns[i]->getColor() != new_pawn->getColor())
            return vPawns[i];
    }
    return (PPawn *)NULL;
}

//---------------------------------------------------------------------------

/**
 * Adds a new Pawn pointer to live in my space
 * @param new_pawn pointer to Pawn * that wants to enter my space
 * @return true if allowed or false if not
 */
bool PSpace::addPawn(PPawn *new_pawn)
{
    PSpace *fromSpace = new_pawn->getSpace();
    bool allowed = false;

    // If the Pawn is not assigned to any space then allow it
    if (fromSpace == (PSpace *)NULL)
    {
        allowed = true;
    }
    else
    {
        // If the Pawn is not already here then allow it
        if (fromSpace == this)
        {
            dbg.printF(3,
                       "|  %-8s can't add %-8s. It's already here        |  * "
                       "WARNING !!",
                       this->getName().c_str(),
                       new_pawn->getName().c_str());
        }
        else
        {
            allowed = true;
        }
    }

    // If the Pawn is Prohibited here, then do not allow it
    if (allowed)
    {
        if ((this->isFinal() || this->isHome() || this->isRamp()) &&
            (this->getColor() != new_pawn->getColor()))
            allowed = false;
    }

    // If allowed to be added to this space...
    if (allowed)
    {

        // If enough space, then allow it
        if (this->getNumPawns() < this->getNumMaxPawns())
        {

            // Add it and increment number of pawns here
            vPawns.push_back(new_pawn);
            this->numPawns++;
        }
        else
        {
            // If too many pawns, then mark it as not allowed
            allowed = false;
            oss.str("");
            oss << "WARNING: " << getName()
                << " can't add Pawn: " << new_pawn->getName()
                << ". Space is FULL.";
            dbg.print(3, oss.str());
        }
    }

    // Show debugging information
    showInfo();

    return allowed;
}

//---------------------------------------------------------------------------

/**
 * Remove a Pawn from my space
 * @param new_pawn pointer to Pawn * that needs to be removed
 * @return true if allowed or false if not
 */
bool PSpace::delPawn(PPawn *new_pawn)
{
    bool done = false;

    // If I don't have Pawns then return
    if (!this->getNumPawns())
        return done;

    // If I'm a HOME role and never used the "1st 5 get's two out" and the board
    // allows, then let's check if I need to set the flag.
    if (board->getGame()->isRunning())
    {
        if (this->isHome() && this->getNumPawns() == 4)
        {
            if (board->getGame()->canTwoGoOutHome())
            {
                if (!this->bUsedFirstTwoGoOut)
                {
                    this->bCanGetOutOtherPawn = true;
                    this->bUsedFirstTwoGoOut = true;
                    board->getGame()->setFlagTwoGoOutHome(true);
                }
            }
        }
    }

    // Go through the vector and erase the Pawn passed
    std::vector<PPawn *>::iterator iter = vPawns.begin();
    while (iter != vPawns.end())
    {
        if (*iter == new_pawn)
        {
            done = true;
            iter = vPawns.erase(iter);
            this->numPawns--;
        }
        else
        {
            ++iter;
        }
    }

    // Show debugging information
    showInfo();

    // Return
    return done;
}

//---------------------------------------------------------------------------

/**
 * Returns the Pawn position inside the Space.
 * @return integer value with the Pawns position (0-'n') or -1 if Pawn is not in this Space
 */
int PSpace::getPawnPosition(PPawn *new_pawn)
{
    int ret = -1;

    // If I don't have Pawns then return
    if (!this->getNumPawns())
        return ret;

    // Go through the vector and return index when Pawn found
    std::vector<PPawn *>::iterator iter = vPawns.begin();
    int i = 0;

    // Find out where is this pawn
    while (iter != vPawns.end())
    {
        if (*iter == new_pawn)
        {
            ret = i;
            break;
        }
        else
        {
            ++iter;
            ++i;
        }
    }

    // Return
    return ret;
}

//---------------------------------------------------------------------------

/**
 * Returns what will be the position of this inside this Space if moved here
 * @return integer value with the Pawns position (0-'n') or -1 if Pawn cannot be moved here
 */
int PSpace::getPawnWillBePosition(PPawn *new_pawn)
{
    int ret = -1;

    // If already here, don't look anymore, and return current position
    if ((ret = getPawnPosition(new_pawn)) == -1)
    {

        // It's not here, so lets look for its future position

        // If it's NOT allowed here, then return -1.
        if ((this->isFinal() || this->isHome() || this->isRamp()) &&
            (this->getColor() != new_pawn->getColor()))
        {
            ret = -1;
        }
        else
        {
            // If enough space, then its future position will be at the end
            if (this->getNumPawns() < this->getNumMaxPawns())
            {
                ret = (int)vPawns.size();
            }
        }
    }

    // Return
    return ret;
}

//---------------------------------------------------------------------------

/**
 * Find out if the passed Pawn could be added to this Space
 * @param new_pawn pointer to Pawn * that wants to enter my space
 * @return true if allowed or false if not
 */
bool PSpace::canAddPawn(PPawn *new_pawn)
{
    bool allowed = false;
    bool bOtherColor = false;

    // Special Case:
    // If this space is a "Start" of the new_pawn's color and the new_pawn is
    // at it's home and I have "two" pawn's already, any of them from a
    // different color, then the pawn can obviously be placed here (and will also eat :-))
    if (this->isStart() && new_pawn->isAtHome())
    {
        allowed = true;
        if (this->getNumPawns() == 2)
        {
            for (unsigned int i = 0; i < vPawns.size(); i++)
            {
                if (vPawns[i]->getColor() != new_pawn->getColor())
                {
                    bOtherColor = true;
                }
            }
            if (bOtherColor == true)
            {
                allowed = true;
                if (this->isBarrier() && !board->getGame()->canEatHomeBarrier())
                {
                    allowed = false;
                    //                    oss.str ("");
                    //                    oss << getName() << " can't add Pawn: " << new_pawn->getName() << ". canEatHomeBarrier is not active";
                    //                    dbg.print ( 3, oss.str() );
                }
            }
            else
            {
                allowed = false;
                //                oss.str ("");
                //                oss << getName() << " can't add Pawn: " << new_pawn->getName() << ". Barrier of my same color";
                //                dbg.print ( 3, oss.str() );
            }
        }
    }
    else
    {
        // If there is enough space to place the pawn, then return allowed
        if (new_pawn->getSpace() != this)
        {
            if (this->getNumPawns() < this->getNumMaxPawns())
            {
                // Enough space to place the pawn
                allowed = true;
                //                oss.str ("");
                //                oss << getName() << " can add Pawn: " << new_pawn->getName();
                //                dbg.print ( 3, oss.str() );
            }
            else
            {
                // If too many pawns, then mark it as not allowed
                allowed = false;
                //                oss.str ("");
                //                oss << getName() << " can't add Pawn: " << new_pawn->getName() << ". Space is FULL";
                //                dbg.print ( 3, oss.str() );
            }
        }
        else
        {
            allowed = false;
            //            oss.str ("");
            //            oss << getName() << " can't add Pawn: " << new_pawn->getName() << ". The Pawn is already here.";
            //            dbg.print ( 3, oss.str() );
        }
    }
    return allowed;
}

//---------------------------------------------------------------------------

/**
 * Find out if the Pawn could walk through my space
 * @param new_pawn pointer to Pawn * that wants to cross my space
 * @return true if allowed or false if not
 */
bool PSpace::canWalkPawn(PPawn *new_pawn)
{

    // IF BARRIER analyse it to see if can jump over...
    if (this->isBarrier() && (this->isSafe() || this->isStart()))
    {

        //        oss.str ("");
        //        oss << getName() << " Enters this is barrier and safe place";
        //        dbg.print ( 3, oss.str() );

        // IF DIFFERENT COLOR, then new_pawn can't walk me through
        if (vPawns[0]->getColor() != new_pawn->getColor())
        {
            //            oss.str ("");
            //            oss << getName() << " BARRIER different color doesn't allow " << new_pawn->getName() << " to walk me through.";
            //            dbg.print ( 3, oss.str() );
            return false;

            // IF SAME COLOR but Option "canCrossSelfBarrier" is not true,
            // then the new_pawn can't walk me through
        }
        else if (!board->getGame()->canCrossSelfBarrier())
        {
            //            oss.str ("");
            //            oss << getName() << " BARRIER same color doesn't allow " << new_pawn->getName() << " to walk me through.";
            //            dbg.print ( 3, oss.str() );
            return false;
        }
    }

    return true;
}

//---------------------------------------------------------------------------

/**
 * Find out if the Pawn new_pawn could eat another pawn located at my space
 * @param new_pawn pointer to Pawn * that wants to eat :-)
 * @return true if allowed or false if not
 */
bool PSpace::canEatPawn(PPawn *new_pawn)
{
    bool bCanEat = false;
    bool bOtherColor = false;

    // SPACE @Start and PAWN IS AT HOME
    // If this space is a "Start" of the new_pawn's color and the new_pawn is
    // at it's home and I have "two" pawn's already, any of them from a
    // different color, then the pawn can probably eat here :-)
    if (this->isStart() && new_pawn->isAtHome())
    {
        if (this->getNumPawns() == 2)
        {
            for (unsigned int i = 0; i < vPawns.size(); i++)
            {
                if (vPawns[i]->getColor() != new_pawn->getColor())
                {
                    //                    oss.str ("");
                    //                    oss << "CAN EAT?: " << getName() << " has 2 pawns and different color than " << new_pawn->getName();
                    //                    dbg.print ( 3, oss.str() );
                    bOtherColor = true;
                }
            }
            if (bOtherColor == true)
            {
                bCanEat = true;
                if (this->isBarrier() && !board->getGame()->canEatHomeBarrier())
                {
                    //                    oss.str ("");
                    //                    oss << "CAN EAT?: " << getName() << " has a Barrier but Option canEatHomeBarrier prohibits " << new_pawn->getName() << "to eat";
                    //                    dbg.print ( 3, oss.str() );
                    bCanEat = false;
                }
            }
        }
    }
    else
    {

        // SPACE @Normal and have 1 tentative victim.
        // If this space is a Normal Space and I have already a tentative victim (1 pawn)
        // which color is different than the "new_pawn" color, then it may eat here :-)
        if (this->getNumPawns() == 1)
        {
            if (this->isNormal() &&
                vPawns[0]->getColor() != new_pawn->getColor())
                bCanEat = true;
        }
    }

    // Return my decission....
    return bCanEat;
}

//---------------------------------------------------------------------------

/**
 * Find out if the Pawn new_pawn has an enemy in this Space
 * @param new_pawn pointer to Pawn * that wants to know
 * @return true if an enemy exists, false otherwise
 */
bool PSpace::hasEnemy(PPawn *new_pawn)
{
    bool bOtherColor = false;

    for (unsigned int i = 0; i < vPawns.size(); i++)
    {
        if (vPawns[i]->getColor() != new_pawn->getColor())
        {
            bOtherColor = true;
        }
    }
    return bOtherColor;
}

//---------------------------------------------------------------------------

/**
 * Was, the passed Pawn, the first one to arrive to this Space?
 *
 * @return true if never used and all pawns are at home
 */
bool PSpace::wasFirst(PPawn *new_pawn)
{
    if (getPawnPosition(new_pawn) == 0)
        return true;

    return false;
}

//---------------------------------------------------------------------------

/**
 * Was, the passed Pawn, the last one to arrive to this Space?
 *
 * @return true if never used and all pawns are at home
 */
bool PSpace::wasLast(PPawn *new_pawn)
{
    if (getPawnPosition(new_pawn) == 1)
        return true;

    return false;
}

//---------------------------------------------------------------------------

/**
 * Finds out if this space allows to get two pawnw out of HOME (if this is a home)
 * This is linked to the game option "bOptionCanTwoGoOutHome"
 * This can be used only once.
 *
 * @return true if never used and all pawns are at home
 */
bool PSpace::canGetTwoPawnsOutFromHome()
{
    if (bCanGetOutOtherPawn)
    {
        this->bCanGetOutOtherPawn = false;
        return true;
    }
    return false;
}


//---------------------------------------------------------------------------

/**
 * Find out if the passed Dice can be added to this Space
 *  This method has no impact in the game, it's just moving the dice from the
 *  HOME of one color to the next, etc. Why? well, it's useful for simple
 *  screen/graphics placement of the dice based on which space they are in
 *  and maybe for future implementations...
 * @param new_pawn pointer to Dice * that wants to enter my space
 * @return true if allowed or false if not
 */
bool PSpace::canAddDice(PDice *new_dice)
{
    bool allowed = true;
    return allowed;
}

/**
 * Adds the Dice to the space
 *  This method has no impact in the game, it's just moving the dice from the
 *  HOME of one color to the next, etc. Why? well, it's useful for simple
 *  screen/graphics placement of the dice based on which space they are in
 *  and maybe for future implementations...
 * @param new_pawn pointer to Dice * that wants to enter my space
 * @return true if the placement was successful or false otherwise
 */
bool PSpace::addDice(PDice *new_dice)
{
    PSpace *fromSpace = new_dice->getSpace();
    bool allowed = false;

    // If the Pawn is not assigned to any space then allow it
    if (fromSpace == (PSpace *)NULL)
    {
        allowed = true;
    }
    else
    {
        // If the Pawn is not already here then allow it
        if (fromSpace == this)
        {
            dbg.printF(3,
                       "|  %-8s can't add %-8s. It's already here        |  * "
                       "WARNING !!",
                       this->getName().c_str(),
                       new_dice->getName().c_str());
        }
        else
        {
            allowed = true;
        }
    }

    // If the Dice is Prohibited here, then do not allow it
    // As of today's, the unique space allowed is HOME's
    if (allowed)
    {
        if (!this->isHome())
            allowed = false;
    }

    // If allowed to be added to this space...
    if (allowed)
    {

        // Add it here and remove from the old space.
        this->setDice(new_dice);
        new_dice->setSpace(this);
    }

    return allowed;
}


//---------------------------------------------------------------------------

/**
 * Gets the dice pointer living in my Space
 *  This method has no impact in the game, it's just moving the dice from the
 *  HOME of one color to the next, etc. Why? well, it's useful for simple
 *  screen/graphics placement of the dice based on which space they are in
 *  and maybe for future implementations...
 * @return is the pointer to the dice
 */
PDice *PSpace::getDice()
{
    return dice;
}


//---------------------------------------------------------------------------

/**
 * Set's the Dice living in my Space
 *  This method has no impact in the game, it's just moving the dice from the
 *  HOME of one color to the next, etc. Why? well, it's useful for simple
 *  screen/graphics placement of the dice based on which space they are in
 *  and maybe for future implementations...
 * @return is the pointer to the dice
 */
void PSpace::setDice(PDice *the_Dice)
{
    dice = the_Dice;
}


//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
