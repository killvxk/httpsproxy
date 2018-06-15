#ifndef HPY_CORE_HPY_TLS_
#define HPY_CORE_HPY_TLS_

#define HANDSHAKE 0x16

typedef unsigned char uint8;
typedef unsigned int uint32;
typedef char opaque;
typedef opaque SessionID;

typedef struct {
    uint8 major;
    uint8 minor;
} ProtocolVersion;

typedef struct {
    uint32 gmt_unix_time;
    opaque random_bytes[28];
} Random;



#endif