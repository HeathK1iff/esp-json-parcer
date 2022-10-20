#include "EspJsonBasic.h"

#ifndef JSON_VALUE_H
#define JSON_VALUE_H

class EspJsonValue : public EspJsonBasic {
private:
	char* _valPtr;
	int _size;
public:
	EspJsonValue(char* valPtr, int size);
	char* getValuePtr();
	int getSize();
	virtual const char* className();
};

#endif;