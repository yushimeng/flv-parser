
#pragma once

#include "common.h"

typedef enum SoundFormatE { 
    LinearPCMPlatformEndian = 0,
    ADPCM,
    MP3,
    LinearPCMLittleEndian,
    Nellymoser16KHZMono,
    Nellymoser8KHZMono,
    Nellymoser,
    G711ALawLogarithmicPCM,
    G711muLawLogarithmicPCM,
    reserved,
    AAC,
    Speex,
    MP38KHZ,
    DeviceSpecificSound,
} SoundFormatE;

/**
 * the aac object type, for RTMP sequence header
 * for AudioSpecificConfig, @see ISO_IEC_14496-3-AAC-2001.pdf, page 33
 * for audioObjectType, @see ISO_IEC_14496-3-AAC-2001.pdf, page 23
 */
typedef enum AacObjectType
{
    AacObjectTypeReserved = 0,
    AacObjectTypeForbidden = 0,
    
    // Table 1.1 - Audio Object Type definition
    // @see @see ISO_IEC_14496-3-AAC-2001.pdf, page 23
    AacObjectTypeAacMain = 1,
    AacObjectTypeAacLC = 2,
    AacObjectTypeAacSSR = 3,
    
    // AAC HE = LC+SBR
    AacObjectTypeAacHE = 5,
    // AAC HEv2 = LC+SBR+PS
    AacObjectTypeAacHEV2 = 29,
}AacObjectType;

typedef enum AacSampleRateIndex{
    SampleRate96000 = 0x0,
    SampleRate88200 = 0x1,
    SampleRate64000 = 0x2,
    SampleRate48000 = 0x3,
    SampleRate44100 = 0x4,
    SampleRate32000 = 0x5,
    SampleRate24000 = 0x6,
    SampleRate22050 = 0x7,
    SampleRate16000 = 0x8,
    SampleRate12000 = 0x9,
    SampleRate11025 = 0xa,
    SampleRate8000 = 0xb,
    SampleRate7350 = 0xc,
    SampleRatereserved_0xd = 0xd,
    SampleRatereserved_0xe = 0xe,
    SampleRateEscapeValue_0xf = 0xf,
}AacSampleRateIndex;




class FLVParser
{
private:
    const int minByteRequired = 12;
    StreamBuf* sb;
private:
    typedef struct FLVHeader{
        uint8_t signature[3]; // FLV
        uint8_t version; // File version(for example, 0x01 for flv version 1)
        uint8_t type_flags_reserved_5bit : 5; // Must be 0
        uint8_t type_flags_audio : 1; // audio tags are present
        uint8_t type_flags_reserved_1bit : 1; // must be 0
        uint8_t type_flags_video : 1; // video tags are present
        uint32_t data_offset;   // offset in bytes from start of file to start of body(that is, size of header)
        public : 
            string toString();
    } FLVHeader;
    FLVHeader header;

public:
    uint32_t previous_tag_size;
    typedef enum TagTypeE { 
        TAG_TYPE_AUDIO = 8, 
        TAG_TYPE_VIDEO = 9,
        TAG_TYPE_SCRIPT = 18,
        // all others: reserved
    }TagTypeE;

    typedef struct FLVTagHeader {
        // type of this tag, values are:
        // 8: audio
        // 9: video
        // 18: script data 
        // all others: reserved 
        unordered_map<TagTypeE, string> tag_type_mp={
            {TAG_TYPE_AUDIO, "audio"},
            {TAG_TYPE_VIDEO, "video"},
            {TAG_TYPE_SCRIPT, "script"},
        };
        TagTypeE tag_type:8;
        // length of the data in data field
        uint32_t data_size : 24;
        // time in milliseconds at which the data in this tag applies.
        // this value is relative to the first tag in the flv file, 
        // which always has a timestamp of 0.
        uint32_t timestamp : 24;
        // extension of timestamp field to form a SI32 value. 
        // this field represents the upper 8bits, 
        // while the previous Timestamp field represents the lower 24 bits 
        // of the time in milliseconds.
        uint8_t timestamp_extended;
        uint32_t stream_id : 24; // always 0
        // data...
        public:
            uint32_t Timestamp();
            string toString();
    } FLVTagHeader;
    FLVTagHeader tag_header;

