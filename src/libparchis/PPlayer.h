/**
 *  @class  PPlayer PPlayer.h "PPlayer.h"
 *  @brief  Parchis Class: Base player derived to create PHuman's PRobotSimple's PRobotSmart's
 *
 *  Belongs to the Library: "Parchis Engine C++ library"
 *
 *  @author  Luis Palacios
 *  @version 0.1
 *  @date    8/Sep/09
 *
 *  @par Description
 *
 *  This class is responsible of playing its Pawns in the Board. I've defined a base
 *  class called PPlayer from which it derives the PHuman, PRobotSimple and PRobotSmart
 *
 */


#ifndef PPLAYER_H
#define PPLAYER_H

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#pragma mark ====== DEFINES

//---------------------------------------------------------------------------

#define NUM_STATES 45 // Maximum number of states analysed by the robots
#define STAT_DICES_GOTTEN                                                      \
    21 // Define's for statistics on how many of each dice (or 10/20) got this player
#define NUMPLAYERTYPES 3 // Number of different players and types
#define PLAYER_HUMAN 0
#define PLAYER_ROBOT_SIMPLE 1
#define PLAYER_ROBOT_SMART 2
#define MAX_NUM_STORED_DICES 3 // Number of historical dices to store

//---------------------------------------------------------------------------

#pragma mark ====== INCLUDES

//---------------------------------------------------------------------------

// My includes
#include "PDebug.h"
#include "PDice.h"
#include "PPawn.h"
#include "PPlayerMemento.h"
#include "PSnapshot.h"

// Standard includes
#include <iostream>
#include <string>

//---------------------------------------------------------------------------


#pragma mark ====== CLASS PPlayer

//---------------------------------------------------------------------------

class PPlayer
{

#pragma mark ====== PRIVATE INSTANCE MEMBERS
private:
    // DEBUGGING purposes

    PDebug dbg;             //!< To be able to send Log messages
    std::ostringstream oss; //!< Construct complex strings

    // PRIVATE ATTRIBUTES

    int type;        //!< Type of Player, either Human or Robot
    int turnPenalty; //!< Number of turns this Player has been punished (i.e.: 3 x 6's)
    int statDicesGotten
        [STAT_DICES_GOTTEN]; //!< How many of 1,2,3,4,5,6, 10's or 20's the player got.
    int statLastDices
        [MAX_NUM_STORED_DICES]; //!< Stores the last 'MAX_NUM_STORED_DICES' dices rolled by this player


#pragma mark ====== PRIVATE INSTANCE METHODS

    // PRIVATE METHODS

    void initAttributes();            // Initialization of the class
    void addDicesGotten(int new_var); // Connection with my dice
    void setDicesGotten(int new_pos, int new_var);
    void setTurnPenalty(int new_var);
    void storeDice(
        int new_var); // Add rolled dice value to the stack of historical dices gotten


#pragma mark ====== PROTECTED ATTRIBUTES
protected:
    // PROTECTED ATTRIBUTES AND METHODS, USED BY DERIVED CLASSES
    /////////////////////////////////////////////////////////
    static const char *sPlayerType[NUMPLAYERTYPES]; //!< String of player's type
    PDice *dice;                                    //!< Connection with my dice
    PPawn **pawns; //!< Connection with my pawns
    int index; //!< The id of the Player, which is the index in the allocated array of Players
    std::string
        name; //!< String with the name assigned to this Player, typically for debugging purposes
    void setIndex(int new_var); // Set the index of this Player
    void setType(
        int new_var); // Establish the type of Player (human, robot, ...)


#pragma mark ====== PUBLIC INSTANCE METHODS
public:
    // CONSTRUCTOR/DESTRUCTOR

    PPlayer(); // Constructor
    PPlayer(std::string new_name,
            int new_index,
            PDice *new_dice); // Constructor
    virtual ~PPlayer();       // Destructor


    // STATIC METHODS

    static int getNumTypeHuman();  // Return the type of player Human
    static int getNumTypeSimple(); // Return the type of player Robot Simple
    static int getNumTypeSmart();  // Return the type of player Robot Smart
    static int
    getNumMaxStoredDices(); // Return maximum number of dice's this player can stored
    const char *
    getStringPlayerType(); // Return a string with the readable player type
    static void copyPlayer(PPlayer *sp,
                           PPlayer *dp); // Clone two players of different type


    // PUBLIC METHODS

    void setName(std::string new_var); // Set the name of the player object
    void setPawns(PPawn **new_pawns);  // Connection with my pawns
    void setDice(PDice *new_dice);     // Connection with my dice
    PPawn **
    getPawns(); // Get the pointer to player's pawns (needed for COPY operation)
    PDice *
    getDice(); // Get the pointer to player's dice (needed for COPY operation)
    int getDicesGotten(
        int new_var);      // Return how many times a dice has a appeared
    int getIndex();        // Get the index assigned to this Player
    std::string getName(); // Get the name of the player
    int getType();         // Get the type of player
    int
    getTurnPenalty(); // Return true/false if this player has a penalty (looses one turn)
    void newGame();             // Initialize the player for a new game
    int tossDice(int new_dice); // Player is asked to toss his dice
    int getStoredDice(
        int new_var); // Return the value of the dice gotten in the past at 'new_var' position


