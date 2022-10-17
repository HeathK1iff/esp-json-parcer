#ifndef JSON_CREATOR_H
#define JSON_CREATOR_H

#include <stdio.h>
#include <string.h>

#ifdef ESP32
#include <stdlib_noniso.h>
#else
#include <stdlib.h>
#endif

class EspJsonCreator{
  private:
    char* _buffer;
    char* _ptr;
    bool _empty;

    char* write(char* ptr, char* text);
    char* writeTextToken(char* text, bool quotes);
    void putText(char* name, char* value, bool valueQuotes);

  public:
    EspJsonCreator(char* buffer, int size);
    
    void put(const char* name, char* value);
    void put(const char* name, const char* value);
    void put(char* name, int value);

    char* toJson();
};

#endif