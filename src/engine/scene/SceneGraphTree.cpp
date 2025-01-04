#include "SceneGraphTree.h"
#include <iostream>
#include "Model.h"

SceneGraphTree::~SceneGraphTree() {
	std::cout << "Deleting: SceneGraphTree" << std::endl;
	m_rootNode->deleteNode();
}

void SceneGraphTree::applyTransformation(Node* node) {
	Model* model = static_cast<Model*>(node->getData());
	glm::mat4 mat = model->getEntity().getModelMatrix();
	m_ignoreNodeName = node->getName();
	model->getEntity().updateModelMatrix();
	applyTransformation(&node->getParent(), mat);
}


void SceneGraphTree::applyTransformation(Node* node, glm::mat4 transform) {
	unsigned int childSize = node->getChildren().size();
	
	for (int i = 0; i < childSize; i++) {
		Node* childNode = node->getChildren().at(i);
		if (childNode->getDataType() == DataType::model) {
		//	if (childNode->getName() != m_ignoreNodeName) {	// prolly not needed
				Model* model = static_cast<Model*>(childNode->getData());
				model->getEntity().applyMatrixTransform(transform);
				model->getEntity().updateModelMatrix();
				glm::mat4 mat = model->getEntity().getModelMatrix();
				applyTransformation(childNode, mat);
		//	}
		}
	}

}

Node* SceneGraphTree::getRootNode() {
	return m_rootNode;
}

void SceneGraphTree::setRootNode(Node* node) {
	m_rootNode = node;
}
