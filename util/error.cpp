#include "error.h"

errors::errors(/* args */)
{
    // illegal direct call.
}

errors::~errors()
{

}

errors* errors::creat(const char* func, const char* file, int line, int code, const char* fmt, ...) {
    return nullptr;
}

errors* errors::wrap(const char* func, const char* file, int line, errors* ret, const char* fmt, ...) {
    return nullptr;
}

string errors::description(errors* ret) {
    return "";
}