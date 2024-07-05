#include <stdexcept>
#include <string>

#ifndef ERROR_H
#define ERROR_H

using std::string;
class MatrixError : public std::runtime_error{
public:
    using runtime_error::runtime_error;
};

class IoError : public std::runtime_error{
public:
    using runtime_error::runtime_error;
};

#endif