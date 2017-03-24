#pragma once
#include<iostream>
#include<string>
using namespace std;
template <class K,class V>
struct AVLTreeNode
{
	AVLTreeNode<K,V>* left;
	AVLTreeNode<K,V>* right;
	AVLTreeNode<K,V>* parent;
	int bf;
	K key;
	V value;
	AVLTreeNode(const K &_k, const V &_v)
	{
		left = NULL;
		right = NULL;
		parent = NULL;
		key = _k;
		value = _v;
		bf = 0;
	}
};
template<class K,class V>
class AVLtree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLtree()
		:root(NULL)
	{}
	AVLtree(const Node* _root)
		:_root(new Node())
	{
		root = _root;
	}
	~AVLtree()
	{}
public:
	bool Insert(K k, V v)
	{
		if (root == NULL)
		{
			root = new Node(k, v);
			root->bf = 0;
			return true;
		}
		
		Node*parent = NULL;
		Node*cur = root;
		while (cur)
		{
			if (cur->key < k)
			{
				parent = cur;
				cur = cur->right;
			}
			else if (cur->key > k)
			{
				parent = cur;
				cur = cur->left;
			}
			else
			{
				break;
			}
		}
		cur = new Node(k, v);
		if (parent->key < k)
		{
			 parent->right=cur;
			 cur->parent = parent;
		}
		else if (parent->key > k)
		{
			 parent->left=cur;
			 cur->parent = parent;
		}
		else
		{
			parent = cur;
		}
		while (cur->parent)
		{
			Node*pparent = cur->parent;
			if (pparent->left == cur)
			{
				pparent->bf--;
			}
			else
			{
				pparent->bf++;
			}
			if (pparent->bf == 0)
			{
				break;
			}
			else if (pparent->bf == -1 || pparent->bf == 1)
			{
				cur=pparent;
				pparent = cur->parent;
			}
			else
			{
				if (pparent->bf == 2)
				{
					Node*subR = pparent->right;
					Node*subRL = subR->left;
					Node*Sparent = pparent;
					if (pparent->right->bf==1)
					{
						//×ó
						rotateL(pparent);
						subR->bf = 0;
						Sparent->bf = 0;
						break;
					}
					else
					{
						//ÓÒ×ó
						rotateRL(pparent->right);
						subR->bf = 0;
						subRL->bf = 0;
						Sparent->bf = 0;
						break;
					}
				}

				else
				{
					Node*subL = pparent->left;
					Node*subLR = subL->right;
					Node*Sparent = pparent;
					if (pparent->left->bf ==-1)
					{
						//ÓÒ
						rotateR(pparent);
						subL->bf = 0;
						Sparent->bf = 0;
						break;
					}
					else
					{
						//×óÓÒ
						rotateLR(pparent->left);
						subL->bf = 0;
						subLR->bf = 0;
						Sparent->bf = 0;
						break;
					}
				}
			}
		}
		return true;
	}
	Node* Find(K k)
	{
		Node* cur = root;
	
		while (cur)
		{
			if (cur->key > k)
			{
				cur = cur->left;
			}
			else if (cur->key < k)
			{
				cur = cur->right;
			}
			else
			{
				return cur;
			}
		}
		return cur;
	}
	bool Delete(K k)
	{
		Node* cur = Find(k);
		Node* Pcur;
		Node*qcur;
		if (cur == NULL)
		{
			return false;
		}
		//ÓÐÁ½×ÓÅ®
		if (cur->left != NULL && cur->right != NULL)
		{
			Pcur = cur;
			qcur = cur->left;
			while (qcur->right != NULL)
			{
				Pcur = qcur;
				qcur = qcur->right;
			}
			Pcur->key = qcur->key;
			Pcur = qcur;
		}
		//ÓÐÒ»×ÓÅ®
		if (cur->left != NULL)
		{
			cur = cur->left;
		}
		else
		{
			cur = cur->right;
		}
	}
	//×óÓÒÐý
	void rotateLR(Node* parent)
	{
		Node*pparent = parent->parent;
		rotateL(parent);
		rotateR(pparent);
	}
	//ÓÒÐý
	void rotateR(Node* parent)
	{
		Node*subL = parent->left;
		Node*subLR = subL->right;
		parent->left = subLR;
		if (subLR)
			subLR->parent = parent;
		subL->right = parent;
		Node*pparent = parent->parent;
		parent->parent = subL;
		if (pparent == NULL)
		{
			root = subL;
			subL->parent = NULL;
		}
		else
		{
			if (pparent->left == parent)
			{
				pparent->left = subL;
			}
			else
			{
				pparent->right = subL;
			}
			subL->parent = pparent;
		}

	}
	//ÓÒ×óÐý
	void rotateRL(Node* parent)
	{
		Node*pparent = parent->parent;
		rotateR(parent);
		rotateL(pparent);
	}
	//×óÐý
	void rotateL(Node* parent)
	{
		Node* subR = parent->right;
		Node* subRL = subR->left;
		parent->right = subRL;
		if (subRL)
			subRL->parent = parent;
		subR->left = parent;
		Node*pparent = parent->parent;
		parent->parent = subR;
		if (pparent == NULL)
		{
			root = subR;
			subR->parent = NULL;
		}
		else
		{
			if (pparent->left == parent)
			{
				pparent->left = subR;
			}
			else
			{
				pparent->right = subR;
			}
			subR->parent = pparent;
		}
	}
public:
	void inorder()
	{
		_inorder(root);
		std::cout << std::endl;
	}
	void _inorder(Node* _root)
	{
		if (_root == NULL)
		{
			return ;
		}
		_inorder(_root->left);
		cout << _root->key <<":"<<_root->bf<< " ";
		_inorder(_root->right);
	}
	int _Csheck(Node* _root)
	 {
	  if (_root == NULL)
	  {
		  return 0;
	  }
	  int nleft = _Csheck(_root->left);
	  int nright = _Csheck(_root->right);

	  return (nleft > nright) ? (nleft + 1) : (nright + 1);
	 
	}
	bool Blance()
	{
		return isBlance(root);
	}
	bool isBlance(Node* _root)
	{
		if (_root == NULL)
		{
			return true;
		}
		int depth = _Csheck(_root->left) - _Csheck(_root->right);
		if (depth > 1 || depth < -1)
		{
			return false;
		}
		else
		{
			return isBlance(_root->left) && isBlance(_root->right);
		//	return true;
		}
	}
public:
	Node* root;
};
void test()
{
	AVLtree<int, int> t;
//	int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	for (int i = 0; i < sizeof(a)/sizeof(a[0]); i++)
	{
		t.Insert(a[i], i);
	}
	t.inorder();
	t.Delete(15);
	t.inorder();
//	std::cout << t.Blance() << std::endl;
	//cout << t.Find(16)->key << endl;
 //   cout << t.Find(3)->key << endl;
	//cout << t.Find(7)->key << endl;
	//cout << t.Find(11)->key << endl;
	//cout << t.Find(9)->key << endl;
	//cout << t.Find(26)->key << endl;
	//cout << t.Find(18)->key << endl;
	//cout << t.Find(14)->key << endl;
	//cout << t.Find(15)->key << endl;
}