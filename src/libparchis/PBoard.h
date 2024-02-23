
/**
 *  @class  PBoard PBoard.h "PBoard.h"
 *  @brief  Parchis Class Declaration: Represents the board, instantiates PGame, PSpace's, PPawn's, PSnapshot's and PDice
 *
 *  Belongs to the Library: "Parchis Engine C++ library"
 *
 *  @author  Luis Palacios
 *  @version 0.1
 *  @date    8/Sep/09
 *
 *  @par Description
 *
 *  This class represents the Parchis's Board. It has information like
 *  colors, quadrants, space types, number of players, total spaces,
 *  number of pawns per player. The Board is in charge of instantiating
 *  most of the objects (w/ the excepcion of the Players)
 *
 *  @par Number associations
 *  @verbatim
 Normal:                  1 - 68

 Yellow Start:            5
 Blue Start:              22
 Red Start:               39
 Green Start:             56

 Ramp Yellow:             69 - 76
 Ramp Blue:               77 - 84
 Ramp Red:                85 - 92
 Ramp Green:              93 - 100

 Ramp Final Yellow:       76
 Ramp Final Blue:         84
 Ramp Final Red:          92
 Ramp Final Green:        100

 RampSafe Yellow:         68
 RampSafe Blue:           17
 RampSafe Red:            34
 RampSafe Green:          51

 RampFirst Yellow:        69
 RampFirst Blue:          77
 RampFirst Red:           85
 RampFirst Green:         93

 Yellow's HOME:           101
 Blue's HOME:             102
 Red's HOME:              103
 Green's HOME:            104
 @endverbatim
 *
 *  The Board instantiates:
 *    - PGame
 *    - PSpace's
 *    - PPawn's
 *    - PPawn's Paths
 *    - PSnapshot's
 *    - PDice
 *    - PPlayer's
 *
 *  It main methods are calcBehind, calcAhead and calcSpanshot
 *  calculate what's behind and ahead for each of the Pawn's and the
 *  snapshot's of the pawn's (that will be used by the robots)
 *
 *  @par Sample usage:
 *  @code
 *
 *  // ToDo
 *
 *  @endcode
 *
 *
 */

#ifndef BOARD_H
#define BOARD_H

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#pragma mark -
#pragma mark Defines

//---------------------------------------------------------------------------

// Colors
#define YELLOW 0  // Id to identify the color Yellow
#define BLUE 1    // Id to identify the color Blue
#define RED 2     // Id to identify the color Red
#define GREEN 3   // Id to identify the color Green
#define NOCOLOR 4 // Id to identify when something has no color

// Quadrants
#define QUADRANT1 1 // Id to identify the first quadrant of the Board
#define QUADRANT2 2 // Id to identify the second quadrant of the Board
#define QUADRANT3 3 // Id to identify the third quadrant of the Board
#define QUADRANT4 4 // Id to identify the fourth quadrant of the Board

// getSpaceType
#define SPACE_NORMAL 0 // A normal space, which is not any of the following
#define SPACE_SAFE 1   // A space which is a Safe position, can't be eated there
#define SPACE_RAMP                                                             \
    2 // The RAMP at the end of pawn's path, just before the final
#define SPACE_FINAL 3 // The FINAL space, when the pawn's finished
#define SPACE_HOME 4  // The HOME space for all the pawn's of a player
#define SPACE_START                                                            \
    5 // This is the first space when going out of HOME. It's a safe space too.
#define SPACE_RAMPSAFE                                                         \
    6 // The space which is just before the final ramp of a pawn

#define NUMPLAYERS                                                             \
    4 // Number of players. This version only supports 4 players, not 6
#define TOTALNUMSPACES                                                         \
    104 // Total number of spaces in the Board, including homes, ramps, finals
#define NUMPAWNSPERPLAYER 4 // Number of Pawn's per player

//---------------------------------------------------------------------------

#pragma mark Forward Declarations

//---------------------------------------------------------------------------

class PGame;
class PPawn;
class PSpace;
class PBoardMemento;

//---------------------------------------------------------------------------

#pragma mark Includes

//---------------------------------------------------------------------------

#include "PBoardMemento.h"
#include "PDebug.h"
#include "PGame.h"
#include "PPawn.h"
#include "PPlayer.h"
#include "PSpace.h"

