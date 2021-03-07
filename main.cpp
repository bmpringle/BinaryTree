#include "BinaryTree.h"
#include <memory>
#include <optional>
#include <sstream>
#include <algorithm>
#include <filesystem>

class serializableString : public BinarySerializable {
    public:
        void serialize(std::string* data, int depth) {
            std::cout << depth << std::endl;
            for(int i = 0; i < depth; ++i) {
                //4 spaces
                *data = *data + "    ";                
            }
            *data = *data + "{\n";
            for(int i = 0; i < depth + 1; ++i) {
                //4 spaces
                *data = *data + "    ";                
            }
            *data = *data + containedString + "\n";
            for(int i = 0; i < depth; ++i) {
                //4 spaces
                *data = *data + "    ";                
            }
            *data = *data + "}";
        }

        void deserialize(std::stringstream* s, int depth) {
            std::cout << depth << std::endl;
            std::string val;
            if (getline(*s, val, ' ')) {
                std::cout << val << std::endl;
                containedString = val;
            }
        }

        serializableString(std::string str) {
            containedString = str;
        } 

        std::string containedString;
};

bool intCheck(int* i) {
    bool tf = (*i < 4);
    ++*i;
    return tf;
}

bool isIntThree(int i, bool isLeaf, std::optional<serializableString> containedItem) {
    if(!isLeaf) {
        return true;
    }else {
        return i == 4;
    }
}

int main() {
    BinaryTree<serializableString, int, serializableString> tree = BinaryTree<serializableString, int, serializableString>(intCheck, intCheck, 0, 0, serializableString("a"));
    std::vector<std::optional<serializableString>*> strs = tree.getLeafOfTree(isIntThree);

    //pre-test
    std::cout << strs.size() << std::endl;
    for(std::optional<serializableString>* s : strs) {
        std::cout << (*s).value().containedString << std::endl;
        *s = serializableString("b"); 
    }
    strs = tree.getLeafOfTree(isIntThree);
    for(std::optional<serializableString>* s : strs) {
        std::cout << (*s).value().containedString << std::endl;
    }

    std::cout << "\n\n----------------------------------------------------------------------------\n\n" << std::endl;

    std::cout << tree.serialize() << std::endl;

    tree.deserialize(tree.serialize());
    
    std::cout << "\n\n----------------------------------------------------------------------------\n\n" << std::endl;

    std::cout << tree.serialize() << std::endl;

    std::cout << "\n\n----------------------------------------------------------------------------\n\n" << std::endl;

    std::stringstream s ("[(grass|0|3|4),(dirt|1|8|-2),(water|1|1|3)]");
    std::string lineData = s.str();
    lineData.erase(remove(lineData.begin(), lineData.end(), '['), lineData.end());
    lineData.erase(remove(lineData.begin(), lineData.end(), ']'), lineData.end());
    std::cout << lineData << std::endl;
    std::stringstream s2(lineData);
    while(std::getline(s2, lineData, ',')) {
        std::string rawData = lineData.substr(1, lineData.size() - 2);
        std::stringstream s3(rawData);
        std::string datatoken;
        //0 is blocktype, 1 is pos.x, 2 is pos.y, 3 is po.z
        int tokennum = 0;

        std::string blocktypename = "";
        std::string xstr = "";
        std::string ystr = "";
        std::string zstr = "";

        while(std::getline(s3, datatoken, '|')) {
            switch(tokennum) {
                case 0:
                    blocktypename = datatoken;
                    break;
                case 1:
                    xstr = datatoken;
                    break;
                case 2:
                    ystr = datatoken;
                    break;
                case 3:
                    zstr = datatoken;
                    break;
            }
            ++tokennum;
        }
        std::cout << "typestr: " << blocktypename << ", xstr: " << xstr << ", ystr: " << ystr << ", zstr: " << zstr << std::endl; 
    }
}