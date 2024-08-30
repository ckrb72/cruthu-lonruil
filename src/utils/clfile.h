#pragma once
#include <string>
#include <vector>
enum WriteType
{
    CL_WRITE_OVERWRITE,
    CL_WRITE_APPEND
};

std::vector<unsigned char> clReadFileBinary(const std::string& path);
std::string clReadFileText(const std::string& path);

void clWriteFile(void* data, int memsize, int memcount, const std::string& path, WriteType type);