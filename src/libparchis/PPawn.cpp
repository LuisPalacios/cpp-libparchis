
/**
 *  @class  PPawn PPawn.cpp "PPawn.cpp"
 *  @file   PPawn.cpp
 *  @brief  Parchis Class: Control and Status of a Pawn
 *
 *  ---------------------------------------------------------------------------
 */


//---------------------------------------------------------------------------

#include "PPawn.h"

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Private Methods
#pragma mark-- Private: Class initialization

/**
 * Initialize the attributes and create all instances
 */
void PPawn::initAttributes()
{

    bCanMove = false;
    bCanEatPawn = false;
    mySpace = (PSpace *)NULL;

    dbg.printF(4,
               "|  Constructor PPawn %-8s, idx=%d. color=%-8s     |",
               getName().c_str(),
               getIndex(),
               board->getColorName(getColor()));
}

//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Public Methods
#pragma mark-- Public Constructor/Destructor

//---------------------------------------------------------------------------

/**
 * Constructor of PPawn without the Space parameter
 *
 * Creates a pawn instance, passing several parameters but the space. This version of
 * the constructor is typically used when saving mementos (undo/redo)
 *
 * @param new_board is the pointer to the PBoard where this pawn will play
 * @param new_name is the internal name assigned to this pawn
 * @param new_index represents the pawn id, it's the index inside the array of all pawns
 * @param new_number is the pawn number
 * @param new_color is the color this pawn belongs to
 */
PPawn::PPawn(PBoard *new_board,
             std::string new_name,
             int new_index,
             int new_number,
             int new_color)
{
    dbg.setCallerName("PPawn  ");
    board = new_board;
    index = new_index;
    number = new_number;
    name.assign(new_name);
    color = new_color;

    // Finish initializing attributes
    initAttributes();
}

//---------------------------------------------------------------------------

/**
 * Destructor of PPawn
 *
 */
PPawn::~PPawn()
{
    dbg.printF(4,
               "|  Destructor PPawn: %-8s                            |",
               getName().c_str());
}

//---------------------------------------------------------------------------


#pragma mark-- Getters for main attributes

//---------------------------------------------------------------------------

/**
 * Getter: the value of index,the id of this pawn in the array of pawns
 * @return the value of index
 */
int PPawn::getIndex()
{
    return index;
}

//---------------------------------------------------------------------------

/**
 * Getter: the number of pawn in the list of all pawns available of its color
 * @return the number of this pawn
 */
int PPawn::getNumber()
{
    return number;
}

//---------------------------------------------------------------------------

/**
 * Getter: the name assigned to this pawn
 * @return the name of the pawn
 */
std::string PPawn::getName()
{
    return name;
}

//---------------------------------------------------------------------------

/**
 * Getter: the color this pawn belongs to
 * @return the number of the color
 */
int PPawn::getColor()
{
    return color;
}

//---------------------------------------------------------------------------

/**
 * Getter: the space where this pawn is located
 * @return pointer to the PSpace
 */
PSpace *PPawn::getSpace()
{
    return mySpace;
}

//---------------------------------------------------------------------------

/**
 * Store the Space where this pawn is located
 *
 * @param new_space the new value of mySpace
 */
void PPawn::setSpace(PSpace *new_space)
{
    mySpace = new_space;
}

//---------------------------------------------------------------------------


#pragma mark-- Public methods: Status about the Pawn

//---------------------------------------------------------------------------
/**
 * It calls same method on the PBoard to find out if the Board is in editable mode?
 * @return bool true/false indicating if the board is editable.
 */
bool PPawn::isEditable()
{
    return board->isEditable();
}

//---------------------------------------------------------------------------

/**
 * Is the Pawn locate in a NORMAL space?
 * @return true or false depending on where it's located.
 */
bool PPawn::isAtNormal()
{
    if (mySpace->isNormal())
        return true;
    return false;
}

//---------------------------------------------------------------------------

/**
 * Is the Pawn locate in a SAFE space?
 * @return true or false depending on where it's located.
 */
bool PPawn::isAtSafe()
{
    if (mySpace->isSafe())
        return true;
    return false;
}

//---------------------------------------------------------------------------

/**
 * Is the Pawn locate in a RAMP space?
 * @return true or false depending on where it's located.
 */
bool PPawn::isAtRamp()
{
    if (mySpace->isRamp() && this->getColor() == mySpace->getColor())
        return true;
    return false;
}

