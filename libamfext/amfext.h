#ifndef __AMFEXT_H__
#define __AMFEXT_H__

#include <assert.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>
#include <errno.h>

#include <locale.h>
#include <time.h>
#include <mbstring.h>

#include <liblog/log.h>

#define AMFEXT_VERSION      "1.0"

#define AMFEXT_SUCCESS       0
#define AMFEXT_FAILURE       1

/*
#define AMFEXT_WITHOUT_MARKER       0
#define AMFEXT_WITH_MARKER          1
*/

/*
// Number formats and sizes
//
// U8  =  An unsigned byte, 8-bits of data, an octet
// U16  =  An unsigned 16-bit integer in big endian (network) byte order
// S16  =  An signed 16-bit integer in big endian (network) byte order
// U32  =  An unsigned 32-bit integer in big endian (network) byte order
// DOUBLE  =  8 byte IEEE-754 double precision floating point value in network byte order (sign bit in low memory).
*/

/*
#define toAMFTIMESTAMP(x) (int)(((*(x + 3)) << 24) + ((*(x)) << 16) + ((*(x + 1)) << 8) + (*(x + 2)))
*/

/* sizes are in bytes */

#define AMF_MARKER_SIZE                         1

#define AMF_UI8_SIZE                            1
#define AMF_SI8_SIZE                            1
#define AMF_UI16_SIZE                           2
#define AMF_SI16_SIZE                           2
#define AMF_UI24_SIZE                           3
#define AMF_SI24_SIZE                           3
#define AMF_UI32_SIZE                           4
#define AMF_SI32_SIZE                           4

#define AMF_NUMBER_SIZE                         8
#define AMF_BOOLEAN_SIZE                        1


#define AMF_FALSE                               0
#define AMF_TRUE                                1

#define AMF0_ENCODING                           0
#define AMF3_ENCODING                           3

#define AMF_STRING_EMPTY                        ""
#define AMF_STRING_SHORT_MAX_SIZE               0xffff
#define AMF_STRING_LONG_MAX_SIZE                0xffffffff

#define AMF_CLIENT_SUCCESS_METHOD               "/onResult"
#define AMF_CLIENT_FAILURE_METHOD               "/onStatus"
#define AMF_DEFAULT_REQUEST_RESPONSE_URI        "/1"
#define AMF_CONTENT_TYPE                        "application/x-amf"
#define AMF_FIELD_EXPLICIT_TYPE                 "_explicitType"
#define AMF_FIELD_EXTERNALIZED_DATA             "_externalizedData"
#define AMF_CREDENTIALS_HEADER_NAME             "Credentials"
#define AMF_CREDENTIALS_FIELD_USERID            "userid"
#define AMF_CREDENTIALS_FIELD_PASSWORD          "password"

typedef unsigned char         AMF_UI8;
typedef char                  AMF_SI8;
typedef unsigned short int    AMF_UI16;
typedef short int             AMF_SI16;
typedef unsigned int          AMF_UI24;
typedef int                   AMF_SI24;
typedef unsigned int          AMF_UI32;
typedef int                   AMF_SI32;
typedef AMF_UI8               AMF_BOOLEAN;
typedef AMF_UI8               AMF_MARKER;
typedef double                AMF_NUMBER;
typedef char*                 AMF_STRING;

enum AMF0Codes {
    /* (code) | DOUBLE_VALUE */
    MARKER_AMF0_NUMBER        = 0x00,
    /* (code) | (0-false / 1-true) */
    MARKER_AMF0_BOOLEAN       = 0x01,
    /* (code) | .... UTF8 string */
    MARKER_AMF0_STRING        = 0x02,
    MARKER_AMF0_OBJECT        = 0x03,
    MARKER_AMF0_MOVIECLIP     = 0x04,
    MARKER_AMF0_NULL          = 0x05,
    MARKER_AMF0_UNDEFINED     = 0x06,
    MARKER_AMF0_REFERENCE     = 0x07,
    MARKER_AMF0_ECMAARRAY     = 0x08,
    MARKER_AMF0_OBJECTEND     = 0x09,
    MARKER_AMF0_STRICTARRAY   = 0x0A,
    MARKER_AMF0_DATE          = 0x0B,
    MARKER_AMF0_LONGSTRING    = 0x0C,
    MARKER_AMF0_UNSUPPORTED   = 0x0D,
    MARKER_AMF0_RECORDSET     = 0x0E,
    MARKER_AMF0_XMLDOCUMENT   = 0x0F,
    MARKER_AMF0_TYPEDOBJECT   = 0x10,
    /* - AMF3 marker */
    MARKER_AMF0_AVMPLUSOBJECT = 0x11
};

enum AMF3Codes {
    MARKER_AMF3_UNDEFINED     = 0x00,
    MARKER_AMF3_NULL          = 0x01,
    MARKER_AMF3_FALSE         = 0x02,
    MARKER_AMF3_TRUE          = 0x03,
    MARKER_AMF3_INTEGER       = 0x04,
    MARKER_AMF3_NUMBER        = 0x05,
    MARKER_AMF3_STRING        = 0x06,
    MARKER_AMF3_XML           = 0x07,
    MARKER_AMF3_DATE          = 0x08,
    MARKER_AMF3_ARRAY         = 0x09,
    MARKER_AMF3_OBJECT        = 0x0A,
    MARKER_AMF3_XMLSTRING     = 0x0B,
    MARKER_AMF3_BYTEARRAY     = 0x0C
};

typedef struct AMFContext {
  unsigned int inited;
} AMFContext;


typedef struct AMFBitStream {
    unsigned char *bytes;
    size_t length;
    size_t byte;
    short bit;
} AMFBitStream;

typedef struct AMFByteStream {
    unsigned char *data;
    size_t allocated;
    size_t used;
    size_t offset;
} AMFByteStream;

typedef struct AMFObject {
    unsigned int type;
    struct AMFByteStream* value;
} AMFObject;

/* Flash remoting related */

typedef struct AMFMessage {
    char* targetUri;
    char* responseUri;
    size_t length;
    struct AMFObject* body;
    struct AMFObject** parameters;
    struct AMFObject** returnValues;
} AMFMessage;

typedef struct AMFHeader {
    char* name;
    unsigned char required;
    struct AMFObject* data;
} AMFHeader;

struct AMFPacket;
typedef struct AMFPacket {
    unsigned char version;
    unsigned int clientVersion;
    struct AMFHeader** headers;
    unsigned short int headersLength;
    struct AMFMessage** messages;
    unsigned short int messagesLength;
    struct AMFPacket* other;
} AMFPacket;


#ifdef __cplusplus
extern "C"
{
#endif
    struct AMFContext amfContext;

    int AMFContext_init();
    int AMFContext_isBigEndian(void);

#ifdef __cplusplus
}
#endif

#endif /* __AMFEXT_H__ */
