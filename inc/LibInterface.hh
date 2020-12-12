#ifndef	LIBINTERFACE_HH
#define	LIBINTERFACE_HH

#include <iostream>
#include <dlfcn.h>
#include <sstream>
#include <string>
#include <cassert>

#include "Interp4Command.hh"

class LibInterface
{
	void * _pLibHnd;
	std::string _CmdName;
	Interp4Command *(*pCreateCmd)(void);
	void *pFun;
	
	public:
	LibInterface(const std::string LibPath);
	~Libinterface(delete pCmd; dlclose(pLibHnd););
	
	Interp4Command *CreateCmd() {return _pCreateCmd();}
	const std::string GetCmdName(){return _CmdName;}
	
};

#endif
