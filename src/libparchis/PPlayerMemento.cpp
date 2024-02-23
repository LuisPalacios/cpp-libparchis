
/**
 *  @class  PPlayerMemento PPlayerMemento.cpp "PPlayerMemento.cpp"
 *  @file   PPlayerMemento.cpp
 *  @brief  Parchis Class: Stores/Restores internal state of a Player object
 *
 *  ---------------------------------------------------------------------------
 */


//---------------------------------------------------------------------------

#include "PPlayerMemento.h"

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Public Methods
#pragma mark-- Class initialization

/**
 * PPlayerMemento Constructor:
 *
 * @param o_name   Value of "name" passed from the Originator (Player class)
 * @param o_type   Value of "type" passed from the Originator (Player class)
 */
PPlayerMemento::PPlayerMemento(std::string o_name, int o_type)
{
    dbg.setCallerName("PlayerMemento");
    oss.str("");
    oss << "Constructor PlayerMemento";
    dbg.print(3, oss.str());

    // Store the value of "name"
    this->name = o_name;
    this->type = o_type;
}

//---------------------------------------------------------------------------

/**
 * PlayerMemento Destructor
 *
 */
PPlayerMemento::~PPlayerMemento()
{
    dbg.print(3, "Destructor PlayerMemento");
}

//---------------------------------------------------------------------------


#pragma mark-- More public methods

//---------------------------------------------------------------------------

/**
 * Get the value of name
 * @return string with the "name" value
 */
std::string PPlayerMemento::getName()
{
    return name;
}

//---------------------------------------------------------------------------

/**
 * Get the value of type
 * @return int with the "type" value
 */
int PPlayerMemento::getType()
{
    return type;
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
