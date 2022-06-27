#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "BinaryNode.h"

template<typename Container, class NodeData, class... ContainerArgs>
    requires BinarySerialize<Container>
class BinaryTree final {
    public:
        BinaryTree(std::function<bool(NodeData*)> leftCreate, std::function<bool(NodeData*)> rightCreate, NodeData lData, NodeData rData, ContainerArgs ... args) : rootNode(std::nullopt){
            rootNode = BinaryNode<Container, NodeData, ContainerArgs...>(leftCreate, rightCreate, lData, rData, args...);
        }
        
        std::vector<std::optional<Container>*> getAllLeavesOfTree() {
            if(!rootNode.has_value()) {
                std::cout << "rootnode is null" << std::endl;
                abort();
            }
            std::vector<std::optional<Container>*> vector = std::vector<std::optional<Container>*>();
            rootNode.value().getAllLeavesOfTree(&vector);
            return vector;
        }

        std::vector<std::optional<Container>*> getLeafOfTree(std::function<bool(NodeData, bool, std::optional<Container>*)> eval) {
            if(!rootNode.has_value()) {
                std::cout << "rootnode is null" << std::endl;
                abort();
            }
            std::vector<std::optional<Container>*> vector = std::vector<std::optional<Container>*>();
            rootNode.value().getLeafOfTree(&vector, eval);
            return vector;
        }

        BinaryTree() : rootNode(std::nullopt) {

        }

        std::string serialize() {
            if(!rootNode.has_value()) {
                std::cout << "rootnode is null" << std::endl;
                abort();
            }
            std::string ret = "";
            rootNode.value().serialize(&ret, 0);
            return ret;
        }

        void deserialize(std::string str) {
            if(!rootNode.has_value()) {
                std::cout << "rootnode is null" << std::endl;
                abort();
            }
            rootNode.value().deserialize(&str, 0);
        }

    private:
        std::optional<BinaryNode<Container, NodeData, ContainerArgs...>> rootNode;
};
#endif
