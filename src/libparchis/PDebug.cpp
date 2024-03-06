
/**
 *  @class  PDebug PDebug.cpp "PDebug.cpp"
 *  @file   Pdebug.cpp
 *  @brief  Parchis Class definition: Shows debug messages on screen (or in the UI)
 *
 *  ---------------------------------------------------------------------------
 */


//---------------------------------------------------------------------------

#include "PDebug.h"
#include <cstring>
#include <fmt/core.h>
#include <spdlog/spdlog.h>
#include <stdarg.h>

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Static Attributes

// The C++ standard requires a definition of static's
int PDebug::debug;
void *PDebug::savedObjCObject;
bool PDebug::bSavedObjCObject;
bool PDebug::bPrintToGui;

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Private Methods
#pragma mark-- Class initialization

/**
 * Initialize the attributes and create all instances
 */
void PDebug::initAttributes()
{
    static int flag = 0;

    // Pongo a cero
    memset(callerName, '\0', MAXCALLERNAME);

    // Initial values for the static's
    if (flag == 0)
    {
        setDebug(0);
        setCallerName("PDebug ");
        flag = 1;
    }
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Public Methods
#pragma mark-- Constructor/Destructor

//---------------------------------------------------------------------------

/**
 * Constructor of PDebug
 */
PDebug::PDebug()
{
    initAttributes();
}
/**
 * Destructor of PDebug
 */
PDebug::~PDebug()
{
}

//---------------------------------------------------------------------------


#pragma mark-- Public Methods

//---------------------------------------------------------------------------

/**
 * Set the value of debug
 * @param new_var the new value of debug
 */
void PDebug::setDebug(int new_var)
{
    debug = new_var;
    //std::cout << "PDebug::setDebug debug='" << debug << "'" << std::endl;
}

//---------------------------------------------------------------------------

/**
 * Get the value of debug
 * @return the value of debug
 */
int PDebug::getDebug()
{

    return debug;
}

//---------------------------------------------------------------------------

/**
 * Set the value of callersName from a "std::string"
 * @param new_var the new value of callerName
 */
void PDebug::setCallerName(std::string new_var)
{
    strncpy(callerName, new_var.c_str(), MAXCALLERNAME - 1);
}

//---------------------------------------------------------------------------

/**
 * Get the value of callerName
 * @return the value of callerName
 */
//std::string PDebug::getCallerName ( )   {
//    return callerName;
//}

//---------------------------------------------------------------------------

/**
 * Show a message in the standard output if "the_dbg_level" y <= "debug"
 * @param dbg_level the Debug Level for which this message must be shown.
 * @param dbg_msg the message to show
 *
 * ORIGINAL:
 *  std::cout << "PDebug(" << dbg_level << ") " << callerName << ": " << dbg_msg << std::endl;
 *
 * PRUEBAS CallBack a ObjC
 *
 */
void PDebug::print(int dbg_level, std::string dbg_msg)
{
    if (dbg_level && (dbg_level <= debug))
    {

        // Show it on Console
        //sprintf(dbgMsg, "PDebug(%d) %s: %s\n", dbg_level, callerName, dbg_msg.c_str());
        //std::cout << dbgMsg; // << std::endl;

        // Show it on Console
        // std::cout << "PDebug(" << dbg_level << ") " << callerName << ": "
        //           << dbg_msg.c_str() << std::endl;


        auto mensaje =
            fmt::format("PDebug({}) {}: {}", dbg_level, callerName, dbg_msg);
        spdlog::info(mensaje);
    }
}

//---------------------------------------------------------------------------

/**
 * Show a message using the sprintf format dbg_fmt in the standard output if enough debug level
 * @param dbg_level the Debug Level for which this message must be shown.
 * @param dbg_fmt format to use.
 *
 *  @par Sample usage:
 *  @code
 *
 *   :
 *   dbg.printF( 1, "| %-7s (%-7s). Round: %3d. Dice: %2d.  |", board->getColorName(this->getTurn()), player[getTurn()]->getName().c_str(), getNumRound(), i);
 *   :
 *
 *  @endcode
 *
 */
// void PDebug::printF(int dbg_level, const char *dbg_fmt, std::string dbg_msg) {
//    sprintf(strMsg, dbg_fmt, dbg_msg.c_str() );
//}
void PDebug::printF(int dbg_level, const char *first_arg, ...)
{
    if (dbg_level && (dbg_level <= debug))
    {

        va_list ap;
        va_start(ap, first_arg);

        vsnprintf(strMsg, MAXSTRINGDBG - 1, first_arg, ap);

        print(dbg_level, strMsg);
        va_end(ap);
    }
}

//---------------------------------------------------------------------------


#pragma mark-- Public Methods: Callbak to GUI

//---------------------------------------------------------------------------

/**
 *  Save the Objective-C++ object that I'll use to
 *  show debug messages in the UI.
 */
void PDebug::saveObjCObject(void *objectiveCObject)
{
    savedObjCObject = objectiveCObject;
    bSavedObjCObject = true;
}

//---------------------------------------------------------------------------

/**
 *  Set the flag (true/false) that tells me if I should callback to Objective-C++
 *  to print also in the GUI.
 *  @param new_var the new boolean value (true or false)
 */
void PDebug::setPrintToGui(bool new_var)
{
    bPrintToGui = new_var;
}

//---------------------------------------------------------------------------

/**
 *  Tells if I'm going to print also in the Gui or not.
 *  @return the vlue of the boolean flag bPrintToGui
 */
bool PDebug::isPrintToGui()
{
    if (bPrintToGui)
        return true;
    return false;
}

//---------------------------------------------------------------------------

/**
 * clearScreen()
 * Emulates a cls in the gui output.
 */
void PDebug::clearScreen()
{
    // Clear the GUI's debug screen
    if (bPrintToGui)
    {
        //        if ( bSavedObjCObject ) {
        //            GUIWrapperClearMensajes(savedObjCObject);
        //        }
    }
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
