#include "EspJsonScanner.h"

bool EspJsonScanner::_isDigit(char chr) {
	int i = 0;
	while (i < DIGITS_LENGTH) {
		if (_digits[i] == chr)
			return true;
		i++;
	}
	return false;
}

bool EspJsonScanner::_isDigits(char* buf, int len) {
	for (int i = 0; i < len; i++) {
		if (!_isDigit(buf[i])) {
			return false;
		}
	}
	return true;
}

bool EspJsonScanner::_isReserved(char symbol) {
	int i = 0;
	while (i < RESERVED_LENGTH) {
		if (_reserved_symbols[i] == symbol)
			return true;
		i++;
	}
	return false;
}

TokenType EspJsonScanner::_getTokenType(char symbol) {

	if (symbol == BEGIN_BRACKET) {
		return ttBraceBegin;
	}
	else
		if (symbol == END_BRACKET) {
			return ttBraceEnd;
		}
		else
			if (symbol == DOT_DOT) {
				return ttColon;
			}
			else
				if (symbol == BEGIN_HARD_BRACKET) {
					return ttSquareBracketBegin;
				}
				else
					if (symbol == END_HARD_BRACKET) {
						return ttSquareBracketEnd;
					}
					else
						if (symbol == COMMA) {
							return ttComma;
						}
						else
							if (symbol == END_CHAR) {
								return ttEndChar;
							}
							else
							{
								return ttUndefined;
							}
}


EspJsonScanner::EspJsonScanner(char* text) {
	_text = text;
	_ptr = _text;
	_len = 0;
}

Token EspJsonScanner::nextToken() {
	Token token;

	token.length = 0;
	token.type = ttUndefined;
	token.reserved = false;
	token.token = _ptr;

	bool quoteMark = false;
	while ((_ptr[0] != '\0') && (!_isReserved(_ptr[0]))) {
		if (_ptr[0] == '\"') {
			token.token++;
			_ptr++;
			while ((_ptr[0] != '\"') && (_ptr[0] != '\0')) {
				token.length++;
				_ptr++;
			};
			_ptr++;
			break;
		}

		if ((_ptr[0] == SPACE_CHAR) && (_ptr == token.token)) {
			token.token++;
			_ptr++;
			continue;

		}
		token.length++;
		_ptr++;
	}

	if (token.length > 0) {
		if ((token.length == 1) && (token.token[0] == SPACE_CHAR)) {
			token.type = ttSpaceChar;
		}
		else
			token.type = ttWord;
	}


	if (_isReserved(token.token[0])) {
		token.reserved = true;
		token.type = _getTokenType(token.token[0]);
		token.length = 1;
		if (token.type != ttEndChar)
			_ptr++;
		return token;
	}

	if (_isDigits(token.token, token.length)) {
		token.type = ttNumber;
		return token;
	}

	return token;
}
