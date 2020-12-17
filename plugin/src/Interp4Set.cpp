#include <iostream>
#include <string>
#include <unistd.h>

#include "Vector3D.hh"
#include "Interp4Set.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Set"; }
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Set::CreateCmd();
}


/*!
 *
 */
Interp4Set::Interp4Set()
{}


/*!
 *	\brief funkcja wypisuje wczytane parametry w terminalu.
 */
void Interp4Set::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName()<< " " << sName << " " << _X  << " " << _Y << ' ' << _Z << endl;
}


/*!
 *
 */
const char* Interp4Set::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Set::ExecCmd( Scene *pScena) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */

	std::shared_ptr<MobileObj> pObject;
	if (!pScena->Find(sName, pObject)){
		std::cerr << "Object not found: " << sName << endl;
		return 0;
	}
	Vector3D Pos;

		// MODYFIKACJA
		pScena->LockAccess();
		Pos = pObject->GetPositoin_m();
		pObject->SetPosition_m(Pos);
		pScena->MarkChange();
		pScena->UnlockAccess();
		// KONIEC MODYFIKCAJI
		usleep(1000000);
	
  return true;
}


/*!
 *	\brief Funkcja wczytuje parametry z pliku do odpowiednich pol klasy.
 */
bool Interp4Set::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList >> sName >> _X >> _Y >> _Z;
  if (Strm_CmdsList.fail()) return false;
  return true;
}


/*!
 *
 */
Interp4Command* Interp4Set::CreateCmd()
{
  return new Interp4Set();
}


/*!
 *
 */
void Interp4Set::PrintSyntax() const
{
  cout << "   Set  NazwaObiektu	  Wymiar X[m]	  Wymiar Y[m]	  Wymiar Z[m]" << endl;
}
