#pragma once

#include <iostream>
#include <stdio.h>
#include <unordered_map>
#include <unordered_set>
#include <pthread.h>
#include <algorithm>
#include <fstream>
#include "error.h"
#include "streambuf.h"
#include <sstream>
#include "reflect.h"
#include <map>
#include <inttypes.h>
#include "amf.h"

#define CR '\r'
#define LF '\n'
#define CRLF "\r\n"
#define varName(var) #var
#define varType(var) typeid(var).name()
#define freep(p) \
    if (p) { \
        delete(p); \
        p = NULL; \
    } \
    (void)0
using namespace std;
