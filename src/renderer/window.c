#include "window.h"
#include <stdint.h>

typedef struct window_t
{
    void* handle;
    uint32_t width;
    uint32_t height;
}window_t;