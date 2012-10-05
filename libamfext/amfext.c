#include "amfext.h"
#include "AMFByteStream.h"

struct AMFContext amfContext;

int AMFContext_init() {
    if (!amfContext.inited) {
        amfContext.inited = 1;
        setlocale(LC_ALL, "C-UTF-8");
    }
    return AMFEXT_SUCCESS;
}

int AMFContext_isBigEndian(void) {
    long one = 1;
    return !(*((char *)(&one)));
}