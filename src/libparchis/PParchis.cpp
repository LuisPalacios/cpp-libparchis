
/**
 *  @class  PParchis PParchis.cpp "PParchis.cpp"
 *  @file   PParchis.cpp
 *  @brief  Parchis Class: Definition: Main class responsible for instantiating the board (PBoard).
 *
 *  ---------------------------------------------------------------------------
 */


//---------------------------------------------------------------------------

#include "PParchis.h"
// Librerías externas
#include <fmt/core.h>
#include <spdlog/spdlog.h>

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Private Methods
#pragma mark-- Private: Class initialization

/**
 * Initialize the attributes and create all instances
 */
void PParchis::initAttributes()
{

    // Instantiate the Parchis Rules, Board and Players:
    board = new PBoard("Tablero"); // Instantiate the Board (and Game)

    // Get the version number
    PVersion *pVersion = new PVersion();
    const auto versionTitle =
        fmt::format("|                version: {:<20}           |",
                    pVersion->getVersionFull());

    // Debug purposes
    dbg.setCallerName("Parchis");
    dbg.print(1, "+========================================================+");
    dbg.print(1, "|                    PParchis init                       |");
    dbg.print(1, versionTitle);
    dbg.print(1, "+========================================================+");

    delete pVersion;
}

//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Public Methods
#pragma mark-- Public Constructor/Destructor

//---------------------------------------------------------------------------

/**
 * Constructor of PParchis
 *
 * It will default to name="Human" and Index=0
 */
PParchis::PParchis()
{
    initAttributes();
}

//---------------------------------------------------------------------------

/**
 * Destructor of PParchis
 *
 */
PParchis::~PParchis()
{
    dbg.print(4, "+========================================================+");
    dbg.print(4, "|                 PParchis DESTRUCTOR                    |");
    delete board;
    dbg.print(4, "+===============Fin Destructor PParchis==================+");
    dbg.print(4, "|                                                        |");
}

//---------------------------------------------------------------------------


#pragma mark-- Class Methods (static Public Methods)

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


#pragma mark-- Public methods: More public methods

//---------------------------------------------------------------------------

/**
 * Getter: Access to the board where this game is being played.
 * @return Pointer to PBoard that instantiated me
 */
PBoard *PParchis::getBoard()
{
    return board;
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
