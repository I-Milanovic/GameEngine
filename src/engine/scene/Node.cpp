#include "Node.h"
#include <iostream>



Node::Node(std::string name, Node* parent, glm::mat4 nodeTransformation, DataType dataType)
 :	m_name(name),
	m_parent(parent),
	m_nodeTransformation(nodeTransformation),
	m_dataType(dataType) {
	if (parent)
		m_parent->m_children.push_back(this);
	//std::cout << "Node created: " << getName() << std::endl;
}

Node::Node(std::string name, Node* parent, DataType dataType) : Node(name, parent, glm::mat4(1.0f), dataType) {}

Node::~Node() {
	std::cout << "Node deleted: " << getName() << std::endl;
}

//void Node::addChild(std::unique_ptr<Node> childNode) {
//	//m_children.push_back(std::move(childNode));
//}

std::vector<Node*>& Node::getChildren() {
	return m_children;
}

std::string Node::getName() {
	return m_name;
}

glm::mat4& Node::getNodeTransformation() {
	return m_nodeTransformation;
}

Node& Node::getParent() {
	return *m_parent;
}

void Node::deleteNode() {
	deleteChildren(this);
}

void Node::setData(void* data) {
	m_data = data;
}

void* Node::getData() {
	return m_data;
}

DataType Node::getDataType() {
	return m_dataType;
}

void Node::setDataType(DataType dataType) {
	m_dataType = dataType;
}

void Node::deleteChildren(Node* node) {

	for (int i = 0; i < node->m_children.size(); i++) {
		deleteChildren(node->m_children.at(i));
	}
	if (m_parent) {
		std::vector<Node*>::iterator pend = std::remove_if(m_parent->getChildren().begin(), m_parent->getChildren().end(),
			[this](Node* node) {return this->m_name == node->getName();});
		m_parent->getChildren().erase(pend, m_parent->getChildren().end());
	}

	delete node;
}

//void Node::applyTransformation(Node* node) {
//	for (int i = 0; i < node->m_children.size(); i++) {
//		if (node->getDataType() == DataType::mesh) {
//			applyTransformation(node);
//			static_cast<Model*>(node->getData());
//			// apply transform
//
//		}
//	}
//}

void Node::printDataType() {
	if (m_dataType == DataType::model)
		std::cout << "Data Type: model" << std::endl;

	if (m_dataType == DataType::bone)
		std::cout << "Data Type: bone" << std::endl;

	if (m_dataType == DataType::mesh)
		std::cout << "Data Type: mesh" << std::endl;

	if (m_dataType == DataType::material)
		std::cout << "Data Type: material" << std::endl;
}
