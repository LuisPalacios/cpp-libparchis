/**
 *  @class  PParchis PParchis.h "PParchis.h"
 *  @brief  Parchis Class: Declaration: Main class responsible for instantiating the board (PBoard).
 *
 *  Belongs to the Library: "Parchis Engine C++ library"
 *
 *  @author  Luis Palacios
 *  @version 0.1
 *  @date    03/Sep/09
 *
 *  @par Description of the Game:
 *
 *  "Parchís" game, also known as Pachisi, Parchisi, Parcheesi, Parchesi & Veinticinco,
 *
 *  Parcheesi is an American adaptation of the Indian Cross and Circle game Pachisi. Created in India
 *  around 500 BC, the game is often subtitled Royal Game of India because royalty supposedly played
 *  using costumed dancers as pieces on large outdoor boards (such a court is preserved at Fatehpur Sikri).
 *
 *  The game and its variants are known worldwide; for example, a similar game called Parchís
 *  is especially popular in Spain, and Parqués is a Colombian variant. A version is available in the
 *  United Kingdom under the name of Ludo.
 *
 *  This version of Parchís is based on the Spanish game, where it's played with 1 dice and 68 spaces
 *  around the board, twelve of which are darkened safe spaces where a piece (pawn) cannot be captured.
 *  The goal of the game is to move each of one's pieces home to the center space. Each player selects
 *  four pieces of the same color and places them in their "nest," or starting area. The game board
 *  should be positioned so that each player's nest is to their right.
 *
 *  Note: The following rules are the Parcheesi ones, not used in this implementation. I'll update it...
 *
 *  Pieces enter play onto the darkened space to the left of their nest and continue counter-clockwise
 *  around the board to the home path directly in front of the player. Each player rolls a die; the highest
 *  roller goes first, and subsequent play continues to the left. On each turn, players throw one or both
 *  dice and use the values shown to move their pieces around the board. If an amount on one or both of
 *  the dice cannot be moved, that amount is forfeited.
 *
 *  Any time a player rolls, he must use as much of the dice showing as possible. (i.e. If a player rolls
 *  4 and 5 and could move either 4 or 5, but not both, then he must move 5.)
 *
 *  Entering pawns
 *  Five has a special value in entering pieces out of the nest from where they begin the game.
 *  A player may enter a piece only by throwing a five or a total sum of five on the dice. Each time a five
 *  is tossed, the player must start another piece, if viable.
 *
 *  Capturing
 *  Any piece that is not on a safe space or a part of a blockade can be captured by an opposing pawn.
 *  A player is awarded 20 bonus spaces for capturing an opposing piece. The 20 spaces may not be divided
 *  between pieces and must be moved, if possible.
 *  Team Rules: If opposing team has two pawns on player's exit area, the player can not exit.
 *
 *  Blockades
 *  When two pieces occupy the same space, they prevent any pieces behind the two from advancing past the
 *  blockade. This includes blocking pieces from leaving their nest. Two pieces that form a blockade may
 *  not be moved forward together to form a new blockade on the same roll.
 *
 *  Safe spaces
 *  The dark spaces are safe spaces. A piece may not be captured as long as it sits on one of these spaces.
 *  The only exception is if a piece sits on the safe space where another player enters the board from her
 *  nest. Those spaces are safe from all other players, but the piece can be taken if the player whose nest
 *  it is has a piece in her nest and rolls a 5 (as long as it isn't a blockade).
 *  Two pieces that form a blockade are also safe.
 *
 *  Doublets (Two dice version)
 *  When a doublet (doubles) is tossed, the player gains another roll of the dice. In addition, if all that
 *  player’s pieces are outside the nest, the values on reverse side of dice are also used. For example, a
 *  player who rolls 6-6 can also move 1-1 in any combination. Therefore, when a doublet is tossed, the player
 *  has a total of fourteen spaces to move one or more pawns.
 *  If a player rolls doubles and cannot move the entire number of spaces, he/she cannot move any spaces,
 *  but still gets to roll again.
 *  The third consecutive doublet rolled in one turn is a penalty, and pieces are not moved the number of
 *  spaces shown on dice. A player with a three doublet penalty also removes his piece closest to home back
 *  to their nest, and his/her turn ends.
 *
 *  A player cannot split doubles in order to enter home. This means that a player can only enter home by
 *  rolling doubles if he is exactly 14 spaces from home.
 *
 *  Home
 *  The center home space can only be entered by exact throw of the die or dice. When a piece enters the
 *  center space by exact count, that player is awarded ten movement points that may be moved with any one
 *  piece still in play at the end of their turn. If the bonus movement amount cannot be used, it is forfeit.
 *  Each player has his own home path and may not enter another's. So, when a piece is on its home path,
 *  it can no longer be captured. Once a piece has been moved into her home path, it can no longer be moved
 *  except to move all the way to home.
 *
 *  Winning the game
 *  The first player to get all four pieces home wins, at which point the winner must yell "PARCHEESI!"
 *
 *
 *  @par Sample Code:
 *  @code
 *
 *  #import "PDebug.h"
 *  #import "PParchis.h"
 *
 *  // Instantiate the Parchis object
 *  PParchis* parchis= new PParchis ();
 *  :
 *  // Store the board
 *  board = parchis->getBoard();
 *  :
 *
 *  @endcode
 *
 *
 *  @par NOTES about this implementation:
 *  @verbatim
 - Player plays with 1 dice
 - There are 68 spaces
 - Pieces are called PAWNs
 - Nest is called HOME
 - Home is called FINAL
 - Blockades are called Barriers
 - Home path is called Ramp
 @endverbatim
 *
 *
 *  @par Color codes used with Blender and Gimp to build the sprites
 *  @verbatim
 R   G   B    H   S   V    HEX
 Yellow: 976 867 024  147 976 976  0xF9DD06
 Blue  : 024 131 976  648 976 976  0x0521F9
 Red   : 898 090 032  011 976 976  0xE51608
 Green : 033 915 084  343 964 915  0x08E915
 @endverbatim
 *
 *  @par Build deployment versions:
 *  @verbatim
  Mac OSX w/ QT Creator:
    Build for release
    copy Parchis.app from bin to temporary dir (i.e. distri)
    IconoGrapher, open Parchis.icns, save into Parchis.app
    macdeployqt Parchis.app -dmg
    otool -L Parchis.app/Contents/MacOS/Parchis
 @endverbatim
 *
 *  @par How to Insert SVN Revision Number in my Xcode project
 *  @verbatim

 1. In Xcode, add an empty header file to your project’s “Other Sources” group called “revision.h”.
 2. Add a “New Run Script Build Phase” to your target.
 3. When defining your build phase, use “/bin/sh” for the Shell value and enter the following script:
 REV=`svnversion -n`
 echo "#define kRevision @\"$REV\"" > ${PROJECT_DIR}/revision.h

 4. Ensure that the new build phase happens before your “Compile Sources” build phase.
 5. Build your app.

 That’s it! From now on you can use a string define called kRevision wherever
 you would like to reference your revision number at run-time.
 IMPORTANT: Do NOT add your revision.h file to your subversion repository.
 It will be generated automatically each time you build your app.
 @endverbatim
 *
 *  @par To Implement:
 *  @verbatim
 - El primero en salir es quien saca el dado más alto.
 - Envío animado avanzado de fichas a su casa: jugador de golf, de tenis, de baseball, baloncesto...
 @endverbatim
 *
 *  @par Review in the future:
 *  @verbatim
 - Hay un problema en "LINUX" con el gstreamer (backend the phonon)
 que provoca que ficheros de audio "cortos" no se reproduzcan enteros
 Fixed (workaround): Creando ficheros de un mínimo de 2 segundos
 - Los ficheros .mp3 no funcionan desde qtResources.qrc
 parece un problema de la 4.6, revisitar en el futuro.
 - En linux Actualizar widgets de mainwindow no funciona tras inicializar phonon
 - Analizar mensajes de DBUS al arrancar
 @endverbatim
 *
 *
 *  @bug
 *  0001: Undo/3x6 si tres ya en casa la ultima por entrar ¿? No recuerdo qué era esto... :-)
 *
 *  @bug
 *  0002: En Windows la animación (gif's) no funciona, solo cuando se mueve el ratón.
 *
 *  @bug
 *  0003: When human eats, the eater pawn is allways selected to move 20.
 *
 */

