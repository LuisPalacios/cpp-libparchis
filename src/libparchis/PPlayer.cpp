/**
 *  @class  PPlayer PPlayer.cpp "PPlayer.cpp"
 *  @file   PPlayer.cpp
 *  @brief  Parchis Class: Base player derived to create PHuman's PRobotSimple's PRobotSmart's
 *
 *  ---------------------------------------------------------------------------
 */


//---------------------------------------------------------------------------

#include "PPlayer.h"

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Static Attributes

const char *PPlayer::sPlayerType[NUMPLAYERTYPES] = {"Human",
                                                    "Robot Simple",
                                                    "Robot Smart"};

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Private Methods
#pragma mark-- Class initialization

//---------------------------------------------------------------------------

/**
 * Initialize the attributes and create all instances
 */
void PPlayer::initAttributes()
{

    dbg.setCallerName("Player ");
    dbg.printF(4,
               "|  Constructor Player %-8s, idx(%2d)                  |",
               getName().c_str(),
               getIndex());

    // Initialize the stack of historical dices gotten
    for (int i = 0; i < MAX_NUM_STORED_DICES; i++)
    {
        statLastDices[i] = 0;
    }
}

//---------------------------------------------------------------------------

/**
 * Increment by 1 the statistics about how many times the Player has gotten a 1,2,3,4,5,6,10 or 20.
 *
 * @param new_var is the position in the array
 */
void PPlayer::addDicesGotten(int new_var)
{
    statDicesGotten[new_var]++;
}

//---------------------------------------------------------------------------

/**
 * Set statistics about how many times the Player has gotten a 1,2,3,4,5,6,10 or 20.
 *
 * @param new_pos is the position in the array which value will be set with new_var
 * @param new_var the value that will be placed in the new_pos position.
 */
void PPlayer::setDicesGotten(int new_pos, int new_var)
{
    statDicesGotten[new_pos] = new_var;
}

//---------------------------------------------------------------------------

/**
 * Set the value of turns this Player has been punished
 *
 * @param new_var the new value of turnsPenalty
 */
void PPlayer::setTurnPenalty(int new_var)
{
    turnPenalty = new_var;
}

//---------------------------------------------------------------------------

/**
 * Add rolled dice value to the stack of historical dices gotten
 *
 * @param new_var integer value of current dice to be added to the historical list of dices
 *
 *  @par Sample Code:
 *  @code
 *   statLastDices[0]                    = newer
 *   statLastDices[:]                    = :
 *   statLastDices[MAX_NUM_STORED_DICES] = oldest
 *  @endcode
 *
 */
