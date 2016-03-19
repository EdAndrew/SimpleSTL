#pragma once
#include "listNode.h" //引入列表节点类

template <typename T> class List
{ //列表模板类
private:
    int _size; 
    ListNode<T> *header; 
    ListNode<T> *trailer; //规模、头哨兵、尾哨兵
protected:
    void init(); //列表创建时的初始化
    int clear(); //清除所有节点
    void copyNodes(ListNode<T> *p, int n); //复制列表中自位置p起的n项
public:
//  构造函数
    List() {init();} //默认
    List(const List<T> &L){copyNodes(L.first(), L.size());} //整体复制列表L
    List(const List<T> &L, Rank r, int n){copyNodes(L[r], n);} //复制列表L中自第r项起的n项
    List(ListNode<T> *p, int n){copyNodes(p, n);} //复制列表中自位置p起的n项
//  重载赋值操作符
    List& operator=(const List<T> &L);    
//  析构函数
    virtual ~List(){clear(); delete header; delete trailer;} //释放（包含头、尾哨兵在内的）所有节点
//  只读访问接口
    Rank size() const {return _size;} //规模
    bool empty() const{return _size <= 0;} //判空
    T& operator[] (Rank r); //重载，支持循秩访问（效率低）
    ListNode<T>* first() const  {return header->succ;} //首节点位置
    ListNode<T>* last() const {return trailer->pred;} //末节点位置
    bool valid(ListNode<T> *p) //判断位置p是否对外合法
    {return p && ( trailer != p ) && (header != p);} //将头、尾节点等同于NULL
    int disordered() const; //判断列表是否已排序
    ListNode<T>* find(const T &e, int n, ListNode<T> *p) const;
    ListNode<T>* find(const T &e) const{return find(e, _size, trailer);}
    ListNode<T>* insertAsFirst(const T &e){_size++; return header->insertAsSucc(e);}
    ListNode<T>* insertAsLast(const T &e){_size++; return trailer->insertAsPred(e);}
    ListNode<T>* insertBefore(ListNode<T> *p, const T &e){_size++; return p->insertAsPred(e);}
    ListNode<T>* insertAfter(ListNode<T> *p, const T &e){_size++; return p->insertAsSucc(e);}
    T remove(ListNode<T> *p); //删除合法位置p处的节点,返回被删除节点
    ListNode<T>* search(const T &e, int n, ListNode<T> *p);
    void insertSort(ListNode<T> *p, int n);
    ListNode<T>* selectMax(ListNode<T> *p, int n);
    void selectSort(ListNode<T> *p, int n);
    void sort(ListNode<T> *p, int n);
    void sort(){sort (first(), _size);}
/*
   ListNodePosi(T) search ( T const& e ) const //有序列表查找
   { return search ( e, _size, trailer ); }
   ListNodePosi(T) search ( T const& e, int n, ListNodePosi(T) p ) const; //有序区间查找
   ListNodePosi(T) selectMax ( ListNodePosi(T) p, int n ); //在p及其n-1个后继中选出最大者
   ListNodePosi(T) selectMax() { return selectMax ( header->succ, _size ); } //整体最大者
// 可写访问接口
   ListNodePosi(T) insertAsFirst ( T const& e ); //将e当作首节点插入
   ListNodePosi(T) insertAsLast ( T const& e ); //将e当作末节点插入
   ListNodePosi(T) insertA ( ListNodePosi(T) p, T const& e ); //将e当作p的后继插入
   ListNodePosi(T) insertB ( ListNodePosi(T) p, T const& e ); //将e当作p的前驱插入
   T remove ( ListNodePosi(T) p ); //删除合法位置p处的节点,返回被删除节点
   void merge ( List<T>& L ) { merge ( first(), size, L, L.first(), L._size ); } //全列表归并
   void sort ( ListNodePosi(T) p, int n ); //列表区间排序
   void sort() { sort ( first(), _size ); } //列表整体排序
   int deduplicate(); //无序去重
   int uniquify(); //有序去重
   void reverse(); //前后倒置（习题）
// 遍历
   void traverse ( void (* ) ( T& ) ); //遍历，依次实施visit操作（函数指针，只读或局部性修改）
   template <typename VST> //操作器
   void traverse ( VST& ); //遍历，依次实施visit操作（函数对象，可全局性修改）
*/
};

template <typename T> void List<T>::init()
{
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->succ = trailer;
    header->pred = nullptr;
    trailer->pred = header;
    trailer->succ = nullptr;
    _size = 0;
}

template <typename T> T& List<T>::operator[](Rank r)     
{
    ListNode<T> *p = first();  
    while(r--) p = p->succ;
    return p->data;    
}

template <typename T> ListNode<T>* find(const T &e, int n, ListNode<T> *p)
{
    while(n--)
    {
	p = p->pred;
	if(p->data == e) return p;
    }
    return nullptr;
}

template <typename T> void List<T>::copyNodes(ListNode<T> *p, int n)
{
    init();
    while(n--) 
    {
	insertAsLast(p->data);   
	p = p->succ;
    }
}

template <typename T> T List<T>::remove(ListNode<T> *p)
{
    T oldData = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;
    --_size;
    return oldData;
}

template <typename T> int List<T>::clear()
{
    int oldSize = _size;
    while(_size) remove(header->succ);
    return oldSize;      
}

template <typename T> List<T>& List<T>::operator=(const List<T> &L)
{
//  为了处理自我赋值和保证异常安全的重载赋值函数
    int n = L.size(), oldSize = _size;
    ListNode<T> *p = L.first();
    while(n--)
    {
	insertAsLast(p->data);
	p = p->succ;
    }    
    while(oldSize--)
    {
	remove(header->succ);		
    }
    _size = L.size();
    return *this;
}

template <typename T> ListNode<T>* List<T>::search(const T &e, int n, ListNode<T> *p)
{
    while(0 <= n--)
    {
	p = p->pred;
	if(p->data <= e)  break;
    }
    return p;
}

template <typename T> void List<T>::insertSort(ListNode<T> *p, int n)
{
    for(int r = 0; r < n; ++r)
    {
	insertAfter(search(p->data, r, p), p->data);
	p = p->succ;
	remove(p->pred);	
    }    
}

template <typename T> ListNode<T>* List<T>::selectMax(ListNode<T> *p, int n)
{
    ListNode<T> *max = p;
    for(ListNode<T> *cur = p; n > 1; n--)
    {
	cur = cur->succ;
	if(cur->data > max->data) max = cur;
    }
    return max;
}

template <typename T> void List<T>::selectSort(ListNode<T> *p, int n)
{
    ListNode<T> *head = p->pred, *tail = p;
    int i = n;
    while(i--) tail = tail->succ;
    while(n > 1)
    {
	ListNode<T> *max = selectMax(head->succ, n);
	insertBefore(tail, remove(max));
	tail = tail->pred;
	n--;
    }    
}

template <typename T> void List<T>::sort(ListNode<T> *p, int n)
{
    switch(2)
    {
	case 1: insertSort(p, n); break;
	case 2: selectSort(p, n); break;
    }
}








