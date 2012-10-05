#include "AMFByteStream.h"
#include <sys/stat.h>

/* Direct buffer i/o operations */


AMF_UI8 AMFByteStream_readUI8(const unsigned char *ptr) {
    return (AMF_UI8)ptr[0];
}
void AMFByteStream_writeUI8(const AMF_UI8 value, unsigned char *ptr) {
    ptr[0] = value;
}
AMF_SI8 AMFByteStream_readSI8(const unsigned char *ptr) {
    return (AMF_SI8)ptr[0];
}
void AMFByteStream_writeSI8(const AMF_SI8 value, unsigned char *ptr) {
    ptr[0] = value;
}

AMF_UI16 AMFByteStream_readUI16(const unsigned char *ptr) {
    if (AMFContext_isBigEndian()) {
        // TODO: verify
        return (AMF_UI16)(ptr[0] | ((unsigned)ptr[1] << 8));
    } else {
        return (AMF_UI16)(ptr[1] | ((unsigned)ptr[0] << 8));
    }
}
void AMFByteStream_writeUI16(const AMF_UI16 value, unsigned char *ptr) {
    if (AMFContext_isBigEndian()) {
        // TODO: write as is
        ptr[1] = (value >> 8) & 0xFF;
        ptr[0] = value & 0xFF;
    } else {
        ptr[0] = (value >> 8) & 0xFF;
        ptr[1] = value & 0xFF;
    }
}
AMF_SI16 AMFByteStream_readSI16(const unsigned char *ptr) {
    if (AMFContext_isBigEndian()) {
        // TODO: verify
        return (AMF_SI16)(ptr[0] | ((unsigned)ptr[1] << 8));
    } else {
        return (AMF_SI16)(ptr[1] | ((unsigned)ptr[0] << 8));
    }
}
void AMFByteStream_writeSI16(const AMF_SI16 value, unsigned char *ptr) {
    if (AMFContext_isBigEndian()) {
        // TODO: write as is
        ptr[1] = (value >> 8) & 0xFF;
        ptr[0] = value & 0xFF;
    } else {
        ptr[0] = (value >> 8) & 0xFF;
        ptr[1] = value & 0xFF;
    }
}


AMF_UI24 AMFByteStream_readUI24(const unsigned char *ptr) {
    if (AMFContext_isBigEndian()) {
        return (AMF_UI32)(ptr[0] | ((unsigned)ptr[1] << 8) | ((unsigned)ptr[2] << 16));
    } else {
        return (AMF_UI32)(ptr[2] | ((unsigned)ptr[1] << 8) | ((unsigned)ptr[0] << 16));
    }
}
void AMFByteStream_writeUI24(const AMF_UI24 value, unsigned char *ptr) {
    if (AMFContext_isBigEndian()) {
        // TODO: verify
        ptr[2] = (value >> 16) & 0xFF;
        ptr[1] = (value >> 8) & 0xFF;
        ptr[0] = value & 0xFF;
    } else {
        ptr[0] = (value >> 16) & 0xFF;
        ptr[1] = (value >> 8) & 0xFF;
        ptr[2] = value & 0xFF;
    }
}
AMF_SI24 AMFByteStream_readSI24(const unsigned char *ptr) {
    if (AMFContext_isBigEndian()) {
        return (AMF_SI24)(ptr[0] | ((unsigned)ptr[1] << 8) | ((unsigned)ptr[2] << 16));
    } else {
        return (AMF_SI24)(ptr[2] | ((unsigned)ptr[1] << 8) | ((unsigned)ptr[0] << 16));
    }
}
void AMFByteStream_writeSI24(const AMF_SI24 value, unsigned char *ptr) {
    if (AMFContext_isBigEndian()) {
        // TODO: verify
        ptr[2] = (value >> 16) & 0xFF;
        ptr[1] = (value >> 8) & 0xFF;
        ptr[0] = value & 0xFF;
    } else {
        ptr[0] = (value >> 16) & 0xFF;
        ptr[1] = (value >> 8) & 0xFF;
        ptr[2] = value & 0xFF;
    }
}