// Standard includes
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Class interface

//---------------------------------------------------------------------------

class PBoard
{

#pragma mark ====== PRIVATE INSTANCE MEMBERS
private:
    // DEBUGGING purposes

    PDebug dbg;             //!< To be able to send Log messages
    std::ostringstream oss; //!< Construct complex strings

    // STATIC PRIVATE ATTRIBUTES (For ivar's use comments for doxygen: //!<)

    static const char
        *colorName[5]; //!< Strings for each of the colors readable name

    // PRIVATE ATTRIBUTES

    int indexHomeSpaceByColor
        [NUMPLAYERS]; //!< Indexes inside "space" where each Color's HOME is located
    int indexStartSpaceByColor
        [NUMPLAYERS]; //!< Indexes inside "space" where each Color's START is located
    int indexFinalSpaceByColor
        [NUMPLAYERS]; //!< Indexes inside "space" where each Color's FINAL is located
    int indexRampSafeSpaceByColor
        [NUMPLAYERS]; //!< Indexes inside "space" where each Color's RAMP SAFE is located
    int indexRampFirstSpaceByColor
        [NUMPLAYERS]; //!< Indexes inside "space" where each Color's RAMP FIRST is located
    bool bEditable;   //!< True if the board is in editable mode
    std::string name; //!< Name of the Board, mainly for debugging purposes
    std::vector<std::string> vColorName; //!< Names of the colors


    // PRIVATE ATTRIBUTES: Pointers Instantiated by me (Board)

    PGame *game;      //!< Pointer to the Game I will instantiate
    PPlayer **player; //!< NEW: Pointer to the players I will instantiate
    PDice *dice;      //!< Pointer to the dice
    PPawn **yPawn;    //!< Yellow Pawns
    PPawn **bPawn;    //!< Blue Pawns
    PPawn **rPawn;    //!< Red Pawns
    PPawn **gPawn;    //!< Green Pawns
    std::vector<PPawn *> vPawns; //!< Vector to all the Pawns in the Board.
    PSpace **space;              //!< Pointer to All the spaces
    std::vector<PSpace *>
        vPathYellow; //!< Vector to the path that a Yellow Pawn can walk through its Spaces
    std::vector<PSpace *>
        vPathBlue; //!< Vector to the path that a Blue Pawn can walk through its Spaces
    std::vector<PSpace *>
        vPathRed; //!< Vector to the path that a Red Pawn can walk through its Spaces
    std::vector<PSpace *>
        vPathGreen; //!< Vector to the path that a Green Pawn can walk through its Spaces
    std::vector<PSpace *>
        vPathAnalysis; //!< Vector to the 1-68 spaces, used for "behind" and "ahead" analysis
    PPawn **
        lastPawnMoved; //!< Array pointers to the last Pawn that was played (stored for each color)


#pragma mark ====== PRIVATE INSTANCE METHODS

    // PRIVATE METHODS

    void setName(
        std::string new_var); // Set the name of the instantiated object
    void
    initAttributes(); // Instantiate all objects and initialize attributes, called from the constructor
    void
    initVPaths(); // Initialize the vPath*, called from initAttributes() and setMemento()


#pragma mark ====== PUBLIC INSTANCE METHODS
public:
    // CONSTRUCTOR/DESTRUCTOR

    PBoard(std::string new_name); // Constructor
    virtual ~PBoard();            // Destructor


    // STATIC PUBLIC METHODS: accesible by "Board::method()"

    static int getNoColor(); // Get the id for "no color"
    static int getYellow();  // Get the id assigned to the color Yellow
    static int getBlue();    // Get the id assigned to the color Blue
    static int getRed();     // Get the id assigned to the color Red
    static int getGreen();   // Get the id assigned to the color Green
    static int numPlayers(); // Return the number of Players (will be 4)
    static int
    numSpaces(); // Return the total number of spaces in the board (104)
    static int pawnsPerPlayer(); // Return the number of pawns per player (4)
    static int numPawns(); // Return the total number of pawns in the board
    static int
    spaceTypeNormal(); // Returns the ID associated to the space of type Normal
    static int
    spaceTypeSafe(); // Returns the ID associated to the space of type Safe
    static int
    spaceTypeRamp(); // Returns the ID associated to the space of type Ramp
    static int
    spaceTypeFinal(); // Returns the ID associated to the space of type Final
    static int
    spaceTypeHome(); // Returns the ID associated to the space of type Home
    static int
    spaceTypeStart(); // Returns the ID associated to the space of type Start
    static int
    spaceTypeRampSafe(); // Returns the ID associated to the space of type Ramp Safe
    static int Q1();     // Returns the id associated to the quadrant 1
    static int Q2();     // Returns the id associated to the quadrant 2
    static int Q3();     // Returns the id associated to the quadrant 3
    static int Q4();     // Returns the id associated to the quadrant 4


