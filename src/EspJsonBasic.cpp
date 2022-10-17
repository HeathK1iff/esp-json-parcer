#include "EspJsonBasic.h"

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

EspJsonBasic::~EspJsonBasic() {
	if ((_autoFree) && (_child != nullptr))
		delete _child;
}
