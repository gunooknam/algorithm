#pragma once
#include <iostream>
#define STR_MAX 60
#define RED true
#define BLACK false
class RBNode 
{
private:
	std::pair<int , char[STR_MAX] > data;
	RBNode * left;
	RBNode * right;
	RBNode * parent;
	bool color;
	// black=0, red=1 //default = black = 0
public:
	RBNode() {
		color = false;
		left = NULL;
		right = NULL;
		parent = NULL;
	}
	void SetLeft(RBNode* pLeft) { this->left = pLeft; }
	void SetRight(RBNode* pRight) { this->right = pRight; }
	void SetParent(RBNode* pParent) { this->parent = pParent; }
	RBNode* GetLeft() { return this->left;}
	RBNode* GetRight() { return this->right;}
	RBNode* GetParent() { return this->parent;}
	int GetNum() {return data.first;}
	std::string GetValue() {return data.second;}
	void SetNum(int num) {data.first = num;}
	void SetValue(char*str){strcpy_s(data.second, str);}
	void SetColortoRed() {color = RED;}
	void SetColortoBlack() {color = BLACK;}
	bool GetColor() {return color;}
};