AMF_UI32 AMFByteStream_readUI32(const unsigned char *ptr) {
    if (AMFContext_isBigEndian()) {
        return (AMF_UI32)(ptr[0] | ((unsigned)ptr[1] << 8) | ((unsigned)ptr[2] << 16) | ((unsigned)ptr[3] << 24));
    } else {
        return (AMF_UI32)(ptr[3] | ((unsigned)ptr[2] << 8) | ((unsigned)ptr[1] << 16) | ((unsigned)ptr[0] << 24));
    }
}
void AMFByteStream_writeUI32(const AMF_UI32 value, unsigned char *ptr) {
    if (AMFContext_isBigEndian()) {
        // TODO: verify
        ptr[3] = (value >> 24) & 0xFF;
        ptr[2] = (value >> 16) & 0xFF;
        ptr[1] = (value >> 8) & 0xFF;
        ptr[0] = value & 0xFF;
    } else {
        ptr[0] = (value >> 24) & 0xFF;
        ptr[1] = (value >> 16) & 0xFF;
        ptr[2] = (value >> 8) & 0xFF;
        ptr[3] = value & 0xFF;
    }
}
AMF_SI32 AMFByteStream_readSI32(const unsigned char *ptr) {
    if (AMFContext_isBigEndian()) {
        return (AMF_SI32)(ptr[0] | ((unsigned)ptr[1] << 8) | ((unsigned)ptr[2] << 16) | ((unsigned)ptr[3] << 24));
    } else {
        return (AMF_SI32)(ptr[3] | ((unsigned)ptr[2] << 8) | ((unsigned)ptr[1] << 16) | ((unsigned)ptr[0] << 24));
    }
}
void AMFByteStream_writeSI32(const AMF_SI32 value, unsigned char *ptr) {
    if (AMFContext_isBigEndian()) {
        // TODO: verify
        ptr[3] = (value >> 24) & 0xFF;
        ptr[2] = (value >> 16) & 0xFF;
        ptr[1] = (value >> 8) & 0xFF;
        ptr[0] = value & 0xFF;
    } else {
        ptr[0] = (value >> 24) & 0xFF;
        ptr[1] = (value >> 16) & 0xFF;
        ptr[2] = (value >> 8) & 0xFF;
        ptr[3] = value & 0xFF;
    }
}

AMF_UI8 AMFByteStream_readMarker(const unsigned char* ptr) {
    return AMFByteStream_readUI8(ptr);
}
void AMFByteStream_writeMarker(const AMF_UI8 value, unsigned char *ptr) {
    AMFByteStream_writeUI8(value, ptr);
}

AMF_NUMBER AMFByteStream_readNumber(const unsigned char *cp) {
    union aligned {
        AMF_NUMBER dval;
        char cval[8];
    } d;

    if(AMFContext_isBigEndian()) {
        d.cval[7] = cp[7];
        d.cval[6] = cp[6];
        d.cval[5] = cp[5];
        d.cval[4] = cp[4];
        d.cval[3] = cp[3];
        d.cval[2] = cp[2];
        d.cval[1] = cp[1];
        d.cval[0] = cp[0];
    } else {
        d.cval[0] = cp[7];
        d.cval[1] = cp[6];
        d.cval[2] = cp[5];
        d.cval[3] = cp[4];
        d.cval[4] = cp[3];
        d.cval[5] = cp[2];
        d.cval[6] = cp[1];
        d.cval[7] = cp[0];
    }
    return d.dval;
}
void AMFByteStream_writeNumber(const AMF_NUMBER value, unsigned char *ptr) {
    union {
        char dc[8];
        double dd;
    } d;
    d.dd = value;
    // encode BE
    if (AMFContext_isBigEndian()) {
        ptr[0] = d.dc[0];
        ptr[1] = d.dc[1];
        ptr[2] = d.dc[2];
        ptr[3] = d.dc[3];
        ptr[4] = d.dc[4];
        ptr[5] = d.dc[5];
        ptr[6] = d.dc[6];
        ptr[7] = d.dc[7];
    } else {
        ptr[0] = d.dc[7];
        ptr[1] = d.dc[6];
        ptr[2] = d.dc[5];
        ptr[3] = d.dc[4];
        ptr[4] = d.dc[3];
        ptr[5] = d.dc[2];
        ptr[6] = d.dc[1];
        ptr[7] = d.dc[0];
    }
}

AMF_BOOLEAN AMFByteStream_readBoolean(const unsigned char *ptr) {
    return (AMF_BOOLEAN)AMFByteStream_readUI8(ptr);
}
void AMFByteStream_writeBoolean(const AMF_BOOLEAN value, unsigned char *ptr) {
    AMFByteStream_writeUI8(value, ptr);
}