    // PLAYER STATUS

    bool isHuman(); // Return true/false if this player is Human
    bool isRobot(); // Return true/false if this player is a Robot
    bool
    isFinished(); // Return true if all my Pawns are actually at the "Final" space.
    bool
    isAllPawnsOut(); // Return true if all my Pawns are actually playing, out of HOME

    // METHODS TO OVERRIDE by derived classes Human, Robot*

    virtual PPawn *getPawnToMove(
        PSnapshot **snap); // Pointer to the Pawn selected to be moved.

    // METHODS TO HANDLE MEMENTO's (UNDO/REDO)

    PPlayerMemento *createMemento(); // Save actual state, creates a memento
    void setMemento(
        PPlayerMemento *m); // Go back to a "memento", restores state
};

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


/**
 *  @brief  Parchis Class: Derived from PPlayer, represents a Human player..
 *
 *  Class derived from PPlayer. Represents a Human player and basically
 *  does few things. Its equivalent to the Robot* classes, and controls
 *  the human dice object and statistics.
 *
 *  @par Sample usage:
 *  @code
 *
 *  // ToDo
 *
 *  @endcode
 *
 */
//---------------------------------------------------------------------------


#pragma mark ====== CLASS PHuman

//---------------------------------------------------------------------------

class PHuman : public PPlayer
{

#pragma mark ====== PRIVATE INSTANCE MEMBERS
private:
    // DEBUGGING purposes

    PDebug dbg;             //!< To be able to send Log messages
    std::ostringstream oss; //!< Construct complex strings


#pragma mark ====== PRIVATE INSTANCE METHODS

    // PRIVATE METHODS

    void initAttributes();


#pragma mark ====== PUBLIC INSTANCE METHODS
public:
    // CONSTRUCTORS/DESTRUCTOR
    /////////////////////////////////////////////////////////
    PHuman();
    PHuman(std::string new_name, int new_index, PDice *new_dice);
    virtual ~PHuman();


    // PUBLIC METHODS
    /////////////////////////////////////////////////////////
    PPawn *getPawnToMove(); // Asked to return the pawn selected to be moved
};


/**
 *  @brief  Parchis Class: Derived from PPlayer. Represents a Simple robot player.
 *
 * Derived from "Player", this class is a simple robot that decides
 * "randomly" which pawn to play from the movable ones.
 *
 *  @par Sample usage:
 *  @code
 *
 *  // ToDo
 *
 *  @endcode
 *
 */
//---------------------------------------------------------------------------


#pragma mark ====== CLASS PRobotSimple

//---------------------------------------------------------------------------

class PRobotSimple : public PPlayer
{

#pragma mark ====== PRIVATE INSTANCE MEMBERS
private:
    // DEBUGGING purposes

    PDebug dbg;             //!< To be able to send Log messages
    std::ostringstream oss; //!< Construct complex strings


#pragma mark ====== PRIVATE INSTANCE METHODS

    // PRIVATE METHODS

    void initAttributes();


#pragma mark ====== PUBLIC INSTANCE METHODS
public:
    // CONSTRUCTOR/DESTRUCTOR

    PRobotSimple();
    PRobotSimple(std::string new_name, int new_index, PDice *new_dice);
    virtual ~PRobotSimple();


    // METHODS OVERRIDEN

    PPawn *getPawnToMove(PSnapshot **snap);
};


/**
 *  @brief  Parchis Class: Derived from PPlayer. Represents a Smart robot player.
 *
 * Derived from "Player", this class is a smarter robot that decides
 * which pawn to play based on weights.
 *
 *  @par Sample usage:
 *  @code
 *
 *  // ToDo
 *
 *  @endcode
 *
 */
//---------------------------------------------------------------------------


#pragma mark ====== CLASS PRobotSmart

//---------------------------------------------------------------------------

class PRobotSmart : public PPlayer
{

#pragma mark ====== PRIVATE INSTANCE MEMBERS
private:
    // DEBUGGING purposes

    PDebug dbg;             //!< To be able to send Log messages
    std::ostringstream oss; //!< Construct complex strings


    // PRIVATE ATTRIBUTES
    /////////////////////////////////////////////////////////
    static const int weight[NUM_STATES];


#pragma mark ====== PRIVATE INSTANCE METHODS

    // PRIVATE METHODS

    void initAttributes();


#pragma mark ====== PUBLIC INSTANCE METHODS
public:
    // CONSTRUCTOR/DESTRUCTOR

    PRobotSmart();
    PRobotSmart(std::string new_name, int new_index, PDice *new_dice);
    virtual ~PRobotSmart();


    // METHODS OVERRIDEN

    PPawn *getPawnToMove(PSnapshot **snap);
};

#endif // PPLAYER_H
