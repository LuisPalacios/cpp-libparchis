
/**
 *  @class  PGame PGame.cpp "PGame.cpp"
 *  @file   PGame.cpp
 *  @brief  Parchis Class: Responsible of the game start, managment, status, options, etc.
 *
 *  ---------------------------------------------------------------------------
 */


//---------------------------------------------------------------------------

#include "PBoard.h"

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Static Attributes

const char *PGame::txtGameStatus[GAME_NUMBER_OF_STATUS] = {
    "STAT 0: Game Stopped",
    "STAT 1: Waiting for player to Roll the dice",
    "STAT 2: Rolling the dice",
    "STAT 3: Dice has been tossed",
    "STAT 4: Player got three six",
    "STAT 5: Analysing the rules",
    "STAT 6: Waiting for a pawn to be selected",
    "STAT 7: The pawn to be moved has been selected",
    "STAT 8: The pawn is being moved",
    "STAT 9: The pawn finished moving",
    "STAT 10: Changing the turn",
    "STAT 11: Pawn eats: Counts 20",
    "STAT 12: Pawn finished: Counts 10"};

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Private Methods
#pragma mark-- Private: Class initialization

/**
 * Initialize the attributes and create all instances
 */
void PGame::initAttributes()
{
    dbg.setCallerName("Game   ");
    dbg.print(4, "| Constructor Game                                       |");

    // Setup initial Game options
    bUndoActive =
        false; // Disable Undo feature (NOTE I had to do it due to memory leak...)

    bOptionCanCrossSelfBarrier =
        true; // True/False if a Pawn can jump or cross a barrier of 2 pawns from its self color
    bOptionCanEatHomeBarrier =
        false; // True/False if a Pawn at HOME can eat Barrier at its start (different color)
    bOptionCanTwoGoOutHome =
        true; // True/False first 5 lets get two pawn out of HOME
    bOptionFirstWinnerEndsGame =
        true; // True/false: Tells me to FINISH the GAME when first player Wins or leaves it till all at HOME
    bOptionStartTwoOut =
        false; // True/False: Option by default, start two out of Home.

    // Initially the game is stopped
    gameStatus = this->getStatusGameStopped();

    // Instantiate the Rules
    rules = new PRules("Rules", this); // Instantiate the Rules

    // Instantiate the Snapshot's
    //
    // One per each "pawnsPerPlayer". Each snapshot will be calculated
    // at each turn of the game, and will contain a "snapshot" of the
    // current situation of the pawn, as: can eat, is eatable, can move,
    // its coleagues are in danger, etc, etc.
    //
    // This information will be sent to the Robots so they have subjective
    // information about the actual rationale, situation and conditions
    // of each Pawn at the board in the current turn.
    //
    // This will allow the robots to make their decisions
    snapshot = NULL;
    snapshot = new PSnapshot *[PBoard::pawnsPerPlayer()];
    for (int i = 0; i < PBoard::pawnsPerPlayer(); i++)
    {
        oss.str("");
        oss << "Snap" << i << "  ";
        snapshot[i] = new PSnapshot(oss.str());
    }

    // Initialize the number of saved mementos and which memento we
    // are actually in.
    if (bUndoActive)
    {
        numSavedMementos = 0;
        numActualMemento = 0;
    }

    // Init lastEatedPawn
    lastEatedPawn = (PPawn *)NULL;
}

//---------------------------------------------------------------------------

#pragma mark-- Private: Set private attributes

//---------------------------------------------------------------------------

/** Setter: Store how many "three sixes" happened during this game.
 *  @param new_var new value
 */
void PGame::setNumThreeSixes(int new_var)
{
    numThreeSixes = new_var;
}

//---------------------------------------------------------------------------

/** Setter: Store how many players finished their game (got all pawns FINAL)
 *  @param new_var new value
 */
void PGame::setNumPlayerFinished(int new_var)
{
    numPlayerFinished = new_var;
}

//---------------------------------------------------------------------------

/** Setter: Set's a Flag (true/False) to know if a Pawn has been eaten while
 *  moving it to its destination during current turn. If true, eventually
 *  the player will counts 20 next time
 *  @param new_var new value
 */
void PGame::setPawnEated(bool new_var)
{
    bPawnEated = new_var;
}

//---------------------------------------------------------------------------

/** Setter: Store the pointer to the last eaten pawn
 *  @param new_pawn new value
 */
void PGame::setLastEatedPawn(PPawn *new_pawn)
{
    lastEatedPawn = new_pawn;
}

//---------------------------------------------------------------------------

/** Setter: Set Flag (True/False) that controls if Pawn 'got to final space',
 *  during current turn. If it's true, then player counts 10 next time
 *  @param new_var new value
 */
void PGame::setPawnGotFinal(bool new_var)
{
    bPawnGotFinal = new_var;
}

//---------------------------------------------------------------------------


#pragma mark-- Private: Game status

//---------------------------------------------------------------------------

/** Getter: Get the associated int value to the Status of the Game: Stopped
 *  @return Status value
 */
int PGame::getStatusGameStopped()
{
    return STATUS_GAMESTOPPED;
}

//---------------------------------------------------------------------------

/** Getter: Get the associated int value to the Status of the Game: Three Sixes
 *  @return Status value
 */
int PGame::getStatusThreeSix()
{
    return STATUS_THREESIX;
}

//---------------------------------------------------------------------------

/** Getter: Get the associated int value to the Status of the Game: Aplying the rules
 *  @return Status value
 */
int PGame::getStatusApplyingRules()
{
    return STATUS_APPLYINGRULES;
}

//---------------------------------------------------------------------------

/** Getter: Get the associated int value to the Status of the Game: Wiating for user/robot to select a pawn
 *  @return Status value
 */
int PGame::getStatusWaitingSelectPawn()
{
    return STATUS_WAITINGSELECTPAWN;
}

//---------------------------------------------------------------------------

/** Getter: Get the associated int value to the Status of the Game: Rolling the Dice
 *  @return Status value
 */
int PGame::getStatusRollingDice()
{
    return STATUS_ROLLINGDICE;
}

//---------------------------------------------------------------------------

/** Getter: Get the associated int value to the Status of the Game: Pawn has been selected
 *  @return Status value
 */
int PGame::getStatusPawnSelected()
{
    return STATUS_PAWNSELECTED;
}

//---------------------------------------------------------------------------

/** Getter: Get the associated int value to the Status of the Game: Moving the pawn
 *  @return Status value
 */
int PGame::getStatusMovingPawn()
{
    return STATUS_MOVINGPAWN;
}

//---------------------------------------------------------------------------

/** Getter: Get the associated int value to the Status of the Game: Finished moving the pawn
 *  @return Status value
 */
int PGame::getStatusFinishMovingPawn()
{
    return STATUS_FINISHMOVINGPAWN;
}

//---------------------------------------------------------------------------

/** Getter: Get the associated int value to the Status of the Game: Changing the turn
 *  @return Status value
 */
int PGame::getStatusChangingTurn()
{
    return STATUS_CHANGINGTURN;
}

//---------------------------------------------------------------------------

/** Getter: Get the associated int value to the Status of the Game: Counts twenty
 *  @return Status value
 */
int PGame::getStatusCountTwenty()
{
    return STATUS_COUNTTWENTY;
}

//---------------------------------------------------------------------------

/** Getter: Get the associated int value to the Status of the Game: Counts ten
 *  @return Status value
 */
int PGame::getStatusCountTen()
{
    return STATUS_COUNTTEN;
}

//---------------------------------------------------------------------------

/** Setter: Set the game status to: Waiting to roll the dice
 */
void PGame::setStatusWaitingRollingDice()
{
    setGameStatus(getStatusWaitingRollingDice());
}

//---------------------------------------------------------------------------

/** Setter: Set the game status to: Rolling the dice
 */
void PGame::setStatusRollingDice()
{
    if (isRunning())
        setGameStatus(getStatusRollingDice());
}

//---------------------------------------------------------------------------

/** Setter: Set the game status to: Dice has been tossed
 */
void PGame::setStatusDiceTossed()
{
    if (isRunning())
        setGameStatus(getStatusDiceTossed());
}

//---------------------------------------------------------------------------

/** Setter: Set the game status to: Three sixes happened
 */
void PGame::setStatusThreeSix()
{
    if (isRunning())
        setGameStatus(getStatusThreeSix());
}

//---------------------------------------------------------------------------

/** Setter: Set the game status to: Applying the rules
 */
void PGame::setStatusApplyingRules()
{
    if (isRunning())
        setGameStatus(getStatusApplyingRules());
}

//---------------------------------------------------------------------------

/** Setter: Set the game status to: Waiting for a pawn to be selected
 */
void PGame::setStatusWaitingSelectPawn()
{
    if (isRunning())
        setGameStatus(getStatusWaitingSelectPawn());
}

//---------------------------------------------------------------------------

/** Setter: Set the game status to: Pawn has been selected
 */
void PGame::setStatusPawnSelected()
{
    if (isRunning())
        setGameStatus(getStatusPawnSelected());
}

//---------------------------------------------------------------------------

/** Setter: Set the game status to: Moving the pawn
 */
void PGame::setStatusMovingPawn()
{
    if (isRunning())
        setGameStatus(getStatusMovingPawn());
}

//---------------------------------------------------------------------------

/** Setter: Set the game status to: Fnished moving the pawn
 */
void PGame::setStatusFinishMovingPawn()
{
    if (isRunning())
        setGameStatus(getStatusFinishMovingPawn());
}

//---------------------------------------------------------------------------

/** Setter: Set the game status to: Changing the turn
 */
void PGame::setStatusChangingTurn()
{
    if (isRunning())
        setGameStatus(getStatusChangingTurn());
}

//---------------------------------------------------------------------------

