#ifndef MOBILEOBJ_HH
#define MOBILEOBJ_HH

#include <iostream>
#include <string>
#include "Vector3D.hh"


/*!
 * \file
 * \brief Zawiera definicję klasy MobileObj
 *
 * Plik zawiera definicję klasy MobileObj.
 * 
 */

/*!
 * \brief Odpowiedzialna za przechowywanie podstawowych informacji o obiekcie
 */


   
    class MobileObj {
       
       /*!
        * \brief Współrzędne aktualnej pozycji obiektu.
	*
	* Współrzędne aktualnej pozycji obiektu. Przyjmuje się,
	* że współrzędne wyrażone są w metrach.
        */
       Vector3D _Position;
       /*!
        * \brief Wartosc koloru obiektu
	*
	* Wartosc koloru obiektu wyrazona w RGB
        */
       Vector3D _RGB;
       /*!
        * \brief Wymiary obiektu
	*
	* Wymiary obiektu wyrazone w m
        */
       Vector3D _Wymiary;
       /*!
        * \brief Wartosc kata orientacji obiektu
	*
	* Wartosc kata orientacji obiektu wyrazony w deg
        */
       Vector3D _Kat;

       /*!
        * \brief Nazwa obiektu, która go indentyfikuje.
        *
        * Nazwa obiektu, która go indentyfikuje. Z tego względu musi
        * musi to być nazwa unikalna wśród wszystkich obiektów na scenie.
        */
       std::string  _Name;

     public:
     
		MobileObj(std::string Name, Vector3D Kolor, Vector3D Wym)
		{
			_Name = Name;
			_RGB = Kolor;
			_Wymiary = Wym;
			
			for(int i =0; i < 3; i++)
			{
				_Position[i] = 0;
				_Kat[i] = 0;
			}
			
			std::cout << "MobileObj" << std::endl;
		}
		
		
		
		/*!
       * \brief Udostępnia współrzędne położenia obiektu w trybie tylko do odczytu.
       *
       * Udostępnia współrzędne punktu, który definiuje położenia obiektu
       * w trybie tylko do odczytu.
       * Domyślnie przyjmuje się, że jest to geometryczny środek bryły.
       */
		const Vector3D & GetPositoin_m() const { return _Position; }
		      /*!
       * \brief Zmienia współrzędne położenia obiektu.
       *
       * Zmienia współrzędne punktu, który definiuje położenia obiektu.
       * Domyślnie przyjmuje się, że jest to geometryczny środek bryły.
       * \param[in] rPos_m - współrzędne nowgo położenia. Przyjmuje się,
       *                     że są one wyrażone w metrach.
       */
       void SetPosition_m(const Vector3D &rPos_m) { _Position = rPos_m; }

		const Vector3D & GetKolor() const { return _RGB; }
		void SetKolor(const Vector3D &rKolor){_RGB = rKolor;}
		const Vector3D & GetWymiar() const { return _Wymiary; }
		void SetWymiary(const Vector3D &rWymiary){_Wymiary = rWymiary;}
		const Vector3D & GetKat() const { return _Kat; }
		void SetKat(const Vector3D &rKat){_Kat = rKat;}
		
		
      /*!
       * \brief Udostępnia współrzędne położenia obiektu w trybie modyfikacji.
       *
       * Udostępnia współrzędne punktu, który definiuje położenia obiektu
       * w trybie modyfikacji.
       * Domyślnie przyjmuje się, że jest to geometryczny środek bryły.
       */
       Vector3D & UsePosition_m() { return _Position; }


      /*!
       * \brief Zmienia nazwę obiektu.
       *
       *  Zmienia nazwę obiektu.
       *  \param[in] sName - nowa nazwa obiektu.
       */
       void SetName(const char* sName) { _Name = sName; }
       /*!
        * \brief Udostępnia nazwę obiektu.
	*
	* Udostępnia nazwę obiektu w trybie tylko do odczytu.
        */
       const std::string & GetName() const { return _Name; }
    };
		
     
      /*!
       * \brief Udostępia wartość kąta \e roll.
       *
       * Udostępia wartość kąta \e roll. Jest ona wyrażona w stopniach.
       */
       //double GetAng_Roll_deg() const { return _Ang_Roll_deg; }
      /*!
       * \brief Udostępia wartość kąta \e pitch.
       *
       * Udostępia wartość kąta \e pitch. Jest ona wyrażona w stopniach.
       */
       //double GetAng_Pitch_deg() const { return _Ang_Pitch_deg; }
       /*!
       * \brief Udostępia wartość kąta \e yaw.
       *
       * Udostępia wartość kąta \e yaw. Jest ona wyrażona w stopniach.
       */
       //double GetAng_Yaw_deg() const { return _Ang_Yaw_deg; }

      /*!
       * \brief Zmienia wartość kąta \e roll.
       *
       * Zmienia wartość kąta \e roll.
       * \param[in] Ang_Roll_deg - nowa wartość kąta \e roll wyrażona w stopniach.
       */
       //void SetAng_Roll_deg(double Ang_Roll_deg) { _Ang_Roll_deg = Ang_Roll_deg; }
      /*!
       * \brief Zmienia wartość kąta \e pitch.
       *
       * Zmienia wartość kąta \e pitch.
       * \param[in] Ang_Pitch_deg - nowa wartość kąta \e pitch wyrażona w stopniach.
       */
       //void SetAng_Pitch_deg(double Ang_Pitch_deg) { _Ang_Pitch_deg = Ang_Pitch_deg; }
      /*!
       * \brief Zmienia wartość kąta \e yaw.
       *
       * Zmienia wartość kąta \e yaw.
       * \param[in] Ang_Yaw_deg - nowa wartość kąta \e yaw wyrażona w stopniach.
       */
       //void SetAng_Yaw_deg(double Ang_Yaw_deg) { _Ang_Yaw_deg = Ang_Yaw_deg; }

      



#endif
