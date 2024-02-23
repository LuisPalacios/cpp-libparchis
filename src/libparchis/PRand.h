/**
 *  @class  PRand PRand.h "PRand.h"
 *  @brief  Parchis Class declaration: Generar números aleatorios
 *
 *  Belongs to the Library: "Parchis Engine C++ library"
 *
 *  @author  Luis Palacios
 *  @version 0.1
 *  @date    8/Sep/09
 *
 *  @par Description
 *
 *  Genera números aleatorios
 *
 *  @par Sample usage:
 *  @code
 *
 *  MyClass.h
 *    class MyClass {
 *    :
 *      PRand*   aleatorio;       /// Pointer to the class
 *
 *  MyClass.cpp
 *
 *    // DICE
 *    aleatorio = new PRand ( "Alea" );
 *    :
 *
 *  @endcode
 *
 */


#ifndef PRAND_H
#define PRAND_H

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


#pragma mark ====== INCLUDES

//---------------------------------------------------------------------------

// Standard includes
#include "PDebug.h"

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


#pragma mark ====== CLASS PRand

//---------------------------------------------------------------------------

class PRand
{


#pragma mark ====== PRIVATE INSTANCE MEMBERS
private:
    // DEBUGGING purposes

    PDebug dbg;             //!< To be able to send Log messages
    std::ostringstream oss; //!< Construct complex strings


    // PRIVATE ATTRIBUTES
    std::string name; //!< Name assigned to this object

#pragma mark ====== PRIVATE INSTANCE METHODS

    // PRIVATE METHODS

    void initAttributes(); // Initialize the attributes
    // Future study (hash())
    // unsigned hash(time_t t, clock_t c);


#pragma mark ====== PUBLIC INSTANCE METHODS
public:
    // CONSTRUCTOR/DESTRUCTOR

    PRand(std::string new_var); // Constructors/Destructors
    virtual ~PRand();           // Destructor


    // PUBLIC METHODS
    void setName(std::string new_var); // Set the name assigned to this object
    std::string getName();             // Get the name of the object
    float getRandom(float min, float max);
};


//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#endif // PRAND_H
