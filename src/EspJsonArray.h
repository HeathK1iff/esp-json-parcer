#ifndef JSON_ARRAY_H
#define JSON_ARRAY_H

#include "EspJsonBasic.h"

class EspJsonArray : public EspJsonBasic {
private:
	EspJsonBasic* _root;
	EspJsonBasic* _last;
	int _count;
public:
	EspJsonArray();
	~EspJsonArray();
	void addItem(EspJsonBasic* item);
	EspJsonBasic* getItem(int index);
	virtual const char* className();
	int getCount();
};

#endif // ! JSON_ARRAY_H