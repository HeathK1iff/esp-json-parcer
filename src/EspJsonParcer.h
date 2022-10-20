#ifndef ESP_JSON_PARCER_H
#define ESP_JSON_PARCER_H

#include "EspJsonObject.h"
#include "EspJsonScanner.h"

class EspJsonParcer {
private:
	EspJsonScanner* _scanner;
	JsonObject* _root;
	JsonObject* _current;
	EspJsonPair* _currentPair;
	EspJsonArray* _currentArray;
	bool _isError;
	
	void Value(Token prevToken);
	void BraceBegin(Token prevToken);
	void BraceEnd(Token prevToken);
	void Colon(Token prevToken);
	void SquareBracketBegin(Token prevToken);
	void SquareBracketEnd(Token prevToken);
	void Comma(Token prevToken);
public:
	EspJsonParcer(char* text);
	~EspJsonParcer();

	bool parce();
	bool getValue(const char* key, char* dest);
	int getIntValue(const char* key);
	double getFloatValue(const char* key);
	int getArraySize(const char* key);

};

#endif // !ESP_JSON_PARCER_H