//---------------------------------------------------------------------------

/**
 * Is the Pawn locate in a FINAL space?
 * @return true or false depending on where it's located.
 */
bool PPawn::isAtFinal()
{
    if (mySpace->isFinal() && this->getColor() == mySpace->getColor())
        return true;
    return false;
}

//---------------------------------------------------------------------------

/**
 * Is the Pawn locate in a HOME space?
 * @return true or false depending on where it's located.
 */
bool PPawn::isAtHome()
{
    if (mySpace->isHome() && this->getColor() == mySpace->getColor())
        return true;
    return false;
}

//---------------------------------------------------------------------------

/**
 * Is the Pawn locate in a START space?
 * @return true or false depending on where it's located.
 */
bool PPawn::isAtStart()
{
    if (mySpace->isStart() && this->getColor() == mySpace->getColor())
        return true;
    return false;
}

//---------------------------------------------------------------------------

/**
 * Is the Pawn locate in a SAFE space?
 * @return true or false depending on where it's located.
 */
bool PPawn::isAtRampSafe()
{
    if (mySpace->isRampSafe() && this->getColor() == mySpace->getColor())
        return true;
    return false;
}

//---------------------------------------------------------------------------

/**
 * Are there any other Pawn's from this color still at home?
 * @return true or false depending on pawn's from this color still at home
 */
bool PPawn::anyAtHome()
{
    if (board
            ->getSpaceByIndex(board->getIndexHomeSpaceByColor(this->getColor()))
            ->getNumPawns() != 0)
        return true;
    return false;
}

//---------------------------------------------------------------------------

/**
 * Return true if the Pawn can be moved after executing the Rules
 * @return the true or false depending movable status
 */
bool PPawn::canMove()
{
    return bCanMove;
}

//---------------------------------------------------------------------------

/**
 * Return true if the Pawn can eat afte ther rules have been analysed
 * @return the true or false depending "can I eat?" status
 */
bool PPawn::canEatPawn()
{
    return bCanEatPawn;
}

//---------------------------------------------------------------------------

/**
 * Return true if the Pawn can be eated (dice distance), which was stablished during backward analysis
 * @return true or false if the pawn is at dice distance and eatable
 */
bool PPawn::isBehindEatable()
{
    return bBehindEatable;
}

//---------------------------------------------------------------------------

/**
 * Returns bool if the Pawn can eat ahead.
 * @return true if "ahead" analysis says that pawn could eat an enemy pawn
 */
bool PPawn::isAheadEats()
{
    return bAheadEats;
}

/**
 * Returns what is my position inside the Space I'm actually in
 * @return integer value with the position (0-'n') or -1 if Pawn is not in any Space
 */
int PPawn::getPawnPosition()
{
    int pos = -1;

    // If I've got no Space assigned yet, then get out...
    if (mySpace != (PSpace *)NULL)
    {

        // If I'm the unique Pawn in the space, then position = 0
        if (mySpace->getNumPawns() == 1)
        {
            pos = 0;
        }
        else
        {
            pos = mySpace->getPawnPosition(this);
        }
    }
    // Return
    return pos;
}

/**
 *
 * Returns what is my position inside the array of delta's. (DOCUMENTAR)
 *
 * @return integer value within the array which can be used in a graphical context i.e.
 *
 *  Posición
 *
 *    0     Está centrado en la casilla
 *
 *    1     Casa, arriba/izda
 *    2     Casa, arriba/dcha
 *    3     Casa, abajo/izda
 *    4     Casa, abajo/dcha
 *
 *    5     Fin Horizontal Ama, izda
 *    6     Fin Horizontal Ama,  :
 *    7     Fin Horizontal Ama,  :
 *    8     Fin Horizontal Ama, dcha
 *
 *    9     Fin Vertical Azu, arriba
 *    10    Fin Vertical Azu,  :
 *    11    Fin Vertical Azu,  :
 *    12    Fin Vertical Azu, abajo
 *
 *    13     Fin Horizontal Roj, izda
 *    14    Fin Horizontal Roj,  :
 *    15    Fin Horizontal Roj,  :
 *    16    Fin Horizontal Roj, dcha
 *
 *    17    Fin Vertical Ver, arriba
 *    18    Fin Vertical Ver,  :
 *    19    Fin Vertical Ver,  :
 *    20    Fin Vertical Ver, abajo
 *
 *    21    Horizontal, izquierda
 *    22    Horizontal, derecha
 *
 *    23    Vertical, arriba
 *    24    Vertical, abajo
 *
 *
 */
