#include "EspJsonObject.h"
#include <string.h>

#ifdef ESP32
#include <stdlib_noniso.h>
#else
#include <stdlib.h>
#endif


JsonObject::JsonObject() {
	_root = nullptr;
	_last = nullptr;
	_autoFree = false;
}

char* JsonObject::_nextKey(const char* key, char* buf) {
	char* ptrKey = (char*)key;
	int size = 0;

	while ((ptrKey[0] != '.') && (ptrKey[0] != '\0')) {
		size++;
		ptrKey++;
	}
	
	ptrKey++;
	strncpy(buf, key, size);
	buf[size] = '\0';
	
	if (strlen(key) == size) {
		return nullptr;
	}
	else {
		return ptrKey;
	}	
}

int JsonObject::_parceArrayKey(const char* key, char* field) {
	char* ptrKey = (char*)key;
	int size = 0;
	int index = -1;
	while (ptrKey[0] != '\0') {
		if (ptrKey[0] == '[') {
			ptrKey++;
			int indexSize = 0;
			char* indexPtr = ptrKey;

			while ((ptrKey[0] != ']') && (ptrKey[0] != '\0')) {
				ptrKey++;
				indexSize++;
			}

			char buf[20];
			strncpy(buf, indexPtr, indexSize);
			index = atoi(buf);
			break;
		}
		ptrKey++;
		size++;
	}

	strncpy(field, key, size);
	field[size] = '\0';
	return index;
}

JsonObject::~JsonObject() {
	if (_root != nullptr)
		delete _root;
}

EspJsonPair* JsonObject::createPair(EspJsonValue* key) {
	EspJsonPair* newLast = new EspJsonPair(key);

	if (_last != nullptr) {
		_last->setChild(newLast);
	}
	else {
		_root = newLast;
	}

	_last = newLast;
	return _last;
}

EspJsonValue* JsonObject::getValuePtr(const char* key)
{
	char bufKey[20];
	char* pKey = _nextKey(key, bufKey);

	char bufKeyArr[20];
	int index = _parceArrayKey(bufKey, bufKeyArr);

	EspJsonPair* item = _root;
	EspJsonBasic* found = nullptr;

	while (item != nullptr) {
		if (item->isKey(bufKeyArr))
		{
			found = item->getValue();
			break;
		}
		item = (EspJsonPair*)item->getChild();
	}

	if (index >= 0) {
		found = ((EspJsonArray*)found)->getItem(index);
	}

	if (pKey != nullptr)
		return ((JsonObject*)found)->getValuePtr(pKey);


	return (EspJsonValue*)found;
}