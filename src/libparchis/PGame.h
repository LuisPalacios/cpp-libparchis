
/**
 *  @class  PGame PGame.h "PGame.h"
 *  @brief  Parchis Class: Responsible of the game start, managment, status, options, etc.
 *
 *  Belongs to the Library: "Parchis Engine C++ library"
 *
 *  @author  Luis Palacios
 *  @version 0.1
 *  @date    8/Sep/09
 *
 *  @par Description
 *
 *  This class is responsible of the "game", starting a new game,
 *  different status of the game, options, turns, pawn moving, control, etc.
 *  Main methods are calcBehind, calcAhead and calcSpanshot
 *  calculate what's behind and ahead for each of the Pawn's and the
 *  snapshot's of the pawn's (that will be used by the robots)
 *
 *  Game instantiates:
 *   - PRules
 *   - PSnapshot's
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

#ifndef GAME_H
#define GAME_H

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#pragma mark ====== DEFINES

//---------------------------------------------------------------------------

// Memento
#define UNDOLEVELS 10 // Number of UNDO's allowed

// Game status
#define GAME_NUMBER_OF_STATUS 13
#define STATUS_GAMESTOPPED 0
#define STATUS_WAITINGROLLINGDICE 1
#define STATUS_ROLLINGDICE 2
#define STATUS_DICETOSSED 3
#define STATUS_THREESIX 4
#define STATUS_APPLYINGRULES 5
#define STATUS_WAITINGSELECTPAWN 6
#define STATUS_PAWNSELECTED 7
#define STATUS_MOVINGPAWN 8
#define STATUS_FINISHMOVINGPAWN 9
#define STATUS_CHANGINGTURN 10
#define STATUS_COUNTTWENTY 11
#define STATUS_COUNTTEN 12

//---------------------------------------------------------------------------

#pragma mark ====== FORWARD DECLARATIONS

//---------------------------------------------------------------------------

class PBoard;
class PPlayer;
class PRules;

//---------------------------------------------------------------------------

#pragma mark ====== INCLUDES

//---------------------------------------------------------------------------

#include "PBoard.h"
#include "PBoardMemento.h"
#include "PDebug.h"
#include "PPlayer.h"
#include "PPlayerMemento.h"
#include "PRules.h"
#include "PSnapshot.h"

// Standard includes
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>


#pragma mark ====== CLASS PGame

//---------------------------------------------------------------------------

class PGame
{

#pragma mark ====== PRIVATE INSTANCE MEMBERS
private:
    // DEBUGGING purposes

    PDebug dbg;             //!< To be able to send Log messages
    std::ostringstream oss; //!< Construct complex strings

    // PRIVATE ATTRIBUTES (For ivar's use comments for doxygen: //!<)

    std::string name; //!< Name of the Game, mainly for debugging purposes
    int turn; //!< Integer to the turn number (0-4) equivalen to the color number
    PBoard *
        board; //!< Pointer to the Board. I'm passed this pointer, which is instantiated by the PBoard class
    PPlayer **
        player; //!< Pointer to the Players. I'm passed this pointer, which is instantiated by the PBoard class
    std::vector<PPawn *>
        vPawns; //!< Vector to all the Pawns pointers, instantiated by PBoard class
    PRules *rules; //!< Pointer to the Rules, instantiated by this class "PGame"
    int numSavedMementos; //!< Total number of saved mementos (or undos available)
    int numActualMemento; //!< In which "memento" we are actually.
    PPawn *selectedPawn;  //!< Pointer to the Selected pawn to be moved
    PPawn *lastEatedPawn; //!< Pointer to the last eated pawn

    // MEMENTO CONTROL

    std::vector<PPlayerMemento *>
        vPlayerMemento; //!< Vector to the pointers of all player's memento's.
    std::vector<PBoardMemento *>
        vBoardMemento; //!< Vector to the pointers to board's memento's.


    // PRIVATE ATTRIBUTES: Game options

    bool bUndoActive; //!< True if Undo functionality is enabled.
    bool
        bOptionCanCrossSelfBarrier; //!< True if a Pawn can jump or cross a barrier of 2 pawns from its self color
    bool
        bOptionCanEatHomeBarrier; //!< True if a Pawn at HOME can eat Barrier at its start (different color)
    bool
        bOptionCanTwoGoOutHome; //!< True if first 5 lets get two pawn out of HOME
    bool
        bOptionStartTwoOut; //!< True, then when starting new game plac two pawns at START
    bool
        bOptionFirstWinnerEndsGame; //!< True/false: Tells me to FINISH the GAME when first player Wins or leaves it till all at HOME


    // PRIVATE ATTRIBUTES: Game status

    static const char *txtGameStatus
        [GAME_NUMBER_OF_STATUS]; //!< Strings that describe each of the game status
    int gameStatus; //!< Integer to identify which status we are inside the game (0-11)
    bool
        playerPlaysAgain; //!< Used internally between newTurn() and playerTossDice() to identify if the player plays again


    // PRIVATE ATTRIBUTES: Game control

    int lastDice; //!< Value of the last dice tossed (1,2,3,4,5,6)
    int lastDiceForward; //!< Value of the real num. of spaces to move forward (1..6,7,10,20)
    int numRound;      //!< Number of turns/plays done in the whole game
    int numSixes;      //!< Number of 6's got by current player
    int numThreeSixes; //!< Number of times 3 sixes appeared
    int numPlayerFinished; //!< Number of players that finished (got all pawns FINAL)
    int numColorWinner; //!< First color to win
    bool
        bFlagThirdSix; //!< Flag true/false: Pawn got its third 6, so it has to go home and turn changes.
    bool bFlagSix;     //!< Flag true/false: Pawn got a 6 so can't change turn
    bool
        bPawnEated; //!< Flag true/false: Pawn 'eated', so player repeats and counts 20.
    bool
        bPawnGotFinal; //!< Flag true/false: Pawn 'got to final space', so player repeats and counts 10
    bool
        bFlagTwoGoOutHome; //!< Flag true/false: Pawn got a 5 and can get two out of HOME.dy at START
    PSnapshot *
        *snapshot; //!< Pointer to each of the pawn's status (one per each pawn)
    std::vector<PSpace *> *
        vPathAnalysis; //!< Vector to the 1-68 spaces for "behind" and "ahead" analysis. Instantiated at Board class


#pragma mark ====== PRIVATE INSTANCE METHODS

    // PRIVATE METHODS: Set private attributes

    void
    initAttributes(); // Instantiate all objects and initialize attributes, called from the constructor
    void setNumThreeSixes(int new_var); // Number of times 3 sixes appeared
    void setNumPlayerFinished(
        int new_var); // Number of players that have finished (got all pawns FINAL)
    void setPawnEated(bool new_var); // Controls if Pawn 'eated', so counts 20.
    void setLastEatedPawn(PPawn *);  // Store the pointer to the last eated pawn
    void setPawnGotFinal(
        bool new_var); // Controls if Pawn 'got to final space', so counts 10


    // PRIVATE METHODS: Getters/Setters Game status

    int getStatusGameStopped();       // Returns such status
    int getStatusRollingDice();       // Returns such status
    int getStatusThreeSix();          // Returns such status
    int getStatusApplyingRules();     // Returns such status
    int getStatusWaitingSelectPawn(); // Returns such status
    int getStatusPawnSelected();      // Returns such status
    int getStatusMovingPawn();        // Returns such status
    int getStatusFinishMovingPawn();  // Returns such status
    int getStatusChangingTurn();      // Returns such status
    int getStatusCountTwenty();       // Returns such status
    int getStatusCountTen();          // Returns such status

    void setStatusGameStopped(); // Change the status of the game to such value
    void
    setStatusWaitingRollingDice(); // Change the status of the game to such value
    void setStatusRollingDice(); // Change the status of the game to such value
    void setStatusDiceTossed();  // Change the status of the game to such value
    void setStatusThreeSix();    // Change the status of the game to such value
    void
    setStatusApplyingRules(); // Change the status of the game to such value
    void
    setStatusWaitingSelectPawn(); // Change the status of the game to such value
    void setStatusPawnSelected(); // Change the status of the game to such value
    void setStatusMovingPawn();   // Change the status of the game to such value
    void
    setStatusFinishMovingPawn();  // Change the status of the game to such value
    void setStatusChangingTurn(); // Change the status of the game to such value
    void setStatusCountTwenty();  // Change the status of the game to such value
    void setStatusCountTen();     // Change the status of the game to such value
    void setGameStatus(
        int new_status); // Change the status of the game to the passed value


    // PRIVATE METHODS: Game control

    void
    calcSnapshots(); // Calculate the Snapshot, all info that will be used by the Robots
    void calcBehind(
        PPawn *p,
        PSpace *s); // Calculate what's behind the Pawn p, starting at Space s
    void calcAhead(
        PPawn *p,
        PSpace *s); // Calculate what's ahead the Pawn p, starting at Space s


    // MEMENTO Saving/Restoring
    void saveMementos(); // Caretaker that saves the mementos


#pragma mark ====== PUBLIC INSTANCE METHODS
public:
    // CONSTRUCTOR/DESTRUCTOR

    PGame(std::string new_name);
    virtual ~PGame();


    // PUBLIC METHODS: Connect Game with the board & players

    void setBoardPlayers(PBoard *new_board, PPlayer **new_player);


    // PUBLIC METHODS: Getters information about the game

    std::string getName();
    void setNumRound(
        int new_var); // Number of the ruond we (turns/plays) done during the whole game
    int
    getNumRound(); // Number of the ruond we (turns/plays) done during the whole game
    int getNumSixes();             // Number of 6's got by current player
    void setNumSixes(int new_var); // Number of 6's got by current player
    int getNumThreeSixes();        // Number of times 3 sixes appeared
    int
    getNumColorWinner(); // Number of the first color to win (reach all pawns FINAL)
    int
    getNumPlayerFinished(); // Number of players that have finished (all pawns got FINAL)


    // PUBLIC METHODS: Game flags

    bool
    isOptionFirstWinnerEndsGame(); // Flag true/false: Tells me to FINISH the GAME when first player Wins or leaves it till all at HOME
    bool
    isFlagThirdSix(); // Flag true/false: Pawn got its third 6, so it has to go home and turn changes.
    bool isFlagSix(); // Flag true/false: Pawn got a 6, so turn doesn't change
    bool
    isFlagPawnEated(); // Flag true/false: Pawn 'eated', so player repeats and counts 20.
    bool
    isFlagPawnGotFinal(); // Flag true/false: Pawn 'got to final space', so player repeats and counts 10
    bool
    isFlagTwoGoOutHome(); // Flag true/false: Pawn got a 5 and can get two out of HOME.
    bool
    isOptionStartTwoOut(); // Flag true/false: New game will have first two Pawns already at START
    void setOptionFirstWinnerEndsGame(
        bool
            new_value); // Flag true/false: Tells me to FINISH the GAME when first player Wins or leaves it till all at HOME
    void setFlagTwoGoOutHome(
        bool
            new_value); // Flag true/false: Pawn got a 5 and can get two out of HOME.
    void setOptionStartTwoOut(
        bool
            new_value); // When starting new game, do it with first two pawns already at START
    bool
    canCrossSelfBarrier(); // True if a Pawn can jump or cross a barrier of 2 pawns from its self color
    bool
    canEatHomeBarrier(); // True if a Pawn at HOME can eat Barrier at its start (different color)
    bool canTwoGoOutHome(); // True if first 5 lets get two pawn out of HOME


    // PUBLIC METHODS: Game status

    int getGameStatus(); // Returns actual gameStatus value (STATUS_???)
    int getStatusWaitingRollingDice(); // Returns such status
    int
    getStatusDiceTossed(); // Returns the value of status "STAT 2: Dice has been tossed"
    bool isRunning(); // Returns true if Status != STATUS_GAMESTOPPED
    bool
    isWaitingSelectPawn(); // Returns true if Game is waiting for Player to select a Pawn
    bool
    isPlayingAgain(); // Returns true if current player is actually playing again because last turn got 6, 10 or 20
    bool
    isPlayerFinished(); // Returns true if current player has finished, has all Pawn's at END space
    const char *
    getTxtGameStatus(); // Returns text that describes current game status (from txtGameStatus[GAME_POSSIBLE_STATUS])
    bool
    movablePawns(); // true if there are movable Pawns after execution of the rules


    // PUBLIC METHODS: Game actions

    void newGame(); // Start a new game
    void
    execRules(); // Analyse the rules and stablish if movable, eatable, etc.
    void playerTossDice(
        int new_dice); // Ask the Player to toss the dice and control the effect of the new dice
    void setTurn(int new_var); // Set the turn to the passed value
    int getTurn(); // Get the current turn value (equals to the color value)
    bool
    newTurn(); // Changes the turn and Returns true if the turn has changed or false otherwise
    void
    selectPawn(); // Ask the robot to select a pawn a save its pointer (selectedPawn)
    void selectPawn(PPawn *new_pawn); // Save the pointer to the selected pawn
    int
    selectedPawnOriginSpaceIndex(); // Returns the origin space of the selected pawn that is being moved
    int
    selectedPawnOriginSpacePos(); // Returns the position inside the origin space of the selected pawn that is being moved
    int
    selectedPawnDestinationSpaceIndex(); // Returns the destination space of the selected pawn that is being moved
    int
    selectedPawnDestinationSpacePos(); // Returns the position inside the destination space of the selected pawn that is being moved
    PPawn *getSelectedPawn();
    void movePawn(); // Move the Pawn
    bool movePawnManuallyToSpace(
        PPawn *new_pawn,
        int new_space_index); // Move a pawn manually to a space
    void sendLastMovedHome(); // Send Home the last Pawn moved (due to 3 sixes)


    // PUBLIC METHODS: Game control

    int getLastDice(); // Get Value of the dice played in last/previous turn
    void setLastDice(
        int new_var); // Set manually the value of the last dice played
    void setLastDiceForward(
        int new_var); // Set the value of the (dice) spaces to advance, not equal to the dice: remember 7, 10, 20...
    int getLastDiceForward(); // Get number of spaces to advance 1..6, 7, 10, 20
    PPawn *getLastEatedPawn(); // Get the pointer to the last eated pawn
    PPlayer *
    getCurrentPlayer(); // Return the pointer to the current player in this turn
    bool undo();        // Undo last action
    bool redo();        // Redo last action
};


//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#endif // GAME_H
