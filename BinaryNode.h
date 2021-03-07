#ifndef BINARYNODE_H
#define BINARYNODE_H

#include <cstdarg>
#include <optional>
#include <functional>
#include <vector>
#include <iostream>
#include "Serializable.h"
#include <type_traits>

template<class Serial> 
concept BinarySerialize = std::is_base_of<BinarySerializable, Serial>::value;

template<class Container, class NodeData, class... ContainerArgs> 
    requires BinarySerialize<Container>
class BinaryNode final : public BinarySerializable {
    public:
        BinaryNode(std::function<bool(NodeData*)> leftCreate, std::function<bool(NodeData*)> rightCreate, NodeData lData, NodeData rData, ContainerArgs ... args) : containedObject(std::nullopt), left(nullptr), right(nullptr), leftData(lData), rightData(rData) {
            bool lCreate = leftCreate(&lData);
            bool rCreate = rightCreate(&rData);

            if(lCreate) {
                left = std::make_shared<BinaryNode>(leftCreate, rightCreate, lData, lData, args...);
            }

            if(rCreate) {
                right = std::make_shared<BinaryNode>(leftCreate, rightCreate, rData, rData, args...);
            }
            

            if(!lCreate && !rCreate) {
                containedObject = Container(args...);
            }            
        };

        void getLeafOfTree(std::vector<std::optional<Container>*>* result, std::function<bool(NodeData, bool, std::optional<Container>&)> eval) {
            bool leftTraverse = eval(leftData, (left == nullptr && right == nullptr), containedObject);
            bool rightTraverse = eval(rightData, (left == nullptr && right == nullptr), containedObject);
            
            if(left != nullptr && leftTraverse) {
                left->getLeafOfTree(result, eval);
            }
            if(right != nullptr && rightTraverse) {
                right->getLeafOfTree(result, eval);
            }
            if(left == nullptr && right == nullptr) {
                if(leftTraverse || rightTraverse) {
                    result->push_back(&containedObject);
                }
            }
        };

        void serialize(std::string* data, int depth) {
            *data = *data + "{";
            if(left != nullptr) {
                left->serialize(data, depth + 1);
            }

            if(right != nullptr) {
                right->serialize(data, depth + 1);
            }

            if(left == nullptr && right == nullptr) {
                if(containedObject.has_value()) {
                    containedObject.value().serialize(data, depth + 1);
                }
            }
            *data = *data + "}";
        }

        void deserialize(std::string* data, int depth) {
            while(true) {
                char c = data->at(0);     
                if(c == '{') {
                    data->erase(0, 1);
                    if(left != nullptr) {
                        ++depth;
                        left->deserialize(data, depth);
                    }
                    if(right != nullptr) {
                        ++depth;
                        right->deserialize(data, depth);
                    }
                }
                if(c == '}') {
                    data->erase(0, 1);
                    --depth;
                    return;
                }
                if(left == nullptr && right == nullptr) {
                    if(containedObject.has_value()) {
                        containedObject.value().deserialize(data, depth + 1);                    
                    }
                }
            }
        }

    private:
        std::optional<Container> containedObject;  
        std::shared_ptr<BinaryNode> left;
        std::shared_ptr<BinaryNode> right;
        NodeData leftData;
        NodeData rightData;
};
#endif