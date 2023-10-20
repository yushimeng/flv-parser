
#include <amf.h>
#include <utility>
#include <vector>
#include <sstream>
using namespace std;

// AMF0 marker
#define RTMP_AMF0_Number                     0x00
#define RTMP_AMF0_Boolean                     0x01
#define RTMP_AMF0_String                     0x02
#define RTMP_AMF0_Object                     0x03
#define RTMP_AMF0_MovieClip                 0x04 // reserved, not supported
#define RTMP_AMF0_Null                         0x05
#define RTMP_AMF0_Undefined                 0x06
#define RTMP_AMF0_Reference                 0x07
#define RTMP_AMF0_EcmaArray                 0x08
#define RTMP_AMF0_ObjectEnd                 0x09
#define RTMP_AMF0_StrictArray                 0x0A
#define RTMP_AMF0_Date                         0x0B
#define RTMP_AMF0_LongString                 0x0C
#define RTMP_AMF0_UnSupported                 0x0D
#define RTMP_AMF0_RecordSet                 0x0E // reserved, not supported
#define RTMP_AMF0_XmlDocument                 0x0F
#define RTMP_AMF0_TypedObject                 0x10
// AVM+ object is the AMF3 object.
#define RTMP_AMF0_AVMplusObject             0x11
// origin array whos data takes the same form as LengthValueBytes
#define RTMP_AMF0_OriginStrictArray         0x20

// User defined
#define RTMP_AMF0_Invalid                     0x3F

Amf0Any::Amf0Any()
{
    marker = RTMP_AMF0_Invalid;
}

Amf0Any::~Amf0Any()
{
}

bool Amf0Any::is_string()
{
    return marker == RTMP_AMF0_String;
}

bool Amf0Any::is_boolean()
{
    return marker == RTMP_AMF0_Boolean;
}

bool Amf0Any::is_number()
{
    return marker == RTMP_AMF0_Number;
}

bool Amf0Any::is_null()
{
    return marker == RTMP_AMF0_Null;
}

bool Amf0Any::is_undefined()
{
    return marker == RTMP_AMF0_Undefined;
}

bool Amf0Any::is_object()
{
    return marker == RTMP_AMF0_Object;
}

bool Amf0Any::is_ecma_array()
{
    return marker == RTMP_AMF0_EcmaArray;
}

bool Amf0Any::is_strict_array()
{
    return marker == RTMP_AMF0_StrictArray;
}

bool Amf0Any::is_date()
{
    return marker == RTMP_AMF0_Date;
}

bool Amf0Any::is_complex_object()
{
    return is_object() || is_object_eof() || is_ecma_array() || is_strict_array();
}

string Amf0Any::to_str()
{
    Amf0String* p = dynamic_cast<Amf0String*>(this);
    assert(p != NULL);
    return p->value;
}

const char* Amf0Any::to_str_raw()
{
    Amf0String* p = dynamic_cast<Amf0String*>(this);
    assert(p != NULL);
    return p->value.data();
}

bool Amf0Any::to_boolean()
{
    Amf0Boolean* p = dynamic_cast<Amf0Boolean*>(this);
    assert(p != NULL);
    return p->value;
}

double Amf0Any::to_number()
{
    Amf0Number* p = dynamic_cast<Amf0Number*>(this);
    assert(p != NULL);
    return p->value;
}

int64_t Amf0Any::to_date()
{
    Amf0Date* p = dynamic_cast<Amf0Date*>(this);
    assert(p != NULL);
    return p->date();
}

int16_t Amf0Any::to_date_time_zone()
{
    Amf0Date* p = dynamic_cast<Amf0Date*>(this);
    assert(p != NULL);
    return p->time_zone();
}

Amf0Object* Amf0Any::to_object()
{
    Amf0Object* p = dynamic_cast<Amf0Object*>(this);
    assert(p != NULL);
    return p;
}

Amf0EcmaArray* Amf0Any::to_ecma_array()
{
    Amf0EcmaArray* p = dynamic_cast<Amf0EcmaArray*>(this);
    assert(p != NULL);
    return p;
}

Amf0StrictArray* Amf0Any::to_strict_array()
{
    Amf0StrictArray* p = dynamic_cast<Amf0StrictArray*>(this);
    assert(p != NULL);
    return p;
}

void Amf0Any::set_number(double value)
{
    Amf0Number* p = dynamic_cast<Amf0Number*>(this);
    assert(p != NULL);
    p->value = value;
}

bool Amf0Any::is_object_eof()
{
    return marker == RTMP_AMF0_ObjectEnd;
}

