#include <iostream>
#include <string>
#include <unistd.h>

#include "Vector3D.hh"
#include "Interp4Pause.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Pause"; }
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Pause::CreateCmd();
}


/*!
 *
 */
Interp4Pause::Interp4Pause()
{}


/*!
 *	\brief funkcja wypisuje wczytane parametry w terminalu.
 */
void Interp4Pause::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName()<< " " << _CzasTrwania  << endl;
}


/*!
 *
 */
const char* Interp4Pause::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Pause::ExecCmd( Scene *pScena) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
 
	

		usleep(_CzasTrwania);
	
  return true;
}


/*!
 *	\brief Funkcja wczytuje parametry z pliku do odpowiednich pol klasy.
 */
bool Interp4Pause::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList >> _CzasTrwania;
  if (Strm_CmdsList.fail()) return false;
  return true;
}


/*!
 *
 */
Interp4Command* Interp4Pause::CreateCmd()
{
  return new Interp4Pause();
}


/*!
 *
 */
void Interp4Pause::PrintSyntax() const
{
  cout << "   Pause  NazwaObiektu  Czas trwania[ks]" << endl;
}