void AMFByteStream_readShortString(AMF_STRING value, const unsigned char *ptr) {
    AMF_UI16 size = AMFByteStream_readUI16(ptr);
    value = (AMF_STRING)calloc(sizeof(AMF_STRING), size + 1);
    memcpy(value, ptr, size);
    value[size] = '\0';
}
void AMFByteStream_writeShortString(const AMF_STRING value, unsigned char *ptr) {
    AMFByteStream_writeUI16(strlen(value), ptr);
    memcpy(ptr + AMF_UI16_SIZE, value, strlen(value));
}

void AMFByteStream_readLongString(AMF_STRING value, const unsigned char *ptr) {
    AMF_UI32 size = AMFByteStream_readUI32(ptr);
    value = (AMF_STRING)calloc(sizeof(AMF_STRING), size + 1);
    memcpy(value, ptr, size);
    value[size] = '\0';
}
void AMFByteStream_writeLongString(const AMF_STRING value, unsigned char *ptr) {
    AMFByteStream_writeUI32(strlen(value), ptr);
    memcpy(ptr + AMF_UI32_SIZE, value, strlen(value));
}


/* Stream operations */


int AMFByteStream_streamInit(AMFByteStream *stream) {
    if (stream == NULL) {
        return AMFEXT_FAILURE;
    }
    stream->data = (unsigned char*) malloc(sizeof(stream->data));
    memset(stream->data, 0, sizeof(stream->data));
    stream->allocated = 0;
    stream->used = 0;
    stream->offset = 0;
    return AMFEXT_SUCCESS;
}

int AMFByteStream_streamReset(AMFByteStream *stream) {
    if (stream == NULL) {
        return AMFEXT_FAILURE;
    }
    stream->offset = 0;
    return AMFEXT_SUCCESS;
}

int AMFByteStream_streamFree(AMFByteStream *stream) {
    if (stream == NULL) {
        return AMFEXT_FAILURE;
    }
    if((stream->data != NULL) && (stream->allocated > 0)) {
        free(stream->data);
    }
    stream->data = NULL;
    stream->allocated = 0;
    stream->used = 0;
    AMFByteStream_streamReset(stream);
    return AMFEXT_SUCCESS;
}

int AMFByteStream_streamAppendBytes(AMFByteStream *stream, unsigned const char *bytes, size_t nbytes) {
    if(stream == NULL) {
        return AMFEXT_FAILURE;
    }
    if(bytes == NULL) {
        return AMFEXT_SUCCESS;
    }
    if(nbytes == 0) {
        return AMFEXT_SUCCESS;
    }
    // Check if we have to increase the stream size
    size_t new_size_min = stream->used + nbytes;
    if(stream->allocated < new_size_min) {
        // Pre-allocating some memory. Round up to the next 1024 bound
        size_t size = (new_size_min / AMFSTREAM_BUCKET_SIZE + (AMFSTREAM_BUCKET_SIZE > 1 ? 1 : 0)) * AMFSTREAM_BUCKET_SIZE;
        //size_t size = stream->used + nbytes;
        unsigned char *data = (unsigned char *)realloc(stream->data, size);
        if(data == NULL) {
            RTMP_Log(RTMP_LOGERROR, "Allocation has failed");
            return AMFEXT_FAILURE;
        } else {
            memset(data + stream->used, 0, nbytes);
            stream->allocated = size;
            stream->data = data;
        }
    }
    // Copy the stuff into the stream only if resize complete (test again allocated size)
    if(stream->allocated >= new_size_min) {
        memcpy(stream->data + stream->used, bytes, nbytes);
        stream->used += nbytes;
        stream->offset = stream->used;
        return AMFEXT_SUCCESS;
    }
    return AMFEXT_FAILURE;
}

int AMFByteStream_streamAppendString(AMFByteStream *dst, const char *string) {
    if(string == NULL) {
        return AMFEXT_SUCCESS;
    }
    return AMFByteStream_streamAppendBytes(dst, (unsigned char*)string, strlen(string));
}

int AMFByteStream_streamAppendStream(AMFByteStream *dst, const AMFByteStream *src) {
    if(src == NULL) {
        return AMFEXT_SUCCESS;
    }
    return AMFByteStream_streamAppendBytes(dst, src->data, src->used);
}

