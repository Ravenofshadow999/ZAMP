#ifndef	LIBINTERFACE_HH
#define	LIBINTERFACE_HH

#include <iostream>
#include <dlfcn.h>
#include <sstream>
#include <string>
#include <cassert>

#include "Interp4Command.hh"

//obsluguje klase Set4LibsInterfaces, ktora jest mapa wtyczek

/*!
 * \file
 * \brief Zawiera definicję klasy LibInterface
 */


/*!
 * \brief Obsluguje klase Set4LibsInterfaces, ktora jest mapa wtyczek
 */

class LibInterface
{	
	/*!
   * 	\brief Parametry klasy 
   * 	\param pLibHnd - wskaznik do biblioteki
   * 	\param sCmdName - przechowuje nazwe komendy
   * 
   */
	void * pLibHnd;
	std::string sCmdName;
	Interp4Command *(*pCreateCmd)(void);
	
	public:
	/*!
    * \brief Konstruktor.
    */
	explicit LibInterface(const std::string sLibName);
	/*!
    * \brief Destruktor.
    */
	~LibInterface(){};
	
	Interp4Command *CreateCmd() {return pCreateCmd();}
	/*!
   * \brief Dostęp do nazwy komendy.
   *
   * Dostęp do nazwy komendy.
   * \retval sCmdName
   */
	const std::string GetCmdName(){return sCmdName;}
	
};

#endif
