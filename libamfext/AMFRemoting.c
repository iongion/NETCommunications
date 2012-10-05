#include "AMFRemoting.h"


int AMFRemoting_readHeaders(struct AMFByteStream *stream, struct AMFHeader** headers, AMF_UI16 *length) {

    RTMP_Log(RTMP_LOGINFO, "Reading headers");

    /*
    size_t cPos;
    AMF_UI8 fByte, sByte;

    cPos = 0;

    // Read first byte
    fByte = AMFByteStream_readUI8(stream->data + cPos);
    cPos += AMF_UI8_SIZE;

    assert(fByte == 0 || fByte == 3);
    if (!(fByte == 0 || fByte == 3)) {
        // Connection dropped ?!?
        return AMFEXT_FAILURE;
    }

    // Read second byte
    sByte = AMFByteStream_readUI8(stream->data + cPos);
    cPos += AMF_UI8_SIZE;
    assert(sByte == 0 || sByte == 1); // 0 - Flash, 1 - FMS/Red5/Wowza
    if (!(sByte == 0 || sByte == 1)) {
        return AMFEXT_FAILURE;
    }

    // Read headers length
    length = AMFByteStream_readUI16(stream->data + cPos);
    cPos += AMF_UI16_SIZE;

    RTMP_Log(RTMP_LOGINFO, "First byte is %d, second byte is %d, there are %d headers", fByte, sByte, *length);

    AMF_UI16 h = 0;
    while (h < *length) {
        // TODO: reset references
        AMF_STRING header;
        //AMFByteStream_readString(stream, &header);

        h++;
    }
    */

    /*
        while ($this->headersLeftToProcess--) { // loop over all of the header elements
            $this->resetReferences();
            $name = $this->readUTF();
            $required = $this->readByte() == 1; // find the must understand flag
            //$length   = $this->readLong(); // grab the length of  the header element
            $this->currentByte += 4; // grab the length of the header element

            $type = $this->readByte();  // grab the type of the element
            $content = $this->readData($type); // turn the element into real data

            $header = new Amfphp_Core_Amf_Header($name, $required, $content);
            $this->deserializedPacket->headers[] = $header;
        }
    */

    return AMFEXT_SUCCESS;
}

int AMFRemoting_readMessages(struct AMFByteStream *stream, struct AMFMessage** messages, AMF_UI16 *length) {

    return AMFEXT_SUCCESS;
}