int AMFByteStream_streamWriteUI8(AMFByteStream *stream, const AMF_UI8 value) {
    unsigned char *bytes = (unsigned char*) calloc(sizeof(*bytes), AMF_UI8_SIZE);
    AMFByteStream_writeUI8(value, bytes);
    AMFByteStream_streamAppendBytes(stream, bytes, AMF_UI8_SIZE);
    free(bytes);
    return AMFEXT_SUCCESS;
}
int AMFByteStream_streamReadUI8(const AMFByteStream *stream, AMF_UI8 *value) {
    if ((stream->offset + AMF_UI8_SIZE) > stream->used) {
        return AMFEXT_FAILURE;
    }
    *value = AMFByteStream_readUI8(stream->data);
    return AMFEXT_SUCCESS;
}
int AMFByteStream_streamWriteSI8(AMFByteStream *stream, const AMF_SI8 value) {
    unsigned char *bytes = (unsigned char*) calloc(sizeof(*bytes), AMF_SI8_SIZE);
    AMFByteStream_writeSI8(value, bytes);
    AMFByteStream_streamAppendBytes(stream, bytes, AMF_SI8_SIZE);
    free(bytes);
    return AMFEXT_SUCCESS;
}
int AMFByteStream_streamReadSI8(const AMFByteStream *stream, AMF_SI8 *value) {
    if ((stream->offset + AMF_SI8_SIZE) > stream->used) {
        return AMFEXT_FAILURE;
    }
    *value = AMFByteStream_readSI8(stream->data);
    return AMFEXT_SUCCESS;
}

int AMFByteStream_streamWriteUI16(AMFByteStream *stream, const AMF_UI16 value) {
    unsigned char *bytes = (unsigned char*) calloc(sizeof(*bytes), AMF_UI16_SIZE);
    AMFByteStream_writeUI16(value, bytes);
    AMFByteStream_streamAppendBytes(stream, bytes, AMF_UI16_SIZE);
    free(bytes);
    return AMFEXT_SUCCESS;
}
int AMFByteStream_streamReadUI16(const AMFByteStream *stream, AMF_UI16 *value) {
    if ((stream->offset + AMF_UI16_SIZE) > stream->used) {
        return AMFEXT_FAILURE;
    }
    *value = AMFByteStream_readUI16(stream->data);
    return AMFEXT_SUCCESS;
}
int AMFByteStream_streamWriteSI16(AMFByteStream *stream, const AMF_SI16 value) {
    unsigned char *bytes = (unsigned char*) calloc(sizeof(*bytes), AMF_SI16_SIZE);
    AMFByteStream_writeSI16(value, bytes);
    AMFByteStream_streamAppendBytes(stream, bytes, AMF_SI16_SIZE);
    free(bytes);
    return AMFEXT_SUCCESS;
}
int AMFByteStream_streamReadSI16(const AMFByteStream *stream, AMF_SI16 *value) {
    if ((stream->offset + AMF_SI16_SIZE) > 0) {
        return AMFEXT_FAILURE;
    }
    *value = AMFByteStream_readSI16(stream->data);
    return AMFEXT_SUCCESS;
}

int AMFByteStream_streamWriteUI24(AMFByteStream *stream, const AMF_UI24 value) {
    unsigned char *bytes = (unsigned char*) calloc(sizeof(*bytes), AMF_UI24_SIZE);
    AMFByteStream_writeUI24(value, bytes);
    AMFByteStream_streamAppendBytes(stream, bytes, AMF_UI24_SIZE);
    free(bytes);
    return AMFEXT_SUCCESS;
}
int AMFByteStream_streamReadUI24(const AMFByteStream *stream, AMF_UI24 *value) {
    if ((stream->offset + AMF_UI24_SIZE) > 0) {
        return AMFEXT_FAILURE;
    }
    *value = AMFByteStream_readUI24(stream->data);
    return AMFEXT_SUCCESS;
}

int AMFByteStream_streamWriteSI24(AMFByteStream *stream, const AMF_SI24 value) {
    unsigned char *bytes = (unsigned char*) calloc(sizeof(*bytes), AMF_SI24_SIZE);
    AMFByteStream_writeSI24(value, bytes);
    AMFByteStream_streamAppendBytes(stream, bytes, AMF_SI24_SIZE);
    free(bytes);
    return AMFEXT_SUCCESS;
}
int AMFByteStream_streamReadSI24(const AMFByteStream *stream, AMF_SI24 *value) {
    if ((stream->offset + AMF_SI24_SIZE) > 0) {
        return AMFEXT_FAILURE;
    }
    *value = AMFByteStream_readSI24(stream->data);
    return AMFEXT_SUCCESS;
}

