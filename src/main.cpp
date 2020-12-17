#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <memory>

#include "Interp4Command.hh"
#include "LibInterface.hh"
#include "Set4LibInterfaces.hh"
#include "MobileObj.hh"
#include "Sender.hh"

//xerces
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include "xmlinterp.hh"
#include <iostream>
#include <list>

//do srwera graficznego
//#include <iostream>
#include <iomanip>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <vector>
#include "AccessControl.hh"
#include "Port.hh"

using namespace std;
using namespace xercesc;

#define LINE_SIZE 500

/*! \brief Wczytuje plik z komendami
 * 
 * 
 */
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

/*!
 * \brief Wyszukuje nazwe polecenia i wykonuje je
 * 
 * 
 */
bool ExecProgram(Set4LibInterfaces &Libs, istream &IStrm, Scene *Scena)
{
	string KeyWord;
	IStrm >> KeyWord; //wczytuje pojedyncze slowo - ciag znakow ograniczony znakami bialymi
	std::shared_ptr<LibInterface> pLibInterface;
	Interp4Command *pInterp;
	
	while(!IStrm.fail())
	{
		if (!Libs.Find(KeyWord, pLibInterface))
		{
			cout << "Brak definicji funkcji: " << KeyWord << endl;
			return false;
		}
		
		pInterp = pLibInterface->CreateCmd(); //polimorfia Interp4Command = *lista wtyczek
		if(!pInterp->ReadParams(IStrm))
		{
			cout << "Blad parsowania funkcji: " << KeyWord << endl;
			return false;
		}
		
		cout << "ser1" << endl;
		pInterp->PrintCmd();
		cout << "ser2" << endl;
		//pInterp->PrintSyntax();
		pInterp->ExecCmd(Scena);	//wykonuje polecenie z wtyczki
		delete pInterp;
		
		Scena->MarkChange(); //serwer graficzny
		usleep(100000); //to bylo w przykladzie do klienta (serwer graficzny)
		
		IStrm >> KeyWord;
	}
	
	return true;	
}



/*!
 * Czyta z pliku opis poleceń i dodaje je do listy komend,
 * które robot musi wykonać.
 * \param sFileName - (\b we.) nazwa pliku z opisem poleceń.
 * \param CmdList - (\b we.) zarządca listy poleceń dla robota.
 * \retval true - jeśli wczytanie zostało zrealizowane poprawnie,
 * \retval false - w przeciwnym przypadku.
 */
bool ReadFile(const char* sFileName, Configuration *pConfig)
{
	
   try {
            XMLPlatformUtils::Initialize();
   }
   catch (const XMLException& toCatch) {
            char* message = XMLString::transcode(toCatch.getMessage());
            cerr << "Error during initialization! :\n";
            cerr << "Exception message is: \n"
                 << message << "\n";
            XMLString::release(&message);
            return 1;
   }
	
   SAX2XMLReader* pParser = XMLReaderFactory::createXMLReader();

   pParser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
   pParser->setFeature(XMLUni::fgSAX2CoreValidation, true);
   pParser->setFeature(XMLUni::fgXercesDynamic, false);
   pParser->setFeature(XMLUni::fgXercesSchema, true);
   pParser->setFeature(XMLUni::fgXercesSchemaFullChecking, true);

   pParser->setFeature(XMLUni::fgXercesValidationErrorAsFatal, true);

   DefaultHandler* pHandler = new XMLInterp4Config(pConfig);
   pParser->setContentHandler(pHandler);
   pParser->setErrorHandler(pHandler);

   try {
     
     if (!pParser->loadGrammar("config/config.xsd",
                              xercesc::Grammar::SchemaGrammarType,true)) {
       cerr << "!!! Plik grammar/actions.xsd, '" << endl
            << "!!! ktory zawiera opis gramatyki, nie moze zostac wczytany."
            << endl;
       return false;
     }
     
     pParser->setFeature(XMLUni::fgXercesUseCachedGrammarInParse,true);
    
    
     cout << sFileName << endl;
     pParser->parse(sFileName);
    
   }
   
   catch (const XMLException& Exception) {
	   
            char* sMessage = XMLString::transcode(Exception.getMessage());
            cerr << "Informacja o wyjatku: \n"
                 << "   " << sMessage << "\n";
            XMLString::release(&sMessage);
            return false;
   }
   
   catch (const SAXParseException& Exception) {
	   
            char* sMessage = XMLString::transcode(Exception.getMessage());
            char* sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

            cerr << "Blad! " << endl
                 << "    Plik:  " << sSystemId << endl
                 << "   Linia: " << Exception.getLineNumber() << endl
                 << " Kolumna: " << Exception.getColumnNumber() << endl
                 << " Informacja: " << sMessage 
                 << endl;

            XMLString::release(&sMessage);
            XMLString::release(&sSystemId);
            return false;
   }
   catch (...) {
	   
            cout << "Zgloszony zostal nieoczekiwany wyjatek!\n" ;
            return false;
   }

   delete pParser;
   delete pHandler;
   return true;
}

