#include <string>
using namespace std;
class SVGObject;

class SVGObjectList {
private:
	SVGObject *apHead;
	SVGObject *aTail;
	int aSize=0;
public:
	SVGObjectList();
	void AddSvgObject(SVGObject* pObject);
	void RemoveSvgObject(SVGObject* pObject);
	void SetHead( SVGObject* pHead);
	SVGObject* GetHead();
	int GetSize();
	void setSize(int a);
	void Clear();
};