int AMFByteStream_streamWriteUI32(AMFByteStream *stream, const AMF_UI32 value) {
    unsigned char *bytes = (unsigned char*) calloc(sizeof(*bytes), AMF_UI32_SIZE);
    AMFByteStream_writeUI32(value, bytes);
    AMFByteStream_streamAppendBytes(stream, bytes, AMF_UI32_SIZE);
    free(bytes);
    return AMFEXT_SUCCESS;
}
int AMFByteStream_streamReadUI32(const AMFByteStream *stream, AMF_UI32 *value) {
    if ((stream->offset + AMF_UI32_SIZE) > 0) {
        return AMFEXT_FAILURE;
    }
    *value = AMFByteStream_readUI32(stream->data + stream->offset - AMF_UI32_SIZE);
    return AMFEXT_SUCCESS;
}
int AMFByteStream_streamWriteSI32(AMFByteStream *stream, const AMF_SI32 value) {
    unsigned char *bytes = (unsigned char*) calloc(sizeof(*bytes), AMF_SI32_SIZE);
    AMFByteStream_writeSI32(value, bytes);
    AMFByteStream_streamAppendBytes(stream, bytes, AMF_SI32_SIZE);
    free(bytes);
    return AMFEXT_SUCCESS;
}
int AMFByteStream_streamReadSI32(const AMFByteStream *stream, AMF_SI32 *value) {
    if ((stream->offset + AMF_SI32_SIZE) > 0) {
        return AMFEXT_FAILURE;
    }
    *value = AMFByteStream_readSI32(stream->data + stream->offset - AMF_SI32_SIZE);
    return AMFEXT_SUCCESS;
}


int AMFByteStream_streamReadBit(AMFBitStream *bitstream) {
    int bit;
    if(bitstream->byte == bitstream->length) {
        return 0;
    }
    bit = (bitstream->bytes[bitstream->byte] >> (7 - bitstream->bit)) & 0x01;
    bitstream->bit++;
    if(bitstream->bit == 8) {
        bitstream->byte++;
        bitstream->bit = 0;
    }
    return bit;
}
int AMFByteStream_streamReadBits(AMFBitStream *bitstream, int nbits) {
    int i, rv = 0;
    for(i = 0; i < nbits; i++) {
        rv = (rv << 1);
        rv += AMFByteStream_streamReadBit(bitstream);
    }
    return rv;
}


int AMFByteStream_streamWriteMarker(AMFByteStream *stream, const AMF_MARKER marker) {
    unsigned char *bytes = (unsigned char*) calloc(sizeof(*bytes), AMF_MARKER_SIZE);
    AMFByteStream_writeMarker(marker, bytes);
    AMFByteStream_streamAppendBytes(stream, bytes, AMF_MARKER_SIZE);
    free(bytes);
    return AMFEXT_SUCCESS;
}
int AMFByteStream_streamReadMarker(const AMFByteStream *stream, AMF_MARKER *marker) {
    if ((stream->offset - AMF_MARKER_SIZE) < 0) {
        return AMFEXT_FAILURE;
    }
    AMFByteStream_streamReadUI8(stream + stream->offset - AMF_MARKER_SIZE, marker);
    return AMFEXT_SUCCESS;
}


int AMFByteStream_streamWriteNumber(AMFByteStream *stream, const AMF_NUMBER value) {
    unsigned char *bytes = (unsigned char*) calloc(sizeof(*bytes), AMF_NUMBER_SIZE);
    AMFByteStream_streamWriteMarker(stream, MARKER_AMF0_NUMBER);
    AMFByteStream_writeNumber(value, bytes);
    AMFByteStream_streamAppendBytes(stream, bytes, AMF_NUMBER_SIZE);
    free(bytes);
    return AMFEXT_SUCCESS;
}
int AMFByteStream_streamReadNumber(const AMFByteStream *stream, AMF_NUMBER *value) {
    AMF_MARKER marker = AMFByteStream_readMarker(stream->data + stream->offset);
    if (marker != MARKER_AMF0_NUMBER) {
        return AMFEXT_FAILURE;
    }
    *value = AMFByteStream_readNumber(stream->data + stream->offset + AMF_MARKER_SIZE);
    return AMFEXT_SUCCESS;
}

