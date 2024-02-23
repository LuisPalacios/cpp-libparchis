/**
 *  @class  PPlayerMemento PPlayerMemento.h "PPlayerMemento.h"
 *  @brief  Parchis Class: Stores/Restores internal state of a Player object
 *
 *  Belongs to the Library: "Parchis Engine C++ library"
 *
 *  @author  Luis Palacios
 *  @version 0.1
 *  @date    8/Abr/10
 *
 *  @par Description
 *
 *  Stores/Restores internal state of a Player object, it's based on the
 *  Memento design patter. Good reference (spanish)
 *  www.freewebz.com/amanecer/personal/papers/paper.memento.pdf
 *
 *  A memento is an object that stores a snapshot of the internal state of another
 *  object. It can be leveraged to support multi-level undo.
 *
 *  Originator   Player.class        (Creates the memento object)
 *  Memento      PlayerMemento.class (Stores/Restores internal state of a Player object)
 *  CareTaker    Game.cpp            (Calls player's createMemento/setMemento to control the undo/redo's)
 *
 */

#ifndef PLAYERMEMENTO_H
#define PLAYERMEMENTO_H

//---------------------------------------------------------------------------

#pragma mark ====== INCLUDES

//---------------------------------------------------------------------------

// My Includes
#include "PDebug.h"

// Standard includes
#include <iostream>
#include <sstream>
#include <string>

//---------------------------------------------------------------------------


#pragma mark ====== CLASS PPlayerMemento

//---------------------------------------------------------------------------

class PPlayerMemento
{

#pragma mark ====== PRIVATE INSTANCE MEMBERS
private:
    // DEBUGGING purposes

    PDebug dbg;             //!< To be able to send Log messages
    std::ostringstream oss; //!< Construct complex strings

    // PRIVATE ATTRIBUTES THAT ARE SAVED

    int type; //!< Type of Player, either Human or Robot
    std::string
        name; //!< String with the name assigned to this Player, typically for debugging purposes

    // FRIEND CLASS:

    friend class
        Player; //!< declare the originator a friend. For memento (undo/redo)

#pragma mark ====== PUBLIC INSTANCE METHODS
public:
    // CONSTRUCTOR/DESTRUCTOR

    PPlayerMemento(std::string o_name, int o_type); // Constructor
    virtual ~PPlayerMemento();                      // Destructor


    // PUBLIC METHODS

    std::string getName(); // Get the name of the object
    int getType();         // Get the type of the object
};

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#endif // PLAYERMEMENTO_H
