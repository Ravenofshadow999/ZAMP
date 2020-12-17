#ifndef SCENE_HH
#define SCENE_HH

#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <sstream>
#include <iterator>

#include "AccessControl.hh"
#include "MobileObj.hh"

/*!
 * Zawiera definicje klasy Scene z wykorzystaniem szablonu
 * std::map<> i wskaźników dzielonych jako kolekcji obiektów mobilnych.
 * Zawiera też użycie metody std::map<>::find().
 * Należy zwrócić uwagę wszystkie obiekty stworzone
 * w sposób dynamiczny są poprawnie poddawane destrukcji.
 */

/*
class MobileObj {
  string _Name;
 public:
  const string& GetName() const { return _Name; }
  void SetName(const char* sName) { _Name = sName; }  

  MobileObj() { cout << "+++ MobileObj" << endl; }
  MobileObj(const char* sName): _Name(sName) { cout << "+++ MobileObj" << endl; }  
  ~MobileObj() { cout << "--- MobileObj" << endl; }
};
*/

typedef std::map<const std::string, std::shared_ptr<MobileObj>> Set0MobileObjs; // Set of Mobile Objets 

class Scene: public AccessControl {
	/*!
   * 	\brief Parametry klasy 
   * 	\param  _Set0MobObjs - kolekcja obiektow na scenie
   */
    Set0MobileObjs   _Set0MobObjs;
   public:
    /*Scene(): _Container4Objects(3)
    {
      _Set0MobObjs[0].SetCmds(Cmds4Obj1);
      _Set0MobObjs[1].SetCmds(Cmds4Obj2);
      _Set0MobObjs[2].SetCmds(Cmds4Obj3);
    }*/
    const Set0MobileObjs & GetMobObjs() const { return _Set0MobObjs; }
    
    /*!
   * 	\brief Dodanie obiektu do listy
   */
    void Add(std::shared_ptr<MobileObj> &PMobObj)
    { 
		_Set0MobObjs.insert(std::pair<std::string,std::shared_ptr<MobileObj>>(PMobObj->GetName(),PMobObj)); 
	}
	
	/*!
   * 	\brief Znalezienie obiektu na liscie
   */
    bool Find(const std::string &sName, std::shared_ptr<MobileObj> &PMobObj)
     {
        Set0MobileObjs::const_iterator Iter = _Set0MobObjs.find(sName);
	if (Iter == _Set0MobObjs.end()) return false;
	PMobObj = Iter->second;
	return true;
     }
     
    std::stringstream GetObjectsList()
    {
		std::stringstream list;
		for (Set0MobileObjs::const_iterator Iter = _Set0MobObjs.begin(); Iter != _Set0MobObjs.end(); ++Iter)
		{
			list << Iter->first << ' ';
		}
		return list;
	}
     
};

/*

int main()
{
  shared_ptr<MobileObj> PMobObj1 = make_shared<MobileObj>();
  PMobObj1->SetName("Rudy 102");
  shared_ptr<MobileObj> PMobObj2 = make_shared<MobileObj>("Tygrys");
  
  Scene     Scn;
  
  Scn.Add(PMobObj1);
  Scn.Add(PMobObj2);
  
  cout << endl;

  for (const pair<string,shared_ptr<MobileObj>>  &rPair : Scn.GetMobObjs() ) {
    cout << " Obj: " << rPair.second->GetName() << endl;
  }

  cout << endl;
  
  shared_ptr<MobileObj> PMobObjX;

  if (Scn.Find("Rudy 102", PMobObjX)) {
    cout << ":)  Znalazl: " << PMobObjX->GetName() << endl;
  } else {
    cout << ":( Nie znalazl " <<  endl;
  }
  
  cout << endl;  
}
*/
#endif
