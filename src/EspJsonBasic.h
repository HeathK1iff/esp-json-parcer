#ifndef JSON_BASIC_H
#define JSON_BASIC_H

class EspJsonBasic {
private:
	EspJsonBasic* _child;
	EspJsonBasic* _parent;

protected:
	bool _autoFree;

public:
	EspJsonBasic();

	EspJsonBasic* getChild();
	void setChild(EspJsonBasic* child);
	
	EspJsonBasic* getParent();
	void setParent(EspJsonBasic* parent);

	virtual ~EspJsonBasic();
};

#endif