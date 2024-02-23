
/**
 *  @class  PBoardMemento PBoardMemento.cpp "PBoardMemento.cpp"
 *  @file   PBoardMemento.cpp
 *  @brief  Parchis Class definition: Stores/Restores internal state of the Board object for undo/redo.
 *
 *  ---------------------------------------------------------------------------
 */


//---------------------------------------------------------------------------

#include "PBoardMemento.h"


//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Public Methods
#pragma mark-- Constructor/Destructor

/**
 * Constructor of PBoardMemento
 *
 * I receive as param's all the pointers
 */
PBoardMemento::PBoardMemento(int new_index,
                             PBoard *the_board,
                             PGame *o_game,
                             PPlayer **o_player,
                             PPawn **o_yPawn,
                             PPawn **o_bPawn,
                             PPawn **o_rPawn,
                             PPawn **o_gPawn,
                             std::vector<PPawn *> o_vPawns,
                             PSpace **o_space,
                             PPawn **o_lastPawnMoved)
{

    // For loops
    int i = 0;


    // Initialize the debug
    dbg.setCallerName("Memento");

    // STORE which memento is this one inside the undo stack
    // ============================================================================
    index = new_index;
    oss.str("");
    oss << "|  BoardMemento created. Index: " << index;
    dbg.print(3, oss.str());


    // GAME
    // ============================================================================

    // Save the current status of the game. I only save the most important
    // attributes that will be needed to be restores
    game = new PGame(o_game->getName());
    game->setTurn(o_game->getTurn());
    game->setNumRound(o_game->getNumRound());
    game->setNumSixes(o_game->getNumSixes());


    // PLAYER's
    // ============================================================================

    //Create a new player pointer to numPlayers players
    player = new PPlayer *[PBoard::numPlayers()]; // Instantiate the new Players

    // Create new players and clone them from the existing ones (o_player)
    for (i = 0; i < PBoard::numPlayers(); i++)
    {

        // Create the new Player
        // Copy the attributes
        // Assign the new player
        if (o_player[i]->getType() == PPlayer::getNumTypeHuman())
        {
            PHuman *new_player;
            new_player = new PHuman();
            PPlayer::copyPlayer(o_player[i], new_player);
            player[i] = new_player;
        }
        else if (o_player[i]->getType() == PPlayer::getNumTypeSimple())
        {
            PRobotSimple *new_player;
            new_player = new PRobotSimple();
            PPlayer::copyPlayer(o_player[i], new_player);
            player[i] = new_player;
        }
        else if (o_player[i]->getType() == PPlayer::getNumTypeSmart())
        {
            PRobotSmart *new_player;
            new_player = new PRobotSmart();
            PPlayer::copyPlayer(o_player[i], new_player);
            player[i] = new_player;
        }

        //        oss.str("");
        //        oss << player[i]->getName() << "." << this->index;
        //        player[i]->setName(oss.str());
    }


    // PAWN's & vPAWN's
    // ============================================================================

    // Create the new pawn's pointers
    yPawn = new PPawn *[PBoard::pawnsPerPlayer()]; // Yellow
    bPawn = new PPawn *[PBoard::pawnsPerPlayer()]; // Blue
    rPawn = new PPawn *[PBoard::pawnsPerPlayer()]; // Red
    gPawn = new PPawn *[PBoard::pawnsPerPlayer()]; // Green

    // Create(copy) the yellow pawns
    for (i = 0; i < PBoard::pawnsPerPlayer(); i++)
    {
        //        oss.str("");
        //        oss << o_yPawn[i]->getName() << "." << this->index;
        //        yPawn[i] = new PPawn ( the_board, oss.str(), o_yPawn[i]->getIndex(), o_yPawn[i]->getNumber(),
        //                              o_yPawn[i]->getColor() );
        yPawn[i] = new PPawn(the_board,
                             o_yPawn[i]->getName(),
                             o_yPawn[i]->getIndex(),
                             o_yPawn[i]->getNumber(),
                             o_yPawn[i]->getColor());
        vPawns.push_back(yPawn[i]);
    }
    // Create(copy) the blue pawns
    for (i = 0; i < PBoard::pawnsPerPlayer(); i++)
    {
        //        oss.str("");
        //        oss << o_bPawn[i]->getName() << "." << this->index;
        //        bPawn[i] = new PPawn ( the_board, oss.str(), o_bPawn[i]->getIndex(), o_bPawn[i]->getNumber(),
        //                              o_bPawn[i]->getColor() );
        bPawn[i] = new PPawn(the_board,
                             o_bPawn[i]->getName(),
                             o_bPawn[i]->getIndex(),
                             o_bPawn[i]->getNumber(),
                             o_bPawn[i]->getColor());
        vPawns.push_back(bPawn[i]);
    }
    // Create(copy) the red pawns
    for (i = 0; i < PBoard::pawnsPerPlayer(); i++)
    {
        //        oss.str("");
        //        oss << o_rPawn[i]->getName() << "." << this->index;
        //        rPawn[i] = new PPawn ( the_board, oss.str(), o_rPawn[i]->getIndex(), o_rPawn[i]->getNumber(),
        //                              o_rPawn[i]->getColor() );
        rPawn[i] = new PPawn(the_board,
                             o_rPawn[i]->getName(),
                             o_rPawn[i]->getIndex(),
                             o_rPawn[i]->getNumber(),
                             o_rPawn[i]->getColor());
        vPawns.push_back(rPawn[i]);
    }
    // Create(copy) the green pawns
    for (i = 0; i < PBoard::pawnsPerPlayer(); i++)
    {
        //        oss.str("");
        //        oss << o_gPawn[i]->getName() << "." << this->index;
        //        gPawn[i] = new PPawn ( the_board, oss.str(), o_gPawn[i]->getIndex(), o_gPawn[i]->getNumber(),
        //                              o_gPawn[i]->getColor() );
        gPawn[i] = new PPawn(the_board,
                             o_gPawn[i]->getName(),
                             o_gPawn[i]->getIndex(),
                             o_gPawn[i]->getNumber(),
                             o_gPawn[i]->getColor());
        vPawns.push_back(gPawn[i]);
    }


    // SPACE's
    // ============================================================================

    // Create the new spaces's pointers
    space =
        new PSpace *[PBoard::numSpaces()]; // Total num. of spaces in the Board

    // Create (copy) the spaces
    for (i = 0; i < PBoard::numSpaces(); i++)
    {
        //        oss.str("");
        //        oss << o_space[i]->getName() << "." << this->index;
        //        space[i] = new Space ( the_board, oss.str(), o_space[i]->getRole(), o_space[i]->getIndex(),
        //                               o_space[i]->getNumber(), o_space[i]->getColor(), o_space[i]->getOrientation() );
        space[i] = new PSpace(the_board,
                              o_space[i]->getName(),
                              o_space[i]->getRole(),
                              o_space[i]->getIndex(),
                              o_space[i]->getNumber(),
                              o_space[i]->getColor(),
                              o_space[i]->getOrientation());
    }

    // Assign the newly created pawns to the newly created spaces
    for (unsigned int x = 0; x < vPawns.size(); x++)
    {
        // Move to the same space index as current one
        int s = o_vPawns[x]->getSpace()->getIndex();
        //        if ( !vPawns[x]->setSpace  ( space[s] ) ) {
        if (!the_board->movePawnToSpace(vPawns[x], space[s]))
        {
            oss.str("");
            oss << "|  BoardMemento, ERROR !! BE CAREFUL !!: While creating "
                   "couldn't set the space to "
                << space[s]->getName();
            dbg.print(3, oss.str());
        }
    }

    // LAST PAWN MOVED: lastPawnMoved
    // ============================================================================
    lastPawnMoved = new PPawn *[NUMPAWNSPERPLAYER];
    for (i = 0; i < NUMPAWNSPERPLAYER; i++)
    {
        lastPawnMoved[i] = (PPawn *)NULL;
    }
    if (o_lastPawnMoved[0] != (PPawn *)NULL)
        lastPawnMoved[0] = yPawn[o_lastPawnMoved[0]->getIndex()];
    if (o_lastPawnMoved[1] != (PPawn *)NULL)
        lastPawnMoved[1] = bPawn[o_lastPawnMoved[1]->getIndex()];
    if (o_lastPawnMoved[2] != (PPawn *)NULL)
        lastPawnMoved[2] = rPawn[o_lastPawnMoved[2]->getIndex()];
    if (o_lastPawnMoved[3] != (PPawn *)NULL)
        lastPawnMoved[3] = gPawn[o_lastPawnMoved[3]->getIndex()];
}

