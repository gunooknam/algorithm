#pragma once
#include "RBNode.h"
class RedBlack{
private:
	RBNode * root;
public:
	bool IsBlack(RBNode*Node) {
		return (Node == NULL) ? true : (Node->GetColor() == BLACK) ? true : false;
	}
	bool IsRed(RBNode*Node) {
		return (IsBlack(Node) == true) ? false : true;
	}
	void printRedBlackTree() {
		preOrderTraverse(root, 0);
	}
	void preOrderTraverse(RBNode*node, int depth) {
		for (int i = 0; i < depth; i++)
			std::cout << "	";
		if (node == NULL)
			std::cout << "NULL" << std::endl;
		else {
			std::cout << node->GetNum()<<","<<node->GetColor()<< std::endl;
			preOrderTraverse(node->GetLeft(), depth + 1);
			preOrderTraverse(node->GetRight(), depth + 1);
		}
	}
	RedBlack() {
		root = NULL;
	}
	~RedBlack(){
		if (root)
			postdelete(root);
	}
	void postdelete(RBNode*Node) {
		if (Node) {
			postdelete(Node->GetLeft());
			postdelete(Node->GetRight());
			delete Node;
		}
	}
	RBNode *GetRoot() { return root; }
	//부모 노드까지 고려해서 하는 Left_Rotate
	void Left_Rotate(RBNode*x); 

	void Right_Rotate(RBNode*x); 

	void insert(RBNode*Node);

	void RB_INSERT_FIXUP(RBNode*Node);

	RBNode*search(int id) {
		RBNode *p = root;
		while (p) {
			if (id < p->GetNum())
				p = p->GetLeft();
			else if (id > p->GetNum())
				p = p->GetRight();
			else
				return p;
		}
		return NULL;
	}
	RBNode* rbdelete(RBNode*pNode);
	RBNode* TREE_SUCCESSOR(RBNode*Node);
	void RB_DELETE_FIXEDUP(RBNode*x, RBNode* xparent, bool IsLeft);
};