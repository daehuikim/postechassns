#include <string>

using namespace std;
class SVGObject;

class Selection {
private:
	SVGObject *apSVGobject;
	Selection *next;
public:
	Selection();
	void SetsvgObject(SVGObject* psvgObject);
	SVGObject* GetsvgObject();
	void SetNext(Selection* n);
	Selection* GetNext();
};