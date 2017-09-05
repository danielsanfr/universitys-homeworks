#ifndef CODEREADER_HPP
#define CODEREADER_HPP

#include <string>

class CodeReader {
public:
    virtual bool hasNextLine() = 0;
    virtual std::string getNextLine() = 0;
    virtual void close() = 0;
};

#endif // CODEREADER_HPP
