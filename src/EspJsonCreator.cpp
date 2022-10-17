#include "EspJsonCreator.h"

char* EspJsonCreator::write(char* ptr, char* text){
  char* ptrResult = strcat(ptr, text);
  return ++ptrResult;
}

char* EspJsonCreator::writeTextToken(char* text, bool quotes){
  if (quotes)
    _ptr = write(_ptr, "\"");
      
  _ptr = write(_ptr, text);
      
  if (quotes)
    _ptr = write(_ptr, "\"");
  
  return _ptr;
}

EspJsonCreator::EspJsonCreator(char* buffer, int size){
  _buffer = buffer;
  memset(_buffer, '\0', size);
  _ptr = _buffer;
  _ptr = write(_ptr, "{");
  _empty = true; 
}

void EspJsonCreator::putText(char* name, char* value, bool valueQuotes){
  if (!_empty){
    _ptr = write(_ptr, ",");
  }

  _ptr = writeTextToken(name, true);
  _ptr = write(_ptr, ":");
  _ptr = writeTextToken(value, valueQuotes);
  _empty = false;
}

void EspJsonCreator::put(const char* name, char* value){
   putText((char*) name,  value, true);
}

 void EspJsonCreator::put(const char* name, const char* value){
    putText((char*) name,  (char*) value, true);
 }

void EspJsonCreator::put(char* name, int value){
  char buf[18];
  itoa(value, buf, 10);
  putText(name, buf, false);
}

char* EspJsonCreator::toJson(){
  _ptr = write(_ptr, "}");
  return _buffer;
}
