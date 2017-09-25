
#include <Resource/BlenderFile.hpp>

struct Header {
    char identifier[7];
    char pointerSize;
    char endianess;
    char version[3];
};

struct fileBlock {
    char code[4];
    int size;
    void* address;
    int index;
    int count;
};

static void readHeader(std::istream & input) {

}

namespace jerobins {
    namespace resource {
        
    }
}