/**
 *  @brief  Parchis Include: Declares methods to callback with Objective-C++
 *
 *  Belongs to the Library: "Parchis Engine C++ library"
 *
 *  @author  Luis Palacios
 *  @version 0.1
 *  @date    10/Dec/11
 *
 *  @par Description
 *
 *  This file declares serveral methods that will allow to call
 *  an Objetive-C method from within C++ class.
 *
 *  @par Sample usage:
 *  @code
 *
 *    ToDO
 *
 *  @endcode
 *
 */

#ifndef libcpp_static_PDebugObjC_Interface_h
#define libcpp_static_PDebugObjC_Interface_h

// Lista de Métodos de Objective-C++ que van a poder ser llamados desde C++
void GUIWrapperMuestraMensaje(void *myObjectInstance, char *parameter);
void GUIWrapperClearMensajes(void *myObjectInstance);


#endif