void fill_level_spaces(stringstream& ss, int level)
{
    for (int i = 0; i < level; i++) {
        ss << "    ";
    }
}
void amf0_do_print(Amf0Any* any, stringstream& ss, int level)
{
    std::ios_base::fmtflags oflags = ss.flags();
    
    if (any->is_boolean()) {
        ss << "Boolean " << (any->to_boolean()? "true":"false") << endl;
    } else if (any->is_number()) {
        ss << "Number " << std::fixed << any->to_number() << endl;
    } else if (any->is_string()) {
        ss << "String " << any->to_str() << endl;
    } else if (any->is_date()) {
        ss << "Date " << std::hex << any->to_date()
        << "/" << std::hex << any->to_date_time_zone() << endl;
    } else if (any->is_null()) {
        ss << "Null" << endl;
    } else if (any->is_undefined()) {
        ss << "Undefined" << endl;
    } else if (any->is_ecma_array()) {
        Amf0EcmaArray* obj = any->to_ecma_array();
        ss << "EcmaArray " << "(" << obj->count() << " items)" << endl;
        for (int i = 0; i < obj->count(); i++) {
            fill_level_spaces(ss, level + 1);
            ss << "Elem '" << obj->key_at(i) << "' ";
            if (obj->value_at(i)->is_complex_object()) {
                amf0_do_print(obj->value_at(i), ss, level + 1);
            } else {
                amf0_do_print(obj->value_at(i), ss, 0);
            }
        }
    } else if (any->is_strict_array()) {
        Amf0StrictArray* obj = any->to_strict_array();
        ss << "StrictArray " << "(" << obj->count() << " items)" << endl;
        for (int i = 0; i < obj->count(); i++) {
            fill_level_spaces(ss, level + 1);
            ss << "Elem ";
            if (obj->at(i)->is_complex_object()) {
                amf0_do_print(obj->at(i), ss, level + 1);
            } else {
                amf0_do_print(obj->at(i), ss, 0);
            }
        }
    } else if (any->is_object()) {
        Amf0Object* obj = any->to_object();
        ss << "Object " << "(" << obj->count() << " items)" << endl;
        for (int i = 0; i < obj->count(); i++) {
            fill_level_spaces(ss, level + 1);
            ss << "Property '" << obj->key_at(i) << "' ";
            if (obj->value_at(i)->is_complex_object()) {
                amf0_do_print(obj->value_at(i), ss, level + 1);
            } else {
                amf0_do_print(obj->value_at(i), ss, 0);
            }
        }
    } else {
        ss << "Unknown" << endl;
    }
    
    ss.flags(oflags);
}

char* Amf0Any::human_print(char** pdata, int* psize)
{
    stringstream ss;
    
    ss.precision(1);
    
    amf0_do_print(this, ss, 0);
    
    string str = ss.str();
    if (str.empty()) {
        return NULL;
    }
    
    char* data = new char[str.length() + 1];
    memcpy(data, str.data(), str.length());
    data[str.length()] = 0;
    
    if (pdata) {
        *pdata = data;
    }
    if (psize) {
        *psize = (int)str.length();
    }
    
    return data;
}

// SrsJsonAny* Amf0Any::to_json()
// {
//     switch (marker) {
//         case RTMP_AMF0_String: {
//             return SrsJsonAny::str(to_str().c_str());
//         }
//         case RTMP_AMF0_Boolean: {
//             return SrsJsonAny::boolean(to_boolean());
//         }
//         case RTMP_AMF0_Number: {
//             double dv = to_number();
//             int64_t iv = (int64_t)dv;
//             if (iv == dv) {
//                 return SrsJsonAny::integer(iv);
//             } else {
//                 return SrsJsonAny::number(dv);
//             }
//         }
//         case RTMP_AMF0_Null: {
//             return SrsJsonAny::null();
//         }
//         case RTMP_AMF0_Undefined: {
//             return SrsJsonAny::null();
//         }
//         case RTMP_AMF0_Object: {
//             // amf0 object implements it.
//             assert(false);
//         }
//         case RTMP_AMF0_EcmaArray: {
//             // amf0 ecma array implements it.
//             assert(false);
//         }
//         case RTMP_AMF0_StrictArray: {
//             // amf0 strict array implements it.
//             assert(false);
//         }
//         case RTMP_AMF0_Date: {
//             // TODO: FIXME: implements it.
//             return SrsJsonAny::null();
//         }
//         default: {
//             return SrsJsonAny::null();
//         }
//     }
    
// }

Amf0Any* Amf0Any::str(const char* value)
{
    return new Amf0String(value);
}

Amf0Any* Amf0Any::boolean(bool value)
{
    return new Amf0Boolean(value);
}

Amf0Any* Amf0Any::number(double value)
{
    return new Amf0Number(value);
}

Amf0Any* Amf0Any::null()
{
    return new Amf0Null();
}

Amf0Any* Amf0Any::undefined()
{
    return new Amf0Undefined();
}

Amf0Object* Amf0Any::object()
{
    return new Amf0Object();
}

Amf0Any* Amf0Any::object_eof()
{
    return new Amf0ObjectEOF();
}

Amf0EcmaArray* Amf0Any::ecma_array()
{
    return new Amf0EcmaArray();
}

Amf0StrictArray* Amf0Any::strict_array()
{
    return new Amf0StrictArray();
}

Amf0Any* Amf0Any::date(int64_t value)
{
    return new Amf0Date(value);
}

error_t Amf0Any::discovery(StreamBuf* stream, Amf0Any** ppvalue)
{
    error_t err = errorsOK;
    
    // detect the object-eof specially
    if (amf0_is_object_eof(stream)) {
        *ppvalue = new Amf0ObjectEOF();
        return err;
    }
    
    // marker
    if (!stream->require(1)) {
        return errors_new(-1, "marker requires 1 only %d bytes", stream->Remain());
        // return srs_error_new(-1, "marker requires 1 only %d bytes", stream->Remain());
    }
    
    char marker = stream->Read1Byte();
    
    // backward the 1byte marker.
    stream->Skip(-1);
    
    switch (marker) {
        case RTMP_AMF0_String: {
            *ppvalue = Amf0Any::str();
            return err;
        }
        case RTMP_AMF0_Boolean: {
            *ppvalue = Amf0Any::boolean();
            return err;
        }
        case RTMP_AMF0_Number: {
            *ppvalue = Amf0Any::number();
            return err;
        }
        case RTMP_AMF0_Null: {
            *ppvalue = Amf0Any::null();
            return err;
        }
        case RTMP_AMF0_Undefined: {
            *ppvalue = Amf0Any::undefined();
            return err;
        }
        case RTMP_AMF0_Object: {
            *ppvalue = Amf0Any::object();
            return err;
        }
        case RTMP_AMF0_EcmaArray: {
            *ppvalue = Amf0Any::ecma_array();
            return err;
        }
        case RTMP_AMF0_StrictArray: {
            *ppvalue = Amf0Any::strict_array();
            return err;
        }
        case RTMP_AMF0_Date: {
            *ppvalue = Amf0Any::date();
            return err;
        }
        case RTMP_AMF0_Invalid:
        default: {
            return errors_new(-1, "invalid amf0 message, marker=%#x", marker);
            // return srs_error_new(ERROR_RTMP_AMF0_INVALID, "invalid amf0 message, marker=%#x", marker);
        }
    }
}