    typedef struct FLVTagAudio{
        unordered_map<SoundFormatE, string> sound_format_mp={
            {LinearPCMPlatformEndian, "LinearPCMPlatformEndian"},
            {ADPCM, "ADPCM"},
            {MP3, "MP3"},
            {LinearPCMLittleEndian,"LinearPCMLittleEndian"},
            {Nellymoser16KHZMono, "Nellymoser16KHZMono"},
            {Nellymoser8KHZMono, "Nellymoser8KHZMono"},
            {Nellymoser,"Nellymoser"},
            {G711ALawLogarithmicPCM, "G711ALawLogarithmicPCM"},
            {G711muLawLogarithmicPCM, "G711muLawLogarithmicPCM"},
            {reserved, "reserved"},
            {AAC, "AAC"},
            {Speex,"Speex"},
            {MP38KHZ,"MP38KHZ"},
            {DeviceSpecificSound, "DeviceSpecificSound"},
        };
        SoundFormatE sound_format : 4;
        // 0=5.5khz, 1=11khz, 2=22khz, 3=44khz
        unordered_map<uint8_t, string> sound_rate_mp={
            {0, "5.5KHz"},
            {1, "11KHz"},
            {2, "22KHz"},
            {3, "44KHz"},
        };
        uint8_t sound_rate : 2;
        // Size of each sample. This parameter only pertains to uncompressed formats.
        // Compressed formats always decode to 16 bits internally. 
        // 0 = snd8Bit 1 = snd16Bit
        unordered_map<uint8_t, string> sound_size_mp={
            {0, "snd8Bit"},
            {1, "snd16Bit"},
        };
        uint8_t sound_size : 1;
        // mono or stereo sound.
        // for nellymoser: always 0
        // for aac: always 1
        unordered_map<uint8_t, string> sound_type_mp={
            {0, "sndMono"},
            {1, "sndStereo"},
        };
        uint8_t sound_type : 1;
        // if sound_format == 10, the following values are defined:
        // 0=aac sequence header
        // 1=aac raw
        unordered_map<uint8_t, string> aac_packet_type_mp = {
            {0, "aac sequence header"},
            {1, "aac raw"},
        };
        uint8_t aac_packet_type;
        // @see 1.6.2.1 AudioSpecificConfig ISO_IEC_14496-3-AAC-2001
        // https://ossrs.net/lts/zh-cn/assets/files/ISO_IEC_14496-3-AAC-2001-7f4d0b3622b322cb72c78f85d91c449f.pdf
        unordered_map<AacObjectType, string> aac_object_mp={
            // {AacObjectTypeReserved, "AacObjectTypeReserved"},
            {AacObjectTypeForbidden, "AacObjectTypeForbidden"},
            
            // Table 1.1 - Audio Object Type definition
            // @see @see ISO_IEC_14496-3-AAC-2001.pdf, page 23
            {AacObjectTypeAacMain, "AacObjectTypeAacMain"},
            {AacObjectTypeAacLC, "AacObjectTypeAacLC"},
            {AacObjectTypeAacSSR, "AacObjectTypeAacSSR"},
            
            // AAC HE = LC+SBR
            {AacObjectTypeAacHE, "AacObjectTypeAacHE"},
            // AAC HEv2 = LC+SBR+PS
            {AacObjectTypeAacHEV2, "AacObjectTypeAacHEV2"},
        };
        AacObjectType aac_object; // 5bit
        // @see 1.6.3.3 samplingFrequencyIndex
        unordered_map<AacSampleRateIndex, string> aac_sample_rate_mp = {
            {SampleRate96000, "SampleRate96000"},
            {SampleRate88200, "SampleRate88200"},
            {SampleRate64000, "SampleRate88200"},
            {SampleRate48000, "SampleRate48000"},
            {SampleRate44100, "SampleRate44100"},
            {SampleRate32000, "SampleRate32000"},
            {SampleRate24000, "SampleRate24000"},
            {SampleRate22050, "SampleRate22050"},
            {SampleRate16000, "SampleRate16000"},
            {SampleRate12000, "SampleRate12000"},
            {SampleRate11025, "SampleRate11025"},
            {SampleRate8000, "SampleRate8000"},
            {SampleRate7350, "SampleRate7350"},
            {SampleRatereserved_0xd, "SampleRatereserved_0xd"},
            {SampleRatereserved_0xe, "SampleRatereserved_0xe"},
            {SampleRateEscapeValue_0xf, "SampleRateEscapeValue_0xf"},
        };
        AacSampleRateIndex aac_sample_rate; // 4bit
        // @see 1.6.3.4 channelConfiguration
        uint8_t aac_channels; // 4bit
        // sound data...
        string toString();
    } FLVTagAudio;
    FLVTagAudio audio_tag;
    
