#include "RedBlack.h"

void RedBlack::Left_Rotate(RBNode*x) { //RRȸ��
	RBNode * mid = x->GetRight();
	x->SetRight(mid->GetLeft());
	if(mid->GetLeft())
	mid->GetLeft()->SetParent(x);
	mid->SetParent(x->GetParent());
	if (x->GetParent() == NULL) {
		root = mid;
	}
	else if (x == x->GetParent()->GetLeft()) {
		x->GetParent()->SetLeft(mid);
	}
	else if (x == x->GetParent()->GetRight()) {
		x->GetParent()->SetRight(mid);
	}
	mid->SetLeft(x);
	x->SetParent(mid);
}

void RedBlack::Right_Rotate(RBNode*x) { //LLȸ��
	RBNode * mid = x->GetLeft();
	x->SetLeft(mid->GetRight());
	if(mid->GetRight())
	mid->GetRight()->SetParent(x);
	mid->SetParent(x->GetParent());
	if (x->GetParent() == NULL) {
		root = mid;
	}
	else if (x == x->GetParent()->GetLeft()) {
		x->GetParent()->SetLeft(mid);
	}
	else if (x == x->GetParent()->GetRight()) {
		x->GetParent()->SetRight(mid);
	}
	mid->SetRight(x);
	x->SetParent(mid);
}

void RedBlack::insert(RBNode*Node) {
	RBNode*pp = NULL;
	RBNode*p = root;
	while (p) {
		pp = p;
		if (Node->GetNum() < p->GetNum()) {
			p = p->GetLeft();
		}
		else if (Node->GetNum() > p->GetNum()) {
			p = p->GetRight();
		}
		else // �ߺ��� �ȵȴٴ� ������ ����
			return;
	}
	Node->SetParent(pp);
	if (!pp) root = Node;
	else if (Node->GetNum()<pp->GetNum()){
		pp->SetLeft(Node);
	}
	else
		pp->SetRight(Node);
	Node->SetColortoRed(); // ������ ������� ������ ������ ���ݵ�
						   // ���ɼ��� �ִ�.
	                       // red-red biolation�� ��������.
	RB_INSERT_FIXUP(Node);
}
// rb biolation�� ���ǵ�
// 1. OK 
//    1.	�� ���� red or black�̶�� �� ���� Į�� �ο��� ���̴�
// 2. ���� z��Ʈ����� ����, �ƴ϶�� OK
//    ��Ʈ ���� �׻� ���̴�.
// 3. OK   
//    ��� ���� ���(��, NIL)�� black�̴�.
// 4. z�� �θ� p[z] �� red�̸� ����
//    red����� �ڽĵ��� ���� black�̴�
// 5. OK   
//    ��� ��忡 ���ؼ� �� ���κ��� �ڼ��� ���� ��忡 �̸��� ��� ��ο��� ������ ������ black��尡 �����ؾ� �Ѵ�
void RedBlack::RB_INSERT_FIXUP(RBNode*Node) {
	RBNode*z=Node;
	RBNode*uncle = NULL;
	while (z->GetParent()&&z->GetParent()->GetColor()==RED) {
		if (z->GetParent() == z->GetParent()->GetParent()->GetLeft()) {
			uncle = z->GetParent()->GetParent()->GetRight();
			if (uncle!=NULL &&uncle->GetColor() == RED) { //case 1
				z->GetParent()->SetColortoBlack();
				uncle->SetColortoBlack();
				z->GetParent()->GetParent()->SetColortoRed();
				z = z->GetParent()->GetParent();
			}
			else {  //case2, 3
					if (z == z->GetParent()->GetRight()) {
						z = z->GetParent();
						Left_Rotate(z);
					}
					z->GetParent()->SetColortoBlack();
					z->GetParent()->GetParent()->SetColortoRed();
					Right_Rotate(z->GetParent()->GetParent());
			}
		}
		else{
			uncle = z->GetParent()->GetParent()->GetLeft();
			if (uncle != NULL&&uncle->GetColor() == RED) { //case 4
				z->GetParent()->SetColortoBlack();
				uncle->SetColortoBlack();
				z->GetParent()->GetParent()->SetColortoRed();
				z = z->GetParent()->GetParent();
			}
			else {  //case5, 6
				if (z == z->GetParent()->GetLeft()) {
					z = z->GetParent();
					Right_Rotate(z);
				}
				z->GetParent()->SetColortoBlack();
				z->GetParent()->GetParent()->SetColortoRed();
				Left_Rotate(z->GetParent()->GetParent());
			}
		}
	}
	root->SetColortoBlack(); //�ǹ̰� ���� ���� ����
}
RBNode*RedBlack::TREE_SUCCESSOR(RBNode*p) {
	RBNode* prevprev = p;
	RBNode* prev = p->GetLeft();
	while (prev->GetRight()) {
		prevprev = prev;
		prev = prev->GetRight();
	}
	return prev;
}
RBNode* RedBlack::rbdelete(RBNode*z) {
	RBNode*y = NULL;
	RBNode*x = NULL;
	if (z == NULL)
		return NULL;

	if (z->GetLeft() == NULL || z->GetRight() == NULL)
		y = z;
	else
		y = TREE_SUCCESSOR(z);

	if (y->GetLeft() != NULL)
		x = y->GetLeft();
	else
		x = y->GetRight();

	if (x)
		x->SetParent(y->GetParent());
		RBNode*xparent = y->GetParent();

	bool IsLeft = false;
	if (y->GetParent() == NULL)
		root = x;
	else if (y == y->GetParent()->GetLeft()) {
		y->GetParent()->SetLeft(x);
		IsLeft = true;
	}
	else {
		y->GetParent()->SetRight(x);
		IsLeft = false;
	}

	if (y != z)
		z->SetNum(y->GetNum());

	if (y->GetColor() == BLACK) {
		RB_DELETE_FIXEDUP(x,xparent,IsLeft);
	}
	return y;
}