UnSortedHashtable::UnSortedHashtable()
{
}

UnSortedHashtable::~UnSortedHashtable()
{
    clear();
}

int UnSortedHashtable::count()
{
    return (int)properties.size();
}

void UnSortedHashtable::clear()
{
    std::vector<Amf0ObjectPropertyType>::iterator it;
    for (it = properties.begin(); it != properties.end(); ++it) {
        Amf0ObjectPropertyType& elem = *it;
        Amf0Any* any = elem.second;
        freep(any);
    }
    properties.clear();
}

string UnSortedHashtable::key_at(int index)
{
    assert(index < count());
    Amf0ObjectPropertyType& elem = properties[index];
    return elem.first;
}

const char* UnSortedHashtable::key_raw_at(int index)
{
    assert(index < count());
    Amf0ObjectPropertyType& elem = properties[index];
    return elem.first.data();
}

Amf0Any* UnSortedHashtable::value_at(int index)
{
    assert(index < count());
    Amf0ObjectPropertyType& elem = properties[index];
    return elem.second;
}

void UnSortedHashtable::set(string key, Amf0Any* value)
{
    std::vector<Amf0ObjectPropertyType>::iterator it;
    
    for (it = properties.begin(); it != properties.end(); ++it) {
        Amf0ObjectPropertyType& elem = *it;
        std::string name = elem.first;
        Amf0Any* any = elem.second;
        
        if (key == name) {
            freep(any);
            it = properties.erase(it);
            break;
        }
    }
    
    if (value) {
        properties.push_back(std::make_pair(key, value));
    }
}

Amf0Any* UnSortedHashtable::get_property(string name)
{
    std::vector<Amf0ObjectPropertyType>::iterator it;
    
    for (it = properties.begin(); it != properties.end(); ++it) {
        Amf0ObjectPropertyType& elem = *it;
        std::string key = elem.first;
        Amf0Any* any = elem.second;
        if (key == name) {
            return any;
        }
    }
    
    return NULL;
}

Amf0Any* UnSortedHashtable::ensure_property_string(string name)
{
    Amf0Any* prop = get_property(name);
    
    if (!prop) {
        return NULL;
    }
    
    if (!prop->is_string()) {
        return NULL;
    }
    
    return prop;
}

Amf0Any* UnSortedHashtable::ensure_property_number(string name)
{
    Amf0Any* prop = get_property(name);
    
    if (!prop) {
        return NULL;
    }
    
    if (!prop->is_number()) {
        return NULL;
    }
    
    return prop;
}

void UnSortedHashtable::remove(string name)
{
    std::vector<Amf0ObjectPropertyType>::iterator it;
    
    for (it = properties.begin(); it != properties.end();) {
        std::string key = it->first;
        Amf0Any* any = it->second;
        
        if (key == name) {
            freep(any);
            
            it = properties.erase(it);
        } else {
            ++it;
        }
    }
}

void UnSortedHashtable::copy(UnSortedHashtable* src)
{
    std::vector<Amf0ObjectPropertyType>::iterator it;
    for (it = src->properties.begin(); it != src->properties.end(); ++it) {
        Amf0ObjectPropertyType& elem = *it;
        std::string key = elem.first;
        Amf0Any* any = elem.second;
        set(key, any->copy());
    }
}

Amf0ObjectEOF::Amf0ObjectEOF()
{
    marker = RTMP_AMF0_ObjectEnd;
}

Amf0ObjectEOF::~Amf0ObjectEOF()
{
}

int Amf0ObjectEOF::total_size()
{
    return Amf0Size::object_eof();
}

error_t Amf0ObjectEOF::read(StreamBuf* stream)
{
    error_t err = errorsOK;
    
    // value
    if (!stream->require(2)) {
        return errors_new(-1, "EOF requires 2 only %d bytes", stream->Remain());
    }
    int16_t temp = stream->Read2Bytes();
    if (temp != 0x00) {
        return errors_new(-1, "EOF invalid marker=%#x", temp);
    }
    
    // marker
    if (!stream->require(1)) {
        return errors_new(-1, "EOF requires 1 only %d bytes", stream->Remain());
    }
    
    char marker = stream->Read1Byte();
    if (marker != RTMP_AMF0_ObjectEnd) {
        return errors_new(-1, "EOF invalid marker=%#x", marker);
    }
    
    return err;
}

