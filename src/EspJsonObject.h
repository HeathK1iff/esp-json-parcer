#ifndef  JSON_OBJECT_H
#define JSON_OBJECT_H

#include "EspJsonPair.h"
#include "EspJsonValue.h"
#include "EspJsonBasic.h"
#include "EspJsonArray.h"

class JsonObject : public EspJsonBasic {
private:
	EspJsonPair* _root;
	EspJsonPair* _last;
	char* _nextKey(const char* key, char* buf);
	int _parceArrayKey(const char* key, char* field);
public:
	JsonObject();
	~JsonObject();
	EspJsonPair* createPair(EspJsonValue* key);
	EspJsonValue* getValuePtr(const char* key);
};

#endif // ! JSON_OBJECT_H
