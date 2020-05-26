#ifndef COMMON_FILE_H
#define COMMON_FILE_H
#include <exception>
#include <fstream>
#include <string>

struct BadFile : public std::exception {
public:
   const char *what() const throw() {
      return "File couldn't be opened!\n";
   }
};

class File {
    private:
        std::ifstream file;
    public:
    explicit File(std::string);   
    ~File();
    bool read(std::string& line);
    bool read(char& c);
    void go_first();
};


#endif
