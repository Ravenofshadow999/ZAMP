#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <cstdio>
#include <string>
#include <sstream>
#include "Interp4Command.hh"
#include "MobileObj.hh"
#include "LibInterface.hh"
#include "Set4LibInterfaces.hh"


#define LINE_SIZE 500


using namespace std;

bool ExecPreprocesor( const char * NazwaPliku, istringstream &IStrm )
{
    std::string Cmd4Preproc = "cpp -P ";
    char Line[LINE_SIZE];
    std::ostringstream OTmpStrm;
    Cmd4Preproc += NazwaPliku;
    FILE* pProc = popen(Cmd4Preproc.c_str(),"r");
    if (!pProc) return false;
    while (fgets(Line,LINE_SIZE,pProc)) {
        OTmpStrm << Line;
    }
    IStrm.str(OTmpStrm.str());
    return pclose(pProc) == 0;
    
    //return true;
}

bool ExecProgram(Set4LibInterfaces &Libs, istream &IStrm)
{
	string KeyWord;
	IStrm >> KeyWord; //wczytuje pojedyncze slowo - ciag znakow ograniczony znakami bialymi
	std::shared_ptr<LibInterface> _PLibInterface;
	
	while(!IStrm.fail())
	{
		if (!Libs.Find(KeyWord, _PLibInterface))
		{
			std::cout << "Brak definicji funkcji: " << KeyWord << endl;
			return false;
		}
		
		if (!_PLibInterface->ReadParams(IStrm))
		{
			std::cout << "Nie udalo sie zparsowac: " << KeyWord << endl;
			return false;
		}
		
		IStrm >> KeyWord;
	}
	
	return true;
}

int main(int argc, char** argv)
{
	
  // sprawdzanie ilosci argumentow
	if(argc < 2)
    {
        cout << "Za malo argumentow" << endl;
        return 1;
    }
	
	cout << endl << "Nazwa pliku: " << argv[1] << endl << endl;
	
	
	Set4LibInterfaces Map_Lib;
	std::shared_ptr<LibInterface> Lib = std::make_shared<LibInterface>("libInterp4Move.so");
	Map_Lib.Add(Lib);
	Map_Lib.Add(std::make_shared<LibInterface>("libInterp4Set.so"));
	
	
	// uruchomienie cpp
	
	istringstream IStrm4Cmd;
	
	if (!ExecPreprocesor(argv[1],IStrm4Cmd))
	{
		cout << "Cos poszlo nie tak" << endl;
		return 1;
	}
	
	//cout << IStrm4Cmd.str() << endl;
	if(!ExecProgram(Map_Lib,IStrm4Cmd))
	{
		std::cerr<< "Error in executing your program" << endl;
		return 3;
	}
	
	return 0;
	/*
  void *pLibHnd_Move = dlopen("libInterp4Move.so",RTLD_LAZY);
  Interp4Command *(*pCreateCmd_Move)(void);
  void *pFun;

  if (!pLibHnd_Move) {
    cerr << "!!! Brak biblioteki: Interp4Move.so" << endl;
    return 1;
  }


  pFun = dlsym(pLibHnd_Move,"CreateCmd");
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Move = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun);


  Interp4Command *pCmd = pCreateCmd_Move();

  cout << endl;
  cout << pCmd->GetCmdName() << endl;
  cout << endl;
  pCmd->PrintSyntax();
  cout << endl;
  pCmd->PrintCmd();
  cout << endl;
  
  delete pCmd;

  dlclose(pLibHnd_Move);
  */
}
