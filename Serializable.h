#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <string>
#include <sstream>

/*
 * binary serialization inteface. all containers must implement.
*/
class BinarySerializable {
    public:
        virtual void serialize(std::string* data, int depth) = 0;
        virtual void deserialize(std::string* data, int depth) = 0;
};
#endif