#pragma once

#include <string>
#include <vector>
#include "glm/matrix.hpp"


enum class DataType {
	model,
	mesh,
	material,
	bone

};

class Node {

	//TODO  remove getters & setters
public:
	Node() = delete;
	Node(std::string name, Node* parent, glm::mat4 nodeTransformation, DataType dataType);
	Node(std::string name, Node* parent, DataType dataType);						// TODO add datatype in constructor
	~Node();

	Node(Node& node) = delete;

//	void addChild(std::unique_ptr<Node> childNode);
	std::vector<Node*>& getChildren();

	std::string getName();
	glm::mat4& getNodeTransformation();
	Node& getParent();

	void deleteNode();

	void setData(void* data);
	void* getData();

	DataType getDataType();
	void setDataType(DataType dataType);
	void printDataType();

private:
	void deleteChildren(Node* node);
	//void applyTransformation(Node* node);
private:
	std::string m_name;
	Node* m_parent;
	std::vector<Node*> m_children;
	glm::mat4 m_nodeTransformation;

	void* m_data = nullptr;
	DataType m_dataType;

};

