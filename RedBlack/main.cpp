#include <iostream>
#include "RedBlack.h"
#include "RBNode.h"
#include <crtdbg.h>
int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //메모리누수 
	RedBlack rb;
	RBNode * node = new RBNode;
	node->SetNum(10);
	rb.insert(node);
	RBNode * node1 = new RBNode;
	node1->SetNum(85);
	rb.insert(node1);
	rb.printRedBlackTree();
	RBNode * node2 = new RBNode;
	node2->SetNum(15);
	rb.insert(node2);
	rb.printRedBlackTree();
	RBNode * node3 = new RBNode;
	node3->SetNum(70);
	rb.insert(node3);
	rb.printRedBlackTree();
	RBNode * node4 = new RBNode;
	node4->SetNum(20);
	rb.insert(node4);
	rb.printRedBlackTree();
	// Testing //
	std::cout << "----------------------------------------" << std::endl;
	delete rb.rbdelete(rb.search(100));
	rb.printRedBlackTree();
	std::cout << "----------------------------------------" << std::endl;
	delete rb.rbdelete(rb.search(20));
	rb.printRedBlackTree();
	std::cout << "----------------------------------------" << std::endl;
	delete rb.rbdelete(rb.search(15));
	rb.printRedBlackTree();
	std::cout << "----------------------------------------" << std::endl;
	delete rb.rbdelete(rb.search(85));
	rb.printRedBlackTree();
	std::cout << "----------------------------------------" << std::endl;
	delete rb.rbdelete(rb.search(70));
	std::cout << "----------------------------------------" << std::endl;
	rb.printRedBlackTree();
}
