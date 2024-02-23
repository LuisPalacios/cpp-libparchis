/**
 *  @class  PTime PTime.h "PTime.h"
 *  @brief  Parchis Class: Manage time
 *
 *  Belongs to the Library: "Parchis Engine C++ library"
 *
 *  @author  Luis Palacios
 *  @version 0.1
 *  @date    2/1/12
 *
 *  @par Description
 *
 *  This class helps calculating time intervales
 *
 */

#ifndef PTIME_H
#define PTIME_H

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

#pragma mark ====== INCLUDES

//---------------------------------------------------------------------------

// My includes
#include "PDebug.h"

// Standard includes
#include <iostream>
#if defined(__APPLE__)
#include <mach/mach.h>
#include <mach/mach_time.h>
#elif defined(__linux)
#include <time.h>
#elif defined(WIN32)
#include <windows.h>
#endif


//---------------------------------------------------------------------------


#pragma mark ====== CLASS PTime

//---------------------------------------------------------------------------

class PTime
{

#pragma mark ====== PRIVATE INSTANCE MEMBERS
private:
    static unsigned long
        count; //!< Does NOTHING. You can use it to record whatever you want (used to count dealloc's once) ;-)

    // DEBUGGING purposes
    PDebug dbg; //!< To be able to send Log messages

#pragma mark ====== PRIVATE INSTANCE METHODS

    // PRIVATE METHODS
    void initAttributes();


#pragma mark ====== PUBLIC INSTANCE METHODS
public:
    // CONSTRUCTOR/DESTRUCTOR
    PTime();
    virtual ~PTime();


    // PUBLIC METHODS
    //    void            setCount (unsigned long new_var );  //!< Sets the value of the static unsigned long count.
    //    void            addCount (unsigned long new_var );  //!< Increments "count" by "new_var".
    //    unsigned long   getCount ( );                       //!< Returns the value of the static unsigned long count.
    double getCurrentTime(); //!< Returns the current time
};

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#endif // PTIME_H