    typedef struct FLVTagVideo {
        // 1: keyframe(for avc, a seekable frame)
        // 2 inter frame(for avc, a non-seekable frame)
        // 3: disposable inter frame(H263 only)
        // 4: generated key frame(reserved for server use only)
        // 5: video info/command frame
        // if frame_type=5, instead of a video payload, the message
        // stream contains a UI8 with the following meaning:
        // 0=start of client-side seeking video frame sequence
        // 1=end of client-side seeking video frame sequence
        map<uint8_t, string> frame_type_mp={
            {1, "keyframe(for avc, a seekable frame)"},
            {2, "inter frame(for avc, a non-seekable frame)"},
            {3, "disposable inter frame(H263 only)"},
            {4, "generated key frame(reserved for server use only)"},
            {5, "video info/command frame"},
        };
        uint8_t frame_type : 4;
        // 1: jpeg(currently unused)
        // 2: sorenson H263
        // 3: screen video
        // 4: on2 VP6
        // 5: on2 vp6 with alpha channel
        // 6: screen video version 2
        // 7: avc
        map<uint8_t, string> codec_id_mp={
            {1, "jpeg(currently unused)"},
            {2, "sorenson H263"},
            {3, "screen video"},
            {4, "on2 VP6"},
            {5, "on2 vp6 with alpha channel"},
            {6, "screen video version 2"},
            {7, "avc"},
        };
        uint8_t codec_id : 4;
        // if codec id == 7, the following values are defined: 
        // 0 = avc sequence header
        // 1 = avc nalu
        // 2 = avc end of sequence(lowwer level nalu sequence ender is not required or supported)
        map<uint8_t, string> avc_packet_type_mp={
            {0,"avc sequence header"},
            {1, "avc nalu"},
            {2, "avc end of sequence"},
        };
        uint8_t avc_packet_type;
        // if codec id == 7, if avc packet type ==1, composition time offset
        // else 0
        uint32_t composition_time:24;
        // video data...
        string toString();
    } FLVTagVideo;
    FLVTagVideo video_tag;
    

    typedef struct AVCVideoPacket {
        // 0: avc sequence header
        // 1: avc nalu
        // 2: avc end of sequence(lower level nalu 
        //    sequence ender is not required or supported)
        uint8_t avc_packet_type;
        // if avc_packet_type == 1, composition time offset
        // else 0
        uint32_t composition_time : 24;
        // if AVCPacketType == 0 
        //      AVCDecoderConfigurationRecord 
        // else if AVCPacketType == 1 
        //      One or more NALUs (can be individual slices per FLV packets; 
        //      that is, full frames are not strictly required) 
        // else if AVCPacketType == 2 
        //      Empty
        // data...
    } AVCVideoPacket;

private:
    error_t parserFLVHeader();
    error_t parserFLVTagHeader();
    error_t parseFLVVideoTag();
    error_t parseFLVAudioTag();
    error_t parseFLVScriptTag();

public:
    FLVParser(char*&& buf, int len);
    ~FLVParser();
public:
    errors* Parse();
};
