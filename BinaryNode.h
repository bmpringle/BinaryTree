#ifndef BINARYNODE_H
#define BINARYNODE_H

#include <cstdarg>
#include <optional>
#include <functional>
#include <vector>
#include <iostream>

static int c = 1;

template<class Container, class NodeData, class... ContainerArgs>
class BinaryNode {
    public:
        BinaryNode<Container>(std::function<bool(NodeData*)> leftCreate, std::function<bool(NodeData*)> rightCreate, NodeData lData, NodeData rData, ContainerArgs ... args) : containedObject(std::nullopt), left(nullptr), right(nullptr), leftData(lData), rightData(rData) {
            bool lCreate = leftCreate(&lData);
            bool rCreate = rightCreate(&rData);

            if(lCreate) {
                left = std::make_shared<BinaryNode>(leftCreate, rightCreate, lData, rData, args...);
            }

            if(rCreate) {
                right = std::make_shared<BinaryNode>(leftCreate, rightCreate, lData, rData, args...);
            }
            

            if(!lCreate && !rCreate) {
                containedObject = Container(args...);
                std::cout << c << ". " << std::endl;
                ++c;
            }            
        };

        void getLeafOfTree(std::vector<std::optional<Container>*>* result, std::function<bool(NodeData)> eval) {
            bool leftTraverse = eval(leftData);
            bool rightTraverse = eval(rightData);
            
            if(left != nullptr && leftTraverse) {
                left->getLeafOfTree(result, eval);
            }
            if(right != nullptr && rightTraverse) {
                right->getLeafOfTree(result, eval);
            }
            if(left == nullptr && right == nullptr) {
                result->push_back(&containedObject);
            }
        };

    private:
        std::shared_ptr<BinaryNode> left;
        std::shared_ptr<BinaryNode> right;
        NodeData leftData;
        NodeData rightData;
        std::optional<Container> containedObject;  

};
#endif