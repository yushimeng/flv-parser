#include "streambuf.h"

StreamBuf::StreamBuf(/* args */)
{
}

StreamBuf::StreamBuf(char* buf, int len)
{
    assert(buf != nullptr);
    assert(len > 0);
    begin = p = buf;
    end = buf + len;
}

StreamBuf::~StreamBuf()
{
}

int StreamBuf::Remain() {
    return end - p;
}

int StreamBuf::Offset() {
    return p - begin;
}

uint16_t StreamBuf::Read2Bytes()
{
    assert(require(2));
    
    uint16_t value;
    char* pp = (char*)&value;
    pp[1] = *p++;
    pp[0] = *p++;
    
    return value;
}

void StreamBuf::Write4Bytes(uint32_t value)
{
    assert(require(4));
    
    char* pp = (char*)&value;
    *p++ = pp[3];
    *p++ = pp[2];
    *p++ = pp[1];
    *p++ = pp[0];
}

bool StreamBuf::require(int size) {
    return Remain() >= size;
}
void StreamBuf::write_string(string value)
{
    if (value.empty()) {
        return;
    }

    assert(require((int)value.length()));
    
    memcpy(p, value.data(), value.length());
    p += value.length();
}

string StreamBuf::read_string(int len)
{
    assert(require(len));
    
    std::string value;
    value.append(p, len);
    
    p += len;
    
    return value;
}
void StreamBuf::Write8Bytes(int64_t value)
{
    assert(require(8));
    
    char* pp = (char*)&value;
    *p++ = pp[7];
    *p++ = pp[6];
    *p++ = pp[5];
    *p++ = pp[4];
    *p++ = pp[3];
    *p++ = pp[2];
    *p++ = pp[1];
    *p++ = pp[0];
}

int64_t StreamBuf::Read8Bytes()
{
    assert(require(8));
    
    int64_t value;
    char* pp = (char*)&value;
    pp[7] = *p++;
    pp[6] = *p++;
    pp[5] = *p++;
    pp[4] = *p++;
    pp[3] = *p++;
    pp[2] = *p++;
    pp[1] = *p++;
    pp[0] = *p++;
    
    return value;
}
void StreamBuf::Write1Bytes(uint8_t value)
{
    assert(require(1));
    
    *p++ = value;
}

void StreamBuf::Write2Bytes(uint16_t value)
{
    assert(require(2));
    
    char* pp = (char*)&value;
    *p++ = pp[1];
    *p++ = pp[0];
}

bool StreamBuf::empty()
{
    return !begin || (p >= end);
}

char StreamBuf::Read1Byte() {
    assert(end > p);
    return *p++;
}

uint32_t StreamBuf::Read3Bytes()
{
    assert(end > p + 3);
    uint32_t value = 0x00;
    char* pp = (char*)&value;
    pp[2] = *p++;
    pp[1] = *p++;
    pp[0] = *p++;
    
    return value;
}

uint32_t StreamBuf::Read4Bytes()
{
    assert(end > p + 4);
    
    uint32_t value;
    char* pp = (char*)&value;
    pp[3] = *p++;
    pp[2] = *p++;
    pp[1] = *p++;
    pp[0] = *p++;
    
    return value;
}

char *StreamBuf::ReadSlice(int size) {
    assert(size >= 0);
    assert(end - p >= size);

    char *t = p;
    p += size;
    return t;
}

void StreamBuf::Skip(int size) {
    // assert(size >= 0);
    assert(p+size <= end);
    assert(p+size >= begin);

    p += size;
    return;
}