error_t Amf0ObjectEOF::write(StreamBuf* stream)
{
    error_t err = errorsOK;
    
    // value
    if (!stream->require(2)) {
        return errors_new(-1, "EOF requires 2 only %d bytes", stream->Remain());
    }
    stream->Write2Bytes(0x00);
    
    // marker
    if (!stream->require(1)) {
        return errors_new(-1, "EOF requires 1 only %d bytes", stream->Remain());
    }
    
    stream->Write1Bytes(RTMP_AMF0_ObjectEnd);
    
    return err;
}

Amf0Any* Amf0ObjectEOF::copy()
{
    return new Amf0ObjectEOF();
}

Amf0Object::Amf0Object()
{
    properties = new UnSortedHashtable();
    eof = new Amf0ObjectEOF();
    marker = RTMP_AMF0_Object;
}

Amf0Object::~Amf0Object()
{
    freep(properties);
    freep(eof);
}

int Amf0Object::total_size()
{
    int size = 1;
    
    for (int i = 0; i < properties->count(); i++){
        std::string name = key_at(i);
        Amf0Any* value = value_at(i);
        
        size += Amf0Size::utf8(name);
        size += Amf0Size::any(value);
    }
    
    size += Amf0Size::object_eof();
    
    return size;
}

error_t Amf0Object::read(StreamBuf* stream)
{
    error_t err = errorsOK;
    
    // marker
    if (!stream->require(1)) {
        return errors_new(-1, "object requires 1 only %d bytes", stream->Remain());
    }
    
    char marker = stream->Read1Byte();
    if (marker != RTMP_AMF0_Object) {
        return errors_new(-1, "object invalid marker=%#x", marker);
    }
    
    // value
    while (!stream->empty()) {
        // detect whether is eof.
        if (amf0_is_object_eof(stream)) {
            Amf0ObjectEOF pbj_eof;
            if ((err = pbj_eof.read(stream)) != errorsOK) {
                return errors_wrap(err, "read EOF");
            }
            break;
        }
        
        // property-name: utf8 string
        std::string property_name;
        if ((err = amf0_read_utf8(stream, property_name)) != errorsOK) {
            return errors_wrap(err, "read property name");
        }
        // property-value: any
        Amf0Any* property_value = NULL;
        if ((err = amf0_read_any(stream, &property_value)) != errorsOK) {
            freep(property_value);
            return errors_wrap(err, "read property value, name=%s", property_name.c_str());
        }
        
        // add property
        this->set(property_name, property_value);
    }
    
    return err;
}

error_t Amf0Object::write(StreamBuf* stream)
{
    error_t err = errorsOK;
    
    // marker
    if (!stream->require(1)) {
        return errors_new(-1, "object requires 1 only %d bytes", stream->Remain());
    }
    
    stream->Write1Bytes(RTMP_AMF0_Object);
    
    // value
    for (int i = 0; i < properties->count(); i++) {
        std::string name = this->key_at(i);
        Amf0Any* any = this->value_at(i);
        
        if ((err = amf0_write_utf8(stream, name)) != errorsOK) {
            return errors_wrap(err, "write property name=%s", name.c_str());
        }
        
        if ((err = amf0_write_any(stream, any)) != errorsOK) {
            return errors_wrap(err, "write property value, name=%s", name.c_str());
        }
    }
    
    if ((err = eof->write(stream)) != errorsOK) {
        return errors_wrap(err, "write EOF");
    }
    
    return err;
}

Amf0Any* Amf0Object::copy()
{
    Amf0Object* copy = new Amf0Object();
    copy->properties->copy(properties);
    return copy;
}

// SrsJsonAny* Amf0Object::to_json()
// {
//     SrsJsonObject* obj = SrsJsonAny::object();
    
//     for (int i = 0; i < properties->count(); i++) {
//         std::string name = this->key_at(i);
//         Amf0Any* any = this->value_at(i);
        
//         obj->set(name, any->to_json());
//     }
    
//     return obj;
// }

void Amf0Object::clear()
{
    properties->clear();
}

int Amf0Object::count()
{
    return properties->count();
}

string Amf0Object::key_at(int index)
{
    return properties->key_at(index);
}

const char* Amf0Object::key_raw_at(int index)
{
    return properties->key_raw_at(index);
}

Amf0Any* Amf0Object::value_at(int index)
{
    return properties->value_at(index);
}

void Amf0Object::set(string key, Amf0Any* value)
{
    properties->set(key, value);
}

Amf0Any* Amf0Object::get_property(string name)
{
    return properties->get_property(name);
}

Amf0Any* Amf0Object::ensure_property_string(string name)
{
    return properties->ensure_property_string(name);
}

Amf0Any* Amf0Object::ensure_property_number(string name)
{
    return properties->ensure_property_number(name);
}

void Amf0Object::remove(string name)
{
    properties->remove(name);
}

Amf0EcmaArray::Amf0EcmaArray()
{
    _count = 0;
    properties = new UnSortedHashtable();
    eof = new Amf0ObjectEOF();
    marker = RTMP_AMF0_EcmaArray;
}

Amf0EcmaArray::~Amf0EcmaArray()
{
    freep(properties);
    freep(eof);
}

int Amf0EcmaArray::total_size()
{
    int size = 1 + 4;
    
    for (int i = 0; i < properties->count(); i++){
        std::string name = key_at(i);
        Amf0Any* value = value_at(i);
        
        size += Amf0Size::utf8(name);
        size += Amf0Size::any(value);
    }
    
    size += Amf0Size::object_eof();
    
    return size;
}

