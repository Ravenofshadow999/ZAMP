#ifndef SENDER_HH
#define SENDER_HH

#include <iostream>
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


int Send(int Sk2Server, const char *sMesg)
{
  ssize_t  IlWyslanych;
  ssize_t  IlDoWyslania = (ssize_t) strlen(sMesg);

  while ((IlWyslanych = write(Sk2Server,sMesg,IlDoWyslania)) > 0) {
    IlDoWyslania -= IlWyslanych;
    sMesg += IlWyslanych;
  }
  if (IlWyslanych < 0) {
    std::cerr << "*** Blad przeslania napisu." << std::endl;
  }
  return 0;
}

/*!
 * \brief Modeluje nadajnik poleceń odzwierciedlających aktualny stan sceny.
 *
 * Modeluje nadajnik poleceń odzwierciedlających aktualny stan sceny.
 * W tym celu monitoruje zmiany na scenie, a gdy je wykryje przesyła
 * informacje o aktualnej pozycji wszystkich obiektów.
 */
class Sender {
  /*!
   * \brief Wartość tego pola decyduje o kontynuacji wykonywania wątku.
   * 
   * Wartość tego pola decyduje o kontynuacji wykonywania wątku.
   * W przypadku wartości \p true, pętla wątku będzie wykonywana.
   * Natomiast wartość \p false powoduje przerwanie pętli.
   */
   volatile bool    _ContinueLooping = true;
  /*!
   * \brief Deskryptor gniazda sieciowego, poprzez które wysyłane są polecenia.
   */
   int             _Socket = 0;
  /*!
   * \brief Wskaźnik na scenę, które stan jest przesyłany w postaci
   *        poleceń do serwera graficzneg.
   */
   Scene          *_pScn = nullptr;

  
 public:
  /*!
   * \brief Inicjalizuje obiekt deskryptorem gniazda i wskaźnikiem
   *        na scenę, na zmianę stanu które będzie ten obiekt reagował.
   */
   Sender(int Socket, Scene *pScn): _Socket(Socket), _pScn(pScn) {}

  /*!
   * \brief Sprawdza, czy pętla wątku może być wykonywana.
   * 
   * Sprawdza, czy pętla wątku może być wykonywana.
   * \retval true - pętla wątku może być nadal wykonywana.
   * \retval false - w przypadku przeciwnym.
   */
   bool ShouldCountinueLooping() const { return _ContinueLooping; }
  /*!
   * \brief Powoduje przerwanie działania pętli wątku.
   *
   * Powoduje przerwanie działania pętli wątku.
   * \warning Reakcja na tę operację nie będize natychmiastowa.
   */  
   void CancelCountinueLooping() { _ContinueLooping = false; }

  /*!
   * \brief Ta metoda jest de facto treścią wątku komunikacyjnego
   *
   * Przegląda scenę i tworzy odpowiednie polecenia, a następnie
   * wysyła je do serwera.
   * \param[in] Socket - deskryptor gniazda sieciowego, poprzez które
   *                     wysyłane są polecenia.
   */
   void Watching_and_Sending() {
     while (ShouldCountinueLooping()) {
       if (!_pScn->IsChanged())  { usleep(10000); continue; }
       _pScn->LockAccess();
       
       //------- Przeglądanie tej kolekcji to uproszczony przykład
       
       Send(_Socket,"Clear\n"); // To jest konieczne, aby usunąć wcześniejsze obiekty.
       std::cout << "Clear\n";
       /*for (const GeomObject &rObj : _pScn->_Container4Objects) {
                                     // Ta instrukcja to tylko uproszczony przykład
	 cout << rObj.GetStateDesc();
         Send(_Socket,rObj.GetStateDesc()); // Tu musi zostać wywołanie odpowiedniej
                                           // metody/funkcji gerującej polecenia dla serwera.
       }*/
       std::stringstream ObjectList =  _pScn->GetObjectsList();
	   std::string sName;
	   std::shared_ptr<MobileObj> pObj;
	   Vector3D vec;
	   ObjectList >> sName;
       
       
        while (!ObjectList.fail())
        {
			if(!_pScn->Find(sName, pObj))
			{
				std::cout << "Object not found in scene: " << sName << std::endl;
				continue;
			}
			
			std::stringstream Desc;
			Desc << "Cube" << ' ';
			
			vec = pObj->GetWymiar();
			Desc << vec[0] << ' ' << vec[1] << ' ' << vec [2] << ' ';
			
			vec = pObj->GetPositoin_m();
			Desc << vec[0] << ' ' << vec[1] << ' ' << vec [2] << ' ';
			
			vec = pObj->GetKat();
			Desc << vec[0] << ' ' << vec[1] << ' ' << vec [2] << ' ';
			
			vec = pObj->GetKolor();
			Desc << vec[0] << ' ' << vec[1] << ' ' << vec [2] << std::endl;
			
			std::cout << Desc.str();
			Send(_Socket,Desc.str().c_str());
			
			ObjectList >> sName;
		   }
		   Send(_Socket,"Display\n"); // To jest konieczne, aby zobaczyć zmiany
		   std::cout << "Display\n";
		   
		   _pScn->CancelChange();
		   _pScn->UnlockAccess();
     }
     }
  
};



#endif
