/**
 *  @class  PDebug PDebug.h "PDebug.h"
 *  @brief  Parchis Class declaration: Shows debug messages on screen (or in the UI)
 *
 *  Belongs to the Library: "Parchis Engine C++ library"
 *
 *  @author  Luis Palacios
 *  @version 0.1
 *  @date    8/Sep/09
 *
 *  @par Description
 *
 *  This class shows debug messages on screen (terminal). It should be
 *  instantiated by each object that wants to show messages. Each object
 *  will use its own Debug object, but all will share the "debug level".
 *
 *  @par PDebug usage:
 *  @code
 *
 *  MyClass.h
 *    class MyClass {
 *    :
 *      private:
 *          PDebug dbg;
 *
 *  MyClass.cpp
 *
 *    // Constructor
 *    PDebug::PDebug ( ) {
 *      dbg.setCallerName ( "MyClass" );
 *      dbg.setDebug(2);
 *    }
 *    :
 *    dbg.printl ( "This is a debug message" );
 *    dbg.printF( 1, "| %-7s (%-7s). Round: %3d. Dice: %2d.  |", board->getColorName(this->getTurn()), player[getTurn()]->getName().c_str(), getNumRound(), i);
 *    :
 *
 *  @endcode
 *
 *  @par Sample: PDebug Cocoa & Objective-C++ callback
 *  @code
 *

 // ParchisPDebugGUIWrapper.m
    :
    #include "PDebug.h"
    #import  "PDebugObjC-Interface.h"
    :
    PDebug guiDbg;
    :
    @implementation ParchisPDebugGUIWrapper
    :
    - (void) awakeFromNib {
        guiDbg.saveObjCObject(self);
    }
    :
    :
    // Class and Instance Methods to Show a Log Message
    void GUIWrapperMuestraMensaje (void *objeto, char *parameter) {
        [(id) objeto muestraMensaje:parameter];
    }
    - (void) muestraMensaje:(char *) aParameter {
        [ self addLog:[NSString stringWithFormat:@"%s", aParameter ]];
    }
    // Class and Instance Methods where I implement the clear of the outlet
    void GUIWrapperClearMensajes (void *objeto) {
        [(id) objeto clearMensajes];
    }
    - (void) clearMensajes {
        [self emptyLog];
    }
 *
 *  @endcode
 */


#ifndef DEBUG_H
#define DEBUG_H

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#pragma mark ====== DEFINES

//---------------------------------------------------------------------------

// MAX STRING
#define MAXCALLERNAME 64  // Max size of memory to reserve for the Caller Name
#define MAXSTRINGDBG 5120 // Max size of memory to reserve to ouput a string

//---------------------------------------------------------------------------

#pragma mark ====== INCLUDES

//---------------------------------------------------------------------------

// Standard includes
#include <iostream>
#include <string>

// Para poder hacer callback a un método de una clase en Objective-C++
//#include "PDebugObjC-Interface.h"


#pragma mark ====== CLASS PDebug

//---------------------------------------------------------------------------

class PDebug
{


#pragma mark ====== PRIVATE INSTANCE MEMBERS
private:
    // STATIC ATTRIBUTES (comment with 3x"/" for doxygen)

    static int
        debug; //!< Overall debug level (shared between all Debug objects)
    static void *
        savedObjCObject; //!< Where I save the pointer to the Objective C Object (instance)
    static bool bSavedObjCObject; //!< true if I've saved the object.
    static bool bPrintToGui;      //!< true if I've to call the savedObjCObject.

    // PRIVATE ATTRIBUTES (comment with 3x"/" for doxygen)

    char callerName[MAXCALLERNAME]; //!< Memory slot to to store the caller name
    char strMsg[MAXSTRINGDBG]; //!< Memory slot to manipulate the debug string
    //char        dbgMsg[MAXSTRINGDBG];           //!< Memory slot to copy the final string to be sent


#pragma mark ====== PRIVATE INSTANCE METHODS

    // PRIVATE METHODS

    void initAttributes(); // Initialize this object, called from constructor


#pragma mark ====== PUBLIC INSTANCE METHODS
public:
    // CONSTRUCTOR/DESTRUCTOR

    PDebug();
    virtual ~PDebug();


    // PUBLIC METHODS

    void setDebug(int new_var); // Set the debug level
    int getDebug();             // Get the debug level

    void setCallerName(std::string new_var); // Set the caller name

    void print(
        int dbg_level,
        std::string
            dbg_msg); // Show a string in screen (debug message) if dbg_level enough
    void printF(int dbg_level, const char *dbg_fmt, ...);

    // To print also in the GUI.
    // Debería montarme un #ifdef ESTOY_EN_XCODE (Averiguar si puedo definirlo igual que en parchis.pro en QT)
    void saveObjCObject(
        void *
            objectiveCObject); // Method used to save the pointer to the Objective-C Object(instance)
    void setPrintToGui(
        bool
            new_var); // Change the flag that tells me if I must call Objective-C to print in the GUI
    bool
    isPrintToGui(); // flag that tells me if I must call Objective-C to print in the GUI
    void clearScreen(); // To emulate a "cls" in the GUI debug output
};


//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#endif // DEBUG_H
