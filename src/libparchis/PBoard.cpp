
/**
 *  @class  PBoard PBoard.cpp "PBoard.cpp"
 *  @file   PBoard.cpp
 *  @brief  Parchis Class Definition: Represents the board, instantiates PGame, PSpace's, PPawn's, PSnapshot's and PDice
 *
 *  ---------------------------------------------------------------------------
 */


//---------------------------------------------------------------------------

#include "PBoard.h"

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Static Attributes

const char *PBoard::colorName[5] = {"Yellow",
                                    "Blue",
                                    "Red",
                                    "Green",
                                    "NoColor"};

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Private Methods
#pragma mark-- Class initialization

/**
 * Initialize the attributes and create all instances
 */
void PBoard::initAttributes()
{
    int i, num;

    // Show about me...
    dbg.setCallerName("Board  ");
    dbg.print(3, "+--------------------------------------------------------+");
    dbg.printF(3,
               "| Constructor Board, name: %-8s                      |",
               getName().c_str());


    // Set mandatory options for the Board.
    // FIXME: this version only supports 4 players, ToDo, add support for 6 players
    setEditable(false);
    vColorName.push_back("YELLOW");
    vColorName.push_back("BLUE");
    vColorName.push_back("RED");
    vColorName.push_back("GREEN");
    vColorName.push_back("NoColor");

    // Instantiate Game object, which will remain in "not running" state
    game = new PGame("Juego");

    // -- spaces instantiation, before PAWN's as they will bind to its HOME's default space
    space =
        new PSpace *[PBoard::numSpaces()]; // Total num. of spaces in the Board
    for (i = 0, num = 1; i < PBoard::numSpaces(); i++, num++)
    {

        // num = Real "number" of the space
        // i   = position in the array.

        oss.str("");
        oss << "Space" << num;

        // Instantiate "start", "normal", "rampsafe" and "safe" spaces
        if ((num >= 1 && num <= 68))
        {

            // START
            if (num == 5)
            {
                space[i] = new PSpace(this,
                                      oss.str(),
                                      PBoard::spaceTypeStart(),
                                      i,
                                      num,
                                      PBoard::getYellow(),
                                      1);
                indexStartSpaceByColor[PBoard::getYellow()] = i;
            }
            else if (num == 22)
            {
                space[i] = new PSpace(this,
                                      oss.str(),
                                      PBoard::spaceTypeStart(),
                                      i,
                                      num,
                                      PBoard::getBlue(),
                                      2);
                indexStartSpaceByColor[PBoard::getBlue()] = i;
            }
            else if (num == 39)
            {
                space[i] = new PSpace(this,
                                      oss.str(),
                                      PBoard::spaceTypeStart(),
                                      i,
                                      num,
                                      PBoard::getRed(),
                                      1);
                indexStartSpaceByColor[PBoard::getRed()] = i;
            }
            else if (num == 56)
            {
                space[i] = new PSpace(this,
                                      oss.str(),
                                      PBoard::spaceTypeStart(),
                                      i,
                                      num,
                                      PBoard::getGreen(),
                                      2);
                indexStartSpaceByColor[PBoard::getGreen()] = i;

                // RAMPSAFE
            }
            else if (num == 17 || num == 34 || num == 51 || num == 68)
            {
                if (num == 17)
                {
                    space[i] = new PSpace(this,
                                          oss.str(),
                                          PBoard::spaceTypeRampSafe(),
                                          i,
                                          num,
                                          PBoard::getNoColor(),
                                          2);
                    indexRampSafeSpaceByColor[PBoard::getBlue()] = i;
                }
                if (num == 34)
                {
                    space[i] = new PSpace(this,
                                          oss.str(),
                                          PBoard::spaceTypeRampSafe(),
                                          i,
                                          num,
                                          PBoard::getNoColor(),
                                          1);
                    indexRampSafeSpaceByColor[PBoard::getRed()] = i;
                }
                if (num == 51)
                {
                    space[i] = new PSpace(this,
                                          oss.str(),
                                          PBoard::spaceTypeRampSafe(),
                                          i,
                                          num,
                                          PBoard::getNoColor(),
                                          2);
                    indexRampSafeSpaceByColor[PBoard::getGreen()] = i;
                }
                if (num == 68)
                {
                    space[i] = new PSpace(this,
                                          oss.str(),
                                          PBoard::spaceTypeRampSafe(),
                                          i,
                                          num,
                                          PBoard::getNoColor(),
                                          1);
                    indexRampSafeSpaceByColor[PBoard::getYellow()] = i;
                }

                // SAFE
            }
            else if (num == 12 || num == 29 || num == 46 || num == 63)
            {
                if (num == 12 || num == 46)
                {
                    space[i] = new PSpace(this,
                                          oss.str(),
                                          PBoard::spaceTypeSafe(),
                                          i,
                                          num,
                                          PBoard::getNoColor(),
                                          2);
                }
                else
                {
                    space[i] = new PSpace(this,
                                          oss.str(),
                                          PBoard::spaceTypeSafe(),
                                          i,
                                          num,
                                          PBoard::getNoColor(),
                                          1);
                }
            }
            else
            {

                // REST of SPACES
                // VERTICALS
                if ((num >= 1 && num <= 8) || (num >= 26 && num <= 42) ||
                    (num >= 60 && num <= 67))
                {
                    space[i] = new PSpace(this,
                                          oss.str(),
                                          PBoard::spaceTypeNormal(),
                                          i,
                                          num,
                                          PBoard::getNoColor(),
                                          1);

                    // HORIZONTALS
                }
                else
                {
                    space[i] = new PSpace(this,
                                          oss.str(),
                                          PBoard::spaceTypeNormal(),
                                          i,
                                          num,
                                          PBoard::getNoColor(),
                                          2);
                }
            }


            // RAMP & FINAL
        }
        else if (num >= 69 && num <= 100)
        {
            if (num >= 69 && num <= 75)
            { // Yellow ramp
                space[i] = new PSpace(this,
                                      oss.str(),
                                      PBoard::spaceTypeRamp(),
                                      i,
                                      num,
                                      PBoard::getYellow(),
                                      1);
                if (num == 69)
                    indexRampFirstSpaceByColor[PBoard::getYellow()] = i;
            }
            else if (num == 76)
            { // Yellow final
                space[i] = new PSpace(this,
                                      oss.str(),
                                      PBoard::spaceTypeFinal(),
                                      i,
                                      num,
                                      PBoard::getYellow(),
                                      1);
                indexFinalSpaceByColor[PBoard::getYellow()] = i;
            }
            else if (num >= 77 && num <= 83)
            { // Blue ramp
                space[i] = new PSpace(this,
                                      oss.str(),
                                      PBoard::spaceTypeRamp(),
                                      i,
                                      num,
                                      PBoard::getBlue(),
                                      2);
                if (num == 77)
                    indexRampFirstSpaceByColor[PBoard::getBlue()] = i;
            }
            else if (num == 84)
            { // Blue final
                space[i] = new PSpace(this,
                                      oss.str(),
                                      PBoard::spaceTypeFinal(),
                                      i,
                                      num,
                                      PBoard::getBlue(),
                                      2);
                indexFinalSpaceByColor[PBoard::getBlue()] = i;
            }
            else if (num >= 85 && num <= 91)
            { // Red ramp
                space[i] = new PSpace(this,
                                      oss.str(),
                                      PBoard::spaceTypeRamp(),
                                      i,
                                      num,
                                      PBoard::getRed(),
                                      1);
                if (num == 85)
                    indexRampFirstSpaceByColor[PBoard::getRed()] = i;
            }
            else if (num == 92)
            { // Red final
                space[i] = new PSpace(this,
                                      oss.str(),
                                      PBoard::spaceTypeFinal(),
                                      i,
                                      num,
                                      PBoard::getRed(),
                                      1);
                indexFinalSpaceByColor[PBoard::getRed()] = i;
            }
            else if (num >= 93 && num <= 99)
            { // Green ramp
                space[i] = new PSpace(this,
                                      oss.str(),
                                      PBoard::spaceTypeRamp(),
                                      i,
                                      num,
                                      PBoard::getGreen(),
                                      2);
                if (num == 93)
                    indexRampFirstSpaceByColor[PBoard::getGreen()] = i;
            }
            else if (num == 100)
            { // Green final
                space[i] = new PSpace(this,
                                      oss.str(),
                                      PBoard::spaceTypeFinal(),
                                      i,
                                      num,
                                      PBoard::getGreen(),
                                      2);
                indexFinalSpaceByColor[PBoard::getGreen()] = i;
            }

            // HOME
        }
        else if (num == 101)
        {
            space[i] = new PSpace(this,
                                  oss.str(),
                                  PBoard::spaceTypeHome(),
                                  i,
                                  num,
                                  PBoard::getYellow(),
                                  0);
            indexHomeSpaceByColor[PBoard::getYellow()] = i;
        }
        else if (num == 102)
        {
            space[i] = new PSpace(this,
                                  oss.str(),
                                  PBoard::spaceTypeHome(),
                                  i,
                                  num,
                                  PBoard::getBlue(),
                                  0);
            indexHomeSpaceByColor[PBoard::getBlue()] = i;
        }
        else if (num == 103)
        {
            space[i] = new PSpace(this,
                                  oss.str(),
                                  PBoard::spaceTypeHome(),
                                  i,
                                  num,
                                  PBoard::getRed(),
                                  0);
            indexHomeSpaceByColor[PBoard::getRed()] = i;
        }
        else if (num == 104)
        {
            space[i] = new PSpace(this,
                                  oss.str(),
                                  PBoard::spaceTypeHome(),
                                  i,
                                  num,
                                  PBoard::getGreen(),
                                  0);
            indexHomeSpaceByColor[PBoard::getGreen()] = i;
        }
    }


    // Define the QUADRANT Attributes, each Space will have 4 attributes, defining
    // in which Quadrant this space is located relative to each color
    // Example: Space5 is Q1 for yellow, Q4 for blue, Q3 for red and Q2 for green
    for (i = 0, num = 1; i < 68; i++, num++)
    {

        // YELLOW
        if ((num >= 5 && num <= 16))
            space[i]->setQuadrant(PBoard::getYellow(), Q1());
        if ((num >= 17 && num <= 33))
            space[i]->setQuadrant(PBoard::getYellow(), Q2());
        if ((num >= 34 && num <= 50))
            space[i]->setQuadrant(PBoard::getYellow(), Q3());
        if ((num >= 51 && num <= 67))
            space[i]->setQuadrant(PBoard::getYellow(), Q4());

        // BLUE
        if ((num >= 22 && num <= 33))
            space[i]->setQuadrant(PBoard::getBlue(), Q1());
        if ((num >= 34 && num <= 50))
            space[i]->setQuadrant(PBoard::getBlue(), Q2());
        if ((num >= 51 && num <= 67))
            space[i]->setQuadrant(PBoard::getBlue(), Q3());
        if (num == 68 || (num >= 1 && num <= 16))
            space[i]->setQuadrant(PBoard::getBlue(), Q4());

        // RED
        if ((num >= 39 && num <= 50))
            space[i]->setQuadrant(PBoard::getRed(), Q1());
        if ((num >= 51 && num <= 67))
            space[i]->setQuadrant(PBoard::getRed(), Q2());
        if (num == 68 || (num >= 1 && num <= 16))
            space[i]->setQuadrant(PBoard::getRed(), Q3());
        if ((num >= 17 && num <= 33))
            space[i]->setQuadrant(PBoard::getRed(), Q4());

        // GREEN
        if ((num >= 56 && num <= 67))
            space[i]->setQuadrant(PBoard::getGreen(), Q1());
        if (num == 68 || (num >= 1 && num <= 16))
            space[i]->setQuadrant(PBoard::getGreen(), Q2());
        if ((num >= 17 && num <= 33))
            space[i]->setQuadrant(PBoard::getGreen(), Q3());
        if ((num >= 34 && num <= 50))
            space[i]->setQuadrant(PBoard::getGreen(), Q4());
    }


    // -- pawn's instantiation and place them in their corresponding HOME's spaces.
    yPawn = new PPawn *[PBoard::pawnsPerPlayer()]; // Yellow
    bPawn = new PPawn *[PBoard::pawnsPerPlayer()]; // Blue
    rPawn = new PPawn *[PBoard::pawnsPerPlayer()]; // Red
    gPawn = new PPawn *[PBoard::pawnsPerPlayer()]; // Green

    for (i = 0, num = 1; i < PBoard::pawnsPerPlayer(); i++, num++)
    {
        oss.str("");
        oss << "pYellow" << num;
        yPawn[i] = new PPawn(this, oss.str(), i, num, PBoard::getYellow());
        this->movePawnToSpace(yPawn[i], this->getHomeSpaceOfPawn(yPawn[i]));
        vPawns.push_back(yPawn[i]);
    }
    for (i = 0, num = 1; i < PBoard::pawnsPerPlayer(); i++, num++)
    {
        oss.str("");
        oss << "pBlue" << num;
        bPawn[i] = new PPawn(this, oss.str(), i, num, PBoard::getBlue());
        this->movePawnToSpace(bPawn[i], this->getHomeSpaceOfPawn(bPawn[i]));
        vPawns.push_back(bPawn[i]);
    }
    for (i = 0, num = 1; i < PBoard::pawnsPerPlayer(); i++, num++)
    {
        oss.str("");
        oss << "pRed" << num;
        rPawn[i] = new PPawn(this, oss.str(), i, num, PBoard::getRed());
        this->movePawnToSpace(rPawn[i], this->getHomeSpaceOfPawn(rPawn[i]));
        vPawns.push_back(rPawn[i]);
    }
    for (i = 0, num = 1; i < PBoard::pawnsPerPlayer(); i++, num++)
    {
        oss.str("");
        oss << "pGreen" << num;
        gPawn[i] = new PPawn(this, oss.str(), i, num, PBoard::getGreen());
        this->movePawnToSpace(gPawn[i], this->getHomeSpaceOfPawn(gPawn[i]));
        vPawns.push_back(gPawn[i]);
    }

    // Initialize the VPaths
    this->initVPaths();

    // lastpawnmoved
    lastPawnMoved =
        new PPawn *[NUMPAWNSPERPLAYER]; // Total num. of spaces in the Board

    for (i = 0; i < NUMPAWNSPERPLAYER; i++)
    {
        lastPawnMoved[i] = (PPawn *)NULL;
    }

    // DICE, create it and move it to the YELLOW HOME
    dice = new PDice("Dice");
    moveDiceToSpace(
        dice,
        this->getSpaceByIndex(this->getIndexHomeSpaceByColor(YELLOW)));
    //this->getSpaceByIndex(this->getIndexHomeSpaceByColor(YELLOW))->setDice(dice);
    //dice->setSpace(this->getSpaceByIndex(this->getIndexHomeSpaceByColor(YELLOW)));


    // PLAYERS: Instantiate the players
    player = new PPlayer *[PBoard::numPlayers()]; // Instantiate the Players

    // Create the players
    oss.str("");
    oss << "Player0";
    //player[0] = new RobotSmart ( oss.str(), 0, dice );
    player[0] = new PRobotSimple(oss.str(), 0, dice);
    oss.str("");
    oss << "Player1";
    player[1] = new PRobotSimple(oss.str(), 1, dice);
    oss.str("");
    oss << "Player2";
    player[2] = new PRobotSimple(oss.str(), 2, dice);
    oss.str("");
    oss << "Player3";
    player[3] = new PRobotSimple(oss.str(), 3, dice);


    // CONNECT the GAME with "me" and with the "players"
    game->setBoardPlayers(this, player);

    // Connect the Players with its Pawns
    player[0]->setPawns(this->yPawn);
    player[1]->setPawns(this->bPawn);
    player[2]->setPawns(this->rPawn);
    player[3]->setPawns(this->gPawn);
}

