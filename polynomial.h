/**
 * @file polynomial.h
 * @date 2022-01-09
 * @author Pineapple (pineapple_cpp@163.com)
 * 
 * @brief 一元多项式 ADT
 */

#ifndef _POLYNOMIAL_H
#define _POLYNOMIAL_H

typedef struct item {
	int coefficient; // 系数
	int exponent; // 指数
} Item;

typedef struct node {
	Item item;
	struct node *next;
} Node;

typedef Item *PtrToItem;
typedef PtrToItem Pitem;
typedef Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

void ListInit(List list);
_Bool ListIsEmpty(List list);
Position ListLast(List list);
Position ListFind(List list, Pitem item);
Position ListFindPrev(List list, Pitem item);
void ListAdd(List list, Pitem item);
void ListDel(List list, Pitem item);
void ListInsert(List list, Pitem item);
void ListInsertPrev(List list, Pitem item);
void ListForEach(List list, void (*func)(Pitem));
void ListClean(List list);

List PolyAdd(List list1, List list2, List new);
List PolyMin(List list1, List list2, List new);
List PolyMul(List list1, List list2, List new);
void PolyMerge(List list);

#endif // _POLYNOMIAL_H