/** Setter: Set the game status to: Counts twenty
 */
void PGame::setStatusCountTwenty()
{
    if (isRunning())
        setGameStatus(getStatusCountTwenty());
}

//---------------------------------------------------------------------------

/** Setter: Set the game status to: Counts ten
 */
void PGame::setStatusCountTen()
{
    if (isRunning())
        setGameStatus(getStatusCountTen());
}

//---------------------------------------------------------------------------

/** Setter: Set the game status to: Game stopped
 */
void PGame::setStatusGameStopped()
{
    setGameStatus(getStatusGameStopped());
    dbg.print(1, "+--------------------------------------------------------+");
    dbg.print(1, "|                   G A M E   O V E R                    |");
    dbg.print(1, "+--------------------------------------------------------+");
}

//---------------------------------------------------------------------------

/** Setter: Set the game status to the passed value
 * @param new_status
 */
void PGame::setGameStatus(int new_status)
{
    gameStatus = new_status;
    dbg.printF(2, "| %-46s         |", txtGameStatus[gameStatus]);
    // For debugging only
    // dbg.print ( 2, "|" );
    // oss.str ( "" ) ;
    // oss << "|  " << txtGameStatus[gameStatus];
    // dbg.print ( 2, oss.str() );
}

//---------------------------------------------------------------------------

#pragma mark-- Private: Game Control

//---------------------------------------------------------------------------

/**
 * Calculate the "Snapshot" of each of the Pawns in the current turn
 *
 * It will be used by the game controller class (Game.cpp) to inform
 * every turn) the Robots about the actual rationale, situation
 * and conditions of each Pawn at the board in the current turn.
 *
 * This will allow the robots to make their decision of which pawn to move.
 *
 */
void PGame::calcSnapshots()
{

    // If playing only
    if (isRunning())
    {

        // Get the pointer to the current playing pawns
        PPawn **cPawn = getCurrentPlayer()->getPawns();

        // If we ain't have movable pawns after rules, get out of here
        if (!this->movablePawns())
            return;

        // Clean all the Snapshots
        for (int i = 0; i < PBoard::pawnsPerPlayer(); i++)
        {
            snapshot[i]->init();
        }


        int i;
        // Make the calculations for each of the Pawns
        for (i = 0; i < PBoard::pawnsPerPlayer(); i++)
        {

            // Setup pointers
            PPawn *p = cPawn[i];       // Pointer to the Pawn actually analyzed
            PSpace *s = p->getSpace(); // Pointer to the Pawn's Space
            PSpace *dSpace =
                cPawn[i]
                    ->getDestinationSpace(); // Pointer to its destination space

            if (!p->canMove())
                continue;

            if (dbg.getDebug())
            {
                dbg.printF(
                    3,
                    "|  Snapshot: Calculating %-4s for pawn: %-8s      |",
                    snapshot[i]->getName().c_str(),
                    p->getName().c_str());
            }

            // Calculate the condition: sNumPawnsMovable
            // --------------------------------------------------------------
            snapshot[i]->setState(PSnapshot::sNumPawnsMovable,
                                  rules->getNumPawnsMovable());


            // Calculate the condition: sNumPawnsCanEat
            // --------------------------------------------------------------
            snapshot[i]->setState(PSnapshot::sNumPawnsCanEat,
                                  rules->getNumPawnsCanEat());


            /////////////////////////////////////////////////////////////////////////////
            // CONDITIONS: ABOUT MYSELF AT MY CURRENT SPACE
            /////////////////////////////////////////////////////////////////////////////

            // Calculate the condition: cv_movable   (IF NOT MOVABLE: JUMP TO NEXT PAWN)
            // -------------------------------------------------------------------------
            if (p->canMove())
                snapshot[i]->setState(PSnapshot::cv_movable, 1);

            // Calculate the condition: cv_atNormal  (CURRENT SPACE)
            // --------------------------------------------------------------
            if (p->isAtNormal())
                snapshot[i]->setState(PSnapshot::cv_atNormal, 1);


            // Calculate the condition: cv_atQ4  (CURRENT SPACE)
            // --------------------------------------------------------------
            if (s->getQuadrant(p->getColor()) == PBoard::Q4())
                snapshot[i]->setState(PSnapshot::cv_atQ4, 1);


            // Calculate the condition: cv_atStart  (CURRENT SPACE)
            // --------------------------------------------------------------
            if (p->isAtStart())
                snapshot[i]->setState(PSnapshot::cv_atStart, 1);


            // Calculate the condition: cv_leavesSafe  (CURRENT/DESTINATION SPACE)
            // -------------------------------------------------------------------
            if (p->isAtSafe() &&
                ((dSpace != (PSpace *)NULL) && !dSpace->isSafe()))
                snapshot[i]->setState(PSnapshot::cv_leavesSafe, 1);


            // Calculate the condition: cv_atRamp  (CURRENT SPACE)
            // --------------------------------------------------------------
            if (p->isAtRamp())
                snapshot[i]->setState(PSnapshot::cv_atRamp, 1);


            // Calculate the condition: cv_atRampSafe  (CURRENT SPACE)
            // --------------------------------------------------------------
            if (p->isAtRampSafe())
                snapshot[i]->setState(PSnapshot::cv_atRampSafe, 1);


            // Calculate the condition: cv_eat  (CURRENT SPACE)
            // --------------------------------------------------------------
            if (p->canEatPawn())
                snapshot[i]->setState(PSnapshot::cv_eat, 1);


            // Calculate the condition: cv_aloneAtEnemyStart  (CURRENT SPACE)
            // ------------------------------------------------------------------
            if (s->isStart() && s->getColor() != p->getColor() &&
                s->getNumPawns() == 1)
                snapshot[i]->setState(PSnapshot::cv_aloneAtEnemyStart, 1);


            // Calculate the condition: cv_movingBreaksNormalBarrier  (CURRENT SPACE)
            // ----------------------------------------------------------------------
            if (s->isBarrier())
                snapshot[i]->setState(PSnapshot::cv_movingBreaksNormalBarrier,
                                      1);


            // Calculate the condition: cv_movingBreaksSafeBarrier  (CURRENT SPACE)
            // --------------------------------------------------------------------
            if (s->isBarrier() && s->isSafe())
                snapshot[i]->setState(PSnapshot::cv_movingBreaksSafeBarrier, 1);


            // Calculate the condition: cv_atEnemyStartFirst  (CURRENT SPACE)
            // --------------------------------------------------------------
            if (s->isStart() && s->getColor() != p->getColor() &&
                s->getNumPawns() == 2)
            {
                if (s->wasFirst(p))
                    snapshot[i]->setState(PSnapshot::cv_atEnemyStartFirst, 1);
            }


            // Calculate the condition: cv_atEnemyStartLast  (CURRENT SPACE)
            // --------------------------------------------------------------
            if (s->isStart() && s->getColor() != p->getColor() &&
                s->getNumPawns() == 2)
            {
                if (s->wasLast(p))
                    snapshot[i]->setState(PSnapshot::cv_atEnemyStartLast, 1);
            }


            // Calculate the condition: cv_eatable  (CURRENT SPACE)
            // --------------------------------------------------------------
            if (!s->isSafe())
            {
                calcBehind(p, s);
                if (p->isBehindEatable())
                    snapshot[i]->setState(PSnapshot::cv_eatable, 1);
            }


            // Calculate the condition: cv_enemyAtMyRampSafe
            // Not used today. ToDo future implementation where enemy can
            // go after pawn's through their final ramp's :-)
            // --------------------------------------------------------------
            if (board
                    ->getSpaceByIndex(
                        board->getIndexRampSafeSpaceByColor(p->getColor()))
                    ->hasEnemy(p))
                snapshot[i]->setState(PSnapshot::cv_enemyAtMyRampSafe, 1);
            //if ( space[P_INDEXRAMPSAFESPACEBYCOLOR[p->getColor()]]->hasEnemy(p) )           snapshot[i]->setState(Snapshot::cv_enemyAtMyRampSafe,  1 );


            /////////////////////////////////////////////////////////////////////////////
            // CONDITIONS: ABOUT MYSELF FROM MY DESTINATION
            /////////////////////////////////////////////////////////////////////////////

            // Calculate the condition: cv_destinationIsSafe  (DESTINATION SPACE)
            // ------------------------------------------------------------------
            if (dSpace != (PSpace *)NULL && dSpace->isSafe())
                snapshot[i]->setState(PSnapshot::cv_destinationIsSafe, 1);


            // Calculate the condition: cv_destinationIsRamp  (DESTINATION SPACE)
            // ------------------------------------------------------------------
            if (dSpace != (PSpace *)NULL && dSpace->isRamp())
                snapshot[i]->setState(PSnapshot::cv_destinationIsRamp, 1);


            // Calculate the condition: cv_destinationFinal  (DESTINATION SPACE)
            // -----------------------------------------------------------------
            if (dSpace != (PSpace *)NULL && dSpace->isFinal())
                snapshot[i]->setState(PSnapshot::cv_destinationFinal, 1);


            // Calculate the condition: cv_destinationRampSafe  (DESTINATION SPACE)
            // --------------------------------------------------------------------
            if (dSpace != (PSpace *)NULL && dSpace->isRampSafe())
                snapshot[i]->setState(PSnapshot::cv_destinationRampSafe, 1);


            // Calculate the condition: cv_destinationCreatesBarrier  (DESTINATION SPACE)
            // --------------------------------------------------------------------------
            if (dSpace != (PSpace *)NULL && dSpace->getNumPawns() == 1 &&
                !dSpace->hasEnemy(p))
                snapshot[i]->setState(PSnapshot::cv_destinationCreatesBarrier,
                                      1);


            // Calculate the condition: cv_destinationEatable  (DESTINATION SPACE)
            // If I move to my destination then I'll be exposed.
            // -------------------------------------------------------------------
            if (dSpace != (PSpace *)NULL && !dSpace->isSafe())
            {
                calcBehind(p, dSpace);
                if (p->isBehindEatable())
                    snapshot[i]->setState(PSnapshot::cv_destinationEatable, 1);
            }


            // Calculate the condition: cv_destinationLeavesDanger  (CURRENT/DESTINATION SPACE)
            // This condition must be calculated after cv_destinationEatable
            // --------------------------------------------------------------------------------
            if (snapshot[i]->getState(PSnapshot::cv_eatable) &&
                (snapshot[i]->getState(PSnapshot::cv_destinationEatable) == 0))
                snapshot[i]->setState(PSnapshot::cv_destinationLeavesDanger, 1);


            // Calculate the condition: cv_destinationThreatsEnemy  (DESTINATION SPACE)
            // ------------------------------------------------------------------------
            if (dSpace != (PSpace *)NULL)
            {
                calcAhead(p, dSpace);
                if (p->isAheadEats())
                    snapshot[i]->setState(PSnapshot::cv_destinationThreatsEnemy,
                                          1);
            }
        }


        /////////////////////////////////////////////////////////////////////////////
        // CONDITIONS: FOR THE COLLEAGUES
        /////////////////////////////////////////////////////////////////////////////

        // Make the calculations for each of the Pawns
        for (i = 0; i < PBoard::pawnsPerPlayer(); i++)
        {

            // Setup pointers
            PPawn *p = cPawn[i]; // Pointer to the Pawn actually analyzed

            if (!p->canMove())
                continue;


            for (int c = 0; c < PBoard::pawnsPerPlayer(); c++)
            {

                if (c != i && cPawn[c]->canMove())
                {


                    /////////////////////////////////////////////////////////////////////////////
                    // CONDITIONS: ABOUT MY COLLEAGUES AT THEIR CURRENT SPACE
                    /////////////////////////////////////////////////////////////////////////////

                    // Calculate the condition: cv_colleagueAtNormal  (CURRENT SPACE)
                    snapshot[i]->setState(
                        PSnapshot::cv_colleagueAtNormal,
                        snapshot[c]->getState(PSnapshot::cv_atNormal));

                    // Calculate the condition: cv_colleagueAtQ4  (CURRENT SPACE)
                    snapshot[i]->setState(
                        PSnapshot::cv_colleagueAtQ4,
                        snapshot[c]->getState(PSnapshot::cv_atQ4));

                    // Calculate the condition: cv_colleagueAtStart  (CURRENT SPACE)
                    snapshot[i]->setState(
                        PSnapshot::cv_colleagueAtStart,
                        snapshot[c]->getState(PSnapshot::cv_atStart));

                    // Calculate the condition: cv_colleagueAtRamp  (CURRENT SPACE)
                    snapshot[i]->setState(
                        PSnapshot::cv_colleagueAtRamp,
                        snapshot[c]->getState(PSnapshot::cv_atRamp));

                    // Calculate the condition: cv_colleagueAtRampSafe  (CURRENT SPACE)
                    snapshot[i]->setState(
                        PSnapshot::cv_colleagueAtRampSafe,
                        snapshot[c]->getState(PSnapshot::cv_atRampSafe));

                    // Calculate the condition: cv_colleagueEats  (CURRENT SPACE)
                    snapshot[i]->setState(
                        PSnapshot::cv_colleagueEats,
                        snapshot[c]->getState(PSnapshot::cv_eat));

                    // Calculate the condition: cv_colleagueAloneAtEnemyStart  (CURRENT SPACE)
                    snapshot[i]->setState(
                        PSnapshot::cv_colleagueAloneAtEnemyStart,
                        snapshot[c]->getState(PSnapshot::cv_aloneAtEnemyStart));

                    // Calculate the condition: cv_colleagueMovingBreaksNormalBarrier  (CURRENT SPACE)
                    snapshot[i]->setState(
                        PSnapshot::cv_colleagueMovingBreaksNormalBarrier,
                        snapshot[c]->getState(
                            PSnapshot::cv_movingBreaksNormalBarrier));

                    // Calculate the condition: cv_colleagueMovingBreaksSafeBarrier  (CURRENT SPACE)
                    snapshot[i]->setState(
                        PSnapshot::cv_colleagueMovingBreaksSafeBarrier,
                        snapshot[c]->getState(
                            PSnapshot::cv_movingBreaksSafeBarrier));

                    // Calculate the condition: cv_colleagueAtEnemyStartFirst  (CURRENT SPACE)
                    snapshot[i]->setState(
                        PSnapshot::cv_colleagueAtEnemyStartFirst,
                        snapshot[c]->getState(PSnapshot::cv_atEnemyStartFirst));

                    // Calculate the condition: cv_colleagueAtEnemyStartLast  (CURRENT SPACE)
                    snapshot[i]->setState(
                        PSnapshot::cv_colleagueAtEnemyStartLast,
                        snapshot[c]->getState(PSnapshot::cv_atEnemyStartLast));

                    // Calculate the condition: cv_colleagueEatable  (CURRENT SPACE)
                    snapshot[i]->setState(
                        PSnapshot::cv_colleagueEatable,
                        snapshot[c]->getState(PSnapshot::cv_eatable));


                    /////////////////////////////////////////////////////////////////////////////
                    // CONDITIONS: CALCULATED FOR MY COLLEAGUES, FROM THEIR DESTINATION
                    /////////////////////////////////////////////////////////////////////////////

                    // Condition: cv_colleagueDestinationIsSafe  (DESTINATION SPACE)
                    snapshot[i]->setState(
                        PSnapshot::cv_colleagueDestinationIsSafe,
                        snapshot[c]->getState(PSnapshot::cv_destinationIsSafe));

                    // Condition: cv_colleagueDestinationIsRamp  (DESTINATION SPACE)
                    snapshot[i]->setState(
                        PSnapshot::cv_colleagueDestinationIsRamp,
                        snapshot[c]->getState(PSnapshot::cv_destinationIsRamp));

                    // Condition: cv_colleagueDestinationFinal  (DESTINATION SPACE)
                    snapshot[i]->setState(
                        PSnapshot::cv_colleagueDestinationFinal,
                        snapshot[c]->getState(PSnapshot::cv_destinationFinal));

                    // Condition: cv_colleagueDestinationRampSafe  (DESTINATION SPACE)
                    snapshot[i]->setState(
                        PSnapshot::cv_colleagueDestinationRampSafe,
                        snapshot[c]->getState(
                            PSnapshot::cv_destinationRampSafe));

                    // Condition: cv_colleagueDestinationCreatesBarrier  (DESTINATION SPACE)
                    snapshot[i]->setState(
                        PSnapshot::cv_colleagueDestinationCreatesBarrier,
                        snapshot[c]->getState(
                            PSnapshot::cv_destinationCreatesBarrier));

                    // Condition: cv_colleagueDestinationEatable  (DESTINATION SPACE)
                    snapshot[i]->setState(
                        PSnapshot::cv_colleagueDestinationEatable,
                        snapshot[c]->getState(
                            PSnapshot::cv_destinationEatable));

                    // Condition: cv_colleagueDestinationLeavesDanger  (CURRENT/DESTINATION SPACE)
                    snapshot[i]->setState(
                        PSnapshot::cv_colleagueDestinationLeavesDanger,
                        snapshot[c]->getState(
                            PSnapshot::cv_destinationLeavesDanger));

                    // Condition: cv_colleagueDestinationThreatsEnemy  (DESTINATION SPACE)
                    snapshot[i]->setState(
                        PSnapshot::cv_colleagueDestinationThreatsEnemy,
                        snapshot[c]->getState(
                            PSnapshot::cv_destinationThreatsEnemy));
                }
            }

            // Just for debugging purposes
            // snapshot[i]->showState();;
        }
    }
}


