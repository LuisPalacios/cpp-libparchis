/**
 *  @class  PRules PRules.h "PRules.h"
 *  @brief  Parchis Class: Rules after dice tossed and calculates destinations
 *
 *  Belongs to the Library: "Parchis Engine C++ library"
 *
 *  @author  Luis Palacios
 *  @version 0.1
 *  @date    8/Sep/09
 *
 *  @par Description
 *
 *  Parchis's rules, responsible for executing the rules after the dice
 *  has been tossed, also is in charge of calculating possible destinations
 *
 */

#ifndef RULES_H
#define RULES_H


//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


#pragma mark ====== INCLUDES

//---------------------------------------------------------------------------

// My includes
#include "PGame.h"

// Standard includes
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

//---------------------------------------------------------------------------


#pragma mark ====== CLASS PRules

//---------------------------------------------------------------------------

class PRules
{

#pragma mark ====== PRIVATE INSTANCE MEMBERS
private:
    // DEBUGGING purposes

    PDebug dbg;             //!< To be able to send Log messages
    std::ostringstream oss; //!< Construct complex strings


    // PRIVATE ATTRIBUTES

    PGame *game; //!< Pointer to the game
    std::string
        name; //!< String with the name assigned to this Rules, typically for debugging purposes
    int numPawnsMovable; //!< After checking the rules I store the number of Pawns that are movable
    int numPawnsCanEat; //!< After checking the rules I store the number of Pawns that can eat

#pragma mark ====== PRIVATE INSTANCE METHODS

    // PRIVATE METHODS

    void
    initAttributes(); // Initialize the attributes of the object, called from constructor
    void setName(std::string new_var); // Set the name of this object


#pragma mark ====== PUBLIC INSTANCE METHODS
public:
    // CONSTRUCTOR/DESTRUCTOR

    PRules(std::string new_name, PGame *new_game); // Constructor
    virtual ~PRules();                             // Destructor


    // PUBLIC METHODS

    std::string getName(); // Get the name of the object
    int
    getNumPawnsMovable(); // After checking the rules I store the number of Pawns that are movable
    int
    getNumPawnsCanEat(); // After checking the rules I store the number of Pawns that can eat
    int execRules(PBoard *board, int new_forward); // Execute the Rules
    PSpace *calcDestination(
        PBoard *board,
        PPawn *new_pawn,
        int new_forward); // Calculate if destination is possible.
};

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#endif // RULES_H
