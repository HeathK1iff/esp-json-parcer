#include "EspJsonValue.h"

EspJsonValue::EspJsonValue(char* valPtr, int size) {
	_valPtr = valPtr;
	_size = size;
}

char* EspJsonValue::getValuePtr() {
	return _valPtr;
}

int EspJsonValue::getSize() {
	return _size;
}

const char* EspJsonValue::className() {
	return "EspJsonValue";
}