int AMFByteStream_streamWriteBoolean(AMFByteStream *stream, const AMF_BOOLEAN value) {
    unsigned char *bytes = (unsigned char*) calloc(sizeof(*bytes), AMF_BOOLEAN_SIZE);
    AMFByteStream_streamWriteMarker(stream, MARKER_AMF0_BOOLEAN);
    AMFByteStream_writeBoolean(value, bytes);
    AMFByteStream_streamAppendBytes(stream, bytes, AMF_BOOLEAN_SIZE);
    free(bytes);
    return AMFEXT_SUCCESS;
}
int AMFByteStream_streamReadBoolean(const AMFByteStream *stream, AMF_BOOLEAN *value) {
    AMF_MARKER marker = AMFByteStream_readMarker(stream->data + stream->offset);
    if (marker != MARKER_AMF0_BOOLEAN) {
        return AMFEXT_FAILURE;
    }
    *value = AMFByteStream_readBoolean(stream->data + stream->offset + AMF_MARKER_SIZE);
    return AMFEXT_SUCCESS;
}

int _AMFByteStream_readString(unsigned char *ptr, AMF_UI8 type, AMF_STRING value) {

    AMF_UI32 size = 0;
    size_t offset = 0;

    if (type == MARKER_AMF0_STRING) {
        AMF_UI16 s_size = 0;
        s_size = AMFByteStream_readUI16(ptr);
        size = s_size;
        offset = AMF_UI16_SIZE;
    }

    if (type == MARKER_AMF0_LONGSTRING) {
        size = AMFByteStream_readUI32(ptr);
        offset = AMF_UI32_SIZE;
    }

    if (size == 0) {
        value = AMF_STRING_EMPTY;
    } else {
        AMF_STRING tmp = (AMF_STRING) malloc(size + 1);
        memcpy(tmp, ptr + offset, size);
        tmp[size] = '\0';
        value = (AMF_STRING)tmp;
    }

    return AMFEXT_SUCCESS;
}

int AMFByteStream_streamWriteShortString(AMFByteStream *stream, const AMF_STRING value) {
    AMF_UI16 length = (AMF_UI16)strlen(value);
    unsigned char *bytes = (unsigned char*) calloc(sizeof(*bytes), length);
    AMFByteStream_streamWriteMarker(stream, MARKER_AMF0_STRING);
    AMFByteStream_streamWriteUI16(stream, length);
    AMFByteStream_streamAppendString(stream, value);
    free(bytes);
    return AMFEXT_SUCCESS;
}
int AMFByteStream_streamReadShortString(const AMFByteStream *stream, AMF_STRING value) {
    AMF_MARKER marker = AMFByteStream_readMarker(stream->data + stream->offset);
    if (marker != MARKER_AMF0_STRING) {
        return AMFEXT_FAILURE;
    }
   _AMFByteStream_readString(stream->data + stream->offset + AMF_MARKER_SIZE, MARKER_AMF0_STRING, value);
    return AMFEXT_SUCCESS;
}

int AMFByteStream_streamWriteLongString(AMFByteStream *stream, const AMF_STRING value) {
    AMF_UI32 length = (AMF_UI32)strlen(value);
    unsigned char *bytes = (unsigned char*) calloc(sizeof(*bytes), length);
    AMFByteStream_streamWriteMarker(stream, MARKER_AMF0_LONGSTRING);
    AMFByteStream_streamWriteUI32(stream, length);
    AMFByteStream_streamAppendString(stream, value);
    free(bytes);
    return AMFEXT_SUCCESS;
}
int AMFByteStream_streamReadLongString(const AMFByteStream *stream, AMF_STRING value) {
    AMF_MARKER marker = AMFByteStream_readMarker(stream->data + stream->offset);
    if (marker != MARKER_AMF0_LONGSTRING) {
        return AMFEXT_FAILURE;
    }
   _AMFByteStream_readString(stream->data + stream->offset + AMF_MARKER_SIZE, MARKER_AMF0_LONGSTRING, value);
    return AMFEXT_SUCCESS;
}



