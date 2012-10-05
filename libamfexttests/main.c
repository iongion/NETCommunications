#include <libamfext/amfext.h>
#include <libamfext/AMFByteStream.h>
#include <libamfext/AMFRemoting.h>

void testStreamAllocation() {
    AMFByteStream stream;
    RTMP_Log(RTMP_LOGINFO, "AMFByteStream_streamInit");
    assert(AMFByteStream_streamInit(&stream) == AMFEXT_SUCCESS);
    assert(AMFByteStream_dumpStream(&stream) == AMFEXT_SUCCESS);
    RTMP_Log(RTMP_LOGINFO, "AMFByteStream_streamReset");
    assert(AMFByteStream_streamReset(&stream) == AMFEXT_SUCCESS);
    assert(AMFByteStream_dumpStream(&stream) == AMFEXT_SUCCESS);
    RTMP_Log(RTMP_LOGINFO, "AMFByteStream_streamFree");
    assert(AMFByteStream_streamFree(&stream) == AMFEXT_SUCCESS);
    assert(AMFByteStream_dumpStream(&stream) == AMFEXT_SUCCESS);
}

void testStreamManipulation() {
    AMFByteStream stream;
    const char bytes1[7] = "abraca";
    const char bytes2[6] = "dabra";

    assert(AMFByteStream_streamInit(&stream) == AMFEXT_SUCCESS);

    RTMP_Log(RTMP_LOGINFO, "AMFByteStream_streamAppendBytes %s", bytes1);
    assert(AMFByteStream_streamAppendBytes(&stream, (unsigned char*)bytes1, strlen(bytes1)) == AMFEXT_SUCCESS);
    assert(AMFByteStream_dumpStream(&stream) == AMFEXT_SUCCESS);

    RTMP_Log(RTMP_LOGINFO, "AMFByteStream_streamAppendBytes %s", bytes2);
    assert(AMFByteStream_streamAppendBytes(&stream, (unsigned char*)bytes2, strlen(bytes2)) == AMFEXT_SUCCESS);
    assert(AMFByteStream_dumpStream(&stream) == AMFEXT_SUCCESS);


    assert(AMFByteStream_streamFree(&stream) == AMFEXT_SUCCESS);
}

void testStreamO() {
    AMFByteStream stream;
    const char bytes1[7] = "into";
    AMF_UI8 value8 = 0x41;
    AMF_UI16 value16 = 0x4243;
    AMF_UI24 value24 = 0x444546;
    AMF_UI32 value32 = 0x4748494A;

    assert(AMFByteStream_streamInit(&stream) == AMFEXT_SUCCESS);
    RTMP_Log(RTMP_LOGINFO, "AMFByteStream_streamAppendBytes %s", bytes1);
    assert(AMFByteStream_streamAppendBytes(&stream, (unsigned char*)bytes1, strlen(bytes1)) == AMFEXT_SUCCESS);
    assert(AMFByteStream_dumpStream(&stream) == AMFEXT_SUCCESS);
    RTMP_Log(RTMP_LOGINFO, "AMFByteStream_streamWriteUI8 %d", value8);
    assert(AMFByteStream_streamWriteUI8(&stream, value8) == AMFEXT_SUCCESS);
    assert(AMFByteStream_dumpStream(&stream) == AMFEXT_SUCCESS);
    RTMP_Log(RTMP_LOGINFO, "AMFByteStream_streamWriteUI16 %d", value16);
    assert(AMFByteStream_streamWriteUI16(&stream, value16) == AMFEXT_SUCCESS);
    assert(AMFByteStream_dumpStream(&stream) == AMFEXT_SUCCESS);
    RTMP_Log(RTMP_LOGINFO, "AMFByteStream_streamWriteUI24 %x", value24);
    assert(AMFByteStream_streamWriteUI24(&stream, value24) == AMFEXT_SUCCESS);
    assert(AMFByteStream_dumpStream(&stream) == AMFEXT_SUCCESS);
    RTMP_Log(RTMP_LOGINFO, "AMFByteStream_streamWriteUI32 %x", value32);
    assert(AMFByteStream_streamWriteUI32(&stream, value32) == AMFEXT_SUCCESS);
    assert(AMFByteStream_dumpStream(&stream) == AMFEXT_SUCCESS);
    assert(AMFByteStream_streamFree(&stream) == AMFEXT_SUCCESS);
}

void testStreamIO() {
    AMFByteStream stream;
    const char bytes1[7] = "into";
    AMF_UI8 value8 = 0x41;
    AMF_UI16 value16 = 0x4243;
    AMF_UI24 value24 = 0x444546;
    AMF_UI32 value32 = 0x4748494A;
    AMF_UI8 ivalue8;
    AMF_UI16 ivalue16;
    AMF_UI24 ivalue24;
    AMF_UI32 ivalue32;

    assert(AMFByteStream_streamInit(&stream) == AMFEXT_SUCCESS);
    RTMP_Log(RTMP_LOGINFO, "AMFByteStream_streamReadBytes %s", bytes1);
    assert(AMFByteStream_streamAppendBytes(&stream, (unsigned char*)bytes1, strlen(bytes1)) == AMFEXT_SUCCESS);
    assert(AMFByteStream_streamWriteUI8(&stream, value8) == AMFEXT_SUCCESS);
    assert(AMFByteStream_streamWriteUI16(&stream, value16) == AMFEXT_SUCCESS);
    assert(AMFByteStream_streamWriteUI24(&stream, value24) == AMFEXT_SUCCESS);
    assert(AMFByteStream_streamWriteUI32(&stream, value32) == AMFEXT_SUCCESS);
    assert(AMFByteStream_streamReadUI32(&stream, &ivalue32) == AMFEXT_SUCCESS);
    RTMP_Log(RTMP_LOGINFO, "AMFByteStream_streamReadBytes %x", ivalue32);
    assert(AMFByteStream_streamReadUI24(&stream, &ivalue24) == AMFEXT_SUCCESS);
    assert(AMFByteStream_streamReadUI16(&stream, &ivalue16) == AMFEXT_SUCCESS);
    assert(AMFByteStream_streamReadUI8(&stream, &ivalue8) == AMFEXT_SUCCESS);
    assert(AMFByteStream_dumpStream(&stream) == AMFEXT_SUCCESS);
    assert(AMFByteStream_streamFree(&stream) == AMFEXT_SUCCESS);
}

