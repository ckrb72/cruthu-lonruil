#pragma once
#include <stdbool.h>
#include <stddef.h>


typedef enum write_flag
{
    CL_WRITE_OVERWRITE,
    CL_WRITE_APPEND
}write_flag;


// Read file from path into a null terminated array of chars
// Memory ownership is passed to user once the function returns (must free memory yourself)
unsigned char* clReadFileText(const char* path);

// Read file from path into an array of bytes (not null terminated)
// Memory ownership passed to user once returns (must free memory yourself)
unsigned char* clReadFileBinary(const char* path);

// Writes data to file at path in binary format (can use for char arrays as well)
// Does not free data passed in
bool clWriteFile(void* data, size_t size, size_t nmemb, const char* path, write_flag flag);