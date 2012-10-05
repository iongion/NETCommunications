#ifndef __AMF_REMOTING_H__
#define __AMF_REMOTING_H__

#include "amfext.h"
#include "AMFByteStream.h"

#ifdef __cplusplus
extern "C"
{
#endif
    int AMFRemoting_readHeaders(struct AMFByteStream *stream, struct AMFHeader** headers, AMF_UI16 *length);
    int AMFRemoting_readMessages(struct AMFByteStream *stream, struct AMFMessage** messages, AMF_UI16 *length);
#ifdef __cplusplus
}
#endif

#endif /* __AMF_REMOTING_H__ */
