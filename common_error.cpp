#include "common_error.h"

const char* Error::what() const noexcept{
    return msg_error.c_str();
}

Error::Error(std::string msj)noexcept: msg_error(msj){}
