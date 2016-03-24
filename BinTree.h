#pragma once
#include "BinNode.h"
template <typename T> class BinTree
{
private:
	int _size;
	BinNode<T> *_root;
	int updateHeight(BinNode<T> *x);
	void updateHeightAbove(BinNode<T> *x);
public:
	BinTree():_size(0), _root(nullptr){}
	~BinTree(){if(_size > 0) remove(_root);}
	int size() const {return _size;}
	bool empty() const {return !_root;}
	BinNode<T>* insertAsRoot(const T &e); 
	BinNode<T>* insertAsLC(BinNode<T> *x, const T &e);
	BinNode<T>* insertAsRC(BinNode<T> *x, const T &e);
	BinNode<T>* attachAsLC(BinNode<T> *x, BinTree<T>* &t);
	BinNode<T>* attachAsRC(BinNode<T> *x, BinTree<T>* &t);
	int remove(BinNode<T> *x);
	BinTree<T>* secede(BinNode<T> *x);
	bool operator==(const BinTree<T> &t) { return _root && t._root && (_root == t._root); }
	bool operator<(const BinTree<T> &t) { return _root && t._root && lt(_root, t._root); }
};

template <typename T> int BinTree<T>::updateHeight(BinNode<T> *x)
{
	return x->height = 1 + max(stature(x->lChlid), stature(x->rClild));
}

template <typename T> void BinTree<T>::updateHeightAbove(BinNode<T> *x)
{
	while(x)
	{
		updateHeight(x);
		x = x->parent;
	}
}

template <typename T> BinNode<T>* BinTree<T>::insertAsRoot(const T &e)
{
	if(_root) return nullptr;
	_size = 1;
	return _root = new BinNode<T>(e);
}

template <typename T> BinNode<T>* BinTree<T>::insertAsLC(BinNode<T> *x, const T &e)
{
	if(x->lChlid) return nullptr;
	x->insertAsLC(e);
	++_size;
	updateHeightAbove(x);
	return x->lChlid;
	
}

template <typename T> BinNode<T>* BinTree<T>::insertAsRC(BinNode<T> *x, const T &e)
{
	if(x->rChlid) return nullptr;
	x->insertAsRC(e);
	++_size;
	updateHeightAbove(x);
	return x->rChlid;
}

template <typename T> BinNode<T>* BinTree<T>::attachAsLC(BinNode<T> *x, BinTree<T>* &t)
{
	if(x->lChlid) return nullptr;
	if(x->lChlid = t->_root) x->lChlid->parent = x;
	_size += t->_size;
	updateHeightAbove(x);
	return x;
}

template <typename T> BinNode<T>* BinTree<T>::attachAsRC(BinNode<T> *x, BinTree<T>* &t)
{
	if(x->rChlid) return nullptr;
	if(x->rChlid = t->_root) x->rChlid->parent = x;
	_size += t->_size;
	updateHeightAbove(x);
	return x;
}

template <typename T> int BinTree<T>::remove(BinNode<T> *x)
{
	FromParentTo(*x) = nullptr;
	updateHeightAbove(x);
	int n = removeAt(x);
	_size -= n;
	return n;
}

template <typename T> int BinTree<T>::removeAt(BinNode<T> *x)
{
	if(!x) return 0;
	int n = 1 + removeAt(x->lChlid) + removeAt(x->rChlid);
	release(x->data);
	release(x);
	return n;
}

template <typename T> BinTree<T>* BinTree<T>::secede(BinNode<T> *x)
{
	if(!x) return nullptr;
	FromParentTo(*x) = nullptr;
	updateHeightAbove(x);
	BinTree<T> *s = new BinTree<T>;
	s->_size = x->size();
	_size -= x->size();
	x->parent = nullptr;
	s->_root = x;
	return s;
}

template <typename T, typename VST> void visitAlongLeftBranch(BinNode<T> *x, VST &visit, Stack<BinNode<T>*> &S)
{
	while(x)
	{
		visit(x->data);
		S.push(x->rChlid);
		x = x->lChlid;
	}
}

template <typename T, typename VST> void travPre(BinNode<T> *x, VST &visit)
{
	Stack<BinNode<T>*> S;
	while(true)
	{
		visitAlongLeftBranch(x, visit, S);
		if(s->empty()) break;
		x = S.pop();
	}
}

template <typename T, typename VST> void pushAlongLeftBranch(BinNode<T> *x, VST &visit, Stack<BinNode<T>*> &S)
{
	while(x)
	{
		S.push(x);
		x = x->lChlid;
	}
}

template <typename T, typename VST> void travIn(BinNode<T> *x, VST &visit)
{
	Stack<BinNode<T>*> S;
	while(true)
	{
		pushAlongLeftBranch(x, visit, S);
		if(S.empty()) break;
		x = S.pop();
		visit(x->data);
		x = x->rChlid;
	}
}

template <typename T, typename VST> void travLevel(BinNode<T> *x, VST &visit)
{
	Queue<BinNode<T>*> Q;
	Q.enqueue(x);
	while(!Q.empty())
	{
		x = Q.dequeue();
		visit(x->data);
		if(HasLChild(*x)) Q.enqueue(x->lChlid);
		if(HasRChild(*x)) Q.enqueue(x->rChlid);
	}
}