/*

// stream management


int AMFByteStream_streamWriteString(AMFByteStream *stream, AMF_STRING value) {
    size_t len = strlen(value);
    if(len > AMF_STRING_SHORT_MAX_SIZE) {
        AMFByteStream_streamWriteMarker(stream, MARKER_AMF0_LONGSTRING);
        AMFByteStream_streamWriteUI32(stream, len);
        AMFByteStream_streamAppendString(stream, (char*)value);
    } else {
        AMFByteStream_streamWriteMarker(stream, MARKER_AMF0_STRING);
        AMFByteStream_streamWriteUI16(stream, len);
        AMFByteStream_streamAppendString(stream, (char*)value);
    }
    return AMFEXT_SUCCESS;
}

int AMFByteStream_streamReadString(AMFByteStream *stream, AMF_STRING *value) {
    AMF_UI8 type = 0;
    AMFByteStream_streamReadMarker(stream, &type);
    return AMFByteStream_readString(stream->data + AMF_MARKER_SIZE, type, value);
}

int AMFByteStream_readShortString(unsigned char *ptr, AMF_STRING *value) {
    return AMFByteStream_readString(ptr, MARKER_AMF0_STRING, value);
}

int AMFByteStream_readLongString(unsigned char *ptr, AMF_STRING *value) {
    return AMFByteStream_readString(ptr, MARKER_AMF0_LONGSTRING, value);
}

int AMFByteStream_readString(unsigned char *ptr, AMF_UI8 type, AMF_STRING *value) {

    AMF_UI32 size = 0;
    size_t offset = 0;

    if (type == MARKER_AMF0_STRING) {
        AMF_UI16 s_size = 0;
        s_size = AMFByteStream_readUI16(ptr);
        size = s_size;
        offset = AMF_UI16_SIZE;
    }

    if (type == MARKER_AMF0_LONGSTRING) {
        AMFByteStream_readUI32(ptr, &size);
        offset = AMF_UI32_SIZE;
    }

    if (size == 0) {
        *value = AMF_STRING_EMPTY;
    } else {
        AMF_STRING tmp = (AMF_STRING) malloc(size + 1);
        memcpy(tmp, ptr + offset, size);
        tmp[size] = '\0';
        *value = (AMF_STRING)tmp;
    }

    return AMFEXT_SUCCESS;
}


int AMFByteStream_writeObjectBegin(AMFByteStream *stream) {
    return AMFByteStream_streamWriteMarker(stream, MARKER_AMF0_OBJECT);
}

int AMFByteStream_writeObjectEnd(AMFByteStream *stream) {
    // TODO: what do they mean ? This marker is always preceded by an empty UTF-8 string and together forms the object end type.
    // writing as UI24 instead of UI8 -> 00:00:MARKER_AMF0_OBJECTEND (maybe those two 0 are the UTF-8 empty string)
    return AMFByteStream_streamWriteUI24(stream, MARKER_AMF0_OBJECTEND);
}

int AMFByteStream_writeStrictArrayBegin(AMFByteStream *stream, size_t len) {
    AMFByteStream_streamWriteMarker(stream, MARKER_AMF0_STRICTARRAY);
    AMFByteStream_streamWriteUI32(stream, len);
    return AMFEXT_SUCCESS;
}

int AMFByteStream_writeStrictArrayEnd(AMFByteStream *stream) {
    return AMFByteStream_writeObjectEnd(stream);
}

int AMFByteStream_writeECMAArrayBegin(AMFByteStream *stream, size_t len) {
    AMFByteStream_streamWriteMarker(stream, MARKER_AMF0_ECMAARRAY);
    AMFByteStream_streamWriteUI32(stream, len);
    return AMFEXT_SUCCESS;
}

int AMFByteStream_writeECMAArrayEnd(AMFByteStream *stream) {
    return AMFByteStream_writeObjectEnd(stream);
}

// int AMFByteStream_writeMovieclip(AMFByteStream *stream, void* stream); {
// }

// int AMFByteStream_writeReference(AMFByteStream *stream, void* stream) {
// }


// int AMFByteStream_writeDate(AMFByteStream *stream, void* stream) {
// }

// int AMFByteStream_writeRecordset(AMFByteStream *stream, char *s) {
// }

// int AMFByteStream_writeXMLDocument(AMFByteStream *stream, char *s) {
// }

// int AMFByteStream_writeTypedObject(AMFByteStream *stream, char *s) {
// }

int AMFByteStream_writeNull(AMFByteStream *stream) {
    return AMFByteStream_streamWriteMarker(stream, MARKER_AMF0_NULL);
}

int AMFByteStream_writeUndefined(AMFByteStream *stream) {
    return AMFByteStream_streamWriteMarker(stream, MARKER_AMF0_UNDEFINED);
}

int AMFByteStream_writeUnsupported(AMFByteStream *stream) {
    return AMFByteStream_streamWriteMarker(stream, MARKER_AMF0_UNSUPPORTED);
}

int AMFByteStream_writeAVMPlusObject(AMFByteStream *stream) {
    return AMFByteStream_streamWriteMarker(stream, MARKER_AMF0_AVMPLUSOBJECT);
}
*/

// Utilities

