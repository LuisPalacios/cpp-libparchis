/**
 *  @class  PRules PRules.cpp "PRules.cpp"
 *  @file   PRules.cpp
 *  @brief  Parchis Class: Rules after dice tossed and calculates destinations
 *
 *  ---------------------------------------------------------------------------
 */


//---------------------------------------------------------------------------

#include "PRules.h"

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Private Methods
#pragma mark-- Class initialization

//---------------------------------------------------------------------------

/**
 * Initialize the attributes and create all instances
 */
void PRules::initAttributes()
{
    dbg.setCallerName("Rules  ");
    dbg.printF(3,
               "| Constructor Rules, name: %-8s                      |",
               getName().c_str());
}

//---------------------------------------------------------------------------

#pragma mark-- Setters

//---------------------------------------------------------------------------

/**
 * Set the value of name
 * @param new_var the new value of name
 */
void PRules::setName(std::string new_var)
{
    name.assign(new_var);
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Public Methods
#pragma mark-- Constructor/Destructor

//---------------------------------------------------------------------------

/**
 * Constructor of PRules
 *
 * @param new_name Name assigned to these rules
 * @param new_game is the pointer to the game
 */
PRules::PRules(std::string new_name, PGame *new_game)
{
    setName(new_name);
    game = new_game;
    initAttributes();
}

//---------------------------------------------------------------------------

/**
 * Destructor
 */
PRules::~PRules()
{
    dbg.print(3, "Destructor Rules");
}
//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Public Methods
#pragma mark-- Getters

//---------------------------------------------------------------------------

/**
 * Get the value of name
 *
 * @return the name assigned to this instance
 */
std::string PRules::getName()
{
    return name;
}

//---------------------------------------------------------------------------

/**
 * Return the number of movable pawns found during the last execRules()
 *
 * @return the numerical value of movable pawns
 */
int PRules::getNumPawnsMovable()
{
    return numPawnsMovable;
}

//---------------------------------------------------------------------------

/**
 * Return the number of pawns that can eat that I found during the last execRules()
 *
 * @return how many pawns can eat
 */
int PRules::getNumPawnsCanEat()
{
    return numPawnsCanEat;
}

//---------------------------------------------------------------------------

/**
 * Execute the rules
 *
 * @param *board pointer to the board
 * @param new_forward the number of spaces asked to move forward
 *
 */
int PRules::execRules(PBoard *board, int new_forward)
{

    int i; // For loops
    int forward = new_forward;
    PSpace *dSpace = (PSpace *)NULL; // Destination space.
    PPlayer *thePlayer = board->getGame()->getCurrentPlayer();
    PPawn **thePawn = thePlayer->getPawns();
    bool bOnePawnGoesOutHome = false;

    // Analyse the rules for each Pawn:
    //
    // Mark movable pawns
    // Mark pawns that can eat
    // Calculate which is the Space where the Pawn can go
    numPawnsMovable = 0;
    numPawnsCanEat = 0;


    // If 3 Sixes: go home...

    if (game->isFlagThirdSix())
    {

        dbg.printF(3,
                   "|  Third Six. exit execRules()                           | "
                   "  <== AQUI LUIS ");
    }
    else
    {

        // Got Through all pawns...

        // CHECK MOVABLE, EAT AND DESTINATIONS
        for (i = 0; i < PBoard::pawnsPerPlayer(); i++)
        {

            // CALCULATE DESTINATION
            // If I'm at HOME and dice is different from a "5" then I cannot move.
            if (forward != 5 && thePawn[i]->getSpace()->isHome())
            {
                dSpace = (PSpace *)NULL;
            }
            else
            {

                // Calculate destination
                dSpace = calcDestination(board, thePawn[i], forward);
                if (dbg.getDebug())
                {
                    if (dSpace != (PSpace *)NULL)
                    {
                        dbg.printF(
                            3,
                            "|  %-8s OK, destination: %-10s                  |",
                            thePawn[i]->getName().c_str(),
                            dSpace->getName().c_str());
                    }
                    else
                    {
                        dbg.printF(3,
                                   "|  %-8s Can't move                         "
                                   "          |",
                                   thePawn[i]->getName().c_str());
                    }
                }
            }

            // IF DESTINATION VALID and can move there...
            // Mark it as movable
            if (dSpace != (PSpace *)NULL)
            {
                thePawn[i]->setCanMove(true);

                // IF ALSO CAN EAT AT DESTINATION
                // Mark it as canEat
                if (dSpace->canEatPawn(thePawn[i]))
                {
                    thePawn[i]->setCanEatPawn(true);
                }
                else
                {
                    thePawn[i]->setCanEatPawn(false);
                }
            }
            else
            {
                thePawn[i]->setCanMove(false);
                thePawn[i]->setCanEatPawn(false);
            }

            // Set a flag if we got a '5' and Pawn can exit Home
            if (forward == 5 && thePawn[i]->canMove() &&
                thePawn[i]->getSpace()->isHome())
            {
                bOnePawnGoesOutHome = true;
            }

            // Store the destination space in the Pawn object
            // This will be used from the Board while setting up the Snapshots
            thePawn[i]->setDestinationSpace(dSpace);
        }


        // CONTROL: A "5" DICE FORCES TO GO OUT HOME
        // If we got a '5' and at least one can go out home then they are forced to do so.
        // In that case I need to clear the movable flag from the other Pawns.
        if (bOnePawnGoesOutHome)
        {
            // Clear movable flag from those not at HOME
            for (i = 0; i < PBoard::pawnsPerPlayer(); i++)
            {
                if (thePawn[i]->canMove() && !thePawn[i]->isAtHome())
                {
                    thePawn[i]->setCanMove(false);
                    thePawn[i]->setCanEatPawn(false);
                }
            }
        }


        // CONTROL: A "6" DICE FORCES TO OPEN A BARRIER
        // If we got a '6' then check if a Barrier exists and their Pawns can move.
        // In that case I need to clear the movable flag from the other Pawns.
        //    dbg.print ( 3, "execRules(): CHECKING THE RULES: 6 OPEN BARRIER?");
        if (forward == 6 || forward == 7)
        {
            bool bBarrierMovable = false;

            // Quick check to see if Barrier exist and movable.
            for (i = 0; i < PBoard::pawnsPerPlayer(); i++)
            {
                if (thePawn[i]->getSpace()->isBarrier() &&
                    thePawn[i]->canMove())
                {
                    bBarrierMovable = true;
                    break;
                }
            }

            // Now clean movable/eat from those not in barrier/movable
            if (bBarrierMovable)
            {
                for (i = 0; i < PBoard::pawnsPerPlayer(); i++)
                {

                    if (!thePawn[i]->getSpace()->isBarrier())
                    {
                        thePawn[i]->setCanMove(false);
                        thePawn[i]->setCanEatPawn(false);
                    }
                }
            }
        }


        // Store the number of movable and canEat pawns, clean Destination spaces
        // from those Pawn's that cannot move.
        // And show conclusions, just for debugging purposes
        for (i = 0; i < PBoard::pawnsPerPlayer(); i++)
        {
            if (thePawn[i]->canMove())
            {
                numPawnsMovable++;
            }
            else
            {
                thePawn[i]->setDestinationSpace((PSpace *)NULL);
            }
            if (thePawn[i]->canEatPawn())
                numPawnsCanEat++;
            if (dbg.getDebug())
            {
                dbg.printF(3,
                           "|  Move: %d, Eat: %d                               "
                           "        |",
                           thePawn[i]->canMove(),
                           thePawn[i]->canEatPawn());
            }
        }
    }

    return numPawnsMovable;
}

//---------------------------------------------------------------------------

/**
 * Calculate if it's possible to move forward the passed Pawn
 * by 'new_forward' spaces. This method will go through each Space in the path
 * and verifying if the Pawn can pass through them.
 *
 * @param board is the pointer to the Board
 * @param new_pawn is the Pawn for which I will calculate
 * @param new_forward is the number of spaces wanted to move forward
 * @return Space * to the space where the pawn is to be moved
 *
 * This method is not only used by the Rules for normal playing but also by
 * the Robots for its analysis.
 *
 */
PSpace *PRules::calcDestination(PBoard *board, PPawn *new_pawn, int new_forward)
{

    PSpace **space =
        board
            ->getSpaces(); // Get the pointer to the array of Spaces in the Board
    PSpace *dSpace = (PSpace *)NULL; // Destination space that I will return.
    PSpace *s;                       // Temporary pointer
    //Luis, I used ANALYZE under Xcode and next line was reported 'Unused entity sf'
    //  Space * sf;                       // Temporary pointer
    unsigned int ini;
    std::vector<PSpace *> *v;
    int forward = new_forward;

    //    oss.str("");
    //    oss << "| Start calculating DESTINATION for " << new_pawn->getName() << ", forward=" << forward;
    //    dbg.print ( 3, oss.str() );
    //    oss.str("");
    //    dbg.print ( 3, oss.str() );

    // Only if the pawn is still playing. If it's at his FINAL then ignore it...
    if (!new_pawn->getSpace()->isFinal())
    {
        // Pawn at HOME and it's a 5 ??
        if (new_pawn->getSpace()->isHome() && forward == 5)
        {
            // Yes, then it's valid, as it's the unique destination valid
            s = space[board->getIndexStartSpaceByColor(new_pawn->getColor())];
            //            oss.str("");
            //            oss << "| checking space " << s->getName();
            //            dbg.print ( 3, oss.str() );
            if (s->canAddPawn(new_pawn))
            {
                dSpace = s;
            }
            //                oss.str("");
            //                oss << "| checking space " << s->getName() << " Can be added";
            //                dbg.print ( 3, oss.str() );
            //            } else {
            //                oss.str("");
            //                oss << "| checking space " << s->getName() << " Cannot be added";
            //                dbg.print ( 3, oss.str() );
            //            }
        }
        else
        {

            // Walk through my color's path
            v = board->getPathVector(new_pawn->getColor());
            ini = board->getPathIndex(new_pawn->getSpace(),
                                      new_pawn->getColor()) +
                  1;
            //Luis, I used ANALYZE under Xcode and next line was reported to 's' is never read
            //          s=(*v)[ini];
            unsigned int x;
            int i = 0;
            if (ini != (v->size()))
            {
                //Luis, I used ANALYZE under Xcode and next line was reported to 'sf' is never read
                //              sf = (*v)[v->size()-1];
                for (x = ini, i = 0; x < v->size() && i < forward; x++, i++)
                {
                    // Get the pointer to the Space I'm walking through
                    s = (*v)[x];

                    // We are at DESTINATION. It is the last Space in the walk
                    //if ( (x==(v->size()-1)) || (i==(forward-1)) ) {
                    if (i == (forward - 1))
                    {
                        // Check if I can be added to the destination.
                        if (s->canAddPawn(new_pawn))
                        {
                            dSpace = s;
                        }
                        else
                        {
                            dSpace = (PSpace *)NULL;
                            // force exit from the for()
                            //Luis, I used ANALYZE under Xcode and next line was reported to 'i' is never read
                            //                          i=forward;
                            break;
                        }
                    }
                    else
                    {
                        // We are WALKING THROUGH THE PATH
                        // Check if I can pass through the space
                        if (!s->canWalkPawn(new_pawn))
                        {
                            dSpace = (PSpace *)NULL;
                            // force exit from the for()
                            //Luis, I used ANALYZE under Xcode and next line was reported to 'i' is never read
                            //                          i=forward;
                            break;
                        }
                    }
                }
            }
        }
    }

    return dSpace;
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