error_t Amf0EcmaArray::read(StreamBuf* stream)
{
    error_t err = errorsOK;
    
    // marker
    if (!stream->require(1)) {
        return errors_new(-1, "requires 1 only %d bytes", stream->Remain());
    }
    
    char marker = stream->Read1Byte();
    if (marker != RTMP_AMF0_EcmaArray) {
        return errors_new(-1, "EcmaArray invalid marker=%#x", marker);
    }
    
    // count
    if (!stream->require(4)) {
        return errors_new(-1, "requires 4 only %d bytes", stream->Remain());
    }
    
    int32_t count = stream->Read4Bytes();
    
    // value
    this->_count = count;
    
    while (!stream->empty()) {
        // detect whether is eof.
        if (amf0_is_object_eof(stream)) {
            Amf0ObjectEOF pbj_eof;
            if ((err = pbj_eof.read(stream)) != errorsOK) {
                return errors_wrap(err, "read EOF");
            }
            break;
        }
        
        // property-name: utf8 string
        std::string property_name;
        if ((err =amf0_read_utf8(stream, property_name)) != errorsOK) {
            return errors_wrap(err, "read property name");
        }
        // property-value: any
        Amf0Any* property_value = NULL;
        if ((err = amf0_read_any(stream, &property_value)) != errorsOK) {
            return errors_wrap(err, "read property value, name=%s", property_name.c_str());
        }
        
        // add property
        this->set(property_name, property_value);
    }
    
    return err;
}

error_t Amf0EcmaArray::write(StreamBuf* stream)
{
    error_t err = errorsOK;
    
    // marker
    if (!stream->require(1)) {
        return errors_new(-1, "requires 1 only %d bytes", stream->Remain());
    }
    
    stream->Write1Bytes(RTMP_AMF0_EcmaArray);
    
    // count
    if (!stream->require(4)) {
        return errors_new(-1, "requires 4 only %d bytes", stream->Remain());
    }
    
    stream->Write4Bytes(this->_count);
    
    // value
    for (int i = 0; i < properties->count(); i++) {
        std::string name = this->key_at(i);
        Amf0Any* any = this->value_at(i);
        
        if ((err = amf0_write_utf8(stream, name)) != errorsOK) {
            return errors_wrap(err, "write property name=%s", name.c_str());
        }
        
        if ((err = amf0_write_any(stream, any)) != errorsOK) {
            return errors_wrap(err, "write property value, name=%s", name.c_str());
        }
    }
    
    if ((err = eof->write(stream)) != errorsOK) {
        return errors_wrap(err, "write EOF");
    }
    
    return err;
}

Amf0Any* Amf0EcmaArray::copy()
{
    Amf0EcmaArray* copy = new Amf0EcmaArray();
    copy->properties->copy(properties);
    copy->_count = _count;
    return copy;
}

// SrsJsonAny* Amf0EcmaArray::to_json()
// {
//     SrsJsonObject* obj = SrsJsonAny::object();
    
//     for (int i = 0; i < properties->count(); i++) {
//         std::string name = this->key_at(i);
//         Amf0Any* any = this->value_at(i);
        
//         obj->set(name, any->to_json());
//     }
    
//     return obj;
// }

void Amf0EcmaArray::clear()
{
    properties->clear();
}

int Amf0EcmaArray::count()
{
    return properties->count();
}

string Amf0EcmaArray::key_at(int index)
{
    return properties->key_at(index);
}

const char* Amf0EcmaArray::key_raw_at(int index)
{
    return properties->key_raw_at(index);
}

Amf0Any* Amf0EcmaArray::value_at(int index)
{
    return properties->value_at(index);
}

void Amf0EcmaArray::set(string key, Amf0Any* value)
{
    properties->set(key, value);
}

Amf0Any* Amf0EcmaArray::get_property(string name)
{
    return properties->get_property(name);
}

Amf0Any* Amf0EcmaArray::ensure_property_string(string name)
{
    return properties->ensure_property_string(name);
}

Amf0Any* Amf0EcmaArray::ensure_property_number(string name)
{
    return properties->ensure_property_number(name);
}

Amf0StrictArray::Amf0StrictArray()
{
    marker = RTMP_AMF0_StrictArray;
    _count = 0;
}

Amf0StrictArray::~Amf0StrictArray()
{
    clear();
}

int Amf0StrictArray::total_size()
{
    int size = 1 + 4;
    
    for (int i = 0; i < (int)properties.size(); i++){
        Amf0Any* any = properties[i];
        size += any->total_size();
    }
    
    return size;
}

error_t Amf0StrictArray::read(StreamBuf* stream)
{
    error_t err = errorsOK;
    
    // marker
    if (!stream->require(1)) {
        return errors_new(-1, "requires 1 only %d bytes", stream->Remain());
    }
    
    char marker = stream->Read1Byte();
    if (marker != RTMP_AMF0_StrictArray) {
        return errors_new(-1, "StrictArray invalid marker=%#x", marker);
    }
    
    // count
    if (!stream->require(4)) {
        return errors_new(-1, "requires 4 only %d bytes", stream->Remain());
    }
    
    int32_t count = stream->Read4Bytes();
    
    // value
    this->_count = count;
    
    for (int i = 0; i < count && !stream->empty(); i++) {
        // property-value: any
        Amf0Any* elem = NULL;
        if ((err = amf0_read_any(stream, &elem)) != errorsOK) {
            return errors_wrap(err, "read property");
        }
        
        // add property
        properties.push_back(elem);
    }
    
    return err;
}