void RedBlack::RB_DELETE_FIXEDUP(RBNode*x,RBNode* xparent, bool IsLeft) {
	RBNode*w = NULL;
	while (x!= root && IsBlack(x)) {
		if (IsLeft) { //case 1234
			w = xparent->GetRight();
			if (IsRed(w)) { // �� ������尡 red ����� ��� case 1
				w->SetColortoBlack(); //w�� �������
				xparent->SetColortoRed();
				Left_Rotate(xparent);
				w=xparent->GetRight();
			}
			if ( IsBlack(w->GetLeft()) && IsBlack(w->GetRight())) { //w�� black w�� �ڽĵ鵵 black
				w->SetColortoRed();
				x = xparent;// ��ĭ ����
				xparent = x->GetParent();
				if (xparent && x == xparent->GetLeft())
					IsLeft = true;
			}
			else {
				if (IsBlack(w->GetRight())) { //w�� ������ �ڽ��� ���̸�..
					w->GetLeft()->SetColortoBlack();
					w->SetColortoRed();
					Right_Rotate(w);
					w = xparent->GetRight();
				}

				if (IsBlack(xparent))
					w->SetColortoBlack();
				else
					w->SetColortoRed();
				xparent->SetColortoBlack();

				w->GetRight()->SetColortoBlack();
				Left_Rotate(xparent);
				x = root;
				xparent=NULL;
			}
			//case4���� ó���� �ϸ� ������ while���� �������Ѵ�. while ���� ������ �ؼ� �̷�����
			//x��� �����ͺ����� root�� ����Ű�� ����
		}
		else { //case 5678
			w = xparent->GetLeft();
			if (IsRed(w)) { // �� ������尡 red ����� ��� case 1
				w->SetColortoBlack(); //w�� �������
				xparent->SetColortoRed(); //B�� ���������� 
				Right_Rotate(xparent);//������ �̸��ٲٰ� ������Ʈ�� �Ѵ�.
				w = xparent->GetLeft();
			}
			if (IsBlack(w->GetLeft()) && IsBlack(w->GetRight())) {
				w->SetColortoRed();
				x = xparent;
				xparent = x->GetParent();
				if (xparent&&x == xparent->GetLeft())
					IsLeft = true;
			}
			else {
				if (IsBlack(w->GetLeft())) {
					w->GetRight()->SetColortoBlack();
					w->SetColortoRed();
					Left_Rotate(w);
					w = xparent->GetLeft();
				}
				if (IsBlack(xparent))
					w->SetColortoBlack();
				else
					w->SetColortoRed();
				xparent->SetColortoBlack();

				w->GetLeft()->SetColortoBlack();
				Right_Rotate(xparent);
				x = root;
				xparent = NULL;
			}
		}
	}
	if(x)
		x->SetColortoBlack(); //root�� Į�� ������ �ٲ�
}
