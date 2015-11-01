/************************************************************************/
/*   ������ʵ�ֶ������Ĺ��죬����������������������������к�         */
/*   ���Թ����Ψһ�Ķ�������������������ĺ����������                 */
/*   ����ֻ���Ǵ�д��ĸ A-Z �����ַ���ʶ�������Ǹ�ʾ������              */
/************************************************************************/
#include <iostream>
using namespace std;
#include <string>

typedef struct node
{
	char value;
	struct node* lchild;
	struct node* rchild;
	node(){
		value = NULL;
		lchild = NULL;
		rchild = NULL;
	}
}*Pnode,*BTree,Node;

/************************************************************************/
/*  ���ݶ��������ص�ʹ������������к�����������н��еݹ鹹�������    */
/************************************************************************/
bool createBTree(string prefixStr, string infixStr, Pnode &parent)
{
	if (0 == prefixStr.length() && 0 == infixStr.length())
	{
		return true;
	}
	if (0 >= prefixStr.length() || 0 >= infixStr.length() || prefixStr.length() != infixStr.length())
	{
		return false;
	} 
	else
	{
		Pnode root = new Node();
		char tempRoot = prefixStr.at(0);
		int tempRootIndex = infixStr.find(tempRoot);
		root->value = tempRoot;
		root->lchild = NULL;
		root->rchild = NULL;
		parent = root;
		if(!createBTree(prefixStr.substr(1,tempRootIndex), infixStr.substr(0,tempRootIndex), root->lchild))
		{
			return false;
		}
		if (!createBTree(prefixStr.substr(tempRootIndex+1,prefixStr.length()-tempRootIndex), infixStr.substr(tempRootIndex+1,infixStr.length()-tempRootIndex), root->rchild))
		{
			return false;
		}
		return true;
	}
}

/************************************************************************/
/* ����������������                                                   */
/************************************************************************/
string getPostfixOfExpress(BTree bTree)
{
	if (bTree == NULL)
	{
		return "";
	}
	return getPostfixOfExpress(bTree->lchild)+getPostfixOfExpress(bTree->rchild)+bTree->value;

}

int main()
{
	string prefixStr;
	string infixStr;

	cout<<"Please input the prefix express of bTree with A-Z:"<<endl;
	cin>>prefixStr;
	cout<<"Please input the infix express of bTree with A-Z:"<<endl;
	cin>>infixStr;

	BTree bTree = new Node();
	bTree->lchild = NULL;
	bTree->rchild = NULL;

	if(createBTree(prefixStr, infixStr, bTree->lchild))
	{
		cout<<"The postfix of the input bTree is:"<<endl;
		cout<<getPostfixOfExpress(bTree->lchild)<<endl;
	}
	else
	{
		cout<<"Create bTree failed!"<<endl;
	}
	return 0;
}