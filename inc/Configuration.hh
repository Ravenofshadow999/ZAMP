#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH


#include <cassert>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <string>

#include "Set4LibInterfaces.hh"
#include "Scene.hh"
#include "Vector3D.hh"

/*!
 * \file
 * \brief Zawiera definicję klasy Configuration
 */

/*!
 * \brief przechowuje wskazniki na mape i scene
 *
 *  Przechowuje wskazniki na mape i scene
 */



class Configuration {

Set4LibInterfaces 	*pSet4Libs;
Scene			*pScene;

public: 
	/*!
	* Konstruktor klasy.
	*/ 
	Configuration(Set4LibInterfaces *rSet4Libs, Scene *rScene)
	{
		pSet4Libs = rSet4Libs;
		pScene = rScene;
		//std::cout << "[+] Konstruktor Configuration" << std::endl;
	}
	
	/*!
    * \brief Dodaje biblioteke do listy
    */ 
  	void AddLib(std::string sName)
  	{
		
  		std::shared_ptr<LibInterface> Lib = std::make_shared<LibInterface>(sName);
  		//std::cout << "Lib: " << Lib << std::endl;
		pSet4Libs->Add(Lib);
		//std::cout << "configuration.hh dodano biblioteke" << std::endl;
  	}
  	
  	/*!
    * \brief Tworzy nowy obiekt i dodaje go do listy obiektow na scenie
    */ 
  	void CreateObject(std::string sName, Vector3D _Pos, Vector3D _RGB)
  	{
  		std::shared_ptr<MobileObj> NewObject = std::make_shared<MobileObj>(sName, _Pos, _RGB);
		pScene->Add(NewObject);
		//std::cout << "configuration.hh stworzono obiekt" << std::endl;
  	}
};


#endif
