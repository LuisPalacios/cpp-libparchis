
/**
 *  @class  PBoardMemento PBoardMemento.h "PBoardMemento.h"
 *  @brief  Parchis Class declaration: Stores/Restores internal state of the Board object for undo/redo.
 *
 *  Belongs to the Library: "Parchis Engine C++ library"
 *
 *  @author  Luis Palacios
 *  @version 0.1
 *  @date    8/Sep/09
 *
 *  @par Description
 *
 *  Stores/Restores internal state of the Board object, it's based on the
 *  Memento design patter. Good reference (spanish)
 *  www.freewebz.com/amanecer/personal/papers/paper.memento.pdf
 *
 *  A memento is an object that stores a snapshot of the internal state of another
 *  object. It can be leveraged to support multi-level undo.
 *
 *  Originator   Parchis.class        (Creates the memento object)
 *  Memento      ParchisMemento.class (Stores/Restores internal state of a Player object)
 *  CareTaker    Game.cpp             (Calls parchi's createMemento/setMemento to control the undo/redo's)
 *
 */

#ifndef BOARDMEMENTO_H
#define BOARDMEMENTO_H

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#pragma mark ====== FORWARD DECLARATIONS

//---------------------------------------------------------------------------

class PPlayer;
class PBoard;

//---------------------------------------------------------------------------

#pragma mark ====== INCLUDES

//---------------------------------------------------------------------------

// My includes
#include "PBoard.h"
#include "PDebug.h"

// Standard includes
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#pragma mark ====== CLASS PBoardMemento

//---------------------------------------------------------------------------

class PBoardMemento
{


#pragma mark ====== PRIVATE INSTANCE MEMBERS
private:
    // DEBUGGING purposes
    PDebug dbg;             //!< To be able to send Log messages
    std::ostringstream oss; //!< Construct complex strings


    // PRIVATE ATTRIBUTES, what I'm saving
    int index; //!< Index of this memento in the stack of mementos


    // PRIVATE ATTRIBUTES, what I'm saving
    PGame *game;      //!< Pointer to what I'm saving: PGame*
    PPlayer **player; //!< Pointer to what I'm saving: PPlayer**
    PPawn **yPawn;    //!< Pointer to what I'm saving: PPawn** yellow pawns
    PPawn **bPawn;    //!< Pointer to what I'm saving: PPawn** blue pawns
    PPawn **rPawn;    //!< Pointer to what I'm saving: PPawn** red pawns
    PPawn **gPawn;    //!< Pointer to what I'm saving: PPawn** yellow pawns
    std::vector<PPawn *>
        vPawns; //!< Pointer to what I'm saving: vector to all the Pawns in the Board.
    PSpace **space; //!< Pointer to what I'm saving: PSpace** Spaces
    PPawn **
        lastPawnMoved; //!< Pointer to what I'm saving: Array pointers to the last Pawn that was played (stored for each color)

    // FRIEND CLASS:
    friend class
        PBoard; //!< declare the originator a friend. For memento (undo/redo)


#pragma mark ====== PUBLIC INSTANCE METHODS
public:
    // CONSTRUCTOR/DESTRUCTOR

    PBoardMemento(int new_index,
                  PBoard *the_board,
                  PGame *o_game,
                  PPlayer **o_player,
                  PPawn **o_yPawn,
                  PPawn **o_bPawn,
                  PPawn **o_rPawn,
                  PPawn **o_gPawn,
                  std::vector<PPawn *> o_vPawns,
                  PSpace **o_space,
                  PPawn **o_lastPawnMoved); // Constructor
    virtual ~PBoardMemento();               // Destructor


    // PUBLIC METHODS

    PGame *getGame();                 // Return the pointer to the game
    PPawn **getYPawn();               // Return the pointer to Yellow Pawns
    PPawn **getBPawn();               // Return the pointer to Blue Pawns
    PPawn **getRPawn();               // Return the pointer to Red Pawns
    PPawn **getGPawn();               // Return the pointer to Green Pawns
    PSpace **getSpaces();             // Return the pointer to all the Spaces
    PPlayer **getPlayers();           // Return the pointer to all the players
    std::vector<PPawn *> getVPawns(); // Return the pointer to all Pawns
    PPawn **getLastPawnMoved();
};


//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#endif // BOARDMEMENTO_H
