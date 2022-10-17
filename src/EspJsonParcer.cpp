#include "EspJsonParcer.h"
#include <string.h>

#ifdef ESP32
#include <stdlib_noniso.h>
#else
#include <stdlib.h>
#endif


void EspJsonParcer::Value(Token prevToken) {
	Token token = _scanner->nextToken();

	switch (token.type) {
	case ttColon:
		Colon(token);
		break;
	case ttComma:
		Comma(token);
		break;
	case ttBraceEnd: {
		BraceEnd(token);
	} break;
	case ttSquareBracketEnd: {
		SquareBracketEnd(token);
	} break;
	}
}

void EspJsonParcer::BraceBegin(Token prevToken) {
	Token token = _scanner->nextToken();

	if (_root == nullptr) {	
		_root = new JsonObject();
		_current = _root;
	}

	switch (token.type) {
	case ttNumber:
	case ttWord: {
		_currentPair = _current->createPair(new EspJsonValue(token.token, token.length));
		Value(token);
	}
	break;
	default:
		_isError = true;
		break;
	}
}

void EspJsonParcer::BraceEnd(Token prevToken) {
	Token token = _scanner->nextToken();
	_current = (JsonObject*)_current->getParent();
	
	switch (token.type) {
	case ttComma:
		Comma(token);
		break;
	case ttBraceEnd:
		BraceEnd(token);
		break;
	case ttSquareBracketEnd:
		SquareBracketEnd(token);
		break;
	case ttEndChar:
		break;
	default:
		_isError = true;
		break;
	}
};

void EspJsonParcer::Colon(Token prevToken) {
	Token token = _scanner->nextToken();

	switch (token.type) {
	case ttNumber:
	case ttWord: {
		_currentPair->assignVal(new EspJsonValue(token.token, token.length));
		_currentPair = nullptr;
		Value(token);
	} break;
	case ttBraceBegin: {
		JsonObject* newObj = new JsonObject();
		_current->setChild(newObj);
		_current = newObj;

		_currentPair->assignVal(newObj);
		_currentPair = nullptr;

		BraceBegin(token);
	}
	break;
	case ttSquareBracketBegin:
		_currentArray = new EspJsonArray();
		_currentArray->setParent(_current);
		_currentPair->assignVal(_currentArray);
		_currentPair = nullptr;

		SquareBracketBegin(token);
		break;
	default:
		_isError = true;
		break;
	}
}

void EspJsonParcer::SquareBracketBegin(Token prevToken) {
	Token token = _scanner->nextToken();
	
	switch (token.type) {
	case ttNumber:
	case ttWord:
		_currentArray->addItem(new EspJsonValue(token.token, token.length));
		Value(token);
		break;
	case ttBraceBegin: {
		JsonObject* newObj = new JsonObject();
		_current->setChild(newObj);
		_current = newObj;
		_currentArray->addItem(newObj);

		BraceBegin(token); }
		break;
	case ttSquareBracketEnd:
		SquareBracketEnd(token);
		break;
	default:
		_isError = true;
		break;
	}
}

void EspJsonParcer::SquareBracketEnd(Token prevToken) {
	if (_currentArray != nullptr) {
		_current = (JsonObject*)_currentArray->getParent();
	}
	else {
		_isError = true;
		return;
	}
	_currentArray = nullptr;

	Token token = _scanner->nextToken();

	switch (token.type) {
	case ttComma:
		Comma(token);
		break;
	case ttBraceEnd:
		BraceEnd(token);
		break;
	default:
		_isError = true;
		break;
	}
}

void EspJsonParcer::Comma(Token prevToken) {
	_currentPair = nullptr;

	Token token = _scanner->nextToken();

	switch (token.type) {
	case ttNumber:
	case ttWord: {
		if (_currentPair == nullptr) {
			_currentPair = _current->createPair(new EspJsonValue(token.token, token.length));
		}
		else
		if (_currentArray != nullptr) {
			_currentArray->addItem(new EspJsonValue(token.token, token.length));
		} 
		Value(token);
	} break;
	case ttBraceBegin: {
		JsonObject* newObj = new JsonObject();
		
		if (_currentArray != nullptr) {
			_currentArray->addItem(newObj);
		}
		else {
			_current->setChild(newObj);	
		}
		
		_current = newObj;

		BraceBegin(token);
	}
		break;
	default:
		_isError = true;
		break;
	}
}

EspJsonParcer::EspJsonParcer(char* text)
{
	_root = nullptr;	
	_current = nullptr;
	_currentPair = nullptr;
	_currentArray = nullptr;
	_isError = false;
	_scanner = new EspJsonScanner(text);
}

EspJsonParcer::~EspJsonParcer() {
	_current = nullptr;
	_currentPair = nullptr;
	_currentArray = nullptr;

	if (_root != nullptr)
		delete _root;
	if (_scanner != nullptr)
		delete _scanner;


}

bool EspJsonParcer::parce() {
	_isError = false;
	Token token = _scanner->nextToken();
	if (token.type == ttBraceBegin)
		BraceBegin(token);
	return !_isError;
};

bool EspJsonParcer::getValue(const char* key, char* dest) {

	EspJsonValue* value = _root->getValuePtr(key);

	if (value != nullptr)
	{
		int strSize = value->getSize() + 1;
		strncpy(dest, value->getValuePtr(), strSize);
		dest[value->getSize()] = '\0';
		return true;
	}

	return false;
}

int EspJsonParcer::getIntValue(const char* key)
{
	EspJsonValue* value = _root->getValuePtr(key);

	if (value != nullptr)
	{
		int strSize = value->getSize() + 1;
		char* buf = new char[strSize];
		strncpy(buf, value->getValuePtr(), strSize);
		buf[value->getSize()] = '\0';
		return atoi(buf);
	}

	return 0;
}

double EspJsonParcer::getFloatValue(const char* key) {
	EspJsonValue* value = _root->getValuePtr(key);

	if (value != nullptr)
	{
		int strSize = value->getSize() + 1;
		char* buf = new char[strSize];
		strncpy(buf, value->getValuePtr(), strSize);
		buf[value->getSize()] = '\0';
		return atof(buf);
	}

	return 0;
}
