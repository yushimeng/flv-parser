#pragma once
#include <assert.h>
#include <string>

using namespace std;

class StreamBuf
{
private:
    /* data */
    char *p;
    char *begin;
    char *end;
    
private:
    StreamBuf();
public:
    StreamBuf(char* buf, int len);
    ~StreamBuf();
public:
    virtual int Remain();
    virtual char Read1Byte();
    virtual uint32_t Read3Bytes();
    virtual uint32_t Read4Bytes();
    virtual char *ReadSlice(int size);
    virtual void Skip(int size);
    virtual int Offset();
    virtual uint16_t Read2Bytes();
    virtual bool require(int size);
    void Write1Bytes(uint8_t value);
    // virtual void Write1Bytes(uint8_t value);
    virtual void Write2Bytes(uint16_t value);
    virtual void Write4Bytes(uint32_t value);
    virtual bool empty();
    int64_t Read8Bytes();
    void Write8Bytes(int64_t value);
    string read_string(int len);
    void write_string(string value);
};
