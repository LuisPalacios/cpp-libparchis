/**
 *  @class  PPawn PPawn.h "PPawn.h"
 *  @brief  Parchis Class: Represents a Pawn
 *
 *  Belongs to the Library: "Parchis Engine C++ library"
 *
 *  @author  Luis Palacios
 *  @version 0.1
 *  @date    8/Sep/09
 *
 *  @par Description
 *
 *  This class represents a Pawn and has all the attributes and
 *  its methods control all type of status of the Pawn.
 *  The PPawns objects are instantiated by the Board class
 *
 */


#ifndef PPAWN_H
#define PPAWN_H

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


#pragma mark ====== FORWARD DECLARATIONS

//---------------------------------------------------------------------------

class PSpace;
class PBoard;

//---------------------------------------------------------------------------

#pragma mark ====== INCLUDES

//---------------------------------------------------------------------------

// My includes
#include "PBoard.h"
#include "PDebug.h"
#include "PSpace.h"

// Standard includes
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

//---------------------------------------------------------------------------


#pragma mark ====== CLASS PPawn

//---------------------------------------------------------------------------

class PPawn
{

#pragma mark ====== PRIVATE INSTANCE MEMBERS
private:
    // DEBUGGING purposes

    PDebug dbg;             //!< To be able to send Log messages
    std::ostringstream oss; //!< Construct complex strings


    // PRIVATE ATTRIBUTES

    int index;  //!< Index of the Pawn in an array (i.e. array of 4 pawns: 0-3)
    int number; //!< Number (ID) of this Pawn (i.e. with 4 Pawns per player: 1-4)
    std::string name; //!< Name assigned to the object
    int color;        //!< Number of color
    PBoard *
        board; //!< Pointer to the Board, which was instantiated by Parchis class
    PSpace *mySpace; //!< Pointer to the Space I'm located at
    int lastSpaceIndex; //!< Index of the last space this pawn was (used for animations)

    PSpace *
        dSpace; //!< Pointer to the "destination" space calculated at the Rules object
    bool bCanMove;    //!< The Pawn's can be moved with the Dice tossed
    bool bCanEatPawn; //!< The Pawn can eat another Pawn with the Dice tossed
    bool
        bBehindEatable; //!< for calcBehind: True if during backward analysis discovered that I'm dice distance by enemy
    int numBehindEatsMe; //!< for calcBehind: Number of enemies that could eat me during such analysis
    bool
        bAheadEats; //!< for calcAhead: True if during ahead analysis I discover I can eat


#pragma mark ====== PRIVATE INSTANCE METHODS

    // PRIVATE METHODS

    void initAttributes(); // Initialize the attributes, called from Constructor


#pragma mark ====== PUBLIC INSTANCE METHODS
public:
    // CONSTRUCTORS/DESTRUCTOR
    PPawn(PBoard *new_board,
          std::string new_name,
          int new_index,
          int new_number,
          int new_color);
    virtual ~PPawn(); // Destructor


    // PUBLIC METHODS: Getters for main attributes

    int getIndex();        // Return the index of this pawn
    int getNumber();       // Return the number (ID) associated to this pawn
    std::string getName(); // Return string to the readable name of the pawn
    int getColor();        // Return color
    PSpace *
    getSpace(); // Get the pointer to the space where this pawn is actually located
    void setSpace(
        PSpace *
            new_var); //  Store the pointer to the space where this pawn is located


    // PUBLIC METHODS: Status information

    bool isEditable(); // Returns board->isEditable() state
    bool isAtNormal(); // Is this Pawn located at a Normal space (true/false)?
    bool
    isAtSafe(); // Is this Pawn located at a Safe/RampSafe/Start space (true/false)?
    bool isAtRamp();     // Is this Pawn located at a Ramp space (true/false)?
    bool isAtFinal();    // Is this Pawn located at a Final space (true/false)?
    bool isAtHome();     // Is this Pawn located at Home space (true/false)?
    bool isAtStart();    // Is this Pawn located at Start space (true/false)?
    bool isAtRampSafe(); // Is this Pawn located at RampSafe space (true/false)?
    bool anyAtHome();    // Are there any colleagues from my color at Home?
    bool canMove();      // After rules analysis, can I move?
    bool canEatPawn();   // After rules analysis, can I eat?
    bool
    isBehindEatable(); // After calculating what's behind... I'm at dice distance? 1-6, 7, 10, 20
    bool
    isAheadEats(); // for calcAhead: True if during ahead analysis I have an enemy at "eat" distance (1-6, 7, 10, 20)
    int
    getNumBehindEatsMe(); // After calculating what's behind... how many pawns are threading me.
    int getLastSpaceIndex(); // Get the value of lastSpaceIndex


    // PUBLIC METHODS: Actions and status change

    void newGame(); // Method to execute when "Game" starts a new game
    void setCanMove(
        bool
            new_var); // Set the flag telling if can move (after rules analysis)
    void setCanEatPawn(
        bool
            new_var); // Change the flag telling if can eat (after rules analysis)
    void setDestinationSpace(
        PSpace *
            new_space); // Set the pointer to the destination space calculated by Rules
    PSpace *
    getDestinationSpace(); // Get the pointer to the destination space, used by Game for snapshots
    void setBehindEatable(
        bool
            new_var); // during calcBehind: Change the flag indicating that I can eat
    void setAheadEats(
        bool
            new_var); // during calcAhead: True if during ahead analysis I could eat
    int
    getPawnPosition(); // Return Pawn's position (0-n) inside the space or -1 not in any space.
    int
    getDeltaPosition(); // Return's Pawn's position in an array of delta's (see implementation)
};


//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#endif // PPAWN_H
