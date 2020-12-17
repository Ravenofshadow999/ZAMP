#ifndef SET4LIBINTERFACES_HH
#define 	SET4LIBINTERFACES_HH

#include <map>
#include <cassert>
#include <sstream>
#include <string>
#include <cstdio>
#include <memory>
#include <iostream>

#include "LibInterface.hh"

/*!
 * \file
 * \brief Definicja klasy Set4LinInterfaces
 *
 * Plik zawiera definicje klasy Set4LibInterfaces
 */

/*!
 * \brief Obsluguje liste wtyczek
 */

typedef std::map<const std::string, std::shared_ptr<LibInterface>> Set4Libs;

//klasa jest zbiorem dodanych wtyczek

class Set4LibInterfaces
{
	/*!
   * 	\brief Parametry klasy 
   * 	\param _Set4Libs - lista wczytanych wtyczek
   */
	Set4Libs _Set4Libs;
	
public:
	Set4LibInterfaces(){std::cout << "Stworzono Set4Libs" << std::endl;};
	/*!
   * \brief Poiera rozmiar listy
   * 
   *  */
	int getSize(){return _Set4Libs.size();}
	
	/*!
   * \brief Dodaje pozycje do listy
   * 
   *  */
	void Add(std::shared_ptr<LibInterface> &PLibInterface)
	{
		_Set4Libs.insert(std::pair<std::string,std::shared_ptr<LibInterface>>(PLibInterface->GetCmdName(),PLibInterface));
	}
	
	/*!
   * \brief Szuka w liscie wtyczki o podanej nazwie
   * 
   *  */
	bool Find(const std::string &Name, std::shared_ptr<LibInterface> &PLibInterface)
	{
		Set4Libs::const_iterator Iter = _Set4Libs.find(Name);
		if (Iter == _Set4Libs.end()) return false;
		PLibInterface = Iter->second;
		return true;
	}
	
	
	
	
	
	
};

#endif
