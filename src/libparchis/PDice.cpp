
/**
 *  @class  PDice PDice.cpp "PDice.cpp"
 *  @file   PDice.cpp
 *  @brief  Parchis Class definition: Represents the dice of the game
 *
 *  ---------------------------------------------------------------------------
 */


//---------------------------------------------------------------------------

#include "PDice.h"

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Macros to define the operating system

/*
   The operating system, must be one of:
     DARWIN   - Darwin OS (synonym for OS_MAC)
     WIN32    - Win32 (Windows 2000/XP/Vista/7 and Windows Server 2003/2008)
     LINUX    - Linux
     UNIX     - Any UNIX BSD/SYSV system
*/
#if defined(__APPLE__) &&                                                      \
    (defined(__GNUC__) || defined(__xlC__) || defined(__xlc__))
#define OS_DARWIN
#define OS_BSD4
#ifdef __LP64__
#define OS_DARWIN64
#else
#define OS_DARWIN32
#endif
#elif !defined(SAG_COM) &&                                                     \
    (defined(WIN64) || defined(_WIN64) || defined(__WIN64__))
#define OS_WIN32
#define OS_WIN64
#elif !defined(SAG_COM) && (defined(WIN32) || defined(_WIN32) ||               \
                            defined(__WIN32__) || defined(__NT__))
#if defined(WINCE) || defined(_WIN32_WCE)
#define OS_WINCE
#else
#define OS_WIN32
#endif
#elif defined(__MWERKS__) && defined(__INTEL__)
#define OS_WIN32
#elif defined(__linux__) || defined(__linux)
#define OS_LINUX
#elif defined(__MAKEDEPEND__)
#else
#error "Parchis does not support/detect this OS - talk to luis@luispa.com"
#endif

#if defined(OS_WIN32) || defined(OS_WIN64) || defined(OS_WINCE)
#define OS_WIN
#endif

#if defined(OS_DARWIN)
#define OS_MAC  /* Q_OS_MAC is mostly for compatibility, but also more clear */
#define OS_MACX /* Q_OS_MACX is only for compatibility.*/
#if defined(OS_DARWIN64)
#define OS_MAC64
#elif defined(OS_DARWIN32)
#define OS_MAC32
#endif
#endif

#if defined(OS_WIN)
#undef OS_UNIX
#elif !defined(OS_UNIX)
#define OS_UNIX
#endif

/*
   The window system, must be one of:

     WS_MACX     - Mac OS X
     WS_WIN      - Windows 32
     WS_WIN32    - Windows 32
     WS_WIN64    - Windows 64
     WS_X11      - X Window System
*/

#if defined(_WIN32_X11_)
#define WS_X11
#elif defined(OS_WIN32)
#define WS_WIN32
#define WS_WIN
#if defined(OS_WIN64)
#define WS_WIN64
#endif
#elif defined(OS_UNIX)
#if defined(OS_MAC) && !defined(__USE_WS_X11__)
#define WS_MAC
#define WS_MACX
#if defined(OS_MAC64)
#define WS_MAC64
#elif defined(OS_MAC32)
#define WS_MAC32
#endif
#else
#define WS_X11
#endif
#endif


// Note: To identify which platform we are compiling at, I need to
// include <qglobal.h>, but this file is from QT4. Need to change
// to a platform independent way of discovering which platform I'm in.
//
// Q_WS_X11 X11
// Q_WS_MAC MacOSX
// Q_WS_QWS QT for Embedded Linux
// Q_WS_WIN Windows
//#include <qglobal.h>


#ifdef WS_WIN
#include <windows.h>
#endif


//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Private Methods
#pragma mark-- Class initialization

/**
 * Initialize the attributes
 */
void PDice::initAttributes()
{

    // Initialize the dice and space to 0 and null
    myDice = 0;
    mySpace = (PSpace *)NULL;

    //Debug purposes
    dbg.setCallerName("Dice   ");
    dbg.printF(4,
               "|    Constructor Dice %-8s, dice %2d.                 |",
               getName().c_str(),
               getDice());

#ifdef WS_X11
    // std::cout.flush();

    struct timeval tv;
    struct timezone tz;
    //    struct tm *tm;
    //    tm = localtime(&tv.tv_sec);

    gettimeofday(&tv, &tz);
    //    cout << "valor " << &tv.tv_usec << ". valor long: " << (long) &tv.tv_usec << endl;
    srand48((long)&tv.tv_usec);

#endif
#ifdef WS_MAC
    struct timeval tv;
    struct timezone tz;
    //    struct tm *tm;
    //    tm = localtime(&tv.tv_sec);

    gettimeofday(&tv, &tz);
    srand48((long)&tv.tv_usec);
#endif
#ifdef WS_WIN
    //    srand((unsigned)time(0));

    LARGE_INTEGER time;
    QueryPerformanceCounter(&time);
    srand((unsigned)time.LowPart);
#endif
}


