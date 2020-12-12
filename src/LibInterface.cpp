#include "LibInterface.hh"
#include <iostream>

LibInterface::LibInterface(const std::string &LibName)
{
	void *LibHandler = dlopen(LibName.c_str(),RTLD_LAZY);
	void *FuncHandler;
	
	std::cout << "Laduje wtyczke " << LibName << std::endl;
	
	
	if(!LibHandler){
		std::cerr << "Nie znaleziono biblioteki: " << LibName << std::endl;
		std::cerr << dlerror() << std::endl;
	}
	FuncHandler = dlsym(LibHandler,"CreateCmd");
	if(!FuncHandler){
		std::cerr << "Nie znaleziono polecnia " << std::endl;
	}

	_pCreateCmd = *reinterpret_cast<Interp4Command* (**)(void)>(&FuncHandler);
	this->_LibHandler = LibHandler;
	this->_CmdName=_pCreateCmd()->GetCmdName();
}