/**
 * Analyze what's behind "p" if p would be at Space *s, it will set flags in the
 * Pawn object: it has a thread, eatable, someone after him, free of followers, should
 * make a barrier to their followers, etc.
 *
 * @param p pointer PPawn* to the Pawn who's "behind" will be analyzed
 * @param s pointer PSpace* to the Space from where the analysis will start backwards
 *
 */
void PGame::calcBehind(PPawn *p, PSpace *s)
{

    int index = 0;
    int i;
    unsigned int num;

    // Get the "path" to the whole board spaces 1 to 68
    std::vector<PSpace *> *v = board->getPathAnalysis();


    // If the Space 's' is out of scope then ignore and return
    // Happens when the analysis is asked for a Pawn which is at Home, Ramp or Final,
    // where it doesn't make sense, as no one can follow adter this Pawn
    if (s->getIndex() >= (int)v->size())
        return;

    // Get Space index inside vPathAnalysis where 's' is located
    for (num = 0; num < v->size(); num++)
    {
        if ((*v)[num] == s)
        {
            index = (int)num;
            break;
        }
    }

    // Debugging purposes
    //    oss.str("");
    //    oss << "| ANALYSIS BEHIND BEGIN for " << p->getName() << " from " << (*v)[index]->getName() << " (excluded)";
    //    dbg.print( 3, oss.str());

    // Clean all previous flags for this Pawn
    p->setBehindEatable(false);


    // Analyse backwards from Space "p" back all the way (68 spaces = full board)
    // Note: Obviously it's not necesary to analysis the full board, but I just
    // leave it as is, due to future analysis.
    //    for ( num=1; num<=vPathAnalysis.size(); num++, i-- ) {
    // Normally I would only analize 20 spaces backward
    //    for ( num=1; num<=20; num++, i-- ) {

    i = (index - 1);
    for (num = 1; num <= 20; num++, i--)
    {
        //for ( num=1; num<=vPathAnalysis.size(); num++, i-- ) {

        // Rotate when reaching Space1
        if (i == -1)
            i = (int)v->size() - 1;

        // CASE 1: Analyse only dice distances
        if (num > 7 && num != 10 && num != 20)
        {
            continue;
        }

        // Body of the analysis.
        PSpace *cs =
            (*v)[i]; // Get a direct pointer to the current Space being analysed

        // Debugging purposes
        //        oss.str("");
        //        oss << "| ANALYSING BEHIND for " << p->getName() << " what's at " << cs->getName();
        //        dbg.print( 3, oss.str());

        // I'M EATABLE?
        // If I will NOT be in a Safe space then check
        if (!s->isSafe())
        {
            // If analysed Space has an enemy
            if (cs->hasEnemy(p))
            {
                // If I'm at dice distance
                if (num <= 7 || num == 10 || num == 20)
                {
                    bool eatsme = true;

                    // If it was a 5 and any of the Pawn's in the space can still reach me...
                    if (num == 5)
                    {
                        // The enemy could not reach me if he's got pawns at home, so check it
                        for (int x = 0; x < cs->getNumPawns(); x++)
                        {
                            PPawn *e = cs->getPawn(x);
                            if (e->getColor() != p->getColor())
                            {
                                if (!e->anyAtHome())
                                {
                                    eatsme = true;
                                }
                                else
                                {
                                    eatsme = false;
                                }
                            }
                        }
                    }

                    if (eatsme)
                    {
                        p->setBehindEatable(true);


                        if (dbg.getDebug())
                        {
                            dbg.printF(3,
                                       "|  Back analysis, enemy at %-8s (%2d): "
                                       "I'm eatable.   |",
                                       cs->getName().c_str(),
                                       num);
                        }
                        break;
                    }
                }
            }
        }
    }

    // LUIS. Mejorar en el futuro. Aquí se debería distinguir entre los siguientes
    // casos; Existe un enemigo que está a tiro de 'i' y siendo i:
    //  1 a 4 me tendría directamente a tiro.
    //  5 (no tiene compis en casa que puedan salir)
    //  6 (si tiene compi en casa)
    //  7 (si no tiene compis en casa)
    //  10 (sólo si tiene alguna compi en su rampa final)
    //  20 (teniendo alguna compi a alguien a tiro (muy difícil de implementar))
    //  nx6 (si el otro sacase un 6 y luego al repetir otro que me comiese...)
    //
}