    // PUBLIC METHODS: Access to objects

    PGame *getGame(); // Return the pointer to the Game I've instantiated
    PPawn *getYellowPawn(
        int new_index); // Return the pointer to a specific Yellow Pawn
    PPawn *getBluePawn(
        int new_index); // Return the pointer to a specific Blue Pawn
    PPawn *getRedPawn(
        int new_index); // Return the pointer to a specific Red Pawn
    PPawn *getGreenPawn(
        int new_index); // Return the pointer to a specific Green Pawn
    PPawn *getPawn(
        int new_index); // Return the pointer to a specific Pawn inside the vector vPawns
    PSpace **getSpaces();   // Return the pointer to all the Spaces
    PPlayer **getPlayers(); // Return the pointer to all the players
    std::vector<PPawn *>
    getVPawns(); // Return the pointer to all the vector vPawns
    void setLastPawnMoved(
        PPawn *new_var); // Pointer to the last Pawn that was played
    PPawn *getLastPawnMoved(
        int new_color); // Pointer to the last Pawn that was played by the color
    PDice *getDice();   // Pointer to the Dice


    // PUBLIC METHODS: More...

    std::string getName();
    void setPlayers(PPlayer **new_player);
    void newGame();
    PSpace *getSpaceByNum(
        int new_num); // Get the Space pointer to the Space which number is new_num
    PSpace *getSpaceByIndex(
        int new_index); // Get the Space pointer to the Space which index is new_index
    void setEditable(
        bool new_var); // Change the Board state to Editable (true/false)
    bool isEditable(); // Return if the board is in editable mode
    const char *getColorName(int new_var); // Get the readable name of a color
    int
    getNumTotalPawns(); // Return the total number of Pawns that exists in the Board
    int getIndexHomeSpaceByColor(
        int new_color); // Return the "index" associated to the Home spaces. Value between 0-P_TOTALNUMSPACES
    int getIndexStartSpaceByColor(
        int new_color); // Return the "index" associated to the Start space for a given color
    int getIndexRampSafeSpaceByColor(
        int new_color); // Return the "index" associated to the RampSafe space for a given color
    int getIndexFirstRampSpaceByColor(
        int new_color); // Return the "index" associated to the FirstRamp space for a given color
    int getIndexFinalSpaceByColor(
        int new_color); // Return the "index" associated to the Final space for a given color
    int getPathIndex(
        PSpace *new_space,
        int new_color); // find's the passed "Space" in the color's Path
    std::vector<PSpace *> *getPathVector(
        int new_color); // Return the vector pointer to the path of a color
    std::vector<PSpace *> *
    getPathAnalysis(); // Return the Vector to the 1-68 spaces, used for "behind" and "ahead" analysis by Game class
    void changePlayerType(
        PPlayer *old_player,
        int new_type); // Change the player type (copy all attributes from the old type)

    // NEW Public Methods.
    PSpace *getHomeSpaceOfPawn(
        PPawn
            *new_pawn); // Return the pointer to the HOME space of a given pawn
    PSpace *getStartSpaceOfPawn(
        PPawn
            *new_pawn); // Return the pointer to the HOME space of a given pawn
    bool movePawnToSpace(
        PPawn *the_pawn,
        PSpace *
            new_space); // Moves the pawn to the space, returns success (true) or fail (false)
    bool moveDiceToSpace(
        PDice *the_dice,
        PSpace *
            new_space); // Moves the dice to a space (typically HOME space of the turn)

    // METHODS TO HANDLE MEMENTO's (UNDO/REDO)

    PBoardMemento *createMemento(
        int new_number);               // Save actual state, creates a memento
    void setMemento(PBoardMemento *m); // Go back to a "memento", restores state
};


//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#endif // BOARD_H
