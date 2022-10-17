#include "EspJsonArray.h"

EspJsonArray::EspJsonArray() {
	_root = nullptr;
	_last = nullptr;
	_autoFree = false;
}

EspJsonArray::~EspJsonArray() {
	_last = nullptr;

	if (_root != nullptr)
		delete _root;
	_root = nullptr;
}

void EspJsonArray::addItem(EspJsonBasic* item) {
	if (_last == nullptr) {
		_root = item;
		_last = _root;
		_count = 1;
		return;
	}

	_last->setChild(item);
	_last = item;
	_count++; 
}

EspJsonBasic* EspJsonArray::getItem(int index) {
	int i = 0;
	EspJsonBasic* item = _root;
	while ((i <= index) && (item != nullptr)) {
		if (i == index)
			return item;
		item = item->getChild();
		i++;
	}
	return nullptr;
}