/**
 * Analyze what's in front
 *
 * @param p Pointer PPawn* to the Pawn who's "ahead" will be analyzed
 * @param s Pointer PSpace* to the Space from where the analysis will start
 *
 */
void PGame::calcAhead(PPawn *p, PSpace *s)
{

    int index = 0;
    int i;
    unsigned int num;

    // Get the "path" to board spaces 1 to 68
    std::vector<PSpace *> *v = board->getPathAnalysis();

    // If the Space where the analysis starts ('s') is out of scope then ignore and return
    // Happens when the analysis is asked from a destination space of type Home, Ramp or Final,
    // or the (RampSafe or RampSafe-1) for that Color, anyway can't eat.
    // where it doesn't make sense:
    // A Pawn cannot eat anything from Ramp/Final
    // A Pawn cannot be sent Home because it would eat from there.... it's worthless to make the analysis
    // A Pawn cannot eat from (RampSafe or RampSafe-1) for that Color
    //    if ( (s->getIndex() >= (int) v->size() ) || ( s->getIndex() >= (P_INDEXRAMPSAFESPACEBYCOLOR[p->getColor()]-1) ) )

    if ((s->getIndex() >= (int)v->size()) ||
        (s->getIndex() >=
         (board->getIndexRampSafeSpaceByColor(p->getColor()) - 1)))
        return;


    // Get Space index inside vPathAnalysis where 's' is located
    for (num = 0; num < v->size(); num++)
    {
        if ((*v)[num] == s)
        {
            index = (int)num;
            break;
        }
    }

    // Debugging purposes
    //    oss.str("");
    //    oss << "| ANALYSIS AHEAD BEGIN for " << p->getName() << " from " << (*v)[index]->getName() << " (excluded)";
    //    dbg.print( 3, oss.str());

    // Clean all previous flags for this Pawn
    p->setAheadEats(false);

    // Analyse ahead starting at Space "s" front all the way (68 spaces = full board)
    // Note: Obviously it's not necesary to analysis the full board, so I study the
    // first 20 spaces...
    // Option to study the whole board:
    //    for ( num=1; num<=vPathAnalysis.size(); num++, i++ ) {
    // Option to study just the following 20 spaces
    //    for ( num=1; num<=20; num++, i+ ) {

    i = (index + 1);
    for (num = 1; num <= 20; num++, i++)
    {

        // Rotate when reaching Space1
        if (i == (int)v->size())
            i = 0;

        // CASE 1: Analyse only dice distances
        if (num > 7 && num != 10 && num != 20)
        {
            continue;
        }

        // If reached the space just before RampSafe of this pawn's color path, then get out of here
        // as from here ahead can't eat anything
        if (i == (board->getIndexRampSafeSpaceByColor(p->getColor()) - 1))
            break;

        // Body of the analysis.
        PSpace *cs =
            (*v)[i]; // Get a direct pointer to the current Space being analysed

        // Debugging purposes
        //        oss.str("");
        //        oss << "| ANALYSING AHEAD for " << p->getName() << " what's at " << cs->getName();
        //        dbg.print( 3, oss.str());


        // CASE 1: ANALYSE IF I CAN EAT SOMEONE
        ///////////////////////////////////////////////////////////////////
        // First ignore safe spaces
        if (!s->isSafe())
        {
            // If analysed Space has an enemy and he's alone
            if (cs->hasEnemy(p) && cs->getNumPawns() == 1)
            {
                // If it's at dice distance
                if (num <= 7 || num == 10 || num == 20)
                {
                    bool caneat = true;

                    // If it is a 5 and I got still pawns at my HOME...
                    if (num == 5 && p->anyAtHome())
                    {
                        // Then I can't eat
                        caneat = false;
                    }

                    if (caneat)
                    {
                        p->setAheadEats(true);

                        if (dbg.getDebug())
                        {
                            oss.str("");
                            oss << "| ANALYSING AHEAD: I CAN EAT Enemy at "
                                << cs->getName() << "(" << num << ")";
                            dbg.print(3, oss.str());
                        }

                        break;
                    }
                }
            }
        }
    }
}

//---------------------------------------------------------------------------

#pragma mark-- Private: Memento management

//---------------------------------------------------------------------------

/**
 * Stores internal state of the objects, based on the Memento design pattern.
 * A memento is an object that stores a snapshot of the internal state of another
 * object. It can be leveraged to support multi-level undo.
 *
 * Originator   Player.class        (Creates the memento object)
 * Memento      PlayerMemento.class (Stores/Restores internal state of a Player object)
 * CareTaker    Game.cpp            (Calls player's createMemento/setMemento to control the undo/redo's)
 *                                  Implemented with:  saveMementos()
 *                                                     undo()
 *                                                     redo()
 *
 */
void PGame::saveMementos()
{


    /*
     //////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\

     //////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\

     //////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\

     //////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\

	 !!!!!!!!!!!!!!!!!!!!!  W A R N I N G !!!!!!!!!!!!!!!!!!


     Mementos implementation has a huge memory leak somewhere
	 I've to investigate. I've detected it while runnin in
	 command line mode and playing 100 games.

	 Two issues arised:

	 1) Playing from Command line multiple games should NOT
	 use the saveMementos() as there is no need to undo()
	 anything. On the other side the playing speed is far too
	 slow.

	 2) I've detected that calling newGame() doesn't clean
	 correctly the mementos. Somewhere there is a memory leak


	 I'm going to disable saveMemento while the game is played
	 in "performance mode"; meaning the game is called from
	 the command line with the objective to play multiple
	 games, as in:

	 $ parchis -n 100

	 In order to "force" Parchis to play without Undo() until
	 I fix it, I've kind of disable it :-(



	 \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\/////////////////////////

	 \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\/////////////////////////

	 \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\/////////////////////////

	 \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\/////////////////////////
     */

    // Just for debuggin purposes
    //    dbg.print ( 2, "|" );
    //    dbg.print ( 2, "|" );
    //    oss.str("");
    //    oss << "|  SAVING MEMENTO. total: " << numSavedMementos << " actual:" << numActualMemento;
    //    dbg.print( 2, oss.str());
    //    dbg.print ( 2, "|" );

    // In the middle of the stack? yes: delete rest of stack to the right
    if (numActualMemento < (numSavedMementos - 1))
    {

        // BOARD
        dbg.printF(3,
                   "|  Memento handling: Actual: %2d. Inside stack, deleting "
                   "to the right. |",
                   numActualMemento);

        for (int i = (numSavedMementos - 1); i > numActualMemento; i--)
        {
            dbg.printF(3, "|  Deleting memento: %d", i);
            delete vBoardMemento.at(i); // Call the destructors
            vBoardMemento.pop_back();
        }
    }
    else
    {
        // Reached capacity of the undo stack? yes: rotate & delete
        if (numSavedMementos == UNDOLEVELS)
        {
            dbg.printF(
                3,
                "|  Memento handling: Actual: %2d. Reached stack capacity |",
                numActualMemento);

            // BOARD
            rotate(vBoardMemento.begin(),
                   vBoardMemento.begin() + 1,
                   vBoardMemento.end());
            delete vBoardMemento.at(
                (numSavedMementos - 1)); // Call the destructor
            vBoardMemento.pop_back();
        }
    }

    // Add current memento to the end of the stack
    numActualMemento = (int)vBoardMemento.size();
    vBoardMemento.push_back(board->createMemento(numActualMemento));
    numSavedMementos = (int)vBoardMemento.size();

    // Increment the number of saved mementos
    // numSavedMementos++;

    // Just for debuggin purposes
    dbg.printF(2,
               "| Saved memento total: %2d (0-%2d) Actual: %2d     |",
               numSavedMementos,
               numSavedMementos - 1,
               numActualMemento);
}

