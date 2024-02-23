
/**
 *  @class  PTime PTime.cpp "PTime.cpp"
 *  @file   PTime.cpp
 *  @brief  Parchis Class: represents each of the Spaces in the Parchis game
 *
 *  ---------------------------------------------------------------------------
 */


//---------------------------------------------------------------------------

#include "PTime.h"


#pragma mark -
#pragma mark Static Attributes

// The C++ standard requires a definition of static's
//unsigned long PTime::count;

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Private Methods
#pragma mark-- Class initialization

/**
 * Initialize the attributes and create all instances
 */
void PTime::initAttributes()
{
    //    static int flag = 0;
    //
    //    // Initial values for the static's
    //    if ( flag == 0 ) {
    //        setCount( 0 );
    //        //dbg.setCallerName ( "PTime  " );
    //        //dbg.printF( 4, "|   Initialization of PTime              |");
    //    }
}

//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Public Methods
#pragma mark-- Public Constructor/Destructor

//---------------------------------------------------------------------------

/**
 * Constructor of PTime
 */
PTime::PTime()
{
    initAttributes();
}

//---------------------------------------------------------------------------

/**
 * Destructor of PTime
 *
 */
PTime::~PTime()
{
}

//---------------------------------------------------------------------------


#pragma mark-- General methods, getters and setters

//---------------------------------------------------------------------------

/**
 * Devolver el tiempo.
 */
double PTime::getCurrentTime()
{

#if defined(__APPLE__)
    /*
     Welcome mach_absolute_time! (credit: http://www.macresearch.org/tutorial_performance_and_time)

        mach_absolute_time is a CPU/Bus dependent function that returns a value based on the number of "ticks" since
        the system started up. It's not well documented. But, the lack of concrete documentation shouldn't be a
        deterrent toward using it, because the behavior is guaranteed on Mac OS X AND it covers any time range that
        the system clock covers (nanoseconds up until the system halts (by differencing)). Would I use it in production
        code, probably not. But for testing, it's a sure thing.

     */

    static mach_timebase_info_data_t timebaseInfo;

    if (timebaseInfo.denom == 0)
    {
        mach_timebase_info(&timebaseInfo);
    }

    // Devuelvo en nanosegundos, es decir la milmillonésima parte de un segundo, 10-9.
    return mach_absolute_time() * (double)timebaseInfo.numer /
           timebaseInfo.denom * 0.000000001;

#elif defined(WIN32)
    static LARGE_INTEGER frequency;
    LARGE_INTEGER currentTime;

    if (frequency.QuadPart == 0)
    {
        QueryPerformanceFrequency(&frequency);
    }
    QueryPerformanceCounter(&currentTime);

    return (double)currentTime.QuadPart / frequency.QuadPart;

#elif defined(__linux)
    struct timespec currentTime;

    clock_gettime(CLOCK_MONOTONIC, &currentTime);
    return currentTime.tv_sec + currentTime.tv_nsec * 0.000000001;
#endif
}


//---------------------------------------------------------------------------
//
///**
// * Set the value of count
// * @param new_var the new value to assign to 'count'
// */
//void PTime::setCount (unsigned long new_var ) {
//    count = new_var;
//}
//
////---------------------------------------------------------------------------
//
///**
// * Get the value of count
// * @return the value of count
// */
//unsigned long PTime::getCount () {
//    return count;
//}
//
////---------------------------------------------------------------------------
//
///**
// * Add's to count variable
// * @param new_var the cuantity to add
// */
//void PTime::addCount (unsigned long new_var )
//{
//    count+=new_var;
//}