error_t Amf0StrictArray::write(StreamBuf* stream)
{
    error_t err = errorsOK;
    
    // marker
    if (!stream->require(1)) {
        return errors_new(-1, "requires 1 only %d bytes", stream->Remain());
    }
    
    stream->Write1Bytes(RTMP_AMF0_StrictArray);
    
    // count
    if (!stream->require(4)) {
        return errors_new(-1, "requires 4 only %d bytes", stream->Remain());
    }
    
    stream->Write4Bytes(this->_count);
    
    // value
    for (int i = 0; i < (int)properties.size(); i++) {
        Amf0Any* any = properties[i];
        
        if ((err = amf0_write_any(stream, any)) != errorsOK) {
            return errors_wrap(err, "write property");
        }
    }
    
    return err;
}

Amf0Any* Amf0StrictArray::copy()
{
    Amf0StrictArray* copy = new Amf0StrictArray();
    
    std::vector<Amf0Any*>::iterator it;
    for (it = properties.begin(); it != properties.end(); ++it) {
        Amf0Any* any = *it;
        copy->append(any->copy());
    }
    
    copy->_count = _count;
    return copy;
}

// SrsJsonAny* Amf0StrictArray::to_json()
// {
//     SrsJsonArray* arr = SrsJsonAny::array();
    
//     for (int i = 0; i < (int)properties.size(); i++) {
//         Amf0Any* any = properties[i];
        
//         arr->append(any->to_json());
//     }
    
//     return arr;
// }

void Amf0StrictArray::clear()
{
    std::vector<Amf0Any*>::iterator it;
    for (it = properties.begin(); it != properties.end(); ++it) {
        Amf0Any* any = *it;
        freep(any);
    }
    properties.clear();
}

int Amf0StrictArray::count()
{
    return (int)properties.size();
}

Amf0Any* Amf0StrictArray::at(int index)
{
    assert(index < (int)properties.size());
    return properties.at(index);
}

void Amf0StrictArray::append(Amf0Any* any)
{
    properties.push_back(any);
    _count = (int32_t)properties.size();
}

int Amf0Size::utf8(string value)
{
    return (int)(2 + value.length());
}

int Amf0Size::str(string value)
{
    return 1 + Amf0Size::utf8(value);
}

int Amf0Size::number()
{
    return 1 + 8;
}

int Amf0Size::date()
{
    return 1 + 8 + 2;
}

int Amf0Size::null()
{
    return 1;
}

int Amf0Size::undefined()
{
    return 1;
}

int Amf0Size::boolean()
{
    return 1 + 1;
}

int Amf0Size::object(Amf0Object* obj)
{
    if (!obj) {
        return 0;
    }
    
    return obj->total_size();
}

int Amf0Size::object_eof()
{
    return 2 + 1;
}

int Amf0Size::ecma_array(Amf0EcmaArray* arr)
{
    if (!arr) {
        return 0;
    }
    
    return arr->total_size();
}

int Amf0Size::strict_array(Amf0StrictArray* arr)
{
    if (!arr) {
        return 0;
    }
    
    return arr->total_size();
}

int Amf0Size::any(Amf0Any* o)
{
    if (!o) {
        return 0;
    }
    
    return o->total_size();
}

Amf0String::Amf0String(const char* _value)
{
    marker = RTMP_AMF0_String;
    if (_value) {
        value = _value;
    }
}

Amf0String::~Amf0String()
{
}

int Amf0String::total_size()
{
    return Amf0Size::str(value);
}

error_t Amf0String::read(StreamBuf* stream)
{
    return srs_amf0_read_string(stream, value);
}

error_t Amf0String::write(StreamBuf* stream)
{
    return srs_amf0_write_string(stream, value);
}

Amf0Any* Amf0String::copy()
{
    Amf0String* copy = new Amf0String(value.c_str());
    return copy;
}

Amf0Boolean::Amf0Boolean(bool _value)
{
    marker = RTMP_AMF0_Boolean;
    value = _value;
}

Amf0Boolean::~Amf0Boolean()
{
}

int Amf0Boolean::total_size()
{
    return Amf0Size::boolean();
}

error_t Amf0Boolean::read(StreamBuf* stream)
{
    return srs_amf0_read_boolean(stream, value);
}

error_t Amf0Boolean::write(StreamBuf* stream)
{
    return srs_amf0_write_boolean(stream, value);
}

Amf0Any* Amf0Boolean::copy()
{
    Amf0Boolean* copy = new Amf0Boolean(value);
    return copy;
}

Amf0Number::Amf0Number(double _value)
{
    marker = RTMP_AMF0_Number;
    value = _value;
}

Amf0Number::~Amf0Number()
{
}

int Amf0Number::total_size()
{
    return Amf0Size::number();
}

error_t Amf0Number::read(StreamBuf* stream)
{
    return srs_amf0_read_number(stream, value);
}

error_t Amf0Number::write(StreamBuf* stream)
{
    return srs_amf0_write_number(stream, value);
}

Amf0Any* Amf0Number::copy()
{
    Amf0Number* copy = new Amf0Number(value);
    return copy;
}

Amf0Date::Amf0Date(int64_t value)
{
    marker = RTMP_AMF0_Date;
    _date_value = value;
    _time_zone = 0;
}

Amf0Date::~Amf0Date()
{
}

int Amf0Date::total_size()
{
    return Amf0Size::date();
}

