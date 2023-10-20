#include "flvparser.h"

FLVParser::FLVParser(char*&& buf, int len)
{
    sb = new StreamBuf(buf, len);

}

FLVParser::~FLVParser()
{
    if (sb) {
        delete sb;
    }
}

error_t FLVParser::parserFLVHeader() {
    assert(sb->Remain() > minByteRequired);
    error_t err = errorsOK;

    char f = sb->Read1Byte();
    char l = sb->Read1Byte();
    char v = sb->Read1Byte();
    if (f != 0x46 || l != 0x4c || v != 0x56) { // FLV
        return errors_new(-1, "signature check failed");
    }

    header.version = sb->Read1Byte();

    char avtag = sb->Read1Byte();
    header.type_flags_audio = (avtag >> 2) & 0x01;
    header.type_flags_video = (0x01 & avtag);

    header.data_offset = sb->Read4Bytes();
    // point to body.
    sb->Skip(header.data_offset - sb->Offset());
    return err;
}

uint32_t FLVParser::FLVTagHeader::Timestamp() {
    return (timestamp_extended << 24) | timestamp;
}

string FLVParser::FLVTagHeader::toString() {
    stringstream ss;
    ss << "flv tag header:\n "
       << "tag_type: " << tag_type_mp[tag_type] << LF
       << "data_size: " << to_string(data_size) << LF
       << "timestamp: " << to_string(timestamp) << LF
       << "timestamp_extended: " << to_string(timestamp_extended) << LF
       << "timestamp(): " << to_string(Timestamp()) << LF
       << "stream_id: " << to_string(stream_id) << LF;
    return ss.str();
}

error_t FLVParser::parserFLVTagHeader() {
    error_t err = errorsOK;
    tag_header.tag_type = (TagTypeE)sb->Read1Byte();
    tag_header.data_size = sb->Read3Bytes();
    tag_header.timestamp = sb->Read3Bytes();
    tag_header.timestamp_extended = sb->Read1Byte();
    tag_header.stream_id = sb->Read3Bytes();
    return err;
}

error_t FLVParser::parseFLVVideoTag() {
    error_t err = errorsOK;
    int pos = sb->Offset();

    uint8_t type = sb->Read1Byte();
    video_tag.frame_type  = (type & 0xf0) >> 4;
    video_tag.codec_id = (type & 0x0f);
    if (video_tag.codec_id == 7) { // avc
        video_tag.avc_packet_type = sb->Read1Byte();
        video_tag.composition_time = sb->Read3Bytes();
    }

    int offset = sb->Offset() - pos;
    // skip video data/
    sb->Skip(tag_header.data_size - offset);
    return err;
}

error_t FLVParser::parseFLVAudioTag() {
    error_t err = errorsOK;
    int pos = sb->Offset();

    uint8_t pa = sb->Read1Byte();
    audio_tag.sound_format = (SoundFormatE)(pa >> 4);
    audio_tag.sound_rate = (pa & 0x0f) >> 2;
    audio_tag.sound_size = (pa & 0x02) >> 1;
    audio_tag.sound_type = (pa & 0x01);
    audio_tag.aac_packet_type = sb->Read1Byte();
    // aac sequence header
    if (audio_tag.aac_packet_type == 0) {
        uint8_t audioObjectType = sb->Read1Byte();
        uint8_t aac_sample_rate = sb->Read1Byte();
        
        audio_tag.aac_channels = (aac_sample_rate >> 3) & 0x0f;
        audio_tag.aac_sample_rate = (AacSampleRateIndex)(((audioObjectType << 1) & 0x0e) | ((aac_sample_rate >> 7) & 0x01));
        // @todo if aac_sample_rate == 0xf 
        // sampling frequency will be present by 24bit as flowing.
        // read 24bit, and reparse sampling frequency.
        audioObjectType = (audioObjectType >> 3) & 0x1f;
        audio_tag.aac_object = (AacObjectType)audioObjectType;
        cout << audio_tag.toString() << endl;
    }

    int offset = sb->Offset() - pos;
    // skip audio data/
    sb->Skip(tag_header.data_size - offset);
    return err;
}

