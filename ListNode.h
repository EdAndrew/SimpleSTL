#pragma once
typedef int Rank; //秩

template <typename T> struct ListNode 
{
 //列表节点模板类（以双向链表形式实现）
// 成员
   T data; 
   ListNode<T> *pred; 
   ListNode<T> *succ; //数值、前驱、后继
// 构造函数
   ListNode() = default; //针对header和trailer的构造
   ListNode(const T &e, ListNode *p = nullptr, ListNode *s = nullptr):data(e), pred(p), succ(s){} //默认构造器
// 操作接口
   ListNode<T>* insertAsPred(const T &e); //紧靠当前节点之前插入新节点
   ListNode<T>* insertAsSucc(const T &e); //紧随当前节点之后插入新节点
};

template <typename T> ListNode<T>* ListNode<T>::insertAsPred(const T &e)
{
    ListNode<T> *p = new ListNode<T>(e, pred, this);
    pred->succ = p;
    pred = p;
    return p; 
}

template <typename T> ListNode<T>* ListNode<T>::insertAsSucc(const T &e)
{
    ListNode<T> *p = new ListNode<T>(e, this, succ);
    succ->pred = p;
    succ = p;
    return p;
}
