#ifndef COMMAND4MOVE_HH
#define COMMAND4MOVE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include <string>
#include "Interp4Command.hh"

/*!
 * \file
 * \brief Definicja klasy Interp4Move
 *
 * Plik zawiera definicję klasy Interp4Move ...
 */

/*!
 * \brief Modeluje polecenie dla robota mobilnego, które wymusza jego ruch do przodu
 *
 *  Klasa modeluje ...
 */
class Interp4Move: public Interp4Command {
  /*!
   * 	\brief Parametry klasy 
   * 	\param _Speed_mmS - predkosc poruszania sie jednostki wyrazona w mm/s
   * 	\param nazwa_obiektu - przechowuje nazwe aktualnie poruszajacego sie obiektu
   * 	\param dlugosc_drogi - dlugosc o jaka nalezy przesunac obiekt wyrazona w mm
   * 
   */
   
  double  _Speed_mmS;
  std::string sName;
  double dlugosc_drogi;
  
  
 public:
  /*!
   * \brief
   */
  Interp4Move();  
  /*!
   * \brief Wyświetla postać bieżącego polecenia (nazwę oraz wartości parametrów)
   */
  virtual void PrintCmd() const override ;
  /*!
   * \brief Wyświetla składnię polecenia
   */
  virtual void PrintSyntax() const override ;
  /*!
   * \brief Wyświetla nazwę polecenia
   */
  virtual const char* GetCmdName() const override ;
  /*!
   * \brief Wykonuje polecenie oraz wizualizuje jego realizację
   */
  virtual bool ExecCmd( Scene *pScena) const override ;
  /*!
   * \brief Czyta wartości parametrów danego polecenia
   */
  virtual bool ReadParams(std::istream& Strm_CmdsList) override ;
  /*!
   * \brief Wczytuje wartości parametrów. Przyjmuje nastepujace parametry:
   * \param Strm_CmdsList - adres strumienia wejsciowego
   */
  virtual void PrintParams(){}
  /*!
   * \brief
   *
   *  Wypisuje wczytane parametry w terminalu.
   */
  static Interp4Command* CreateCmd();
 };

#endif