//
// FUTURE STUDY...
//
//unsigned int Dice::hash( time_t t, clock_t c )
//{
//    // Get a uint32 from t and c
//    // Better than uint32(x) in case x is floating point in [0,1]
//    // Based on code by Lawrence Kirby (fred@genesis.demon.co.uk)
//
//    static unsigned int differ = 0;  // guarantee time-based seeds will change
//
//    unsigned int h1 = 0;
//    unsigned char *p = (unsigned char *) &t;
//    for( size_t i = 0; i < sizeof(t); ++i )
//    {
//        h1 *= UCHAR_MAX + 2U;
//        h1 += p[i];
//    }
//    unsigned int h2 = 0;
//    p = (unsigned char *) &c;
//    for( size_t j = 0; j < sizeof(c); ++j )
//    {
//        h2 *= UCHAR_MAX + 2U;
//        h2 += p[j];
//    }
//    return ( h1 + differ++ ) ^ h2;
//
//
// 1) Seed the random generator
//  srand((unsigned)time(0));
//
// Recomendado usar: clock (time(), GetTickCount(), QueryPerformanceCounter() or even _asm.RDTSC
//
//    GetTickCount - The GetTickCount function retrieves the number of
//    milliseconds that have elapsed since the system was started
//    time (CRT function) - The time function returns the number of seconds
//    elapsed since midnight (00:00:00), January 1, 1970.
//    asm rdtsc - read time stamps counter - not sure about this one, this timer
//    probably works with cpu clock
//    GetSystemTime - The GetSystemTime function retrieves the current system date
//    and time.There are miliseconds, seconds, minutes etc in result
//    QueryPerformanceCounter - function retrieves the current value of the
//    high-resolution performance counter.
//    QueryPerformanceFrequency - function retrieves the frequency of the
//    high-resolution performance counter, if one exists.
//
// 2)
//    unsigned int seed = hash( time(NULL), clock() );
//    cout << "seed: " << seed << endl;
//    srand(seed);
// 3) clock()
//    clock_t start;
//    start = std::clock();
//    cout << "seed: " << start << endl;
//    srand48(start);
// 4)
//}


//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Public Methods
#pragma mark-- Constructor/Destructor

/**
 * Constructor of PDice
 *
 * @param new_var represents the string name of this Dice
 */
PDice::PDice(std::string new_var)
{
    setName(new_var);
    initAttributes();
}

//---------------------------------------------------------------------------

/**
 * Destructor of PDice
 */
PDice::~PDice()
{
    dbg.print(4, "|  Destructor PDice                                      |");
}

//---------------------------------------------------------------------------

/**
 * Set the value of name
 * @param new_var the new value of name
 */
void PDice::setName(std::string new_var)
{
    name.assign(new_var);
}

//---------------------------------------------------------------------------

/**
 * Get the value of name
 * @return the value of name
 */
std::string PDice::getName()
{
    return name;
}

//---------------------------------------------------------------------------

/**
 * Store the value of the last dice tossed by the player
 * @param new_var the new value of myDice
 */
void PDice::setDice(int new_var)
{
    myDice = new_var;
}

//---------------------------------------------------------------------------

/**
 * Get the value of the last dice tossed by the player
 * @return the value of myDice
 */
int PDice::getDice()
{
    return myDice;
}

//---------------------------------------------------------------------------

/**
 * Toss a random Dice
 */
void PDice::randomDice()
{
#ifdef WS_X11
    setDice((((int)lrand48()) % 6) + 1);
#endif
#ifdef WS_MAC
    setDice((((int)lrand48()) % 6) + 1);
#endif
#ifdef WS_WIN
    setDice((((int)rand()) % 6) + 1);
#endif
}

//---------------------------------------------------------------------------

/*
 */
/**
 * Getter: the space where this dice is located
 *  This method has no impact in the game, it's just moving the dice from the
 *  HOME of one color to the next, etc. Why? well, it's useful for simple
 *  screen/graphics placement of the dice based on which space they are in
 *  and maybe for future implementations...
 * @return pointer to the PSpace
 */
PSpace *PDice::getSpace()
{
    return mySpace;
}

//---------------------------------------------------------------------------

/**
 * Store the Space where this dice is located
 *  This method has no impact in the game, it's just moving the dice from the
 *  HOME of one color to the next, etc. Why? well, it's useful for simple
 *  screen/graphics placement of the dice based on which space they are in
 *  and maybe for future implementations...
 * @param new_space the new value of mySpace
 */
void PDice::setSpace(PSpace *new_space)
{
    mySpace = new_space;
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