int PPawn::getDeltaPosition()
{
    int delta = 0;

    // Position inside the Space
    int pos = getPawnPosition();

    // Get my position inside Home
    if (mySpace->isHome())
        delta = pos + 1;
    //    else if ( mySpace->isFinal() && mySpace->isHorizontal() )   delta = pos + 5;
    //    else if ( mySpace->isFinal() && mySpace->isVertical() )     delta = pos + 9;

    else if (mySpace->isFinal())
    {
        if (mySpace->isHorizontal() && mySpace->getColor() == YELLOW)
            delta = pos + 5;
        else if (mySpace->isHorizontal() && mySpace->getColor() == RED)
            delta = pos + 13;
        else if (mySpace->isVertical() && mySpace->getColor() == BLUE)
            delta = pos + 9;
        else if (mySpace->isVertical() && mySpace->getColor() == GREEN)
            delta = pos + 17;
    }
    else if (mySpace->getNumPawns() == 1)
        delta = 0;
    else if (mySpace->isHorizontal())
        delta = pos + 21;
    else if (mySpace->isVertical())
        delta = pos + 23;

    // Return
    return delta;
}


//---------------------------------------------------------------------------

/**
 * Return the number of Pawns that can eat me (dice distance)
 * @return int number of pawns that can eat me, somethig discovered during the backward analysis
 */
int PPawn::getNumBehindEatsMe()
{
    return numBehindEatsMe;
}

//---------------------------------------------------------------------------

/**
 * Return the previous space I was: index of the space where this Pawn was located before.
 * @return int index to the last space this pawn was located
 */
int PPawn::getLastSpaceIndex()
{
    return this->lastSpaceIndex;
}

//---------------------------------------------------------------------------


#pragma mark-- Public methods: Pawn actions and status change

//---------------------------------------------------------------------------

/**
 * Initilialize attributes because a new game has been requested
 */
void PPawn::newGame()
{

    dbg.printF(2,
               "| %-8s: Starting new game                            |",
               this->getName().c_str());

    // Clean all the flags calculated during Board analysis: calcBehind & calcAhead.
    this->setBehindEatable(false);
    this->setAheadEats(false);
}

//---------------------------------------------------------------------------

/**
 * Setter: Set flag that indicates Pawn can move in this turn based on the number gotten by the last tossed dice.
 *
 * @param new_var the bool (true/false) value
 */
void PPawn::setCanMove(bool new_var)
{
    bCanMove = new_var;
}

//---------------------------------------------------------------------------

/**
 * Setter: Set the flag which indicates that the Pawn can Eat a Pawn if moved to the destination calculated by Rules::execRules
 *
 * @param new_var the new value for bCanEat
 */
void PPawn::setCanEatPawn(bool new_var)
{
    bCanEatPawn = new_var;
}

//---------------------------------------------------------------------------

/**
 * Store the pointer to the destination space calculated at the Rules class
 * This information will be later used by the Game object to calculate
 * the snapshots
 *
 * @param new_space the pointer to the destination space
 * Note that this value can be NULL as in cases where the
 * Pawn cannot move
 *
 */
void PPawn::setDestinationSpace(PSpace *new_space)
{
    dSpace = new_space;
}

//---------------------------------------------------------------------------

/**
 * Return the pointer to my destination space calculated through the Rules
 *
 * The Game object uses this method to calculate the snapshots
 *
 * @return the value of my destination space
 * Note that this value can be NULL as in cases where the
 * Pawn cannot move
 *
 */
PSpace *PPawn::getDestinationSpace()
{
    return dSpace;
}

//---------------------------------------------------------------------------

/**
 * Set the flag which indicates that the Pawn is eatable
 * which is calculated during behind analysis
 *
 * @param new_var the new value for bEatable
 */
void PPawn::setBehindEatable(bool new_var)
{
    if ((bBehindEatable = new_var))
        this->numBehindEatsMe++;
    else
        this->numBehindEatsMe = 0;
}

//---------------------------------------------------------------------------

/**
 * Sets (true/false) if during "ahead" analysis it was discovered that this
 * pawn could eat an enemy pawn
 * @param new_var value for this bool bAheadEats
 */
void PPawn::setAheadEats(bool new_var)
{
    bAheadEats = new_var;
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
