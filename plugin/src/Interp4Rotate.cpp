#include <iostream>
#include <string>
#include <unistd.h>

#include "Vector3D.hh"
#include "Interp4Rotate.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Rotate"; }
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Rotate::CreateCmd();
}


/*!
 *
 */
Interp4Rotate::Interp4Rotate()
{}


/*!
 *	\brief funkcja wypisuje wczytane parametry w terminalu.
 */
void Interp4Rotate::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName()<< " " << sName << " " << _Speed  << " " << stopnie << endl;
}


/*!
 *
 */
const char* Interp4Rotate::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Rotate::ExecCmd( Scene *pScena) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
   int Fps = 100;
	std::shared_ptr<MobileObj> pObject;
	if (!pScena->Find(sName, pObject))
	{
		std::cerr << "Object not found: " << sName << endl;
		return 0;
	}
	/*
	Vector3D Pos;
	int steps = (dlugosc_drogi/_Speed_mmS)*Fps;
	if (steps < 0) steps *= -1;
	for(int a = 0; a < steps; a ++){
		// MODYFIKACJA
		pScena->LockAccess();
		Pos = pObject->GetPositoin_m();
		Pos[0] += dlugosc_drogi/steps;
		pObject->SetPosition_m(Pos);
		pScena->MarkChange();
		pScena->UnlockAccess();
		// KONIEC MODYFIKCAJI
		usleep(1000000/Fps);
	}*/
  return true;
}


/*!
 *	\brief Funkcja wczytuje parametry z pliku do odpowiednich pol klasy.
 */
bool Interp4Rotate::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList >> sName >> _Speed >> stopnie;
  if (Strm_CmdsList.fail()) return false;
  return true;
}


/*!
 *
 */
Interp4Command* Interp4Rotate::CreateCmd()
{
  return new Interp4Rotate();
}


/*!
 *
 */
void Interp4Rotate::PrintSyntax() const
{
  cout << "   Rotate  NazwaObiektu  Szybkosc[deg/s]  Kat[deg]" << endl;
}
