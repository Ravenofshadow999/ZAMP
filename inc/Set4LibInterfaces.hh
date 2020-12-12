#ifndef  SET4LIBINTERFACES_HH
#define  SET4LIBINTERFACES_HH
	
#include <map>
#include <iostream>
#include <string>
#include <cstdio>
#include <memory>
#include <cassert>
#include <sstream>
#include "LibInterface.hh"

typedef std::map<const std::string, std::shared_ptr<LibInterface>> Set4Libs;	//zapisuje cala linijke do krotkiego Set4Libs, ktore staje sie jakby aliasem

class Set4LibInterfaces{
	Set4Libs _Set4Libs;
	
	public:
	void Add(const std::shared_ptr<LibInterface> PLibInterface)
	{
		_Set4Libs.insert(std::pair<std::string,std::shared_ptr<LibInterface>>(PLibInterface->GetCmdName(),PLibInterface)); //dodaje pare: nazwa(string) i wskaznik do mapy wtyczek (cos w rodzaju listy)
	}
	
	bool Find(const std::string &Name, std::shared_ptr<LibInterface> &PLibInterface)
	{
		Set4Libs::const_iterator Iter = _Set4Libs.find(Name);	//tworzy iterator, ktory wyszukuje nazwe (string)
		if (Iter == _Set4Libs.end()) return false;	//jesli doszedl do konca mapy i nic nie znalazl zwraca false
		PLibInterface = Iter->second; //jezeli znalazl zapisuje do iteratora drugie pole z pary -> czyli wskaznik
		return true;
     
	}
	
	
};
	
#endif
