#ifndef LIBINTERFACE_HH
#define LIBINTERFACE_HH

#include <dlfcn.h>
#include <sstream>
#include <string>
#include "Interp4Command.hh"

class LibInterface
{
	void *_LibHandler;	// wskaznik "uchwyt" do wtyczki
	std::string _CmdName;	// nazwa wtyczki (string)
	Interp4Command *(* _pCreateCmd)(void);	
	
	public:
	//LibInterface(const char* LibName){}
	LibInterface(const std::string &LibName);
	~LibInterface(){};
	
	bool  ReadParams(std::istream &Strm)	//wczytuje parametry do wtyczki
	{	
		return _pCreateCmd()->ReadParams(Strm);
	}
	
	const std::string GetCmdName(){return _CmdName;}	//zwraca nazwe wtyczki
	
	
	
	
};

#endif
