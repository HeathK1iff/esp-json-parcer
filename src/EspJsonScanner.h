#ifndef JSON_SCANNER_H
#define JSON_SCANNER_H

#define RESERVED_LENGTH 7
#define DIGITS_LENGTH 10

enum TokenType
{
	ttUndefined,
	ttBraceBegin,
	ttBraceEnd,
	ttColon,
	ttSquareBracketBegin,
	ttSquareBracketEnd,
	ttWord,
	ttComma,
	ttNumber,
	ttEndChar,
	ttSpaceChar
};

struct Token {
	TokenType type;
	bool reserved;
	char* token;
	int length;
};

class EspJsonScanner {
private:
	const char BEGIN_BRACKET = '{';
	const char END_BRACKET = '}';
	const char DOT_DOT = ':';
	const char BEGIN_HARD_BRACKET = '[';
	const char END_HARD_BRACKET = ']';
	const char QUOT_MARK = '\"';
	const char COMMA = ',';
	const char END_CHAR = '\0';
	const char SPACE_CHAR = ' ';

	int _len = 0;
	char* _text;
	char* _ptr;
	const char _reserved_symbols[RESERVED_LENGTH] = { BEGIN_BRACKET, END_BRACKET ,DOT_DOT,
		BEGIN_HARD_BRACKET,END_HARD_BRACKET, COMMA, END_CHAR };
	const char _digits[DIGITS_LENGTH] = { '0', '1' , '2', '3', '4', '5', '6', '7', '8', '9' };

	bool _isDigit(char chr);
	bool _isDigits(char* buf, int len);
	bool _isReserved(char symbol);
	TokenType _getTokenType(char symbol);

public:
	EspJsonScanner(char* text);
	
	Token nextToken();
};

#endif // !JSON_SCANNER_H