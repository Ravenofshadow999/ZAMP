#ifndef COMMAND4SET_HH
#define COMMAND4SET_HH

#ifndef _GNUG__
# pragma interface
# pragma implementation
#endif

#include <string>
#include "Interp4Command.hh"

/*!
 * \file
 * \brief Definicja klasy Interp4Set
 *
 * Plik zawiera definicję klasy Interp4Set ...
 */

/*!
 * \brief Modeluje polecenie dla robota mobilnego, które wymusza jego ruch do przodu
 *
 *  Klasa modeluje ...
 */
class Interp4Set: public Interp4Command {
  /*! 
   *  \brief Klasa odpowiedzialna za ustawienie wybranego obiektu w zadanym miejscu na scenie i zadanej orientacji.
   * \param wsp_x - przechowuje wspolrzedna x obiektu. Wyrazone w mm.
   * \param wsp_y - przechowuje wspolrzedna y obiektu. Wyrazone w mm.
   * \param rot_z - przechowuje kat obrotu obiektu wokol osi z. Wyrazone w stopniach.
   * \param nazwa_obiektu - przechowuje nazwe obracanego obiektu.
   * 
   */
   
  double  wsp_x;
  double wsp_y;
  double rot_z;
  std::string nazwa_obiektu;
  
 public:
  /*!
   * \brief
   */
  Interp4Set();  
  /*!
   * \brief Wyświetla postać bieżącego polecenia (nazwę oraz wartości parametrów)
   */
  virtual void PrintCmd() const;
  /*!
   * \brief Wyświetla składnię polecenia
   */
  virtual void PrintSyntax() const;
  /*!
   * \brief Wyświetla nazwę polecenia
   */
  virtual const char* GetCmdName() const;
  /*!
   * \brief Wykonuje polecenie oraz wizualizuje jego realizację
   */
  virtual bool ExecCmd( MobileObj  *pMobObj, int Socket) const;
  /*!
   * \brief Czyta wartości parametrów danego polecenia
   */
  virtual bool ReadParams(std::istream& Strm_CmdsList);
  /*!
   * \brief Wyświetla wartości wczytanych parametrów
   */
  virtual void PrintParams() {}
  /*!
   * \brief
   *
   *  Ta metoda nie musi być zdefiniowna w klasie bazowej.
   */
  static Interp4Command* CreateCmd();
 };

#endif
