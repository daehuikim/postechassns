#include <string>
using namespace std;
class SVGAttribute {
private:
	string aName;
	string aValue ;
	SVGAttribute* next;
public:
	SVGAttribute();
	void SetName(string name);
	string GetName();
	void SetValue(string a);
	string GetValue();
	void SetNext(SVGAttribute* n);
	SVGAttribute* GetNext();
};