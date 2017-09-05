#include "FileCodeReader.hpp"

#include <iostream>

using namespace std;

FileCodeReader::FileCodeReader(string filename) : m_fileStream(ifstream(filename))
{
}

bool FileCodeReader::hasNextLine()
{
    return m_fileStream.peek() != EOF;
}

string FileCodeReader::getNextLine()
{
    string line;
    getline(m_fileStream, line);
    return line;
}

void FileCodeReader::close()
{
    m_fileStream.close();
}