error_t Amf0Date::read(StreamBuf* stream)
{
    error_t err = errorsOK;
    
    // marker
    if (!stream->require(1)) {
        return errors_new(-1, "requires 1 only %d bytes", stream->Remain());
    }
    
    char marker = stream->Read1Byte();
    if (marker != RTMP_AMF0_Date) {
        return errors_new(-1, "Date invalid marker=%#x", marker);
    }
    
    // date value
    // An ActionScript Date is serialized as the number of milliseconds
    // elapsed since the epoch of midnight on 1st Jan 1970 in the UTC
    // time zone.
    if (!stream->require(8)) {
        return errors_new(-1, "requires 8 only %d bytes", stream->Remain());
    }
    
    _date_value = stream->Read8Bytes();
    
    // time zone
    // While the design of this type reserves room for time zone offset
    // information, it should not be filled in, nor used, as it is unconventional
    // to change time zones when serializing dates on a network. It is suggested
    // that the time zone be queried independently as needed.
    if (!stream->require(2)) {
        return errors_new(-1, "requires 2 only %d bytes", stream->Remain());
    }
    
    _time_zone = stream->Read2Bytes();
    
    return err;
}

error_t Amf0Date::write(StreamBuf* stream)
{
    error_t err = errorsOK;
    
    // marker
    if (!stream->require(1)) {
        return errors_new(-1, "requires 1 only %d bytes", stream->Remain());
    }
    
    stream->Write1Bytes(RTMP_AMF0_Date);
    
    // date value
    if (!stream->require(8)) {
        return errors_new(-1, "requires 8 only %d bytes", stream->Remain());
    }
    
    stream->Write8Bytes(_date_value);
    
    // time zone
    if (!stream->require(2)) {
        return errors_new(-1, "requires 2 only %d bytes", stream->Remain());
    }
    
    stream->Write2Bytes(_time_zone);
    
    return err;
}

Amf0Any* Amf0Date::copy()
{
    Amf0Date* copy = new Amf0Date(0);
    
    copy->_date_value = _date_value;
    copy->_time_zone = _time_zone;
    
    return copy;
}

int64_t Amf0Date::date()
{
    return _date_value;
}

int16_t Amf0Date::time_zone()
{
    return _time_zone;
}

Amf0Null::Amf0Null()
{
    marker = RTMP_AMF0_Null;
}

Amf0Null::~Amf0Null()
{
}

int Amf0Null::total_size()
{
    return Amf0Size::null();
}

error_t Amf0Null::read(StreamBuf* stream)
{
    return srs_amf0_read_null(stream);
}

error_t Amf0Null::write(StreamBuf* stream)
{
    return srs_amf0_write_null(stream);
}

Amf0Any* Amf0Null::copy()
{
    Amf0Null* copy = new Amf0Null();
    return copy;
}

Amf0Undefined::Amf0Undefined()
{
    marker = RTMP_AMF0_Undefined;
}

Amf0Undefined::~Amf0Undefined()
{
}

int Amf0Undefined::total_size()
{
    return Amf0Size::undefined();
}

error_t Amf0Undefined::read(StreamBuf* stream)
{
    return srs_amf0_read_undefined(stream);
}

error_t Amf0Undefined::write(StreamBuf* stream)
{
    return srs_amf0_write_undefined(stream);
}

Amf0Any* Amf0Undefined::copy()
{
    Amf0Undefined* copy = new Amf0Undefined();
    return copy;
}

error_t amf0_read_any(StreamBuf* stream, Amf0Any** ppvalue)
{
    error_t err = errorsOK;
    
    if ((err = Amf0Any::discovery(stream, ppvalue)) != errorsOK) {
        return errors_wrap(err, "discovery");
    }
    
    assert(*ppvalue);
    
    if ((err = (*ppvalue)->read(stream)) != errorsOK) {
        freep(*ppvalue);
        return errors_wrap(err, "parse elem");
    }
    
    return err;
}

error_t srs_amf0_read_string(StreamBuf* stream, string& value)
{
    // marker
    if (!stream->require(1)) {
        return errors_new(-1, "requires 1 only %d bytes", stream->Remain());
    }
    
    char marker = stream->Read1Byte();
    if (marker != RTMP_AMF0_String) {
        return errors_new(-1, "String invalid marker=%#x", marker);
    }
    
    return amf0_read_utf8(stream, value);
}

error_t srs_amf0_write_string(StreamBuf* stream, string value)
{   
    // marker
    if (!stream->require(1)) {
        return errors_new(-1, "requires 1 only %d bytes", stream->Remain());
    }
    
    stream->Write1Bytes(RTMP_AMF0_String);
    
    return amf0_write_utf8(stream, value);
}

error_t srs_amf0_read_boolean(StreamBuf* stream, bool& value)
{
    error_t err = errorsOK;
    
    // marker
    if (!stream->require(1)) {
        return errors_new(-1, "requires 1 only %d bytes", stream->Remain());
    }
    
    char marker = stream->Read1Byte();
    if (marker != RTMP_AMF0_Boolean) {
        return errors_new(-1, "Boolean invalid marker=%#x", marker);
    }
    
    // value
    if (!stream->require(1)) {
        return errors_new(-1, "requires 1 only %d bytes", stream->Remain());
    }
    
    value = (stream->Read1Byte() != 0);
    
    return err;
}

error_t srs_amf0_write_boolean(StreamBuf* stream, bool value)
{
    error_t err = errorsOK;
    
    // marker
    if (!stream->require(1)) {
        return errors_new(-1, "requires 1 only %d bytes", stream->Remain());
    }
    stream->Write1Bytes(RTMP_AMF0_Boolean);
    
    // value
    if (!stream->require(1)) {
        return errors_new(-1, "requires 1 only %d bytes", stream->Remain());
    }
    
    if (value) {
        stream->Write1Bytes(0x01);
    } else {
        stream->Write1Bytes(0x00);
    }
    
    return err;
}

