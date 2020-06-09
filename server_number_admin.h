#ifndef NUMBER_ADMIN
#define NUMBER_ADMIN
#include <fstream>
#include <vector>
#include "common_error.h"
#include <string>

class NumbersAdmin{
private:
    std::vector<std::string> numbers;
    size_t pos;
public:
    explicit NumbersAdmin(std::string file_name);
    ~NumbersAdmin();
    std::string get_secret_number();   
};

#endif