//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Public Methods
#pragma mark-- Public Constructor/Destructor

//---------------------------------------------------------------------------

/**
 * Constructor of PGame
 *
 * Constructor of the PGame with the option to assign a name to it
 *
 * @param new_name The name you want to assign to this instance. It's used
 *                 only through PDebug to show debug messages
 */
PGame::PGame(std::string new_name)
{
    name.assign(new_name);
    initAttributes();
}

//---------------------------------------------------------------------------

/**
 * Destructor of PGame
 */
PGame::~PGame()
{

    // Elimino los snapshots que he creado durante el initAttributes
    if (snapshot != NULL)
    {
        for (int i = 0; i < PBoard::pawnsPerPlayer(); i++)
        {
            if (snapshot[i] != NULL)
                delete snapshot[i];
        }
        delete snapshot;
    }

    // Elimino las Rules
    delete rules;

    dbg.print(4, "|                   PGame DESTRUCTOR                     |");
}

//---------------------------------------------------------------------------

#pragma mark-- Public Connections

//---------------------------------------------------------------------------

/**
 * Connect this Game with the "Board", "Players" and "Rules"
 *
 * @param new_board is the pointer to the board
 * @param new_player is the pointer to the array of Players
 */

void PGame::setBoardPlayers(PBoard *new_board, PPlayer **new_player)
{
    int i;

    // Make the connections
    player = new_player;
    board = new_board;
    vPawns = board->getVPawns(); // "                 "

    // For debugging only
    dbg.printF(4,
               "|   %-8s connected with %-8s and Players:        |",
               getName().c_str(),
               board->getName().c_str());
    for (i = 0; i < PBoard::numPlayers(); i++)
    {
        dbg.printF(4,
                   "|       %-8s                                         |",
                   player[i]->getName().c_str());
    }
}

//---------------------------------------------------------------------------

#pragma mark-- Public Getters

//---------------------------------------------------------------------------

/**
 * Getter: Returns the name assigned to this game
 * @return The string name of this game.
 */
std::string PGame::getName()
{
    return name;
} // Return the string (name) given to this object

//---------------------------------------------------------------------------

/**
 * Setter: Number round we (turns/plays) done in the whole game
 * @param new_var The number of round
 */
void PGame::setNumRound(int new_var)
{
    numRound = new_var;
}

//---------------------------------------------------------------------------

/**
 * Getter: Get the number round we (turns/plays) done in the whole game
 * @return The number of round
 */
int PGame::getNumRound()
{
    return numRound;
}

//---------------------------------------------------------------------------

/**
 * Setter: Number of sixes current player has already taken during current turn
 * @param new_var The number of sixes
 */
void PGame::setNumSixes(int new_var)
{
    numSixes = new_var;
}

//---------------------------------------------------------------------------

/**
 * Getter: Number of sixes current player has already taken during current turn
 *
 * @return number of sixes seen during this turn
 */
int PGame::getNumSixes()
{
    return numSixes;
}

//---------------------------------------------------------------------------

/**
 * Getter: Number of times that 3 sixes has happened during the game
 *
 * @return Number of times that 3 sixes has happened during the game
 */
int PGame::getNumThreeSixes()
{
    return numThreeSixes;
}

//---------------------------------------------------------------------------

/**
 * Getter: number of players that has already finished the game
 *
 * @return int number of players that already finished
 */
int PGame::getNumPlayerFinished()
{
    return numPlayerFinished;
}

//---------------------------------------------------------------------------

/**
 * Getter: number of the color that first finished the game
 *
 * @return int Returns the number of the color that first finished the game
 */
int PGame::getNumColorWinner()
{
    return numColorWinner;
}

//---------------------------------------------------------------------------


#pragma mark-- Public Game Flags

//---------------------------------------------------------------------------

/**
 // Changes the Undo enabled/disabled feature.
 // Note this should clean mementos and check status. POOR IMPLEENTATION (Luis)
 */
//void    Game::enabletUndo(bool new_value)           { bUndoActive=new_value; }

//---------------------------------------------------------------------------

/**
 * Getter: flag (true/false) that indicatesan option: FINISH the GAME when first player Wins or leaves it till all at HOME
 *
 * @return bool value of the option
 */
bool PGame::isOptionFirstWinnerEndsGame()
{
    return bOptionFirstWinnerEndsGame;
}

//---------------------------------------------------------------------------

/**
 * Getter: Flag true/false: Pawn got its third 6, so it has to go home and turn changes.
 *
 * @return bool value that indicates the current situation
 */
bool PGame::isFlagThirdSix()
{
    return bFlagThirdSix;
}

//---------------------------------------------------------------------------

/**
 * Getter: Flag true/false: Pawn got a 6, so turn doesn't change.
 *
 * @return bool value that indicates the current situation
 */
bool PGame::isFlagSix()
{
    return bFlagSix;
}

//---------------------------------------------------------------------------

/**
 * Getter: Flag true/false: Pawn 'eated', so player repeats and counts 20.
 *
 * @return bool value that indicates the current situation
 */
bool PGame::isFlagPawnEated()
{
    return bPawnEated;
} // Flag true/false: Pawn 'eated', so player repeats and counts 20.

//---------------------------------------------------------------------------

/**
 * Getter: Flag true/false: Pawn 'got to final space', so player repeats and counts 10.
 *
 * @return bool value that indicates the current situation
 */
bool PGame::isFlagPawnGotFinal()
{
    return bPawnGotFinal;
}

//---------------------------------------------------------------------------

/**
 * Getter: Flag true/false: Pawn got a 5 and can get two out of HOME.
 *
 * @return bool value that indicates the current situation
 */
bool PGame::isFlagTwoGoOutHome()
{
    return bFlagTwoGoOutHome;
}

//---------------------------------------------------------------------------

/**
 * Getter: When starting new game, first two pawns already at START
 *
 * @return bool value that indicates the current situation
 */
bool PGame::isOptionStartTwoOut()
{
    return bOptionStartTwoOut;
}

//---------------------------------------------------------------------------

/**
 * Getter: Flag true/false: Tells me to FINISH the GAME when first player Wins or leaves it till all at HOME
 *
 * @return bool value that indicates the current situation
 */
void PGame::setOptionFirstWinnerEndsGame(bool new_value)
{
    bOptionFirstWinnerEndsGame = new_value;
} //

//---------------------------------------------------------------------------

/**
 * Getter: Changes the flag that says: at start first 5 puts two out of Home
 *
 * @return bool value that indicates the current situation
 */
void PGame::setFlagTwoGoOutHome(bool new_value)
{
    bFlagTwoGoOutHome = new_value;
} //

//---------------------------------------------------------------------------

/**
 * Getter: When starting new game, do it with first two pawns already at START
 *
 * @return bool value that indicates the current situation
 */
void PGame::setOptionStartTwoOut(bool new_value)
{
    bOptionStartTwoOut = new_value;
}

//---------------------------------------------------------------------------

/**
 * Getter: True if a Pawn can jump or cross a barrier of 2 pawns from its self color
 *
 * @return bool value that indicates the current situation
 */
bool PGame::canCrossSelfBarrier()
{
    return bOptionCanCrossSelfBarrier;
}

//---------------------------------------------------------------------------

/**
 * Getter: True if a Pawn at HOME can eat Barrier at its start (different color)
 *
 * @return bool value that indicates the current situation
 */
bool PGame::canEatHomeBarrier()
{
    return bOptionCanEatHomeBarrier;
}

//---------------------------------------------------------------------------

/**
 * Getter: True if first 5 lets get two pawn out of HOME
 *
 * @return bool value that indicates the current situation
 */
bool PGame::canTwoGoOutHome()
{
    return bOptionCanTwoGoOutHome;
}

//---------------------------------------------------------------------------


#pragma mark-- Public Game Status

//---------------------------------------------------------------------------

/**
 * Getter: Returns the current numerical value of the game status
 *
 * @return int value of the current game status
 */
int PGame::getGameStatus()
{
    return gameStatus;
}

//---------------------------------------------------------------------------

/**
 * Getter: Returns the numerical value associated to: Waiting Rolling the Dice
 *
 * @return int value of the status:  Waiting Rolling the Dice
 */
int PGame::getStatusWaitingRollingDice()
{
    return STATUS_WAITINGROLLINGDICE;
}

//---------------------------------------------------------------------------

/**
 * Getter: Returns the numerical value associated to: Dice has been tossed
 *
 * @return int value of the status:  Dice has been tossed
 */
int PGame::getStatusDiceTossed()
{
    return STATUS_DICETOSSED;
}

//---------------------------------------------------------------------------

/**
 * Returns true if the game is running.
 *
 * @return true if the game is running, so none of the Players finished
 */
bool PGame::isRunning()
{
    if (this->getGameStatus() != this->getStatusGameStopped())
        return true;

    return false;
}

//---------------------------------------------------------------------------

/**
 * returns true if waiting for player
 *
 * @return true if waiting for player to select a pawn to move
 */
bool PGame::isWaitingSelectPawn()
{
    if (this->getGameStatus() == this->getStatusWaitingSelectPawn())
        return true;

    return false;
}

//---------------------------------------------------------------------------

/**
 * returns true if the current player is actually playing again, because he got
 * a 6,10,20 in the last turn
 *
 * @return true if playing again
 */
