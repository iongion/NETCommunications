#ifndef __AMF_BYTESTREAM_H__
#define __AMF_BYTESTREAM_H__

#define AMFSTREAM_BUCKET_SIZE       1
/* if AMFSTREAM_BUCKET_DUMP != 0 dump functions will print all alocated bytes instead of used ones */
#define AMFSTREAM_BUCKET_DUMP       1

#include "amfext.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /* Write operations are always BE -  Network byte order                 */
    /* Read operations detect if machine is BE/LE and convert automatically */

    /* Direct buffer i/o operations */

    AMF_UI8 AMFByteStream_readUI8(const unsigned char *ptr);
    void AMFByteStream_writeUI8(const AMF_UI8 value, unsigned char *ptr);
    AMF_SI8 AMFByteStream_readSI8(const unsigned char *ptr);
    void AMFByteStream_writeSI8(const AMF_SI8 value, unsigned char *ptr);

    AMF_UI16 AMFByteStream_readUI16(const unsigned char *ptr);
    void AMFByteStream_writeUI16(const AMF_UI16 value, unsigned char *ptr);
    AMF_SI16 AMFByteStream_readSI16(const unsigned char *ptr);
    void AMFByteStream_writeSI16(const AMF_SI16 value, unsigned char *ptr);

    AMF_UI24 AMFByteStream_readUI24(const unsigned char *ptr);
    void AMFByteStream_writeUI24(const AMF_UI24 value, unsigned char *ptr);
    AMF_SI24 AMFByteStream_readSI24(const unsigned char *ptr);
    void AMFByteStream_writeSI24(const AMF_SI24 value, unsigned char *ptr);

    AMF_UI32 AMFByteStream_readUI32(const unsigned char *ptr);
    void AMFByteStream_writeUI32(const AMF_UI32 value, unsigned char *ptr);
    AMF_SI32 AMFByteStream_readSI32(const unsigned char *ptr);
    void AMFByteStream_writeSI32(const AMF_SI32 value, unsigned char *ptr);

    AMF_MARKER AMFByteStream_readMarker(const unsigned char* ptr);
    void AMFByteStream_writeMarker(const AMF_MARKER value, unsigned char* ptr);

    /* AMF related */

    AMF_NUMBER AMFByteStream_readNumber(const unsigned char *ptr);
    void AMFByteStream_writeNumber(const AMF_NUMBER value, unsigned char *ptr);

    AMF_BOOLEAN AMFByteStream_readBoolean(const unsigned char *ptr);
    void AMFByteStream_writeBoolean(const AMF_BOOLEAN value, unsigned char *ptr);

    void AMFByteStream_readShortString(AMF_STRING value, const unsigned char *ptr);
    void AMFByteStream_writeShortString(const AMF_STRING value, unsigned char *ptr);

    void AMFByteStream_readLongString(AMF_STRING value, const unsigned char *ptr);
    void AMFByteStream_writeLongString(const AMF_STRING value, unsigned char *ptr);

    /* Stream buffer i/o operations - they alter the offset like fseek does for streams */
    int AMFByteStream_streamInit(AMFByteStream *stream);
    int AMFByteStream_streamReset(AMFByteStream *stream);
    int AMFByteStream_streamFree(AMFByteStream *stream);

    int AMFByteStream_streamAppendBytes(AMFByteStream *stream, unsigned const char *bytes, size_t nbytes);
    int AMFByteStream_streamAppendString(AMFByteStream *stream, const char *string);
    int AMFByteStream_streamAppendStream(AMFByteStream *stream, const AMFByteStream *source);

    int AMFByteStream_streamWriteUI8(AMFByteStream *stream, const AMF_UI8 value);
    int AMFByteStream_streamReadUI8(const AMFByteStream *stream, AMF_UI8 *value);
    int AMFByteStream_streamWriteSI8(AMFByteStream *stream, const AMF_SI8 value);
    int AMFByteStream_streamReadSI8(const AMFByteStream *stream, AMF_SI8 *value);

    int AMFByteStream_streamWriteUI16(AMFByteStream *stream, const AMF_UI16 value);
    int AMFByteStream_streamReadUI16(const AMFByteStream *stream, AMF_UI16 *value);
    int AMFByteStream_streamWriteSI16(AMFByteStream *stream, const AMF_SI16 value);
    int AMFByteStream_streamReadSI16(const AMFByteStream *stream, AMF_SI16 *value);

    int AMFByteStream_streamWriteUI24(AMFByteStream *stream, const AMF_UI24 value);
    int AMFByteStream_streamReadUI24(const AMFByteStream *stream, AMF_UI24 *value);
    int AMFByteStream_streamWriteSI24(AMFByteStream *stream, const AMF_SI24 value);
    int AMFByteStream_streamReadSI24(const AMFByteStream *stream, AMF_SI24 *value);

    int AMFByteStream_streamWriteUI32(AMFByteStream *stream, const AMF_UI32 value);
    int AMFByteStream_streamReadUI32(const AMFByteStream *stream, AMF_UI32 *value);
    int AMFByteStream_streamWriteSI32(AMFByteStream *stream, const AMF_SI32 value);
    int AMFByteStream_streamReadSI32(const AMFByteStream *stream, AMF_SI32 *value);

    int AMFByteStream_streamReadBit(AMFBitStream *bitstream);
    int AMFByteStream_streamReadBits(AMFBitStream *bitstream, int nbits);

    int AMFByteStream_streamWriteMarker(AMFByteStream *stream, const AMF_MARKER marker);
    int AMFByteStream_streamReadMarker(const AMFByteStream *stream, AMF_MARKER *marker);

    int AMFByteStream_streamWriteNumber(AMFByteStream *stream, const AMF_NUMBER value);
    int AMFByteStream_streamReadNumber(const AMFByteStream *stream, AMF_NUMBER *value);

    int AMFByteStream_streamWriteBoolean(AMFByteStream *stream, const AMF_BOOLEAN value);
    int AMFByteStream_streamReadBoolean(const AMFByteStream *stream, AMF_BOOLEAN *value);

    int AMFByteStream_streamWriteShortString(AMFByteStream *stream, const AMF_STRING value);
    int AMFByteStream_streamReadShortString(const AMFByteStream *stream, AMF_STRING value) ;

    int AMFByteStream_streamWriteLongString(AMFByteStream *stream, const AMF_STRING value);
    int AMFByteStream_streamReadLongString(const AMFByteStream *stream, AMF_STRING value) ;


    /*

    int AMFByteStream_streamWriteNumber(AMFByteStream *stream, AMF_NUMBER value);
    int AMFByteStream_streamReadNumber(AMFByteStream *stream, AMF_NUMBER *value);

    int AMFByteStream_streamWriteBoolean(AMFByteStream *stream, AMF_BOOLEAN value);
    int AMFByteStream_streamReadBoolean(AMFByteStream *stream, AMF_BOOLEAN *value);

    int AMFByteStream_streamWriteShortString(AMFByteStream *stream, AMF_STRING value);
    int AMFByteStream_streamReadShortString(AMFByteStream *stream, AMF_STRING *value);

    int AMFByteStream_streamWriteLongString(AMFByteStream *stream, AMF_STRING value);
    int AMFByteStream_streamReadLongString(AMFByteStream *stream, AMF_STRING *value);

    int AMFByteStream_streamWriteString(AMFByteStream *stream, AMF_STRING value);
    int AMFByteStream_streamReadString(AMFByteStream *stream, AMF_STRING *value);

    int AMFByteStream_writeObjectBegin(AMFByteStream *stream);
    int AMFByteStream_writeObjectEnd(AMFByteStream *stream);

    int AMFByteStream_writeStrictArrayBegin(AMFByteStream *stream, size_t len);
    int AMFByteStream_writeStrictArrayEnd(AMFByteStream *stream);

    int AMFByteStream_writeECMAArrayBegin(AMFByteStream *stream, size_t len);
    int AMFByteStream_writeECMAArrayEnd(AMFByteStream *stream);
    */

    /*
    // int AMFByteStream_writeMovieclip(AMFByteStream *stream, void* stream);
    // int AMFByteStream_writeReference(AMFByteStream *stream, void* stream);
    // int AMFByteStream_writeDate(AMFByteStream *stream, void* stream);
    // int AMFByteStream_writeRecordset(AMFByteStream *stream, char *s);
    // int AMFByteStream_writeXMLDocument(AMFByteStream *stream, char *s);
    // int AMFByteStream_writeTypedObject(AMFByteStream *stream, char *s);
    */

    /*
    int AMFByteStream_writeNull(AMFByteStream *stream);
    int AMFByteStream_writeUndefined(AMFByteStream *stream);
    int AMFByteStream_writeUnsupported(AMFByteStream *stream);
    int AMFByteStream_writeAVMPlusObject(AMFByteStream *stream);
    */

    /* Utilities */

    int AMFByteStream_streamToFile(AMFByteStream *stream, const char* filename);
    int AMFByteStream_toFile(unsigned char* data, size_t size, const char* filename);
    int AMFByteStream_fromFile(AMFByteStream *stream, const char* filename);

    char* AMFByteStream_bufferToHexStr(char *buffer, size_t size, char first_as_marker);
    int AMFByteStream_dumpStream(AMFByteStream *stream);
    int AMFByteStream_dump(unsigned char* data, size_t length, char first_as_marker);


#ifdef __cplusplus
}
#endif

#endif /* __AMF_BYTESTREAM_H__ */
