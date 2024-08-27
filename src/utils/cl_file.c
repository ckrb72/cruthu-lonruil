#include "cl_file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// Read file from path into a null terminated array of chars
// Memory ownership is passed to user once the function returns (must free memory yourself)
unsigned char* clReadFileText(const char* path)
{
    FILE* file = fopen(path, "r");

    if(!file)
        return NULL;

    fseek(file, SEEK_SET, SEEK_END);

    // Get length of file (includes carriage returns on windows sadly)
    long len = ftell(file);

    // On windows we are kind of allocating too much space since this count includes
    // the carriage return
    unsigned char* buf = malloc(sizeof(char) * (len + 1));

    // Return to start of file
    rewind(file);

    char c;
    long i;

    // Read in characters one at a time
    while((c = fgetc(file)) != EOF)
    {
        // Ignore carriage returns
        if(c != '\r')
            buf[i++] = c;
    }

    // Don't forget null terminator since this is text
    buf[i] = '\0';

    fclose(file);


    return buf;
}




// Read file from path into an array of bytes (not null terminated)
// Memory ownership passed to user once returns (must free memory yourself)
unsigned char* clReadFileBinary(const char* path)
{
    FILE* file = fopen(path, "rb");

    if(!file)
        return NULL;

    fseek(file, SEEK_SET, SEEK_END);
    long len = ftell(file);

    rewind(file);

    unsigned char* buf = malloc(sizeof(char) * len);
    fread(buf, sizeof(char), len, file);

    fclose(file);

    return buf;
}




// Writes data to file at path in binary format (can use for char arrays as well)
// Does not free data passed in
bool clWriteFile(void* data, size_t size, size_t nmemb, const char* path, write_flag flag)
{
    FILE* file;

    if(flag == CL_WRITE_OVERWRITE)
    {
        file = fopen(path, "wb");
    }
    else
    {
        file = fopen(path, "ab");
    }

    if(!file)
        return false;


    if(fwrite(data, size, nmemb, file) == 0)
    {
        fclose(file);
        return false;
    }




    fclose(file);

    return true;
}