bool PGame::isPlayingAgain()
{
    return (this->playerPlaysAgain);
}

//---------------------------------------------------------------------------

/**
 * Returns if all Pawns of the current Player have finised
 * @return true if all Pawns of the current Player have finised (all at END space)
 */
bool PGame::isPlayerFinished()
{
    return (player[getTurn()]->isFinished());
}

//---------------------------------------------------------------------------

/**
 * Returns the string in readable format associated to the game status
 * @return Pointer to char * with the text of the game status
 */
const char *PGame::getTxtGameStatus()
{
    return txtGameStatus[getGameStatus()];
}

//---------------------------------------------------------------------------

/**
 * Are there any movable pawns?
 * @return true if after execRules we got movable pawns
 */
bool PGame::movablePawns()
{
    if (rules->getNumPawnsMovable() > 0)
        return true;
    return false;
}


//---------------------------------------------------------------------------

#pragma mark-- Public Game Actions

//---------------------------------------------------------------------------

/**
 * Starts a new game, set's all statistics to its initial values
 * and notify each component that we are starting a new game
 *
 */
void PGame::newGame()
{

    // Initial value for "turn"
    setTurn(0);     // By default it's YELLOW's turn
    setNumRound(0); // Number round we (turns/plays) done in the whole game

    // To control the number of 'spaces' a Pawn can move forward
    setLastDice(0);
    setLastDiceForward(0);

    // To control the number '6' appeared and how much I count to move forwared
    setNumSixes(0);          // Number of 6's got by current player
    setNumThreeSixes(0);     // Number of times 3 sixes appeared
    setNumPlayerFinished(0); // No one has finished yet :-)
    numColorWinner = -1;     // We don't have a winner yet
    setPawnEated(false);     // Controls if Pawn 'eated', so counts 20.
    setPawnGotFinal(
        false); // Controls if Pawn 'got to final space', so counts 10

    bOptionFirstWinnerEndsGame =
        true; // Flag true/false: Tells me to FINISH the GAME when first player Wins or leaves it till all at HOME
    bFlagThirdSix =
        false; // Flag true/false: Pawn got its third 6, so it has to go home and turn changes.
    bFlagSix = false; // Flag true/false: Pawn gota  6, so turn doesnt change
    bPawnEated =
        false; // Flag true/false: Pawn 'eated', so player repeats and counts 20.
    bPawnGotFinal =
        false; // Flag true/false: Pawn 'got to final space', so player repeats and counts 10
    bFlagTwoGoOutHome =
        false; // Flag true/false: Pawn got a 5 and can get two out of HOME.

    // Notify we are starting a new game
    dbg.print(1, "");
    dbg.print(1, "+--------------------------------------------------------+");
    dbg.print(1, "|          S T A R T I N G   N E W   G A M E             |");
    dbg.print(1, "+--------------------------------------------------------+");

    // Notify the Board that we are starting a new Game.
    // The board will notify the: Spaces, Pawns and Players
    dbg.print(2, "+--------------------------------------------------------+");
    dbg.print(2, "| Signal Board, we are starting a new game               |");
    dbg.print(2, "+--------------------------------------------------------+");
    board->newGame();

    // Notify all Players that we are starting a new Game.
    dbg.print(2, "+--------------------------------------------------------+");
    dbg.print(2, "| Signal Players, we are starting a new game             |");
    dbg.print(2, "+--------------------------------------------------------+");
    for (int i = 0; i < PBoard::numPlayers(); i++)
    {
        player[i]->newGame();
    }

    // Start the game (simply changes the status)
    this->setStatusWaitingRollingDice();

    //
    //  Note: I've got a memory leak. See saveMemento method
    //
    if (bUndoActive)
    {

        // MEMENTO Caretaker
        dbg.print(2,
                  "| New game: memento caretaker                            |");
        //////////////////////////////////////////////////////////////
        // Clear undo (mementos)
        //    if ( numSavedMementos != 0 ) {
        //
        //        // Clear the Player's mementos
        //        for ( int i=0; i<(int)vPlayerMemento.size(); i++ )
        //            delete this->vPlayerMemento.at(i);      // Call the destructors
        //        this->vPlayerMemento.clear();               // Clear the vector
        //
        //    }
        std::vector<PBoardMemento *>::iterator iter = vBoardMemento.begin();
        while (iter != vBoardMemento.end())
        {
            delete *iter++;
        }
        vBoardMemento.clear();
        numSavedMementos = 0;
        numActualMemento = 0;

        // Save memento !!
        this->saveMementos();
    }

    // For debugging purposes only
    dbg.print(1, "");
    dbg.print(1, "+--------------------------------------------------------+");
    dbg.print(1, "|                    N E W   G A M E                     |");
    dbg.print(1, "+--------------------------------------------------------+");
}

//---------------------------------------------------------------------------

/**
 * Method by which I'm asked for the Rules to be executed. This method
 * will call the rules and then fill the snapshots that represent
 * the actual status and conditions for each Pawn.
 *
 * Next step is to wait for a Pawn to be selected. This will be
 * done by the Human of by a Robot, which will use this snapshot
 * hopefully to select the best pawn to move
 *
 */
void PGame::execRules()
{

    // Change the status to "applying" the rules
    this->setStatusApplyingRules();

    // Execute the rules of the Game
    if (rules->execRules(board, getLastDiceForward()) != 0)
    {
        this->setStatusWaitingSelectPawn();

        // Analyse each Pawn's condition and store it in the "snapshot" object
        // LUIS!!! LO METO DENTRO DEL !=0
        calcSnapshots();
    }
    else
    {
        // If it returned 0 one of the reasons could be 3x6's
        if (this->isFlagThirdSix())
            this->sendLastMovedHome();
    }
}

//---------------------------------------------------------------------------

/**
 * Ask current player to toss its Dice. If we pass a value is because
 * we are forcing the rolled dice to be such number :-)
 *
 * @param new_dice "forced dice" if different from zero
 */
void PGame::playerTossDice(int new_dice)
{
    int i;
    char strMsg[MAXSTRINGDBG];

    if (this->isRunning())
    {

        // Reset Flags
        bPawnEated =
            false; // Flag true/false: Pawn 'eated', so player repeats and counts 20.
        bPawnGotFinal =
            false; // Flag true/false: Pawn 'got to final space', so player repeats and counts 10
        bFlagTwoGoOutHome =
            false; // Flag true/false: Pawn got a 5 and can get two out of HOME.

        // Reset bFlagThirdSix and numSixes
        if (this->bFlagThirdSix)
        {
            this->numSixes = 0;
            this->bFlagThirdSix = false;
            this->bFlagSix = false;
        }

        // Increment the number of "plays"
        setNumRound(getNumRound() + 1);

        // Ask the player to toss the dice
        i = player[getTurn()]->tossDice(new_dice);

        // Debugging info
        if (dbg.getDebug())
        {

            if (dbg.getDebug() == 1)
            {
                dbg.printF(
                    1,
                    "| %-7s (%-7s). Round: %3d. Dice: %2d.               |",
                    board->getColorName(this->getTurn()),
                    player[getTurn()]->getName().c_str(),
                    getNumRound(),
                    i);
            }
            else
            {
                dbg.print(2,
                          "+---------------------------------------------------"
                          "-----+");
                snprintf(
                    strMsg,
                    sizeof(strMsg),
                    "|         %6s (%-7s). Round: %3d. Dice: %2d.        |",
                    board->getColorName(this->getTurn()),
                    player[getTurn()]->getName().c_str(),
                    getNumRound(),
                    i);
                dbg.print(2, strMsg);
                dbg.print(2,
                          "+---------------------------------------------------"
                          "-----+");
            }
        }

        // Store DICE value in the board
        setLastDice(i);
        setLastDiceForward(i);

        // If it's a six, store and increment
        if (getLastDice() == 6)
        {

            // Activate the flag
            this->bFlagSix = true;

            // Change to 7 if all out
            if (player[getTurn()]->isAllPawnsOut())
            {
                setLastDiceForward(7);
            }
            // Current player's number of sixes
            this->numSixes++;
            if (this->getNumSixes() == 3)
            {
                setNumThreeSixes(this->numThreeSixes + 1);
                this->bFlagThirdSix = true;
            }
        }
        else
        {

            // Clear any "six" flag if dice tossed is less than 6, 10 or 20
            if (getLastDice() < 6)
            {
                this->numSixes = 0;
                this->bFlagThirdSix = false;
                this->bFlagSix = false;
                this->numSixes = 0;
            }
        }


        // Change the status of the game from rolling the dice to dice tossed.
        setStatusDiceTossed();
    }
    else
    {
        dbg.print(3, "WARNING: Can't toss the dice if the game is not running");
    }
}

//---------------------------------------------------------------------------

/**
 * Set the turn to a specific color
 *
 * @param new_var the new value of turn
 */
void PGame::setTurn(int new_var)
{
    turn = new_var;
}

//---------------------------------------------------------------------------

/**
 * Get the value of turn, indicating which color is the turn now.
 *
 * @return the value of turn
 */
int PGame::getTurn()
{
    return turn;
}

//---------------------------------------------------------------------------

/**
 * Changes turn (if possible) so next player can play
 *
 * Will NOT change turn if:
 *
 * - The current player eated in its last movement. So now has right to play again and move 20.
 * - The current player just enter its FINAL space. So now has right to play again and move 10.
 * - The current player can move its second Pawn from Home (1st 5 moves 2 pawns)
 * - Last dice was a SIX and number of sixes is lower than 3
 *
 *
 * Will change turn if:
 *
 *  - The current player has finished
 *  - Last dice was NOT a six
 *  - Got the third six
 *
 *
 */
