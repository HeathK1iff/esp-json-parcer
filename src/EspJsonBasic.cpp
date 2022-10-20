#include "EspJsonBasic.h"
#include "string.h"

EspJsonBasic::EspJsonBasic() {
	_child = nullptr;
	_parent = nullptr;
	_autoFree = true;
}

void EspJsonBasic::setChild(EspJsonBasic* child) {
	if (child != nullptr)
		child->setParent(this);
	
	_child = child;
}

EspJsonBasic* EspJsonBasic::getChild() {
	return _child;
}

EspJsonBasic* EspJsonBasic::getParent() {
	return _parent;
}

void EspJsonBasic::setParent(EspJsonBasic* parent) {
	_parent = parent;
}

bool EspJsonBasic::isClass(const char* name) {
	return (strcmp(name, this->className()) == 0);
}


const char* EspJsonBasic::className() {
	return "EspJsonBasic";
}


EspJsonBasic::~EspJsonBasic() {
	if ((_autoFree) && (_child != nullptr))
		delete _child;
}