string FLVParser::FLVTagAudio::toString() {
    stringstream ss;
    ss << "audio tag header:" << LF 
        << "format: " << sound_format_mp[sound_format] << LF
        << "rate: " << sound_rate_mp[sound_rate] << LF
        << "sound_size: " << sound_size_mp[sound_size] << LF
        << "sound_type: " << sound_type_mp[sound_type] << LF;
    if (sound_format == AAC) {
        ss << "packet type: " << aac_packet_type_mp[aac_packet_type] << LF; 
        if (aac_packet_type == 0) {
            ss << "aac_packet_type: " << aac_object_mp[aac_object] << LF
                << "aac_sample_rate:" << aac_sample_rate_mp[aac_sample_rate] << LF
                << "aac_channels: " << to_string(aac_channels) << LF; 
        }
    }
    return ss.str();
}

string FLVParser::FLVTagVideo::toString() {
    stringstream ss;
    ss << "video tag header: " << LF
        << "frame_type: " << frame_type_mp[frame_type] << LF
        << "codec id: " << codec_id_mp[codec_id] << LF;
    if (codec_id == 7) {
        ss << "avc_packet_type: " << avc_packet_type_mp[avc_packet_type] << LF
            << "composition_time" << to_string(composition_time) << LF;
    }
    return ss.str();
}

error_t FLVParser::parseFLVScriptTag() {
    error_t err = errorsOK;
    int pos = sb->Offset();

    shared_ptr<void> autoFree(nullptr, [&](void*) {
        int offset = sb->Offset() - pos;
        sb->Skip(tag_header.data_size - offset);
    });

    while (sb->Offset() - pos < tag_header.data_size) {
        Amf0Any* any;
        error_t err = amf0_read_any(sb, &any);
        if (err != errorsOK) {
            return errors_wrap(err, "failed read amf0");
        }
        if (any->is_string()) {
            auto any_str = dynamic_cast<Amf0String*>(any);
            if (any_str) {
                cout << any_str->value << endl;
            }
        } else if (any->is_ecma_array()) {
            auto array = dynamic_cast<Amf0EcmaArray*>(any);
            if (array) {
                for (int i = 0; i < array->count(); i++) {
                    cout << "key at " << to_string(i) << " is " << array->key_at(i) << endl;
                    auto value = array->value_at(i);
                    if (Amf0String* str = dynamic_cast<Amf0String*> (value); str != nullptr) {
                        cout << "value at " << to_string(i) << "is " << value->to_str() << endl;
                    } else if (Amf0Number* num = dynamic_cast<Amf0Number*>(value); num != nullptr) {
                        cout << "value at " << to_string(i) << "is " << value->to_number() << endl;
                    } else if (Amf0Boolean* b = dynamic_cast<Amf0Boolean*>(value); b != nullptr) {
                        cout << "value at " << to_string(i) << "is " << value->to_boolean() << endl;
                    } else if (Amf0Date* b = dynamic_cast<Amf0Date*>(value); b != nullptr) {
                        cout << "value at " << to_string(i) << "is " << value->to_date() << endl;
                    } 
                }
            } 
        } else {
            // @todo other amf0 type.
        }
        freep(any);
    }
    
    return err;
}

/*
Signature
*/
error_t FLVParser::Parse() {
    error_t err = parserFLVHeader();
    if (err) {
        return errors_wrap(err, "parser flv header failed");
    }

    cout << header.toString() << endl;

    // parse flv body.
    int previous_tag_len;
    while (sb->Remain() > 4) {
        previous_tag_len = sb->Read4Bytes();
        cout << "previous tag len=" << previous_tag_len << endl;
        parserFLVTagHeader();
        cout << tag_header.toString() << endl;
        
        switch (tag_header.tag_type)
        {
        case TAG_TYPE_VIDEO:
            /* code */
            parseFLVVideoTag();
            cout << video_tag.toString() << endl;
            break;
        case TAG_TYPE_AUDIO: 
            parseFLVAudioTag(); 
            cout << audio_tag.toString() << endl;
            break;
        case TAG_TYPE_SCRIPT: 
            parseFLVScriptTag();
            break;
        default: break;
        }
        cout << "----------------------" << endl;
    }

    return err;
}

string FLVParser::FLVHeader::toString() {
    stringstream ss;
    ss << "version: " << to_string(version) << LF
       << "type_flags_audio: " << to_string(type_flags_audio) << LF
       << "type_flags_video: " << to_string(type_flags_video) << LF
       << "data_offset: " << data_offset << LF;
    return ss.str();
}