bool PGame::newTurn()
{

    bool changeTurn = true;

    // I will NOT change turn if:
    // ==========================
    //  - The current player eated in its last movement. So now has right to play again and move 20.
    //  - The current player just enter its FINAL space. So now has right to play again and move 10.
    //  - The current player can move its second Pawn from Home (1st 5 moves 2 pawns)
    //  - Last dice was a SIX and number of sixes is lower than 3
    if (!player[getTurn()]->isFinished())
    {

        //  The current player eated in its last movement. So now has right to play again and move 20.
        if (this->isFlagPawnEated())
        {
            changeTurn = false;

            // For debugging only
            dbg.print(
                2,
                "+--------------------------------------------------------+");
            dbg.print(
                2,
                "|  PLAYS AGAIN:  Player counts 20                        |");
            dbg.print(
                2,
                "+--------------------------------------------------------+");
        }

        //  The current player just enter its FINAL space. So now has right to play again and move 10.
        if (this->isFlagPawnGotFinal() &&
            !this->getCurrentPlayer()->isFinished())
        {
            changeTurn = false;
            // For debugging only
            dbg.print(
                2,
                "+--------------------------------------------------------+");
            dbg.print(
                2,
                "|  PLAYS AGAIN:  Player counts 10                        |");
            dbg.print(
                2,
                "+--------------------------------------------------------+");
        }

        //  The current player can move its second Pawn from Home (1st 5 moves 2 pawns)
        if (this->isFlagTwoGoOutHome())
        {
            changeTurn = false;
            dbg.print(
                2,
                "+--------------------------------------------------------+");
            dbg.print(
                2,
                "|  PLAYS AGAIN:  First 5 moves two pawns                 |");
            dbg.print(
                2,
                "+--------------------------------------------------------+");
        }

        //  Player just got a 6 and it's NOT the third one
        if (this->bFlagSix == true && !this->isFlagThirdSix())
        {
            //  if ( this->getLastDice() == 6 && !this->isFlagThirdSix() ) {
            changeTurn = false;
        }
    }

    // I will change turn if:
    // ==========================
    // - The current player has finished
    // - Last dice was NOT a six
    // - Got the third six
    if (changeTurn)
    {
        playerPlaysAgain = false;
        if (player[getTurn()]->isFinished() || this->getNumSixes() > 2 ||
            this->getLastDice() != 6)
        {

            // Change status
            this->setStatusChangingTurn();

            // Increment turn, look for the next "playing" player (not finished)
            int t = this->getTurn();
            for (int i = 0; i < PBoard::numPlayers(); i++)
            {
                // Increment turn
                t++;
                if (t == PBoard::numPlayers())
                {
                    t = 0;
                }
                // If the next player is finished, ignore
                if (player[t]->isFinished())
                    continue;

                // Assign new turn
                setTurn(t);

                // Place the dice in the correct HOME
                board->moveDiceToSpace(
                    board->getDice(),
                    board->getSpaceByIndex(
                        board->getIndexHomeSpaceByColor(getTurn())));

                break;
            }

            // Reset counter of SIX'es
            this->setNumSixes(0);
            this->bFlagSix = false;

            // Reset the flag
            //            flagPlayerChange=false;


            // For debugging only
            dbg.print(
                2,
                "|                                                        |");
            dbg.print(
                2,
                "+=========================================================");
            dbg.print(2, "");
            dbg.print(2, "");
            dbg.print(
                2,
                "+=========================================================");
            dbg.printF(
                2,
                "|                 NEW TURN  %-7s                      |",
                board->getColorName(this->getTurn()));
            dbg.print(
                2,
                "+=========================================================");
            // Change the status
            this->setStatusWaitingRollingDice();
            dbg.print(
                2,
                "|                                                        |");
        }
    }
    else
    {
        // For debugging only
        dbg.print(2,
                  "|                                                        |");
        dbg.print(2,
                  "+=========================================================");
        dbg.print(2, "");
        dbg.print(2, "");
        dbg.print(2,
                  "+=========================================================");
        dbg.printF(2,
                   "|                PLAYS AGAIN  %-7s                    |",
                   board->getColorName(this->getTurn()));
        dbg.print(2,
                  "+=========================================================");
        // Change the status
        this->setStatusWaitingRollingDice();
        // Set the flag plays again
        playerPlaysAgain = true;
    }

    // Save memento !!
    // LUIS: Buscando el memory leak
    if (bUndoActive)
    {
        this->saveMementos();
    }

    // Return indication if we changed turn or not...
    return changeTurn;
}

//---------------------------------------------------------------------------

/**
 * Selects the pawn to be moved.
 *
 * the Game should be running/playing, rules executed and Pawn marked as movable.
 * This is the method needed to be called when the Game is waiting for a pawn to
 * be selected.
 *
 * selectPawn()        Is used to save the pawn selected by the Robot
 * selectPawn(Pawn*)   Is used to save the pawn selected by the Human
 *
 */
void PGame::selectPawn()
{
    // Select the pawn calculated by the robots
    selectPawn((PPawn *)NULL);
}

//---------------------------------------------------------------------------

/**
 * Selects the pawn to be moved.
 *
 * the Game should be running/playing, rules executed and Pawn marked as movable.
 * This is the method needed to be called when the Game is waiting for a pawn to
 * be selected.
 *
 * selectPawn()        Is used to save the pawn selected by the Robot
 * selectPawn(Pawn*)   Is used to save the pawn selected by the Human
 *
 * @param new_pawn is the Pawn selected to be moved.
 *
 */
void PGame::selectPawn(PPawn *new_pawn)
{
    // Obviously execute only if movable Pawns available
    if (this->movablePawns())
    {

        if (new_pawn == (PPawn *)NULL)
            // Ask the Robot to select and return the PAWN to be moved
            selectedPawn = this->getCurrentPlayer()->getPawnToMove(snapshot);
        else
            // Move the Pawn passed, which is the one already selected by Human
            selectedPawn = new_pawn;

        // Double check we still have a pawn to be moved
        if (selectedPawn == (PPawn *)NULL)
        {
            return;
        }

        // For debugging purposes only
        if (dbg.getDebug() >= 2)
        {
            const char *m, *e, *s;
            for (unsigned int x = 0; x < vPawns.size(); x++)
            {
                if (vPawns[x]->getColor() == selectedPawn->getColor())
                {
                    if (vPawns[x]->canMove())
                        m = "x";
                    else
                        m = " ";
                    if (vPawns[x]->canEatPawn())
                        e = "x";
                    else
                        e = " ";
                    if (vPawns[x] == selectedPawn)
                        s = "<== Selected";
                    else
                        s = " ";
                    dbg.printF(
                        2,
                        "|  %-8s  moves (%s)    eats(%s).  %-12s         |",
                        vPawns[x]->getName().c_str(),
                        m,
                        e,
                        s);
                }
            }
        }
    }
}

//---------------------------------------------------------------------------

/**
 * Return what's the origin space of the pawn selected to be moved
 *
 * @return int origin space of the pawn selected to be moved or
 *         return -1 if selectedPawn = NULL
 */
int PGame::selectedPawnOriginSpaceIndex()
{
    if (selectedPawn == (PPawn *)NULL)
        return -1;

    return selectedPawn->getSpace()->getIndex();
}

//---------------------------------------------------------------------------

/**
 * Return what's the position inside the origin space of the pawn selected to be moved
 *
 * @return int position
 */
int PGame::selectedPawnOriginSpacePos()
{
    if (selectedPawn == (PPawn *)NULL)
        return -1;

    return selectedPawn->getSpace()->getPawnPosition(selectedPawn);
}

//---------------------------------------------------------------------------

/**
 * Return what's the destination space of the pawn selected to be moved
 *
 * @return int destination space of the pawn selected to be moved or
 *         return -1 if selectedPawn = NULL
 */
int PGame::selectedPawnDestinationSpaceIndex()
{
    int num = -1;
    PSpace *destSpace;

    if (selectedPawn == (PPawn *)NULL)
    {
        num = -1;
    }
    else
    {

        // Start the moving process
        if ((destSpace = rules->calcDestination(board,
                                                selectedPawn,
                                                getLastDiceForward())) !=
            (PSpace *)NULL)
        {
            num = destSpace->getIndex();
        }
    }

    return num;
}

//---------------------------------------------------------------------------

/**
 * Return what's the positions inside the destination space of the pawn selected to be moved
 *
 * @return int position or -1
 */
int PGame::selectedPawnDestinationSpacePos()
{
    int num = -1;
    PSpace *destSpace;

    if (selectedPawn == (PPawn *)NULL)
    {
        num = -1;
    }
    else
    {
        // Start the moving process
        if ((destSpace = rules->calcDestination(board,
                                                selectedPawn,
                                                getLastDiceForward())) !=
            (PSpace *)NULL)
        {
            num = destSpace->getPawnWillBePosition(selectedPawn);
        }
    }

    return num;
}

//---------------------------------------------------------------------------

/**
 *  Getter: Get the pointer to the selected Pawn
 *
 *  @return pointer to PPawn* to the selected Pawn
 */
PPawn *PGame::getSelectedPawn()
{
    return selectedPawn;
}

//---------------------------------------------------------------------------

/**
 * Execute the move of the selected PPawn.
 * The selected pawn is stored at PPawn * selectedPawn pointer
 */
