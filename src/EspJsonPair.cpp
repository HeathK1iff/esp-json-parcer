#include "EspJsonPair.h"
#include <string.h>

EspJsonPair::EspJsonPair(EspJsonValue* key) {
	_key = key;
	_val = nullptr;
}

EspJsonPair::~EspJsonPair() {
	if (_key != nullptr)
		delete _key;
	
	_key = nullptr;

	if (_val != nullptr)
		delete _val;

	_val = nullptr;
}

void EspJsonPair::assignVal(EspJsonBasic* val) {
	_val = val;
}

bool EspJsonPair::isKey(const char* key) {
	if (strlen(key) != _key->getSize())
		return false;

	const char* ptrKey = key;
	char* ptrInKey = _key->getValuePtr();

	while (ptrKey[0] != '\0')
	{
		if (ptrKey[0] != ptrInKey[0])
			return false;

		ptrKey++;
		ptrInKey++;
	}

	return true;
}

EspJsonBasic* EspJsonPair::getValue() {
	return _val;
}

const char* EspJsonPair::className() {
	return "EspJsonPair";
}