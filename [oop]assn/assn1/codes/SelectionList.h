#include <string>
#include <fstream>

using namespace std;
class SVGObject;
class Selection;
class SVGAttributeList;

class SelectionList {
private:
	Selection * apHead;
	Selection *aTail;
	Selection *next;
	int aSize = 0;
public:
	SelectionList();
	void AddSelection(Selection* pSelection);
	void RemoveSelection(Selection* pSelection);
	void Clear();
	void SetHead(Selection* pHead);
	Selection* GetHead();
	int GetSize();
	void PrintList(SVGObject* svg);
	void Selected(SVGObject* svg);
	void PrintListw(SVGObject* svg);
	void PrintListf(SVGObject* svg,ofstream &outfile);
};