#include "LibInterface.hh"

LibInterface(const std::string sLibName)
{
	//jak nie zadziala uzyj tego:
	//void *LibHnd = dlopen(LibPath.c_str(),RTLD_LAZY);
	//void *Fun;
	this->pLibHnd = dlopen(sLibName.c_str(),RTLD_LAZY);
	
	if (!this->pLibHnd) 
	{
		cerr << "!!! Brak biblioteki: " << LibPath << std::endl;
		return 1;
	}
	
	this->pFun = dlsym(this->pLibHnd,"CreateCmd");
	if (!this->pFun) 
	{
		cerr << "!!! Nie znaleziono funkcji CreateCmd" << std::endl;
		return 1;
	}
	  
	pCreateCmd = *reinterpret_cast<Interp4Command* (**)(void)>(&this->pFun);
	//this->pLibHnd = LibHnd;
	this-> sCmdName = pCreateCmd()->GetCmdName();
	
	
}
