#pragma once

#include "Node.h"

class SceneGraphTree {


public:
	SceneGraphTree() = default;
	~SceneGraphTree();
	void applyTransformation(Node* node);

	Node* getRootNode();
	void setRootNode(Node* node);

private:
	void applyTransformation(Node* node, glm::mat4 transform);
private:
	Node* m_rootNode = nullptr;
	std::string m_ignoreNodeName;

};