/*!
 * \brief Wysyła napis do poprzez gniazdo sieciowe.
 *
 * Wysyła napis do poprzez gniazdo sieciowe.
 * \param[in] Sk2Server - deskryptor gniazda sieciowego, poprzez które 
 *                        ma zostać wysłany napis w sensie języka C.
 * \param[in] sMesg - zawiera napis, który ma zostać wysłany poprzez
 *                    gniazdo sieciowe.
 */


/*!
 * \brief Funkcja jest treścią wątku komunikacyjnego
 * 
 * Funkcja jest treścią wątku komunikacyjnego.
 * \param[in] rSender - odpowiada za śledenie zmian na scenie 
 *                      i przesyłanie do serwera graficznego
 *                      aktualnego stanu sceny, gdy uległ on zmianie.
 */
void Fun_CommunicationThread(Sender  *pSender)
{
  pSender->Watching_and_Sending();
}


/*!
 * Otwiera połączenie sieciowe
 * \param[out]  rSocket - deskryptor gniazda, poprzez które może być
 *                        realizowana komunikacja sieciowa.
 */
bool OpenConnection(int &rSocket)
{
  struct sockaddr_in  DaneAdSerw;

  bzero((char *)&DaneAdSerw,sizeof(DaneAdSerw));

  DaneAdSerw.sin_family = AF_INET;
  DaneAdSerw.sin_addr.s_addr = inet_addr("127.0.0.1");
  DaneAdSerw.sin_port = htons(PORT);


  rSocket = socket(AF_INET,SOCK_STREAM,0);

  if (rSocket < 0) {
     cerr << "*** Blad otwarcia gniazda." << endl;
     return false;
  }

  if (connect(rSocket,(struct sockaddr*)&DaneAdSerw,sizeof(DaneAdSerw)) < 0)
   {
     cerr << "*** Brak mozliwosci polaczenia do portu: " << PORT << endl;
     return false;
   }
  return true;
}


int main(int argc, char **argv)
{
	cout << endl << "%%%%%%%%%%%%%%%%%%%%%" << endl << "main" << endl << "%%%%%%%%%%%%%%%%%%%%%" << endl << endl;
	
  // sprawdzanie ilosci argumentow
	if(argc < 2)
    {
        cout << "Za malo argumentow" << endl;
        return 1;
    }
	
	cout << endl << "Nazwa pliku: " << argv[1] << endl << endl;
	
	Set4LibInterfaces Map_Lib;
	//shared_ptr<LibInterface> Lib; 
	//Lib = make_shared<LibInterface>("libInterp4Move.so");
	//Map_Lib.Add(Lib);
	Scene Scena;
	Configuration Config(&Map_Lib, &Scena);
	int                 Socket4Sending; 
	//cout << 'a' << endl;
	//wywolanie xmlinterp czy jakos tak
	
	
    
    
    try {
		if (!ReadFile("config/config.xml",&Config)) return 1;

		 } catch (int) {
		 cout << "Niepoprawne zakonczenie rogramu" << endl;

		 } catch (...) {
		 cout << "Zgloszenie nieznanego wyjatku" << endl;

		 }
    
    
    
	//cout << 'b' << endl;
	  
	//serwer graficzny
	if (!OpenConnection(Socket4Sending)) return 1;
	Sender   ClientSender(Socket4Sending,&Scena);
  //  thread   Thread4Sending(Fun_Sender, Socket4Sending, &ClientSender);

	thread   Thread4Sending(Fun_CommunicationThread,&ClientSender);
	
	
	
	
	
	
	
	// uruchomienie cpp
	
	istringstream IStrm4Cmd;
	
	if (!ExecPreprocesor(argv[1],IStrm4Cmd))
	{
		cerr << "Cos poszlo nie tak" << endl;
		return 2;
	}
	
	cout << IStrm4Cmd.str() << endl;
	
	if(!ExecProgram(Map_Lib,IStrm4Cmd, &Scena))	// tu sie wykonuje calu program
	{
		cerr<< "Blad wykonywania programu" << endl;
		return 3;
	}
	
	
	//-------------------------------------
  // Należy pamiętać o zamknięciu połączenia.
  // Bez tego serwer nie będzie reagował na
  // nowe połączenia.
  //
  cout << "Close\n" << endl; // To tylko, aby pokazac wysylana instrukcje
  Send(Socket4Sending,"Close\n");
  ClientSender.CancelCountinueLooping();
  Thread4Sending.join();
  close(Socket4Sending);
	
	return 0;
}