int AMFByteStream_streamToFile(AMFByteStream *stream, const char* filename) {
    return AMFByteStream_toFile(stream->data, stream->used, filename);
}

int AMFByteStream_toFile(unsigned char *data, size_t length, const char* filename) {
    FILE *fp = fopen(filename, "wb");
    fwrite(data, length, 1, fp);
    fclose(fp);
    return AMFEXT_SUCCESS;
}

int AMFByteStream_fromFile(AMFByteStream *stream, const char* filename) {
    struct stat st;
    if (access(filename, F_OK) == -1) {
        RTMP_Log(RTMP_LOGERROR, "File %s does not exist", filename);
        return AMFEXT_FAILURE;
    }
    stat(filename, &st);
    if (st.st_size <= 0) {
        RTMP_Log(RTMP_LOGERROR, "File %s is empty", filename);
    } else {
        RTMP_Log(RTMP_LOGINFO, "File size is %lld bytes", st.st_size);
    }
    FILE *fp = fopen(filename, "rb");
    stream->data = (unsigned char*) malloc(st.st_size);
    stream->allocated = st.st_size;
    stream->used = st.st_size;
    fread(stream->data, st.st_size, 1, fp);
    fclose(fp);
    return AMFEXT_SUCCESS;
}

int AMFByteStream_dumpStream(AMFByteStream *stream) {
    char first_as_marker = 1;
    if (stream == NULL) {
        RTMP_Log(RTMP_LOGINFO, "AMFByteStream_dumpStream - NULL stream");
        return AMFEXT_SUCCESS;
    }
    if (stream->data == NULL) {
        RTMP_Log(
            RTMP_LOGINFO,
            "AMFByteStream_dumpStream:\n\t\t<%s>[0]\n\t\t<%s>\n\t\t{a:%ld, u:%ld, o:%ld}",
            "(str)", "", stream->allocated, stream->used, stream->offset
        );
        return AMFEXT_SUCCESS;
    }
    unsigned int len;
    char prefix[] = "(str)";
    unsigned int pxlen = strlen(prefix);
    char *hexb, *tmp;
    if (AMFSTREAM_BUCKET_DUMP == 1) {
        len = stream->allocated;
    } else {
        len = stream->used;
    }
    hexb = AMFByteStream_bufferToHexStr((char*)stream->data, len, first_as_marker);
    tmp = (char*) malloc(len + pxlen + 1);
    memcpy(tmp, prefix, pxlen);
    memcpy(tmp + pxlen, stream->data, len);
    tmp[len + pxlen] = '\0';
    RTMP_Log(
        RTMP_LOGINFO,
        "AMFByteStream_dumpStream:\n\t\t<%s>[%d]\n\t\t<%s>\n\t\t{a:%ld, u:%ld, o:%ld}",
        tmp, strlen(tmp) - pxlen, hexb, stream->allocated, stream->used, stream->offset
    );
    free(tmp);
    return AMFEXT_SUCCESS;

}

int AMFByteStream_dump(unsigned char *data, size_t length, char first_as_marker) {
    unsigned int len;
    char prefix[] = "(str)";
    unsigned int pxlen = strlen(prefix);
    char *hexb, *tmp;
    hexb = AMFByteStream_bufferToHexStr((char*)data, length, first_as_marker);
    len = length+ pxlen + 1;
    tmp = (char*) malloc(len);
    memcpy(tmp, prefix, pxlen);
    memcpy(tmp + pxlen, data, length);
    tmp[len-1] = '\0';
    RTMP_Log(
        RTMP_LOGINFO,
        "AMFByteStream_dump:\n\t\t<%s>[%d]\n\t\t<%s>\n\t\t{a:%ld}",
        tmp, strlen(tmp) - pxlen, hexb, length
    );
    free(tmp);
    return AMFEXT_SUCCESS;
}

char* AMFByteStream_bufferToHexStr(char *buffer, size_t size, char first_as_marker) {
    char* hexb = (char*)malloc(4*size + 1);
    memset(hexb, 0, 3*size + 1);
    int i;
    for (i = 0; i < size; i++) {
        char hexdata[3];
        sprintf(hexdata, "%02x", 255&(char)buffer[i]);
        char* sep = i == 1 && first_as_marker ? "|" : ":";
        if (i == 0) {
            strcat(hexb, hexdata);
        } else {
            strcat(hexb, sep);
            strcat(hexb, hexdata);
        }

    }
    hexb[4*size] = '\0';
    return hexb;
}