void PPlayer::storeDice(int new_var)
{
    if (new_var <= 0 || new_var > 6)
        return;

    // Push back the stack
    for (int i = (MAX_NUM_STORED_DICES - 1); i > 0; i--)
    {
        statLastDices[i] = statLastDices[i - 1];
    }
    statLastDices[0] = new_var;
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Private Methods
#pragma mark-- Class initialization

//---------------------------------------------------------------------------

/**
 * Set the value of index. The index is the where in the array of Players this player is located
 *
 * @param new_var the new value of index
 */
void PPlayer::setIndex(int new_var)
{
    index = new_var;
}

//---------------------------------------------------------------------------

/**
 * Set the name assigned to this Player
 *
 * @param new_var the new value of name
 */
void PPlayer::setName(std::string new_var)
{
    name.assign(new_var);
}

//---------------------------------------------------------------------------

/**
 * Set the value of type of player (human, robot simple, robot smart, etc.)
 *
 * @param new_var the new value of type
 */
void PPlayer::setType(int new_var)
{
    type = new_var;
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Public Methods
#pragma mark-- Constructor/Destructor

//---------------------------------------------------------------------------

/**
 * Constructor of PPlayer
 *
 * Constructor of the PPlayer without parameters, which sets several defaults,
 * like the name="Jugador" and index=0.
 *
 */
PPlayer::PPlayer()
{
    setName("Jugador");
    setIndex(0);
    initAttributes();
}

//---------------------------------------------------------------------------

/**
 * Constructor of PPlayer
 *
 * Constructor of the PPlayer expecting three parameters
 *
 * @param new_name The name you want to assign to this player's instance
 * @param new_index id that this player occupies in the array of players.
 * @param new_dice is the pointer to the PDice assigned to this player
 *
 */
PPlayer::PPlayer(std::string new_name, int new_index, PDice *new_dice)
{
    setName(new_name);
    setIndex(new_index);
    dice = new_dice;
    initAttributes();
}

//---------------------------------------------------------------------------

/**
 * Destructor of PPlayer
 */
PPlayer::~PPlayer()
{
    dbg.printF(4,
               "|  Destructor del Jugador: %-8s                      |",
               getName().c_str());
}

//---------------------------------------------------------------------------


#pragma mark-- Class Methods (static Public Methods)

//---------------------------------------------------------------------------

/**
 * Getter: Returns the value assigned to a player of type HUMAN
 * @return the numerical value
 */
int PPlayer::getNumTypeHuman()
{
    return PLAYER_HUMAN;
}

//---------------------------------------------------------------------------

/**
 * Getter: Returns the value assigned to a player of type Robot Simple
 * @return the numerical value
 */
int PPlayer::getNumTypeSimple()
{
    return PLAYER_ROBOT_SIMPLE;
}

//---------------------------------------------------------------------------

/**
 * Getter: Returns the value assigned to a player of type Robot Smart
 * @return the numerical value
 */
int PPlayer::getNumTypeSmart()
{
    return PLAYER_ROBOT_SMART;
}

//---------------------------------------------------------------------------

/**
 * Getter: maximum number of dice's a player can store
 * @return the numerical value
 */
int PPlayer::getNumMaxStoredDices()
{
    return MAX_NUM_STORED_DICES;
}

//---------------------------------------------------------------------------

/**
 * Get the player description type based on index
 * @return the string that describes the player type
 */
const char *PPlayer::getStringPlayerType()
{
    return sPlayerType[this->type];
}

//---------------------------------------------------------------------------

/**
 * Clone two players of different type
 * It will copy the main attributes, preserving the type of players
 * @param sp is the source Player
 * @param dp is the destination Player
 */
void PPlayer::copyPlayer(PPlayer *sp, PPlayer *dp)
{
    std::string s;

    // COPY the name and index
    s.assign(sp->getName());      // Copy the name
    dp->setIndex(sp->getIndex()); // Copy the index
    dp->setName(s);

    // COPY the pointers to the dice and pawns
    dp->setDice(sp->getDice());
    dp->setPawns(sp->getPawns());

    // COPY the turn penalty attribute
    dp->setTurnPenalty(sp->getTurnPenalty());

    // COPY the stored dices
    for (int i = (MAX_NUM_STORED_DICES - 1); i >= 0; i--)
    {
        dp->storeDice(sp->statLastDices[i]);
    }

    // COPY the statistics
    for (int i = 0; i < STAT_DICES_GOTTEN; i++)
    {
        dp->setDicesGotten(i, sp->getDicesGotten(i));
    }
}

//---------------------------------------------------------------------------


#pragma mark-- Other Public methods

//---------------------------------------------------------------------------

/**
 * Setter: Connect this Player with its Pawns, receive the PPawn** pointer
 *
 * @param new_pawns is the Pawn ** pointer to my pawns
 */
void PPlayer::setPawns(PPawn **new_pawns)
{

    // Make the connection
    pawns = new_pawns;
}

//---------------------------------------------------------------------------

/**
 * Connect this Player with its Dice, used during copy player operations
 *
 * @param new_dice is the pointer to my dice
 */
void PPlayer::setDice(PDice *new_dice)
{

    // Make the connection
    dice = new_dice;

    // For debugging only
    oss.str("");
    oss << getName() << " connected with dice: " << dice->getName();
    dbg.print(4, oss.str());
}

//---------------------------------------------------------------------------

/**
 * Getter: Return pointer of pointers to the pawns owned by this player
 * @return a PPawn** pointer to my array of pawns
 */
PPawn **PPlayer::getPawns()
{
    return (pawns);
}

//---------------------------------------------------------------------------

/**
 * Return my dice, indeed I'm returning the pointer to the dice assigned to this player
 *
 * @return the pointer to my Dice, PDice*
 */
PDice *PPlayer::getDice()
{
    return dice;
}

//---------------------------------------------------------------------------

/**
 * Get statistics about how many times the Player has gotten a 1,2,3,4,5,6,10 or 20.
 *
 * @param new_var is the position in the array which value will be returned
 * @return the number of times the Player has received a 1..20.
 */
int PPlayer::getDicesGotten(int new_var)
{
    return statDicesGotten[new_var];
}

//---------------------------------------------------------------------------

/**
 * Getter: Get the internal index value of this player
 *
 * @return the value of index
 */
int PPlayer::getIndex()
{
    return index;
}

//---------------------------------------------------------------------------

/**
 * Getter: return the name assigned to this player
 *
 * @return the value of name
 */
std::string PPlayer::getName()
{
    return name;
}

//---------------------------------------------------------------------------

/**
 * Get the value of type of player (human, robot simple, robot smart, etc.)
 *
 * @return the numerical type
 */
int PPlayer::getType()
{
    return type;
}

//---------------------------------------------------------------------------

/**
 * Get the value of turnPenalty
 * @return the value of turnPenalty
 */
int PPlayer::getTurnPenalty()
{
    return turnPenalty;
}

//---------------------------------------------------------------------------

/**
 * Initilialize attributes because a new game has been requested
 */
void PPlayer::newGame()
{
    int i;

    // Just debug it out
    dbg.printF(3,
               "| %-7s: New Game                                      |",
               getName().c_str());

    // Initialize the statistics of how many of each dice value gotten
    for (i = 0; i < STAT_DICES_GOTTEN; i++)
    {
        setDicesGotten(i, 0);
    }

    // Initialize the stack of historical dices gotten
    for (int i = 0; i < MAX_NUM_STORED_DICES; i++)
    {
        statLastDices[i] = 0;
    }
}

//---------------------------------------------------------------------------

/**
 * Called from the Game object, I'm asked to roll my dice. If I'm passed
 * a dice value is because I'm forced to use such value, otherwise a random
 * dice will be used.
 *
 * @param new_dice is the numerical dice value
 *
 *  @par NOTE about implementations:
 *  @verbatim
 new_dice == 1,2,3,4,5,6,10,20  Then I'll use this dice value.
 new_dice different: Then I'll issue a random dice between 1 and 6
 @endverbatim
 *
 */
int PPlayer::tossDice(int new_dice)
{
    dbg.print(3, "|  Tossing the dice...                                   |");

    if (new_dice <= 0 || (new_dice > 6 && new_dice != 10 && new_dice != 20))
        dice->randomDice();
    else
        dice->setDice(new_dice);

    // Store historical dices gotten
    storeDice(dice->getDice());

    // Increment statistics
    addDicesGotten(dice->getDice());

    // Return the tossed dice value
    return dice->getDice();
}

//---------------------------------------------------------------------------

/**
 * Return the value of the dice gotten in the past 'new_var' position
 *
 * @param new_var is the value of the historical dice
 */
int PPlayer::getStoredDice(int new_var)
{
    if (new_var < 0 || new_var >= MAX_NUM_STORED_DICES)
        return 0;
    return this->statLastDices[new_var];
}

//---------------------------------------------------------------------------


#pragma mark-- Other Public methods

//---------------------------------------------------------------------------

/**
 * Find out if this player is human
 * @return true for human
 */
bool PPlayer::isHuman()
{
    if (type == PLAYER_HUMAN)
    {
        return true;
    }
    return false;
}

//---------------------------------------------------------------------------

/**
 * Find out if this player robot (doesn't matter which type of robot)
 * @return true for robot or false otherwise
 */
bool PPlayer::isRobot()
{
    if (type == PLAYER_HUMAN)
    {
        return false;
    }
    return true;
}

//---------------------------------------------------------------------------

/**
 * Return true if this player has finished
 * @return true if all its Pawns are at the END space
 */
bool PPlayer::isFinished()
{
    for (int i = 0; i < PBoard::pawnsPerPlayer(); i++)
    {
        if (this->pawns[i]->getSpace()->getRole() != PBoard::spaceTypeFinal())
            return false;
    }
    return true;
}

//---------------------------------------------------------------------------

/**
 * Return true if all its pawns are out of HOME
 * @return true if all its Pawns are out of HOME
 */
bool PPlayer::isAllPawnsOut()
{
    for (int i = 0; i < PBoard::pawnsPerPlayer(); i++)
    {
        if (this->pawns[i]->getSpace()->getRole() == PBoard::spaceTypeHome())
            return false;
    }
    return true;
}

//---------------------------------------------------------------------------


#pragma mark-- Public methods that SHOULD BE OVERRIDEN

//---------------------------------------------------------------------------

/**
 * This method will be overloaded in the Derived classes. It's been declared as virtual at the .h.
 * At Game.cpp will use it without the need to know what kind of (derived) player:
 *   Human, Robot Simple, Robot Smart, new robots...
 * @return the index of the pawn that the Player(human, robot,...) has decided to move
 */
PPawn *PPlayer::getPawnToMove(PSnapshot **snap)
{
    if (snap != (PSnapshot **)NULL)
        dbg.print(3,
                  "WARNING: getPawnToMove() calles at object Player, should be "
                  "derived with Human, Robot***");

    return ((PPawn *)NULL);
}

//---------------------------------------------------------------------------


#pragma mark-- Methods to handle memento's

//---------------------------------------------------------------------------

/**
 * Creates a memento, which saves current Player's state
 *
 *  @par Memento's description:
 *  @verbatim

  Stores/Restores internal state of a Player object, it's based on the
  Memento design patter. A memento is an object that stores a snapshot of
  the internal state of another object. It can be leveraged to support multi-level undo.

  Originator   Player.class  (THIS CLASS)
     Creates the memento object:    createMemento()
     or goes to a specific memento  setMemento()

  See also:
  Memento      PlayerMemento.class (Stores/Restores internal state of a Player object)
  CareTaker    Game.cpp            (Calls myself createMemento/setMemento to control the undo/redo's)

 @endverbatim
 *
 */
PPlayerMemento *PPlayer::createMemento()
{
    // Save actual state, creates a memento

    // Create a new memento object saving the values that I want to save
    //
    //   "name"   Name of the object
    //
    //
    oss.str("");
    oss << this->getName() << ". createMemento()";
    dbg.print(3, oss.str());

    return new PPlayerMemento(name, type);
}

//---------------------------------------------------------------------------

/**
 * Restores to a previous states
 *
 * @param m is the pointer to the PPlayerMemento
 */
void PPlayer::setMemento(PPlayerMemento *m)
{
    // Go back to a "memento", restores state

    oss.str("");
    oss << this->getName() << ". setMemento(): name before= " << name;
    dbg.print(3, oss.str());

    // Restore "name"
    name = m->getName();

    // Restore "type"
    type = m->getType();


    oss.str("");
    oss << this->getName() << ". setMemento(): name after= " << name;
    dbg.print(3, oss.str());
}


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
