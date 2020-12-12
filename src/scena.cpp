#include <iostream>
#include <string>
#include <map>
#include <memory>

using namespace std;


/*!
 * Zawiera przykład definicji klasy Scene z wykorzystaniem szablonu
 * std::map<> i wskaźników dzielonych jako kolekcji obiektów mobilnych.
 * Przykład zawiera też użycie metody std::map<>::find().
 * Należy zwrócić uwagę wszystkie obiekty stworzone
 * w sposób dynamiczny są poprawnie poddawane destrukcji.
 */


class MobileObj {
  string _Name;
 public:
  const string& GetName() const { return _Name; }
  void SetName(const char* sName) { _Name = sName; }  

  MobileObj() { cout << "+++ MobileObj" << endl; }
  MobileObj(const char* sName): _Name(sName) { cout << "+++ MobileObj" << endl; }  
  ~MobileObj() { cout << "--- MobileObj" << endl; }
};


typedef map<string,shared_ptr<MobileObj>> Set0MobileObjs; // Set of Mobile Objets 

class Scene {
    Set0MobileObjs   _Set0MobObjs;
   public:
    const Set0MobileObjs & GetMobObjs() const { return _Set0MobObjs; }
    void Add(shared_ptr<MobileObj> &PMobObj)
                   { _Set0MobObjs.insert(pair<string,shared_ptr<MobileObj>>(PMobObj->GetName(),PMobObj)); }
    bool Find(const char* sName, shared_ptr<MobileObj> &PMobObj)
     {
        Set0MobileObjs::const_iterator Iter = _Set0MobObjs.find(sName);
	if (Iter == _Set0MobObjs.end()) return false;
	PMobObj = Iter->second;
	return true;
     }
};



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

