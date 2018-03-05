#include "RedBlack.h"

void RedBlack::Left_Rotate(RBNode*x) { //RR회전
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

void RedBlack::Right_Rotate(RBNode*x) { //LL회전
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
		else // 중복이 안된다는 것으로 가정
			return;
	}
	Node->SetParent(pp);
	if (!pp) root = Node;
	else if (Node->GetNum()<pp->GetNum()){
		pp->SetLeft(Node);
	}
	else
		pp->SetRight(Node);
	Node->SetColortoRed(); // 무작적 레드노드로 했으니 조건이 위반될
						   // 가능성이 있다.
	                       // red-red biolation을 수정하자.
	RB_INSERT_FIXUP(Node);
}
// rb biolation의 조건들
// 1. OK 
//    1.	각 노드는 red or black이라는 각 각의 칼라를 부여할 것이다
// 2. 만약 z루트노드라면 위반, 아니라면 OK
//    루트 노드는 항상 블랙이다.
// 3. OK   
//    모든 리프 노드(즉, NIL)는 black이다.
// 4. z의 부모 p[z] 가 red이면 위반
//    red노드의 자식들은 전부 black이다
// 5. OK   
//    모든 노드에 대해서 그 노드로부터 자손인 리프 노드에 이르는 모든 경로에는 동일한 개수의 black노드가 존재해야 한다
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
	root->SetColortoBlack(); //의미가 없을 수도 있음
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
			if (IsRed(w)) { // 그 형제노드가 red 노드인 경우 case 1
				w->SetColortoBlack(); //w가 까만색으로
				xparent->SetColortoRed();
				Left_Rotate(xparent);
				w=xparent->GetRight();
			}
			if ( IsBlack(w->GetLeft()) && IsBlack(w->GetRight())) { //w도 black w의 자식들도 black
				w->SetColortoRed();
				x = xparent;// 한칸 위로
				xparent = x->GetParent();
				if (xparent && x == xparent->GetLeft())
					IsLeft = true;
			}
			else {
				if (IsBlack(w->GetRight())) { //w의 오른쪽 자식이 블랙이면..
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
			//case4에서 처리를 하면 무조건 while문을 나가야한다. while 문을 나가야 해서 이렇게함
			//x라는 포인터변수만 root를 가리키게 만듬
		}
		else { //case 5678
			w = xparent->GetLeft();
			if (IsRed(w)) { // 그 형제노드가 red 노드인 경우 case 1
				w->SetColortoBlack(); //w가 까만색으로
				xparent->SetColortoRed(); //B가 빨간색으로 
				Right_Rotate(xparent);//색깔을 미리바꾸고 로테이트를 한다.
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
		x->SetColortoBlack(); //root의 칼라를 블랙으로 바꿈
}
