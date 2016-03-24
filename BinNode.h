#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x).parent->lChild))
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->rChild))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lChild)
#define HasRChild(x) ((x).rChild)
#define HasChild(x) (HasLChild(x) || HasRChild(x)) 
#define HasBothChild(x) (HasLChild(x) && HasRChild(x)) 
#define IsLeaf(x) (!HasChild(x))
#define sibling(p) ( \
 IsLChild(*(p)) ? \
 (p)->parent->rChild : \
 (p)->parent->lChild \
 )
 #define uncle(x) ( \
 IsLChild(*((x)->parent)) ? \
 (x)->parent->parent->rChild : \
 (x)->parent->parent->lChild \
 )
 #define FromParentTo(x) ( \
 IsRoot(x) ? _root : ( \
 IsLChild(x) ? (x).parent->lChild : (x).parent->rChild \
 ) \
 )
 
template <typename T> BinNode<T>* BinNode<T>::insertAsLC(const T &e)
{
	return lChild = new BinNode(e, this);
}

template <typename T> BinNode<T>* BinNode<T>::insertAsRC(const T &e)
{
	return rChild = new BinNode(e, this);
}

template <typename T> BinNode<T>* BinNode<T>::succ()
{
	BinNode<T> *x = this;
	if(rChild)
	{
		x = rChild;
		while(HasLChild(*x)) x = x->lChild;
	}
	else
	{
		while(isRChild(x) x = x->parent;
		x = x->parent;
	}
	return x;
}

//后序遍历

//层次遍历 



