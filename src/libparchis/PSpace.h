/**
 *  @class  PSpace PSpace.h "PSpace.h"
 *  @brief  Parchis Class: represents each of the Spaces in the Parchis game
 *
 *  Belongs to the Library: "Parchis Engine C++ library"
 *
 *  @author  Luis Palacios
 *  @version 0.1
 *  @date    8/Sep/09
 *
 *  @par Description
 *
 *  This class represents each of the Spaces in the Parchis game. It holds
 *  information about the index and number, color, role, orientation (horzontal,
 *  or vertical), number of pawns at the space, etc. It also has several
 *  methods to query the space if a pawn can be placed into it, if there is an
 *  enemy, if a pawn can walk through, etc.
 *
 */

#ifndef SPACE_H
#define SPACE_H

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#pragma mark ====== DEFINES

//---------------------------------------------------------------------------

// Orientation
#define SPACE_NOORIENTATION 0
#define SPACE_HORIZONTAL 1
#define SPACE_VERTICAL 2

// Array of quadrant info
#define NUMPAWNSPERPLAYER 4

//---------------------------------------------------------------------------

#pragma mark ====== FORWARD DECLARATIONS

//---------------------------------------------------------------------------

// Forward declaration of classes
class PPawn;
class PBoard;
class PDice;

//---------------------------------------------------------------------------

#pragma mark ====== INCLUDES

//---------------------------------------------------------------------------

// My includes
#include "PBoard.h"
#include "PDebug.h"
#include "PDice.h"
#include "PPawn.h"

// Standard includes
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
//using namespace std;

//---------------------------------------------------------------------------


#pragma mark ====== CLASS PSpace

//---------------------------------------------------------------------------

class PSpace
{

#pragma mark ====== PRIVATE INSTANCE MEMBERS
private:
    // DEBUGGING purposes

    PDebug dbg;             //!< To be able to send Log messages
    std::ostringstream oss; //!< Construct complex strings

    // PRIVATE ATTRIBUTES

    int index;  //!< The index in the allocated array of Spaces
    int number; //!< The ID or number of this Space
    std::string
        name; //!< String with the name assigned to this space, typically for debugging purposes
    int color; //!< id of the color of the space, if any, only some spaces belong to a Color
    int role; //!< Role (type) of space: normal, safe, ramp, final, home, start and rampsafe.
    int orientation; //!< 0 - N/A,  1- Horizontal  2- Vertical
    int numMaxPawns; //!< Maximum number of Pawns allowed in this Space
    int numPawns;    //!< Number of Pawns currently in this Space
    bool
        bUsedFirstTwoGoOut; //!< True/False if used this Option in my space: First 5 allows to get 2 out of HOME.
    bool bCanGetOutOtherPawn;         //!< Define if can get out other pawn
    int cQuadrant[NUMPAWNSPERPLAYER]; //!< Defines the cuadrants
    PBoard *board;                    //!< Pointer to the board
    std::vector<PPawn *>
        vPawns; //!< Vector to all the Pawns that are currently living in my Space
    PDice *dice; //!< Pointer to the Dice that is currently living in my Space.


#pragma mark ====== PRIVATE INSTANCE METHODS

    // PRIVATE METHODS

    void initAttributes();


#pragma mark ====== PUBLIC INSTANCE METHODS
public:
    // CONSTRUCTOR/DESTRUCTOR

    PSpace(PBoard *new_board,
           std::string new_name,
           int new_type,
           int new_index,
           int new_num,
           int new_color,
           int new_orientation);
    virtual ~PSpace();


    // PUBLIC METHODS: General methos, getters and setters

    void
    newGame(); // To be executed when a new game is asked by the Game object.
    void
    showInfo(); // Just for debugging purposes, show information about this space
    int getIndex();  // Get the ID (index) of the Space
    int getNumber(); // Return the number of the space
    std::string
    getName(); // Return the string readable format of the name given to this object
    void setName(std::string new_name); // Set the space name
    int
    getColor(); // If has a color, return the color of this space, otherwise returns "no color"
    int getOrientation(); // Return the value of orientation
    int
    getRole(); // Get the Role of this space (normal, safe, ramp, final, ...)
    void setQuadrant(
        int new_color,
        int new_var); // Set for each color which Quadrant this Space is located at
    int getQuadrant(
        int new_color); // Get number of quadrant this Space is at for a specific color

    // PUBLIC METHODS: Query Space properties

    bool isHorizontal(); // Returns true if this Space is of type horizontal
    bool isVertical();   // Returns true if this Space is of type vertical
    bool isNormal(); // Returns true if this Space is none of the below cases
    bool
    isSafe(); // Returns true if this Space is of type Safe, Start or RampSafe
    bool isRamp();     // Returns true if this Space is of type Ramp
    bool isFinal();    // Returns true if this Space is of type Final
    bool isHome();     // Returns true if this Space is of type Home
    bool isStart();    // Returns true if this Space is of type Start
    bool isRampSafe(); // Returns true if this Space is of type RampSafe
    bool isBarrier();  // Returns true if this Space is of type Barrier

    // PUBLIC METHODS: Actions with Pawns

    void setNumMaxPawns(
        int new_var); // Store what's the maximum number of Pawns allowed in this space
    int
    getNumMaxPawns(); // Get the maximum number of Pawns allowed to be together in this space
    void setNumPawns(
        int new_var); // Set/Update how many pawns are actually living in the space
    int getNumPawns(); // Get the number of Pawns actually living in the space
    PPawn *getPawn(int new_index); // Get Pawn from vPawns
    PPawn *getEatedPawn(
        PPawn *
            new_pawn); // Return a Pawn (from my space) that is eated by new_pawn
    bool addPawn(PPawn *new_pawn); // Add a new Pawn to my Space
    bool delPawn(PPawn *new_pawn); // Remove Pawn from my Space
    int getPawnPosition(
        PPawn *
            new_pawn); // Return Pawn's position (0-n) inside the space or -1 not present.
    int getPawnWillBePosition(
        PPawn *
            new_pawn); // Return what will be the position of this pawn if moved to my space
    bool canAddPawn(
        PPawn *new_pawn); // Check if the new_pawn Pawn can be added to my space
    bool canWalkPawn(
        PPawn
            *new_pawn); // Check if the new_pawn Pawn can walk through my space
    bool canEatPawn(
        PPawn *
            new_pawn); // Check if the new_pawn Pawn can Eat other Pawn in my space
    bool hasEnemy(
        PPawn *new_pawn); // Check if new_pawn has an enemy in my space.
    bool wasFirst(
        PPawn *
            new_pawn); // Return true if the Pawn was the first one to enter this space
    bool wasLast(
        PPawn *
            new_pawn); // Return true if the Pawn was the last one to enter this space
    bool
    canGetTwoPawnsOutFromHome(); // Check if 1st 5 can get two pawns out of HOME (if this space is a home)?

    bool canAddDice(
        PDice *new_dice);          // Check if the Dice can be added to my space
    bool addDice(PDice *new_dice); // Go ahead and add the dice to the space
    PDice *getDice();              // Return the dice living in my space
    void setDice(PDice *new_dice); // Set the dice living in my space
};

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#endif // SPACE_H