void PGame::movePawn()
{
    PSpace *destSpace;

    // Start the moving process
    if ((destSpace = rules->calcDestination(board,
                                            selectedPawn,
                                            getLastDiceForward())) !=
        (PSpace *)NULL)
    {
        if (this->isWaitingSelectPawn())
        {
            if (selectedPawn->canMove())
            {

                // Change status
                this->setStatusPawnSelected();

                // Change status
                this->setStatusMovingPawn();

                // If the pawn being moved eats at destination, send the other one HOME
                if (selectedPawn->canEatPawn())
                {
                    PPawn *eated_pawn;
                    if ((eated_pawn = destSpace->getEatedPawn(selectedPawn)) !=
                        (PPawn *)NULL)
                    {

                        // Move the eated pawn to its HOME
                        // (void) eated_pawn->setSpace(board->getHomeSpaceOfPawn(eated_pawn));
                        (void)board->movePawnToSpace(
                            eated_pawn,
                            board->getHomeSpaceOfPawn(eated_pawn));

                        // Store the pointer to the last eaten pawn
                        this->setLastEatedPawn(eated_pawn);

                        // Flag that a Pawn has been eated
                        this->setPawnEated(true);
                    }
                }

                // Move the pawn
                //(void) selectedPawn->setSpace(destSpace);
                (void)board->movePawnToSpace(selectedPawn, destSpace);


                // If the pawn being moved entered FINAL space, then activate the flag to count 10
                // and update if Player is finished
                if (destSpace->isFinal())
                {
                    setPawnGotFinal(true);
                    if (player[getTurn()]->isFinished())
                    {
                        this->numPlayerFinished++;
                        if (this->numPlayerFinished == 1)
                        {
                            this->numColorWinner = getTurn();
                        }
                        dbg.printF(3,
                                   "| FINISH: %-8s (round %3d). Players "
                                   "finished: %2d.    |",
                                   board->getColorName(getTurn()),
                                   getNumRound(),
                                   this->getNumPlayerFinished());
                        if (isOptionFirstWinnerEndsGame())
                        {
                            dbg.printF(3,
                                       "| FINISHING THE GAME. First Winner "
                                       "Ends Game.            |");
                            this->setStatusGameStopped();
                        }
                    }
                    // ALL PLAYERS finished ??
                    if (getNumPlayerFinished() == PBoard::numPlayers())
                    {
                        this->setStatusGameStopped();
                    }
                }
                else
                {
                    // Store last Pawn moved
                    board->setLastPawnMoved(selectedPawn);
                }

                // Change status
                this->setStatusFinishMovingPawn();

                // Clear the canMove/canEatPawn status of all pawns
                for (unsigned int x = 0; x < vPawns.size(); x++)
                {
                    vPawns[x]->setCanMove(false);
                    vPawns[x]->setCanEatPawn(false);
                }
            }
        }
    }
}

//---------------------------------------------------------------------------

/**
 * Move manually a Pawn to a Space index. Usefull for editing the Board and
 * during parchis start
 *
 * @return bool true if the movement was sucessfull
 */
bool PGame::movePawnManuallyToSpace(PPawn *new_pawn, int new_space_index)
{

    // Manually move the pawn
    //if ( new_pawn->setSpace(board->getSpaceByIndex(new_space_index)) ) {
    if (board->movePawnToSpace(new_pawn,
                               board->getSpaceByIndex(new_space_index)))
    {
        oss.str("");
        oss << "MANUALLY moved " << new_pawn->getName() << " to "
            << board->getSpaceByIndex(new_space_index)->getName();
        dbg.print(3, oss.str());

        return true;
    }
    return false;
}

//---------------------------------------------------------------------------

/**
 * Send the last Pawn that was moved to its HOME, normally used
 * due to the player getting 3 sixes :-)
 *
 * Note that the "last moved" information is Known by the Board per each
 * color, so this method will get the pointer to the last
 * Pawn that was moved in the Board for a specific color.
 *
 */
void PGame::sendLastMovedHome()
{
    PPawn *p;

    if ((p = board->getLastPawnMoved(this->getTurn())) != (PPawn *)NULL)
    {

        dbg.printF(2,
                   "| Sending Home %-8s                                  |",
                   p->getName().c_str());

        // Send the Pawn to its Home (if it's his turn)
        if (this->getTurn() == p->getColor())
        {
            // (void) p->setSpace(board->getHomeSpaceOfPawn(p));
            (void)board->movePawnToSpace(p, board->getHomeSpaceOfPawn(p));
        }
    }
}


//---------------------------------------------------------------------------

#pragma mark-- Public Game Control

//---------------------------------------------------------------------------

/**
 * Get the value of last dice tossed
 *
 * @return the value of lastDice
 */
int PGame::getLastDice()
{
    return lastDice;
}

//---------------------------------------------------------------------------

/**
 * Store the the value of last Dice tossed
 *
 * @param new_var the new value of lastDice
 */
void PGame::setLastDice(int new_var)
{
    lastDice = new_var;
}

//---------------------------------------------------------------------------

/**
 * Set the value of last Dice Forward. This value will be used as the number
 * of spaces to move
 *
 * @param new_var the new value for lastDiceForward
 */
void PGame::setLastDiceForward(int new_var)
{
    lastDiceForward = new_var;
}

//---------------------------------------------------------------------------

/**
 * Get the value of last Dice Forward. If Dice is 6 and all pawns out, then it
 * should be a 7. Also store here a 10 or a 20
 *
 * @return the value of lastDiceForward
 */
int PGame::getLastDiceForward()
{
    return lastDiceForward;
}

//---------------------------------------------------------------------------

/**
 * Return the pointer to the last eated pawn
 *
 * @return Pawn * pointer to the last eated pawn
 */
PPawn *PGame::getLastEatedPawn()
{
    return this->lastEatedPawn;
}

//---------------------------------------------------------------------------

/**
 * Game control: Get pointer to the current player
 *
 * @return Player *
 */
PPlayer *PGame::getCurrentPlayer()
{
    return (player[getTurn()]);
}

//---------------------------------------------------------------------------

/**
 * Game control: undo last action
 *
 * Works in conbination with saveMemento() Goes back to the last internal state
 * of the saved objects, based on the Memento design pattern.
 *
 * Originator   Board.class         (Creates the memento object)
 * Memento      BoardMemento.class  (Stores/Restores internal state)
 * CareTaker    Game.cpp            (Calls createMemento/setMemento to control the undo/redo's)
 *                                  Implemented with:  saveMementos()
 *                                                     undo()
 *                                                     redo()
 *
 * @return bool true if undo was successfull
 *
 */
bool PGame::undo()
{
    bool result = false;

    if (!bUndoActive)
    {
        return result;
    }

    if (this->isRunning())
    {
        dbg.print(3, "|  UNDO called...");

        // If already at the first memento then ignore and return
        if (numActualMemento == 0)
        {
            oss.str("");
            oss << "|  Can't Undo more...";
            dbg.print(2, oss.str());

            return result;
        }

        // Decrement the number of the actual memento
        numActualMemento--;

        // Go to the previous memento
        board->setMemento(vBoardMemento[numActualMemento]);

        dbg.print(2,
                  "|                                                        |");
        dbg.print(2,
                  "+=========================================================");
        dbg.print(2, "");
        dbg.print(2,
                  "**********************************************************");
        oss.str("");
        oss << "|  UNDO - Restoring MEMENTO. total: " << numSavedMementos
            << "(0-" << numSavedMementos - 1 << ") Actual:" << numActualMemento;
        dbg.print(2, oss.str());
        dbg.print(2,
                  "**********************************************************");
        dbg.print(2,
                  "+=========================================================");
        oss.str("");
        oss << "|              TURN  " << board->getColorName(this->getTurn())
            << "  (Round: " << getNumRound() + 1 << ")";
        dbg.print(2, oss.str());


        // Recreate this memento
        std::vector<PBoardMemento *>::iterator iter =
            vBoardMemento.begin() + (numActualMemento);
        vBoardMemento.erase(iter);
        vBoardMemento.insert(iter, board->createMemento(numActualMemento));

        dbg.print(2, "|  ");

        result = true;
    }

    return result;
}

//---------------------------------------------------------------------------

/**
 * Game control: redo last undo action
 *
 * Works in conbination with saveMemento() Goes back to the last internal state
 * of the saved objects, based on the Memento design pattern.
 *
 * Originator   Board.class         (Creates the memento object)
 * Memento      BoardMemento.class  (Stores/Restores internal state)
 * CareTaker    Game.cpp            (Calls createMemento/setMemento to control the undo/redo's)
 *                                  Implemented with:  saveMementos()
 *                                                     undo()
 *                                                     redo()
 * @return bool true if undo was successfull
 */
bool PGame::redo()
{
    bool result = false;

    if (!bUndoActive)
    {
        return result;
    }

    if (this->isRunning())
    {
        dbg.print(3, "|  REDO called...");

        // If already at last memento then ignore and return
        if (numActualMemento == (numSavedMementos - 1))
        {
            oss.str("");
            oss << "|  Can't Redo more...";
            dbg.print(3, oss.str());

            return result;
        }

        // Go to the next memento
        numActualMemento++;

        // BOARD
        board->setMemento(vBoardMemento[numActualMemento]);

        dbg.print(2,
                  "|                                                        |");
        dbg.print(2,
                  "+=========================================================");
        dbg.print(2, "");
        dbg.print(2,
                  "**********************************************************");
        oss.str("");
        oss << "|  REDO - Restoring MEMENTO. total: " << numSavedMementos
            << "(0-" << numSavedMementos - 1 << ") Actual:" << numActualMemento;
        dbg.print(2, oss.str());
        dbg.print(2,
                  "**********************************************************");
        dbg.print(2,
                  "+=========================================================");
        oss.str("");
        oss << "|              TURN  " << board->getColorName(this->getTurn())
            << "  (Round: " << getNumRound() + 1 << ")";
        dbg.print(2, oss.str());


        // Recreate this memento
        std::vector<PBoardMemento *>::iterator iter =
            vBoardMemento.begin() + (numActualMemento);
        vBoardMemento.erase(iter);
        vBoardMemento.insert(iter, board->createMemento(numActualMemento));
        result = true;

        dbg.print(2, "|  ");
    }

    return result;
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
