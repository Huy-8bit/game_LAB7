#include <iostream>
#include <string>
#include <fstream>
using namespace std;
struct bstNode
{
	string data;
	bstNode *left;
	bstNode *right;
};
bstNode *getNewNode(string data)
{
	bstNode *newNode = new bstNode();
	newNode->data = data;
}
void insert(bstNode *root, int data);
int main()
{
	bstNode *root = NULL;
	return 0;
}