#include <iostream>
#include "hashtable.h"

int main() {
    HashTable a;
    a.insert(Key("first"), Value("f"));
    a.insert(Key("second"), Value("f"));
    a.insert(Key("third"), Value("f"));

    a.clear();
    std::cout<<a.size();
    return 0;
}