//---------------------------------------------------------------------------

/**
 * BoardMemento Destructor
 */
PBoardMemento::~PBoardMemento()
{
    oss.str("");
    oss << "|  BoardMemento destructor at index position: " << index;
    dbg.print(3, oss.str());
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#pragma mark -
#pragma mark Public Methods: Getters

//---------------------------------------------------------------------------

/**
 * getters()
 *
 */

//---------------------------------------------------------------------------

/**
 * Get the yellow Pawns pointer when restauring a memento.
 * @return the pointer of pointers PPawn** to the yellow pawns
 */
PPawn **PBoardMemento::getYPawn()
{
    return yPawn;
}

//---------------------------------------------------------------------------

/**
 * Get the blue Pawns pointer when restauring a memento.
 * @return the pointer of pointers PPawn** to the blue pawns
 */
PPawn **PBoardMemento::getBPawn()
{
    return bPawn;
}

//---------------------------------------------------------------------------

/**
 * Get the red Pawns pointer when restauring a memento.
 * @return the pointer of pointers PPawn** to the red pawns
 */
PPawn **PBoardMemento::getRPawn()
{
    return rPawn;
}

//---------------------------------------------------------------------------

/**
 * Get the green Pawns pointer when restauring a memento.
 * @return the pointer of pointers PPawn** to the green pawns
 */
PPawn **PBoardMemento::getGPawn()
{
    return gPawn;
}

//---------------------------------------------------------------------------

/**
 * Get the spaces pointer when restauring a memento.
 * @return the pointer of pointers PSpace** to the spaces
 */
PSpace **PBoardMemento::getSpaces()
{
    return space;
}

//---------------------------------------------------------------------------

/**
 * Get the players pointer when restauring a memento.
 * @return the pointer of pointers PPlayer** to the players
 */
PPlayer **PBoardMemento::getPlayers()
{
    return player;
}

//---------------------------------------------------------------------------

/**
 * Get the VPawns pointer when restauring a memento.
 * @return the pointer to the vector pointing to all pawns
 */
std::vector<PPawn *> PBoardMemento::getVPawns()
{
    return vPawns;
}

//---------------------------------------------------------------------------

/**
 * Get the Game pointer when restauring a memento.
 * @return the pointer to the game
 */
PGame *PBoardMemento::getGame()
{
    return game;
}

//---------------------------------------------------------------------------

/**
 * Get the pointer of pointers to last pawn's moved when restauring a memento.
 * @return the pointer of pointers to the last moved pawns
 */
PPawn **PBoardMemento::getLastPawnMoved()
{
    return lastPawnMoved;
}


//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
