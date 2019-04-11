#include<string>

class SVGAttribute;
class SVGAttributeList {
private:
	SVGAttribute *apHead;
	SVGAttribute *aTail;
	int aSize=0;
public:
	SVGAttributeList();
	void AddSvgAttribute(SVGAttribute* pAttribute);
	void SetHead(SVGAttribute*pHead);
	SVGAttribute* GetHead();
	int GetSize();
};