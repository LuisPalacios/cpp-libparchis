/**
 *  @class  PDice PDice.h "PDice.h"
 *  @brief  Parchis Class declaration: Represents the dice of the game
 *
 *  Belongs to the Library: "Parchis Engine C++ library"
 *
 *  @author  Luis Palacios
 *  @version 0.1
 *  @date    8/Sep/09
 *
 *  @par Description
 *
 *  Class that represents a Dice. The players will toss a random dice
 *  and set/get lastest tossed dice.
 *
 *  @par Sample usage:
 *  @code
 *
 *  MyClass.h
 *    class MyClass {
 *    :
 *      PDice*   dice;       /// Pointer to the dice
 *
 *  MyClass.cpp
 *
 *    // DICE
 *    dice = new PDice ( "Dice" );
 *    :
 *
 *  @endcode
 *
 */


#ifndef DICE_H
#define DICE_H

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


#pragma mark ====== INCLUDES

//---------------------------------------------------------------------------

// Standard includes
#include "PDebug.h"
#include "PSpace.h"

// Standard includes
#include <climits>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/time.h>

//---------------------------------------------------------------------------


#pragma mark ====== CLASS PDice

//---------------------------------------------------------------------------

class PDice
{


#pragma mark ====== PRIVATE INSTANCE MEMBERS
private:
    // DEBUGGING purposes

    PDebug dbg;             //!< To be able to send Log messages
    std::ostringstream oss; //!< Construct complex strings


    // PRIVATE ATTRIBUTES

    int myDice;       //!< Store the last dice value (tossed)
    PSpace *mySpace;  //!< Pointer to the Space I'm located at
    std::string name; //!< Name assigned to this object


#pragma mark ====== PRIVATE INSTANCE METHODS

    // PRIVATE METHODS

    void initAttributes(); // Initialize the attributes
    // Future study (hash())
    // unsigned hash(time_t t, clock_t c);


#pragma mark ====== PUBLIC INSTANCE METHODS
public:
    // CONSTRUCTOR/DESTRUCTOR

    PDice(std::string new_var); // Constructors/Destructors
    virtual ~PDice();           // Destructor


    // PUBLIC METHODS

    void setName(std::string new_var); // Set the name assigned to this object
    std::string getName();             // Get the name of the object
    void setDice(int new_var);         // Set the last dice tossed
    int getDice();                     // Get the last dice tossed
    void randomDice(); // Toss the dice and generate a random value (1-6)
    PSpace *
    getSpace(); // Get the pointer to the space where this pawn is actually located
    void setSpace(
        PSpace *
            new_var); // Store the pointer to the space where this pawn is located
};


//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#endif // DICE_H