void testStreamNumberIO() {
    AMFByteStream stream;
    AMF_NUMBER oval = 34.689;
    AMF_NUMBER ival= 0;

    assert(AMFByteStream_streamInit(&stream) == AMFEXT_SUCCESS);

    RTMP_Log(RTMP_LOGINFO, "AMFByteStream_streamWriteNumber %f - %x", oval, oval);
    assert(AMFByteStream_streamWriteNumber(&stream, oval) == AMFEXT_SUCCESS);
    assert(AMFByteStream_dumpStream(&stream) == AMFEXT_SUCCESS);
    stream.offset = 0;
    assert(AMFByteStream_streamReadNumber(&stream, &ival) == AMFEXT_SUCCESS);
    RTMP_Log(RTMP_LOGINFO, "AMFByteStream_streamReadNumber %f - %x", ival, ival);
    assert(AMFByteStream_dumpStream(&stream) == AMFEXT_SUCCESS);

    assert(AMFByteStream_streamFree(&stream) == AMFEXT_SUCCESS);
}

void testStreamBooleanIO() {
    AMFByteStream stream;
    AMF_BOOLEAN oval = 1;
    AMF_BOOLEAN ival;

    assert(AMFByteStream_streamInit(&stream) == AMFEXT_SUCCESS);

    RTMP_Log(RTMP_LOGINFO, "AMFByteStream_streamWriteBoolean %d - %x", oval, oval);
    assert(AMFByteStream_streamWriteBoolean(&stream, oval) == AMFEXT_SUCCESS);
    assert(AMFByteStream_dumpStream(&stream) == AMFEXT_SUCCESS);
    stream.offset = 0;
    assert(AMFByteStream_streamReadBoolean(&stream, &ival) == AMFEXT_SUCCESS);
    RTMP_Log(RTMP_LOGINFO, "AMFByteStream_streamReadBoolean %d - %x", ival, ival);
    assert(AMFByteStream_dumpStream(&stream) == AMFEXT_SUCCESS);

    assert(AMFByteStream_streamFree(&stream) == AMFEXT_SUCCESS);
}

void testStreamShortStringIO() {
    AMFByteStream stream;
    AMF_STRING oval = "ostring";
    AMF_STRING ival = "";

    assert(AMFByteStream_streamInit(&stream) == AMFEXT_SUCCESS);

    RTMP_Log(RTMP_LOGINFO, "AMFByteStream_streamWriteShortString %s - %x", oval, oval);
    assert(AMFByteStream_streamWriteShortString(&stream, oval) == AMFEXT_SUCCESS);
    assert(AMFByteStream_dumpStream(&stream) == AMFEXT_SUCCESS);
    stream.offset = 0;
    assert(AMFByteStream_streamReadShortString(&stream, ival) == AMFEXT_SUCCESS);
    RTMP_Log(RTMP_LOGINFO, "AMFByteStream_streamReadShortString %s - %x", ival, ival);
    assert(strcmp(oval, ival) == 0);
    assert(AMFByteStream_dumpStream(&stream) == AMFEXT_SUCCESS);

    assert(AMFByteStream_streamFree(&stream) == AMFEXT_SUCCESS);
}

void testStreamLongStringIO() {
    AMFByteStream stream;
    AMF_STRING oval = "ostring";
    AMF_STRING ival = "";

    assert(AMFByteStream_streamInit(&stream) == AMFEXT_SUCCESS);

    RTMP_Log(RTMP_LOGINFO, "AMFByteStream_streamWriteLongString %s - %x", oval, oval);
    assert(AMFByteStream_streamWriteLongString(&stream, oval) == AMFEXT_SUCCESS);
    assert(AMFByteStream_dumpStream(&stream) == AMFEXT_SUCCESS);
    stream.offset = 0;
    assert(AMFByteStream_streamReadLongString(&stream, ival) == AMFEXT_SUCCESS);
    RTMP_Log(RTMP_LOGINFO, "AMFByteStream_streamReadLongtring %s - %x", ival, ival);
    assert(AMFByteStream_dumpStream(&stream) == AMFEXT_SUCCESS);

    assert(AMFByteStream_streamFree(&stream) == AMFEXT_SUCCESS);
}

int main(int argc, char* argv[]) {

    AMFContext_init();

    RTMP_LogSetLevel(RTMP_LOGDEBUG);

    RTMP_Log(RTMP_LOGINFO, "Creating a stream");

    testStreamAllocation();
    testStreamManipulation();
    testStreamO();
    testStreamNumberIO();
    testStreamBooleanIO();
    testStreamShortStringIO();
    testStreamLongStringIO();

    return AMFEXT_SUCCESS;
}
