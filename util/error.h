#pragma once

#include <string>
using namespace std;
class errors;

#define errors_new(ret, fmt, ...) errors::creat(__FUNCTION__, __FILE__, __LINE__, ret, fmt, ##__VA_ARGS__)
#define errors_wrap(ret, fmt, ...) errors::wrap(__FUNCTION__, __FILE__, __LINE__, ret, fmt, ##__VA_ARGS__)
#define errors_description(ret, fmt, ...) errors::description(__FUNCTION__, __FILE__, __LINE__, ret, fmt, ##__VA_ARGS__)
#define errorsOK  0
typedef errors* error_t;

class errors {
private:
    /* data */
    errors(/* args */);
public:
    ~errors();
    static errors *creat(const char* func, const char* file, int line, int code, const char* fmt, ...);
    static errors *wrap(const char* func, const char* file, int line, errors* ret, const char* fmt, ...);
    static string description(errors* err);
};