error_t srs_amf0_read_number(StreamBuf* stream, double& value)
{
    error_t err = errorsOK;
    
    // marker
    if (!stream->require(1)) {
        return errors_new(-1, "requires 1 only %d bytes", stream->Remain());
    }
    
    char marker = stream->Read1Byte();
    if (marker != RTMP_AMF0_Number) {
        return errors_new(-1, "Number invalid marker=%#x", marker);
    }
    
    // value
    if (!stream->require(8)) {
        return errors_new(-1, "requires 8 only %d bytes", stream->Remain());
    }
    
    int64_t temp = stream->Read8Bytes();
    memcpy(&value, &temp, 8);
    
    return err;
}

error_t srs_amf0_write_number(StreamBuf* stream, double value)
{
    error_t err = errorsOK;
    
    // marker
    if (!stream->require(1)) {
        return errors_new(-1, "requires 1 only %d bytes", stream->Remain());
    }
    
    stream->Write1Bytes(RTMP_AMF0_Number);
    
    // value
    if (!stream->require(8)) {
        return errors_new(-1, "requires 8 only %d bytes", stream->Remain());
    }
    
    int64_t temp = 0x00;
    memcpy(&temp, &value, 8);
    stream->Write8Bytes(temp);
    
    return err;
}

error_t srs_amf0_read_null(StreamBuf* stream)
{
    error_t err = errorsOK;
    
    // marker
    if (!stream->require(1)) {
        return errors_new(-1, "requires 1 only %d bytes", stream->Remain());
    }
    
    char marker = stream->Read1Byte();
    if (marker != RTMP_AMF0_Null) {
        return errors_new(-1, "Null invalid marker=%#x", marker);
    }
    
    return err;
}

error_t srs_amf0_write_null(StreamBuf* stream)
{
    error_t err = errorsOK;
    
    // marker
    if (!stream->require(1)) {
        return errors_new(-1, "requires 1 only %d bytes", stream->Remain());
    }
    
    stream->Write1Bytes(RTMP_AMF0_Null);
    
    return err;
}

error_t srs_amf0_read_undefined(StreamBuf* stream)
{
    error_t err = errorsOK;
    
    // marker
    if (!stream->require(1)) {
        return errors_new(-1, "requires 1 only %d bytes", stream->Remain());
    }
    
    char marker = stream->Read1Byte();
    if (marker != RTMP_AMF0_Undefined) {
        return errors_new(-1, "Undefined invalid marker=%#x", marker);
    }
    
    return err;
}

error_t srs_amf0_write_undefined(StreamBuf* stream)
{
    error_t err = errorsOK;
    
    // marker
    if (!stream->require(1)) {
        return errors_new(-1, "requires 1 only %d bytes", stream->Remain());
    }
    
    stream->Write1Bytes(RTMP_AMF0_Undefined);
    
    return err;
}

// namespace srs_internal
// {
    error_t amf0_read_utf8(StreamBuf* stream, string& value)
    {
        error_t err = errorsOK;
        
        // len
        if (!stream->require(2)) {
            return errors_new(-1, "requires 2 only %d bytes", stream->Remain());
        }
        int16_t len = stream->Read2Bytes();
        
        // empty string
        if (len <= 0) {
            return err;
        }
        
        // data
        if (!stream->require(len)) {
            return errors_new(-1, "requires %d only %d bytes", len, stream->Remain());
        }
        std::string str = stream->read_string(len);
        
        // support utf8-1 only
        // 1.3.1 Strings and UTF-8
        // UTF8-1 = %x00-7F
        // TODO: support other utf-8 strings
        /*for (int i = 0; i < len; i++) {
         char ch = *(str.data() + i);
         if ((ch & 0x80) != 0) {
         ret = ERROR_RTMP_AMF0_DECODE;
         srs_error("ignored. only support utf8-1, 0x00-0x7F, actual is %#x. ret=%d", (int)ch, ret);
         ret = ERROR_SUCCESS;
         }
         }*/
        
        value = str;
        
        return err;
    }
    
    error_t amf0_write_utf8(StreamBuf* stream, string value)
    {
        error_t err = errorsOK;
        
        // len
        if (!stream->require(2)) {
            return errors_new(-1, "requires 2 only %d bytes", stream->Remain());
        }
        stream->Write2Bytes((int16_t)value.length());
        
        // empty string
        if (value.length() <= 0) {
            return err;
        }
        
        // data
        if (!stream->require((int)value.length())) {
            return errors_new(-1, "requires %" PRIu64 " only %d bytes", value.length(), stream->Remain());
        }
        stream->write_string(value);
        
        return err;
    }
    
    bool amf0_is_object_eof(StreamBuf* stream)
    {
        // detect the object-eof specially
        if (stream->require(3)) {
            int32_t flag = stream->Read3Bytes();
            stream->Skip(-3);
            
            return 0x09 == flag;
        }
        
        return false;
    }
    
    error_t amf0_write_object_eof(StreamBuf* stream, Amf0ObjectEOF* value)
    {
        assert(value != NULL);
        return value->write(stream);
    }
    
    error_t amf0_write_any(StreamBuf* stream, Amf0Any* value)
    {
        assert(value != NULL);
        return value->write(stream);
    }
// }

