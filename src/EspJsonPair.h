#ifndef  JSON_PAIR_H
#define JSON_PAIR_H

#include "EspJsonBasic.h"
#include "EspJsonValue.h"

class EspJsonPair : public EspJsonBasic {
private:
	EspJsonValue* _key;
	EspJsonBasic* _val;
public:
	EspJsonPair(EspJsonValue* key);
	~EspJsonPair();
	void assignVal(EspJsonBasic* val);
	bool isKey(const char* key);
	EspJsonBasic* getValue();
	virtual const char* className();
};

#endif // ! JSON_PAIR_H
