#include "BinaryTree.h"
#include <memory>
#include <optional>

bool intCheck(int* i) {
    bool tf = (*i < 4);
    ++*i;
    return tf;
}

bool isIntThree(int i) {
    return i < 4;
}

int main() {
    BinaryTree<std::string, int, std::string> tree = BinaryTree<std::string, int, std::string>(intCheck, intCheck, 0, 0, "a");
    std::vector<std::optional<std::string>*> strs = tree.getLeafOfTree(isIntThree);
    std::cout << strs.size() << std::endl;
    for(std::optional<std::string>* s : strs) {
        std::cout << (*s).value() << std::endl;
        *s = "b"; 
    }
    strs = tree.getLeafOfTree(isIntThree);
    for(std::optional<std::string>* s : strs) {
        std::cout << (*s).value() << std::endl;
    }
}