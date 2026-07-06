#include "HashMap.h"

int HashMap::hashFunction(const std::string &ingredient) {

    unsigned int hash_value = 0;
    // Hash value = multiply current hash value by 31 (base 31) and add the ASCII value of the char in the string
    for (char c: ingredient) {
        hash_value = (hash_value * 31) + c;
    }
    return hash_value % capacity;
}