//---------------------------------------------------------------------------

/**
 * Create the Pawn Paths, meaning the path a Pawn can walk through
 */
void PBoard::initVPaths()
{
    int i, num;

    // Create the Pawn Paths, meaning the path a Pawn can walk through.
    vPathYellow.push_back(space[indexHomeSpaceByColor[PBoard::getYellow()]]);
    vPathBlue.push_back(space[indexHomeSpaceByColor[PBoard::getBlue()]]);
    vPathRed.push_back(space[indexHomeSpaceByColor[PBoard::getRed()]]);
    vPathGreen.push_back(space[indexHomeSpaceByColor[PBoard::getGreen()]]);

    for (int color = 0; color < 4; color++)
    {


        for (i = indexStartSpaceByColor[color];
             i <= indexFinalSpaceByColor[color];
             i++)
        {
            if (color == PBoard::getYellow())
                vPathYellow.push_back(space[i]);
            if (color == PBoard::getBlue())
                vPathBlue.push_back(space[i]);
            if (color == PBoard::getRed())
                vPathRed.push_back(space[i]);
            if (color == PBoard::getGreen())
                vPathGreen.push_back(space[i]);
            if (i == 67 && color != PBoard::getYellow())
                i = -1;
            if (i == indexRampSafeSpaceByColor[color])
            {
                i = indexRampFirstSpaceByColor[color] - 1;
            }
        }
    }

    // Create the vPathAnalysis path. This path will contain simply the 1-68 spaces
    // and will be used by the calcBehind() method
    for (i = 0, num = 1; i < 68; i++, num++)
    {
        vPathAnalysis.push_back(space[i]);
    }
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Public Methods
#pragma mark-- Constructor/Destructor

/**
 * Constructor of PBoard
 *
 * Constructor of the PBoard with the option to assign a name to it
 *
 * @param new_name The name you want to assign to this instance. It's used
 *                 only thorugh PDebug to show debug messages
 */
PBoard::PBoard(std::string new_name)
{
    setName(new_name);
    initAttributes();
}

//---------------------------------------------------------------------------

/**
 * Destructor of PBoard
 */
PBoard::~PBoard()
{
    int i;

    dbg.print(4, "|                  PBoard DESTRUCTOR                     |");
    for (i = 0; i < PBoard::numPlayers(); i++)
    {
        delete player[i];
    }
    delete player;
    delete dice;
    delete lastPawnMoved;
    for (i = 0; i < PBoard::pawnsPerPlayer(); i++)
    {
        delete yPawn[i];
        delete bPawn[i];
        delete rPawn[i];
        delete gPawn[i];
    }
    delete yPawn;
    delete bPawn;
    delete rPawn;
    delete gPawn;
    for (i = 0; i < PBoard::numSpaces(); i++)
    {
        delete space[i];
    }
    delete space;
    delete game;
}

//---------------------------------------------------------------------------

/**
 * Change or Set the name of this instance.
 * @param new_var the new value of name
 */
void PBoard::setName(std::string new_var)
{
    name.assign(new_var);
}

//---------------------------------------------------------------------------


#pragma mark-- Class Methods (static Public Methods)

//---------------------------------------------------------------------------

/** Class method: returns NOCOLOR
 */
int PBoard::getNoColor()
{
    return NOCOLOR;
}

//---------------------------------------------------------------------------

/** Class method: returns Yellow color id (int)
 */
int PBoard::getYellow()
{
    return YELLOW;
}

//---------------------------------------------------------------------------

/** Class method: returns Yellow color id (int)
 */
int PBoard::getBlue()
{
    return BLUE;
}

//---------------------------------------------------------------------------

/** Class method: returns Yellow color id (int)
 */
int PBoard::getRed()
{
    return RED;
}

//---------------------------------------------------------------------------

/** Class method: returns Yellow color id (int)
 */
int PBoard::getGreen()
{
    return GREEN;
}

//---------------------------------------------------------------------------

/** Class method: returns allowed number of players
 */
int PBoard::numPlayers()
{
    return NUMPLAYERS;
}

//---------------------------------------------------------------------------

/** Class method: returns total number of spaces in the board
 */
int PBoard::numSpaces()
{
    return TOTALNUMSPACES;
}

//---------------------------------------------------------------------------

/** Class method: returns how many pawns are available per player (typically 4)
 */
int PBoard::pawnsPerPlayer()
{
    return NUMPAWNSPERPLAYER;
}

//---------------------------------------------------------------------------

/** Class method: returns the total number of pawns in the board (players*pawnsperplayer)
 */
int PBoard::numPawns()
{
    return (NUMPLAYERS * NUMPAWNSPERPLAYER);
}

//---------------------------------------------------------------------------

/** Class method: returns the value assigned to a Normal Space
 */
int PBoard::spaceTypeNormal()
{
    return SPACE_NORMAL;
}

//---------------------------------------------------------------------------

/** Class method: returns the value assigned to a Safe Space
 */
int PBoard::spaceTypeSafe()
{
    return SPACE_SAFE;
}

//---------------------------------------------------------------------------

/** Class method: returns the value assigned to a Ramp Space
 */
int PBoard::spaceTypeRamp()
{
    return SPACE_RAMP;
}

//---------------------------------------------------------------------------

/** Class method: returns the value assigned to a Final Space
 */
int PBoard::spaceTypeFinal()
{
    return SPACE_FINAL;
}

//---------------------------------------------------------------------------

/** Class method: returns the value assigned to a Home Space
 */
int PBoard::spaceTypeHome()
{
    return SPACE_HOME;
}

//---------------------------------------------------------------------------

/** Class method: returns the value assigned to a Start Space
 */
int PBoard::spaceTypeStart()
{
    return SPACE_START;
}

//---------------------------------------------------------------------------

/** Class method: returns the value assigned to a RampSafe Space
 */
int PBoard::spaceTypeRampSafe()
{
    return SPACE_RAMPSAFE;
}

//---------------------------------------------------------------------------

/** Class method: returns the value assigned to identify the first Quadrant Q1
 * @return the int value assigned to Q1
 */
int PBoard::Q1()
{
    return QUADRANT1;
}

//---------------------------------------------------------------------------

/** Class method: returns the value assigned to identify the second Quadrant Q2
 * @return the int value assigned to Q2
 */
int PBoard::Q2()
{
    return QUADRANT2;
}

//---------------------------------------------------------------------------

/** Class method: returns the value assigned to identify the third Quadrant Q3
 * @return the int value assigned to Q3
 */
int PBoard::Q3()
{
    return QUADRANT3;
}

//---------------------------------------------------------------------------

/** Class method: returns the value assigned to identify the fourth Quadrant Q4
 * @return the int value assigned to Q4
 */
int PBoard::Q4()
{
    return QUADRANT4;
}

//---------------------------------------------------------------------------


#pragma mark-- Public methods: Access to objects and indexes

//---------------------------------------------------------------------------

/** Returns the pointer to the Game happening on this Board
 * @return the PGame* pointer to the game happening in this board
 */
PGame *PBoard::getGame()
{
    return game;
}

//---------------------------------------------------------------------------

/** Returns pointer to a specific Yellow PPawn
 * @param new_index identifies which PPawn inside of the array.
 * @return the PPawn* pointer to one specific PPawn in the array of yellow pawns
 */
PPawn *PBoard::getYellowPawn(int new_index)
{
    return yPawn[new_index];
}

//---------------------------------------------------------------------------

/** Returns pointer to a specific Blue PPawn
 * @param new_index identifies which PPawn inside of the array.
 * @return the PPawn* pointer to one specific PPawn in the array of blue pawns
 */
PPawn *PBoard::getBluePawn(int new_index)
{
    return bPawn[new_index];
}

//---------------------------------------------------------------------------

/** Returns pointer to a specific Red PPawn
 * @param new_index identifies which PPawn inside of the array.
 * @return the PPawn* pointer to one specific PPawn in the array of red pawns
 */
PPawn *PBoard::getRedPawn(int new_index)
{
    return rPawn[new_index];
}

//---------------------------------------------------------------------------

/** Returns pointer to a specific Red PPawn
 * @param new_index identifies which PPawn inside of the array.
 * @return the PPawn* pointer to one specific PPawn in the array of green pawns
 */
PPawn *PBoard::getGreenPawn(int new_index)
{
    return gPawn[new_index];
}

//---------------------------------------------------------------------------

/** Returns pointer to a specific PPawn inside the whole vPawns array
 * @param new_index identifies which PPawn inside of the array.
 * @return the PPawn* pointer to one specific PPawn of the board
 */
PPawn *PBoard::getPawn(int new_index)
{
    return vPawns[new_index];
}

//---------------------------------------------------------------------------

/** Return the PSpace** pointer of pointers to the whole Spaces in the board
 * @return the PSpace** pointer to all the spaces in the board
 */
PSpace **PBoard::getSpaces()
{
    return space;
}

//---------------------------------------------------------------------------

/** Return the PSpace** pointer of pointers to all the Players in the board
 * @return the PPlayer** pointer to all the players
 */
PPlayer **PBoard::getPlayers()
{
    return player;
}


/** Returns the pointer to the Dice of the board
 * @return the PDice* pointer to the dice being used in the board
 */
PDice *PBoard::getDice()
{
    return dice;
}

//---------------------------------------------------------------------------

/** Return the vector PPawn pointer to the whole list of pawns
 * @return the std::vector<PPawn *> pointer to the vector that holds all running pawns in the board
 */
std::vector<PPawn *> PBoard::getVPawns()
{
    return vPawns;
}


/**
 * Save the last Pawn that was moved in the Board.
 *
 * Will store this its in a array of 4 pawns, one for each
 * specific color. Later getLasPawnMoved(color) can be used by the Game
 * to decide which pawn to send HOME due to 3 sixes :-)
 *
 * @param new_var the pointer to the Pawn
 */
void PBoard::setLastPawnMoved(PPawn *new_var)
{
    if (new_var != (PPawn *)NULL)
    {
        this->lastPawnMoved[new_var->getColor()] = new_var;
    }
    else
    {
        dbg.print(1, "*** WARNING ***: setLastPawnMoved called with ( NULL )");
    }
}

/**
 * Get the last Pawn moved in the Board of a specific color.
 *
 * This information can be used by the Game to decide which pawn to
 * send HOME due to 3 sixes :-)
 *
 * @param new_color
 * @return the PPawn* pointer to the last Pawn moved for that color.
 */
PPawn *PBoard::getLastPawnMoved(int new_color)
{
    if (lastPawnMoved[new_color] == (PPawn *)NULL)
    {
        dbg.print(1, "*** WARNING ***: getLastPawnMoved() is returning NULL");
    }
    return lastPawnMoved[new_color];
}

//---------------------------------------------------------------------------


#pragma mark-- More public methods

//---------------------------------------------------------------------------

/**
 * Get the name of this board.
 * @return the value of name
 */
std::string PBoard::getName()
{
    return name;
}

//---------------------------------------------------------------------------

/**
 * Connect the game with the players, and the players with the pawns
 *
 * By passing the "PPlayers **" pointer to my PGame instance. At the same time
 * I tell each of these players which are their PPawns, by passing
 * each of them the pointer to pointer to its array of pawns
 *
 * @param new_player is the pointer to the array of players playing on this Board
 */
void PBoard::setPlayers(PPlayer **new_player)
{
    // CONNECT the GAME with PLAYERS
    game->setBoardPlayers(this, new_player);

    // Connect the Players with its Pawns
    new_player[0]->setPawns(this->yPawn);
    new_player[1]->setPawns(this->bPawn);
    new_player[2]->setPawns(this->rPawn);
    new_player[3]->setPawns(this->gPawn);
}

//---------------------------------------------------------------------------

/**
 * Method to call when a new game is started from the Game class.
 *
 * When a new game is started from the PGame instance, this method should
 * be called for the PBoard. Here I reset anything I need and also call
 * the same method on the Pawns and Spaces.
 */
void PBoard::newGame()
{
    dbg.print(2, "| PBoard::newGame()                                      |");

    int i;

    // Notify all Pawns that we are starting a new Game, go back Home...
    for (unsigned int x = 0; x < this->vPawns.size(); x++)
    {
        vPawns[x]->newGame();

        // Move to my Home
        //vPawns[x]->setSpace(this->getSpaceByIndex(this->getIndexHomeSpaceByColor(vPawns[x]->getColor())));
        this->movePawnToSpace(vPawns[x], this->getHomeSpaceOfPawn(vPawns[x]));
    }

    // Move two Pawns to START, if this option is set when starting a new game
    //    if ( game->isFlagStartTwoOut() ) {
    if (game->isOptionStartTwoOut())
    {
        dbg.print(2,
                  "+--------------------------------------------------------+");
        dbg.print(2,
                  "| game->isFlagStartTwoOut()=TRUE.  Start with 2 out      |");
        dbg.print(2,
                  "+--------------------------------------------------------+");
        /*
        (void) vPawns[0]->setSpace(this->getSpaceByIndex(this->getIndexStartSpaceByColor(vPawns[0]->getColor())));
        (void) vPawns[1]->setSpace(this->getSpaceByIndex(this->getIndexStartSpaceByColor(vPawns[1]->getColor())));
        (void) vPawns[4]->setSpace(this->getSpaceByIndex(this->getIndexStartSpaceByColor(vPawns[4]->getColor())));
        (void) vPawns[5]->setSpace(this->getSpaceByIndex(this->getIndexStartSpaceByColor(vPawns[5]->getColor())));
        (void) vPawns[8]->setSpace(this->getSpaceByIndex(this->getIndexStartSpaceByColor(vPawns[8]->getColor())));
        (void) vPawns[9]->setSpace(this->getSpaceByIndex(this->getIndexStartSpaceByColor(vPawns[9]->getColor())));
        (void) vPawns[12]->setSpace(this->getSpaceByIndex(this->getIndexStartSpaceByColor(vPawns[12]->getColor())));
        (void) vPawns[13]->setSpace(this->getSpaceByIndex(this->getIndexStartSpaceByColor(vPawns[13]->getColor())));
*/

        this->movePawnToSpace(vPawns[0], this->getStartSpaceOfPawn(vPawns[0]));
        this->movePawnToSpace(vPawns[1], this->getStartSpaceOfPawn(vPawns[1]));
        this->movePawnToSpace(vPawns[4], this->getStartSpaceOfPawn(vPawns[4]));
        this->movePawnToSpace(vPawns[5], this->getStartSpaceOfPawn(vPawns[5]));
        this->movePawnToSpace(vPawns[8], this->getStartSpaceOfPawn(vPawns[8]));
        this->movePawnToSpace(vPawns[9], this->getStartSpaceOfPawn(vPawns[9]));
        this->movePawnToSpace(vPawns[12],
                              this->getStartSpaceOfPawn(vPawns[12]));
        this->movePawnToSpace(vPawns[13],
                              this->getStartSpaceOfPawn(vPawns[13]));
    }
    else
    {
        dbg.print(2,
                  "+--------------------------------------------------------+");
        dbg.print(2,
                  "| game->isFlagStartTwoOut()=FALSE                        |");
        dbg.print(2,
                  "+--------------------------------------------------------+");
    }

    // Place the dice in the first HOME
    moveDiceToSpace(
        dice,
        this->getSpaceByIndex(this->getIndexHomeSpaceByColor(YELLOW)));

    // Notify all Spaces that we are starting a new Game.
    for (i = 0; i < PBoard::numSpaces(); i++)
    {
        space[i]->newGame();
    }
}


//---------------------------------------------------------------------------

/**
 * Get the Space pointer to the Space which number is new_num
 * @param new_num number of the space I'm looking for its pointer
 * @return PSpace * pointer to the space which number is passed
 */
PSpace *PBoard::getSpaceByNum(int new_num)
{
    if (new_num > 0 && new_num <= PBoard::numSpaces())
        return space[new_num - 1];

    return (PSpace *)NULL;
}

//---------------------------------------------------------------------------

/**
 * Get the Space pointer to the Space which index is new_index
 * @param new_index is the position in the array of spaces
 * @return PSpace * pointer to the space which the index I'm passed
 */
PSpace *PBoard::getSpaceByIndex(int new_index)
{
    if (new_index >= 0 && new_index < PBoard::numSpaces())
        return space[new_index];

    return (PSpace *)NULL;
}

//---------------------------------------------------------------------------

/**
 * Change editable state, true allows to edit the Board.
 * @param new_var true/false
 */
void PBoard::setEditable(bool new_var)
{
    bEditable = new_var;
}

//---------------------------------------------------------------------------

/**
 *
 * @return bool true if allowed to edit the Board.
 */
bool PBoard::isEditable()
{
    if (bEditable)
        return true;
    return false;
}

//---------------------------------------------------------------------------

/**
 * Get the color name of a given color
 * @param new_var the id of the color
 * @return const char* pointer to the name of the color
 */
const char *PBoard::getColorName(int new_var)
{
    return colorName[new_var];
}

//---------------------------------------------------------------------------

/**
 * Get the total number of Pawns in the board
 * @return the value of numPawns x numPlayers
 */
int PBoard::getNumTotalPawns()
{
    return (PBoard::pawnsPerPlayer() * PBoard::numPlayers());
}

//---------------------------------------------------------------------------

/**
 * Return the "index" associated to the Home spaces. Value inside P_INDEXHOMESPACEBYCOLOR
 *
 * @return int "index" inside the "space" object where this color has its Home
 */
int PBoard::getIndexHomeSpaceByColor(int new_color)
{
    return indexHomeSpaceByColor[new_color];
}

//---------------------------------------------------------------------------

/**
 * Return the "index" associated to the Start spaces. Value inside P_INDEXSTARTSPACEBYCOLOR
 *
 * @return int "index" inside the "space" object where this color has its Start
 */
int PBoard::getIndexStartSpaceByColor(int new_color)
{
    return indexStartSpaceByColor[new_color];
}

//---------------------------------------------------------------------------

/**
 * Return the "index" associated to the RampSafe spaces. Value inside P_INDEXRAMPSAFESPACEBYCOLOR
 *
 * @return int "index" inside the "space" object where this color has its RampSafe
 */
int PBoard::getIndexRampSafeSpaceByColor(int new_color)
{
    return indexRampSafeSpaceByColor[new_color];
}

//---------------------------------------------------------------------------

/**
 * Return the "index" associated to the RampFirst spaces. Value inside P_INDEXRAMPFIRSTSPACEBYCOLOR
 *
 * @return int "index" inside the "space" object where this color has its RampFirst
 */
int PBoard::getIndexFirstRampSpaceByColor(int new_color)
{
    return indexRampFirstSpaceByColor[new_color];
}

//---------------------------------------------------------------------------

/**
 * Return the "index" associated to the Final spaces. Value inside P_INDEXFINALSPACEBYCOLOR
 *
 * @return int "index" inside the "space" object where this color has its Final
 */
int PBoard::getIndexFinalSpaceByColor(int new_color)
{
    return indexFinalSpaceByColor[new_color];
}

//---------------------------------------------------------------------------

/**
 * Return the pointer to the HOME space of a given pawn
 *
 * @param new_pawn is the PPawn* pointer to the pawn
 * @return the PSpace* pointer to the HOME PSpace of a given PPawn
 */
PSpace *PBoard::getHomeSpaceOfPawn(PPawn *new_pawn)
{
    return (this->getSpaceByIndex(
        this->getIndexHomeSpaceByColor(new_pawn->getColor())));
}

//---------------------------------------------------------------------------

/**
 * Return the pointer to the START space of a given pawn
 *
 * @param new_pawn is the PPawn* pointer to the pawn
 * @return the PSpace* pointer to the START PSpace of a given PPawn
 */
PSpace *PBoard::getStartSpaceOfPawn(PPawn *new_pawn)
{
    return (this->getSpaceByIndex(
        this->getIndexStartSpaceByColor(new_pawn->getColor())));
}


//---------------------------------------------------------------------------

/**
 * Moves the pawn to the space, returns success (true) or fail (false)


 |   Space101, position 3: pYellow4                       |
 | STAT 1: Waiting for player to Roll the dice            |

 *
 * @param the_pawn is the PPawn* pointer to the pawn to move
 * @param new_space is the PSpace* pointer to the destination space
 * @return true if success or false if failed
 */
bool PBoard::movePawnToSpace(PPawn *the_pawn, PSpace *new_space)
{

    // Return value
    bool allowed = false;

    dbg.printF(3,
               "|    Moving %-8s to %-8s                         |",
               the_pawn->getName().c_str(),
               new_space->getName().c_str());

    if (new_space != (PSpace *)NULL)
    {

        // Get current space
        PSpace *my_oldspace = the_pawn->getSpace();

        // Print Debug information about the movement
        if (my_oldspace != (PSpace *)NULL)
        {
            dbg.printF(3,
                       "|     MOVING %-8s from %-8s to %-8s          |",
                       the_pawn->getName().c_str(),
                       my_oldspace->getName().c_str(),
                       new_space->getName().c_str());
        }
        else
        {
            dbg.printF(3,
                       "|     PLACING %-8s from NULL to %-8s             |",
                       the_pawn->getName().c_str(),
                       new_space->getName().c_str());
        }
        // I Ask the Space to add myself
        if (new_space->addPawn(the_pawn))
        {

            // Change my space pointer
            the_pawn->setSpace(new_space);
            allowed = true;

            // Remove myself from my old space
            if (my_oldspace != (PSpace *)NULL)
            {
                dbg.printF(3,
                           "|  DELETING %-8s from %-8s                       |",
                           the_pawn->getName().c_str(),
                           my_oldspace->getName().c_str());
                my_oldspace->delPawn(the_pawn);
            }
        }
        else
        {
            allowed = false;
            dbg.printF(3,
                       "|  %-8s can't add myself to %-8s                 |  * "
                       "WARNING !!",
                       the_pawn->getName().c_str(),
                       new_space->getName().c_str());
        }
    }
    else
    {
        allowed = false;
        dbg.printF(
            3,
            "|  %-8s can't add myself to NULL Space         |  * WARNING !!",
            the_pawn->getName().c_str());
    }

    return allowed;
}


//---------------------------------------------------------------------------

/**
 * Moves the dice to a space
 *
 *  This method has no impact in the game, it's just moving the dice from the
 *  HOME of one color to the next, etc. Why? well, it's useful for simple
 *  screen/graphics placement of the dice based on which space they are in
 *  and maybe for future implementations...
 *
 * @param the_dice is the PDice* pointer to the dice to move
 * @param new_space is the PSpace* pointer to the destination space
 * @return true if success or false if failed
 */

bool PBoard::moveDiceToSpace(PDice *the_dice, PSpace *new_space)
{

    // Return value
    bool allowed = false;

    if (new_space != (PSpace *)NULL)
    {

        // Get current space
        PSpace *my_oldspace = the_dice->getSpace();

        // Print Debug information about the movement
        if (my_oldspace != (PSpace *)NULL)
        {
            dbg.printF(3,
                       "|     MOVING %-8s from %-8s to %-8s          |",
                       the_dice->getName().c_str(),
                       my_oldspace->getName().c_str(),
                       new_space->getName().c_str());
        }
        else
        {
            dbg.printF(3,
                       "|     PLACING %-8s from NULL to %-8s             |",
                       the_dice->getName().c_str(),
                       new_space->getName().c_str());
        }

        // I Ask the Space to add the Dice
        if (new_space->addDice(the_dice))
        {
            allowed = true;

            // Remove myself from my old space
            if (my_oldspace != (PSpace *)NULL)
            {
                dbg.printF(3,
                           "|  DELETED %-8s from %-8s                        |",
                           the_dice->getName().c_str(),
                           my_oldspace->getName().c_str());
                my_oldspace->setDice(NULL);
            }
        }
        else
        {
            allowed = false;
            dbg.printF(3,
                       "|  %-8s can't be added to %-8s                   |  * "
                       "WARNING !!",
                       the_dice->getName().c_str(),
                       new_space->getName().c_str());
        }
    }
    else
    {
        allowed = false;
        dbg.printF(
            3,
            "|  %-8s can't be added to NULL Space         |  * WARNING !!",
            the_dice->getName().c_str());
    }

    return allowed;
}

//---------------------------------------------------------------------------

/**
 * Returns what position ocupies a given space inside the path of a color.
 *
 * Find's the passed "Space" in the color's Path. For example,
 * If the space number is "22" and the color is "Blue", then it will return
 * that the position of the space 22 is "0" in the Blue's Path.
 *
 * This method together with getPathVector allow the caller to go through
 * a color's path spaces starting from an arbitrary space, which allows
 * to develop methods which analyse what's in front of a pawn, either
 * for rule processing or robot inteligence.
 *
 * @return int index, the index inside the vector<Space *> * where the
 * new_space is located inside the path's vector of the color new_color.
 *
 * NOTE: What are the Pawn's Paths?. See getPathVector.
 *
 */
int PBoard::getPathIndex(PSpace *new_space, int new_color)
{
    int ret = -1;
    std::vector<PSpace *> *v;
    v = getPathVector(new_color);

    for (unsigned int i = 0; i < v->size(); i++)
    {
        if ((*v)[i] == new_space)
        {
            ret = i;
            break;
        }
    }

    return ret;
}

//---------------------------------------------------------------------------

/**
 * getPathVector()
 *
 * getPathVector returns the pointer of the vector of Spaces for a given color.
 * With this information the calling method can walk through the path of the color.
 *
 * Let's see an example for blue pawns. The blue pawn path starts in the
 * space 22, goes all the way to space 68, then continue on 1 until its
 * safe 17, where it enters its final ramp (77-84). In the Board class
 * I've defined 4 path's (using vectors), one per each color.
 *
 * @return vector<Space *> *  pointer to the vector. The calling method can
 * use this pointer as in the following example:
 *
 *  @par Sample usage:
 *  @code
 *
 *   :
 *  vector<Space *> *v;
 *   v = getPathVector ( new_color );
 *
 *   for ( unsigned int i=0; i<v->size(); i++ ) {
 *       if ( (*v)[i] == new_space ) {
 *       :
 *
 *  @endcode
 *
 */
std::vector<PSpace *> *PBoard::getPathVector(int new_color)
{
    if (new_color == PBoard::getYellow())
    {
        return &vPathYellow;
    }
    if (new_color == PBoard::getBlue())
    {
        return &vPathBlue;
    }
    if (new_color == PBoard::getRed())
    {
        return &vPathRed;
    }
    return &vPathGreen;
}

//---------------------------------------------------------------------------

/**
 * Returns a pointer to a vector of all the Spaces from 1 to 68
 * With this information the calling method can analyse Behind and Ahead
 * for snapshot analysis
 *
 * @return vector<Space *> *  pointer to the vector.
 */
std::vector<PSpace *> *PBoard::getPathAnalysis()
{
    return &vPathAnalysis;
}

//---------------------------------------------------------------------------

/**
 * Change one of the player to a new Type. This method will create a new
 * player of the new type and then copy all the attributes from the old
 * one to the new player.
 *
 * @param old_player is the pointer to the player to change
 * @param new_type is the type of the new player being created
 */
void PBoard::changePlayerType(PPlayer *old_player, int new_type)
{
    bool found = false;
    int i;

    // If the type is the same, then do nothing
    if (old_player->getType() == new_type)
        return;

    dbg.print(3, "--");
    oss.str("");
    oss << "Change player " << old_player->getName()
        << " to NEW type: " << new_type;
    dbg.print(2, oss.str());

    // Find the index of the player being changed
    for (i = 0; i < PBoard::numPlayers(); i++)
    {
        if (player[i] == old_player)
        {
            found = true;
            break;
        }
    }

    // Based on new player type, create the new object
    if (found)
    {
        if (new_type == PPlayer::getNumTypeHuman())
        {
            oss.str("");
            oss << "Changing player " << player[i]->getName()
                << " to type HUMAN";
            dbg.print(2, oss.str());

            // Create the new Player
            PHuman *new_player;
            new_player = new PHuman();

            // Copy the attributes
            PPlayer::copyPlayer(old_player, new_player);

            // Debug purposes
            oss.str("");
            oss << "Source,      type: " << old_player->getStringPlayerType()
                << ". Name: " << old_player->getName();
            dbg.print(2, oss.str());
            oss.str("");
            oss << "Destination, type: " << new_player->getStringPlayerType()
                << ". Name: " << new_player->getName();
            dbg.print(2, oss.str());

            // Assign the new player to the array of players
            player[i] = new_player;

            // Free the old player
            delete old_player;
        }
        else if (new_type == PPlayer::getNumTypeSimple())
        {
            oss.str("");
            oss << "Changing player " << player[i]->getName()
                << "to type Robot SIMPLE";
            dbg.print(2, oss.str());

            // Create the new Player
            PRobotSimple *new_player;
            new_player = new PRobotSimple();

            // Copy the attributes
            PPlayer::copyPlayer(old_player, new_player);

            // Debug purposes
            oss.str("");
            oss << "Source,      type: " << old_player->getStringPlayerType()
                << ". Name: " << old_player->getName();
            dbg.print(2, oss.str());
            oss.str("");
            oss << "Destination, type: " << new_player->getStringPlayerType()
                << ". Name: " << new_player->getName();
            dbg.print(2, oss.str());

            // Assign the new player to the array of players
            player[i] = new_player;

            // Free the old player
            delete old_player;
        }
        else if (new_type == PPlayer::getNumTypeSmart())
        {
            oss.str("");
            oss << "Changing player " << player[i]->getName()
                << "to type Robot SSMART";
            dbg.print(2, oss.str());

            // Create the new Player
            PRobotSmart *new_player;
            new_player = new PRobotSmart();

            // Copy the attributes
            PPlayer::copyPlayer(old_player, new_player);

            // Debug purposes
            oss.str("");
            oss << "Source,      type: " << old_player->getStringPlayerType()
                << ". Name: " << old_player->getName();
            dbg.print(2, oss.str());
            oss.str("");
            oss << "Destination, type: " << new_player->getStringPlayerType()
                << ". Name: " << new_player->getName();
            dbg.print(2, oss.str());

            // Assign the new player to the array of players
            player[i] = new_player;

            // Free the old player
            delete old_player;
        }
    }
}

//---------------------------------------------------------------------------


#pragma mark-- Handle Memento's

//---------------------------------------------------------------------------

/**
 * Creates a memento, which saves current Parchis state
 *
 * Memento's description:
 *
 * Stores/Restores internal state of this object, it's based on the
 * Memento design patter. A memento is an object that stores a snapshot of
 * the internal state of another object. It can be leveraged to support multi-level undo.
 *
 * Originator   Board.class  (THIS CLASS)
 *    Creates the memento object:    createMemento()
 *    or goes to a specific memento  setMemento()
 *
 * See also:
 * Memento      BoardMemento.class (Does the real Stores/Restores of the attributes that I want to store/restore)
 * CareTaker    Game.cpp           (Calls me to createMemento/setMemento to control the undo/redo's)
 *
 *
 */
PBoardMemento *PBoard::createMemento(int new_index)
{

    // Save actual state, creates a memento and returns its pointer
    return new PBoardMemento(new_index,
                             this,
                             game,
                             player,
                             yPawn,
                             bPawn,
                             rPawn,
                             gPawn,
                             vPawns,
                             space,
                             lastPawnMoved);
    //    vPathYellow,
    //    vPathBlue,
    //    vPathRed,
    //    vPathGreen,
}

//---------------------------------------------------------------------------

/**
 * Restores to a previous states
 *
 * @param m is the pointer to the Playermemento to restore to.
 */
void PBoard::setMemento(PBoardMemento *m)
{

    // For loops
    int i;


    // RESTORE the status
    ///////////////////////////////////////////

    // RESTORE GAME status
    PGame *new_game = m->getGame();
    game->setTurn(new_game->getTurn());
    game->setNumRound(new_game->getNumRound());
    game->setNumSixes(new_game->getNumSixes());


    // RESTORE PLAYERs
    PPlayer **new_player = m->getPlayers();
    if (player[0] != new_player[0])
    {
        oss.str("");
        oss << "|  Deleting old players !!!!!!!!!!!!!";
        dbg.print(4, oss.str());
        // Destroy the old players
        for (i = 0; i < PBoard::numPlayers(); i++)
        {
            delete player[i];
        }
    }
    // Assign the new players
    for (i = 0; i < PBoard::numPlayers(); i++)
    {
        player[i] = new_player[i];
    }


    // RESTORE PAWNs & vPAWNs
    if (yPawn[0] != m->getYPawn()[0])
    {
        oss.str("");
        oss << "|  Deleting yPawn, bPawn, rPawn, gPawn !!!!!!!!!!!!!";
        dbg.print(4, oss.str());
        for (i = 0; i < PBoard::pawnsPerPlayer(); i++)
        {
            delete yPawn[i];
            delete bPawn[i];
            delete rPawn[i];
            delete gPawn[i];
        }
    }
    // Restore Pawns and vPawns
    PPawn **new_yPawn = m->getYPawn();
    PPawn **new_bPawn = m->getBPawn();
    PPawn **new_rPawn = m->getRPawn();
    PPawn **new_gPawn = m->getGPawn();
    for (i = 0; i < PBoard::pawnsPerPlayer(); i++)
    {
        yPawn[i] = new_yPawn[i];
    }
    for (i = 0; i < PBoard::pawnsPerPlayer(); i++)
    {
        bPawn[i] = new_bPawn[i];
    }
    for (i = 0; i < PBoard::pawnsPerPlayer(); i++)
    {
        rPawn[i] = new_rPawn[i];
    }
    for (i = 0; i < PBoard::pawnsPerPlayer(); i++)
    {
        gPawn[i] = new_gPawn[i];
    }


    // Reassign the vPawns
    vPawns.clear();
    for (i = 0; i < PBoard::pawnsPerPlayer(); i++)
    {
        vPawns.push_back(yPawn[i]);
    }
    for (i = 0; i < PBoard::pawnsPerPlayer(); i++)
    {
        vPawns.push_back(bPawn[i]);
    }
    for (i = 0; i < PBoard::pawnsPerPlayer(); i++)
    {
        vPawns.push_back(rPawn[i]);
    }
    for (i = 0; i < PBoard::pawnsPerPlayer(); i++)
    {
        vPawns.push_back(gPawn[i]);
    }

    // RESTORE SPACEs
    PSpace **new_space = m->getSpaces();
    if (space[0] != new_space[0])
    {
        oss.str("");
        oss << "|  Deleting old spaces !!!!!!!!!!!!!";
        dbg.print(4, oss.str());
        // DELETE SPACEs: Destroy the old spaces
        for (i = 0; i < PBoard::numSpaces(); i++)
        {
            delete space[i];
        }
    }

    // Assign the spaces
    for (i = 0; i < PBoard::numSpaces(); i++)
    {
        space[i] = new_space[i];
    }


    // Reassign the vPath* pointers
    vPathYellow.clear();
    vPathBlue.clear();
    vPathRed.clear();
    vPathGreen.clear();
    vPathAnalysis.clear();
    this->initVPaths();


    // RESTORE lastPawnMoved
    PPawn **new_lastPawnMoved = m->getLastPawnMoved();
    for (i = 0; i < NUMPAWNSPERPLAYER; i++)
    {
        lastPawnMoved[i] = new_lastPawnMoved[i];
    }

    // RESTORE Board-> game connections
    // Make sure Game get's well connected to myself & players.
    // Under Game class note setBoardPlayers() method also set's the vPawns pointer
    game->setBoardPlayers(this, player);


    // Debugging purposes
    dbg.print(4, "");
    oss.str("");
    dbg.print(4, "+--------------------------------------------------------+");
    oss << "|  MEMENTO BACK FINISHED";
    dbg.print(4, oss.str());
    dbg.print(4, "+--------------------------------------------------------+");
    oss.str("");
    dbg.print(4, oss.str());
    dbg.print(4, "|--GAME--------------------------------------------------+");
    oss.str("");
    oss << "|  Turn     : " << getColorName(game->getTurn());
    dbg.print(4, oss.str());
    oss.str("");
    oss << "|  Round    : " << game->getNumRound();
    dbg.print(4, oss.str());

    dbg.print(4, "|--PLAYERS-----------------------------------------------+");
    for (i = 0; i < PBoard::numPlayers(); i++)
    {
        oss.str("");
        if (player[i] == (PPlayer *)NULL)
            oss << "|  player[" << i
                << "] = (NULL)   <========== WARNING !!!!!!!!!!!";
        else
            oss << "|  player[" << i << "] = " << player[i]->getName()
                << ". Type=" << player[i]->getStringPlayerType();
        dbg.print(4, oss.str());
    }
    dbg.print(4, "|--PAWNS ([?]Pawn----------------------------------------+");
    for (i = 0; i < PBoard::pawnsPerPlayer(); i++)
    {
        oss.str("");
        if (yPawn[i] == (PPawn *)NULL)
            oss << "|  yPawn[" << i
                << "] = (NULL)   <========== WARNING !!!!!!!!!!!";
        else
            oss << "|  yPawn[" << i << "] = " << yPawn[i]->getName() << " @ "
                << yPawn[i]->getSpace()->getName();
        dbg.print(4, oss.str());
        oss.str("");
        if (bPawn[i] == (PPawn *)NULL)
            oss << "|  bPawn[" << i
                << "] = (NULL)   <========== WARNING !!!!!!!!!!!";
        else
            oss << "|  bPawn[" << i << "] = " << bPawn[i]->getName() << " @ "
                << bPawn[i]->getSpace()->getName();
        dbg.print(4, oss.str());
        oss.str("");
        if (rPawn[i] == (PPawn *)NULL)
            oss << "|  rPawn[" << i
                << "] = (NULL)   <========== WARNING !!!!!!!!!!!";
        else
            oss << "|  rPawn[" << i << "] = " << rPawn[i]->getName() << " @ "
                << rPawn[i]->getSpace()->getName();
        dbg.print(4, oss.str());
        oss.str("");
        if (gPawn[i] == (PPawn *)NULL)
            oss << "|  gPawn[" << i
                << "] = (NULL)   <========== WARNING !!!!!!!!!!!";
        else
            oss << "|  gPawn[" << i << "] = " << gPawn[i]->getName() << " @ "
                << gPawn[i]->getSpace()->getName();
        dbg.print(4, oss.str());
    }
    dbg.print(4, "|--vPawns------------------------------------------------+");
    for (i = 0; i < PBoard::numPawns(); i++)
    {
        oss.str("");
        if (vPawns[i] == (PPawn *)NULL)
            oss << "|  vPawns[" << i
                << "] = (NULL)   <========== WARNING !!!!!!!!!!!";
        else
            oss << "|  vPawns[" << i << "] = " << vPawns[i]->getName() << " @ "
                << vPawns[i]->getSpace()->getName();
        dbg.print(4, oss.str());
    }
    dbg.print(4, "|--SPACES------------------------------------------------+");
    for (i = 0; i < PBoard::numSpaces(); i++)
    {
        oss.str("");
        if (space[i] == (PSpace *)NULL)
            oss << "|  space[" << i
                << "] = (NULL)   <========== WARNING !!!!!!!!!!!";
        else
        {
            oss << "|  space[" << i << "] = " << space[i]->getName() << ": ";
            for (int x = 0; x < space[i]->getNumPawns(); x++)
            {
                oss << space[i]->getPawn(x)->getName() << " ";
            }
        }
        dbg.print(4, oss.str());
    }

    dbg.print(4, "|--vPathYellow-------------------------------------------+");
    for (int x = 0; x < (int)vPathYellow.size(); x++)
    {
        oss.str("");
        if (vPathYellow[x] == (PSpace *)NULL)
            oss << "|  vPathYellow[" << x
                << "] = (NULL)   <========== WARNING !!!!!!!!!!!";
        else
        {
            oss << "|  vPathYellow[" << x
                << "] = " << vPathYellow[x]->getName();
        }
        dbg.print(4, oss.str());
    }
    dbg.print(4, "|--vPathBlue---------------------------------------------+");
    for (int x = 0; x < (int)vPathBlue.size(); x++)
    {
        oss.str("");
        if (vPathBlue[x] == (PSpace *)NULL)
            oss << "|  vPathBlue[" << x
                << "] = (NULL)   <========== WARNING !!!!!!!!!!!";
        else
        {
            oss << "|  vPathBlue[" << x << "] = " << vPathBlue[x]->getName();
        }
        dbg.print(4, oss.str());
    }
    dbg.print(4, "|--vPathRed----------------------------------------------+");
    for (int x = 0; x < (int)vPathRed.size(); x++)
    {
        oss.str("");
        if (vPathRed[x] == (PSpace *)NULL)
            oss << "|  vPathRed[" << x
                << "] = (NULL)   <========== WARNING !!!!!!!!!!!";
        else
        {
            oss << "|  vPathRed[" << x << "] = " << vPathRed[x]->getName();
        }
        dbg.print(4, oss.str());
    }
    dbg.print(4, "|--vPathGreen-------------------------------------------+");
    for (int x = 0; x < (int)vPathGreen.size(); x++)
    {
        oss.str("");
        if (vPathGreen[x] == (PSpace *)NULL)
            oss << "|  vPathGreen[" << x
                << "] = (NULL)   <========== WARNING !!!!!!!!!!!";
        else
        {
            oss << "|  vPathGreen[" << x << "] = " << vPathGreen[x]->getName();
        }
        dbg.print(4, oss.str());
    }


    dbg.print(4, "|--lastPawnMoved-----------------------------------------+");
    for (i = 0; i < NUMPAWNSPERPLAYER; i++)
    {
        oss.str("");
        if (lastPawnMoved[i] == (PPawn *)NULL)
            oss << "|  lastPawnMoved[" << i << "]: (NULL)";
        else
            oss << "|  lastPawnMoved[" << i
                << "]: " << lastPawnMoved[i]->getName();
        dbg.print(4, oss.str());
    }
    dbg.print(4, "+--------------------------------------------------------+");
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
