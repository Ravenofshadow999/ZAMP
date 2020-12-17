#include <iostream>
#include <string>
#include <unistd.h>

#include "Vector3D.hh"
#include "Interp4Move.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Move"; }
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Move::CreateCmd();
}


/*!
 *
 */
Interp4Move::Interp4Move(): _Speed_mmS(0)
{}


/*!
 *	\brief funkcja wypisuje wczytane parametry w terminalu.
 */
void Interp4Move::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName()<< " " << sName << " " << _Speed_mmS  << " " << dlugosc_drogi << endl;
}


/*!
 *
 */
const char* Interp4Move::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Move::ExecCmd( Scene *pScena) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
   int Fps = 100;
	std::shared_ptr<MobileObj> pObject;
	if (!pScena->Find(sName, pObject)){
		std::cerr << "Object not found: " << sName << endl;
		return 0;
	}
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
	}
  return true;
}


/*!
 *	\brief Funkcja wczytuje parametry z pliku do odpowiednich pol klasy.
 */
bool Interp4Move::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList >> sName >> _Speed_mmS >> dlugosc_drogi;
  if (Strm_CmdsList.fail()) return false;
  return true;
}


/*!
 *
 */
Interp4Command* Interp4Move::CreateCmd()
{
  return new Interp4Move();
}


/*!
 *
 */
void Interp4Move::PrintSyntax() const
{
  cout << "   Move  NazwaObiektu  Szybkosc[m/s]  DlugoscDrogi[m]" << endl;
}
