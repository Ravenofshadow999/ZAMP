#include <iostream>
#include <dlfcn.h>
#include <cassert>

#include "Interp4Command.hh"
#include "LibInterface.hh"
#include "Set4LibInterfaces.hh"
#include "MobileObj.hh"


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

bool ExecProgram(Set4LibInterfaces *Libs, istream &IStrm)
{
	string KeyWord;
	IStrm >> KeyWord; //wczytuje pojedyncze slowo - ciag znakow ograniczony znakami bialymi
	std::shared_ptr<LibInterface> _PLibInterface;
	
	while(!IStrm.fail())
	{
		if (!Libs->Find(KeyWord, _PLibInterface))
		{
			std::cout << "Brak definicji funkcji: " << KeyWord << endl;
			return false;
		}
		
		
		IStrm >> KeyWord;
	}
	
	return true;	
}


int main()
{
	
	
	return 0;
}
