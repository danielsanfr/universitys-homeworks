#ifndef FILECODEREADER_HPP
#define FILECODEREADER_HPP

#include <string>
#include <fstream>

#include "CodeReader.hpp"

class FileCodeReader : public CodeReader
{
public:
    FileCodeReader(std::string filename);
    bool hasNextLine();
    std::string getNextLine();
    void close();
private:
    std::ifstream m_fileStream;
};

#endif // FILECODEREADER_HPP