#ifndef PARCHIS_H
#define PARCHIS_H

//---------------------------------------------------------------------------

#pragma mark ====== INCLUDES

//---------------------------------------------------------------------------

// My includes, with these four I'm really including everything...
#include "PBoard.h"
#include "PDebug.h"
#include "PTime.h"
#include "PVersion.h"

// Standard includes
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

//---------------------------------------------------------------------------


#pragma mark ====== CLASS PParchis

//---------------------------------------------------------------------------

class PParchis
{

#pragma mark ====== PRIVATE INSTANCE MEMBERS
private:
    // DEBUGGING purposes

    PDebug dbg;             //!< To be able to send Log messages
    std::ostringstream oss; //!< Construct complex strings

    // PRIVATE ATTRIBUTES (For ivar's use comments for doxygen: //!<)

    bool bGameActive; //!< Indicates if (true/false) the game is active

#pragma mark ====== PRIVATE INSTANCE METHODS

    // PRIVATE METHODS: Set private attributes

    void initAttributes(); // Initialize the attributes


#pragma mark ====== PROTECTED ATTRIBUTES
protected:
    // PROTECTED ATTRIBUTES AND METHODS, USED BY DERIVED CLASSES

    PBoard *
        board; //!< Parchis instantiates the Board. The Board is responsible for instantiating the game


#pragma mark ====== PUBLIC INSTANCE METHODS
public:
    // CONSTRUCTORS/DESTRUCTOR

    PParchis();
    virtual ~PParchis();


    // STATIC PUBLIC METHODS


    // PUBLIC METHODS

    PBoard *getBoard(); // Return the pointer to the Board
};


//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#endif // PPARCHIS_H
