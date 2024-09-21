#include "clfile.h"
#include <iostream>
#include <fstream>

std::vector<unsigned char> clReadFileBinary(const std::string& path)
{
    std::ifstream file;
    file.open(path, std::ios::in | std::ios::binary | std::ios::ate);

    if(!file.is_open())
    {
        throw std::runtime_error("failed to open file");
        return std::vector<unsigned char>();
    }

    int len = file.tellg();
    file.seekg(0, std::ios::beg);
    
    std::vector<unsigned char> buf(len);

    file.read((char*)buf.data(), len);

    file.close();

    return buf;
}



std::string clReadFileText(const std::string& path)
{
    std::ifstream file;
    file.open(path, std::ios::in);

    if(!file.is_open())
    {
        std::cout << "failed to open file" << std::endl;

        return "";
    }

    std::string str;
    std::string line;

    while(std::getline(file, line))
    {
        str += line + "\n";
    }

    file.close();

    return str;
}



void clWriteFile(void* data, int memsize, int memcount, const std::string& path, WriteType type)
{

}