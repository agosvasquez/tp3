#ifndef ERROR
#define ERROR
#include <typeinfo>
#include <string>


class Error : public std::exception {
protected:
    std::string msg_error;
public:
    const char *what() const noexcept;
    explicit Error(std::string msg_error) noexcept;
    ~Error() noexcept {}
};

class InvalidCommand : public std::exception {
public:
   const char *what()const noexcept {
      return "Error: comando inválido. Escriba AYUDA para obtener ayuda\n";
   }
};

#endif
