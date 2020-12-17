#include "LibInterface.hh"


LibInterface::LibInterface(const std::string sLibName)
{
	//std::cout << "Lib_name: " << sLibName << std::endl;
	//const std::string temp = "/home/raven/Pulpit/Zamp/Od_nowa/zalazek/libs/"+sLibName;
	//std::cout << "temp: " << temp << std::endl;
	
	void *LibHnd = dlopen(sLibName.c_str(),RTLD_LAZY);
	void *Fun;
	
	if (!LibHnd) 
	{
		std::cerr << "err:\t" << dlerror() << std::endl;
		std::cerr << "!!! Brak biblioteki: " << sLibName << std::endl;
		throw 1;
	}
	
	Fun = dlsym(LibHnd,"CreateCmd");
	if (!Fun) 
	{
		std::cerr << "!!! Nie znaleziono funkcji CreateCmd" << std::endl;
		throw 2;
	}
	  
	pCreateCmd = *reinterpret_cast<Interp4Command* (**)(void)>(&Fun);
	this->pLibHnd = LibHnd;
	this-> sCmdName = pCreateCmd()->GetCmdName();
	
	
}
