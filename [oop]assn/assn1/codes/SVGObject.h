#include <string>
using namespace std;
class SVGObjectList;
class AttributeList;
class SVGAttribute;
class SVGAttributeList;

class SVGObject {
private:
	string aTagName;
	SVGObject* apParent;
	SVGObject* next;
	SVGObjectList* apChildList; 
	SVGAttributeList* apAttributeList;
public:
	SVGObject();
	void AppendChild(SVGObject* pChild);
	void AddAttribute(SVGAttribute* pAttribute);
	void SetTagName(string tagName);
	string GetTagName();
	void SetNext(SVGObject* next);
	SVGObject* GetNext();
	void SetChildlist(SVGObjectList*list);
	SVGObjectList* Getchildlist();
	void SetParent(SVGObject* parent);
	SVGObject* GetParent();
	SVGAttribute* GetHeadAttribute();
	SVGObject* GetFirstChild();
	SVGAttributeList* GetAttributeList();
	void SetAttributeList(SVGAttributeList* al);
	void SetHeadAttribute(SVGAttribute* at);
};