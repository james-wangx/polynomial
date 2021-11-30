/**
 * @file polynomial.c
 * @date 2021-11-30
 * @author Pineapple (pineapple_cpp@163.com)
 * 
 * @brief 一元多项式 ADT 实现
 */

#include <stdio.h>
#include <stdlib.h>

#include "polynomial.h"

/**
 * @brief 初始化链表
 * 
 * @param list 
 */
inline void ListInit(List list)
{
	list->next = NULL;
}

/**
 * @brief 判断链表是否为空
 * 
 * @param list 
 * @return _Bool 
 */
inline _Bool ListIsEmpty(List list)
{
	return list->next == NULL;
}

/**
 * @brief 判断是否为链表最后一项
 * 
 * @param pos 
 * @return _Bool 
 */
inline _Bool PosIsLast(Position pos)
{
	return pos->next == NULL;
}

/**
 * @brief 查找链表最后一位元素
 * 
 * @param list 
 */
Position ListLast(List list)
{
	if (ListIsEmpty(list))
		return list;

	Position pos = list->next;

	while (pos->next != NULL)
		pos = pos->next;

	return pos;
}

/**
 * @brief 查找指定元素
 * 
 * @param poly 
 * @param list 
 * @return Position 
 */
Position ListFind(List list, Pitem item)
{
	Position pos = list->next;

	while (pos != NULL && &pos->item != item)
		pos = pos->next;

	return pos;
}

/**
 * @brief 查找前一个元素位置
 * 
 * @param item 
 * @param List 
 * @return Position 
 */
Position ListFindPrev(List list, Pitem item)
{
	Position pos = list->next;

	while (pos->next != NULL && &pos->next->item != item)
		pos = pos->next;

	return pos;
}

/**
 * @brief 添加元素
 * 
 * @param last 
 * @param pos 
 */
static inline void __list_add(Position last, Position new)
{
	last->next = new;
	new->next = NULL;
}

/**
 * @brief 添加元素
 * 
 * @param poly 
 * @param list 
 */
void ListAdd(List list, Pitem item)
{
	Position last = ListLast(list);
	Position new = (Position)malloc(sizeof(struct node));

	new->item = *item;
	__list_add(last, new);
}

static inline void __list_del(Position pos, Position prev)
{
	prev->next = pos->next;
	free(pos);
}

/**
 * @brief 删除元素
 * 
 * @param poly 
 * @param list 
 */
void ListDel(List list, Pitem item)
{
	Position pos = ListFind(list, item);
	Position prev = ListFindPrev(list, item);

	__list_del(pos, prev);
}

/**
 * @brief 在指定元素后插入一个元素
 * 
 * @param item 
 * @param list 
 */
void ListInsert(List list, Pitem item)
{
	Position pos = ListFind(list, item);
	Position new = (Position)malloc(sizeof(struct node));

	new->next = pos->next;
	pos->next = new;
}

/**
 * @brief 在指定元素前插入一个元素
 * 
 * @param item 
 * @param list 
 */
void ListInsertPrev(List list, Pitem item)
{
	Position prev = ListFindPrev(list, item);
	Position new = (Position)malloc(sizeof(struct node));

	new->next = prev->next;
	prev->next = new;
}

/**
 * @brief 遍历链表
 * 
 * @param list 
 * @param func 
 */
void ListForEach(List list, void (*func)(Pitem))
{
	Position pos = list->next;

	while (pos != NULL)
	{
		(*func)(&pos->item); // 执行函数
		pos = pos->next;
	}
}

/**
 * @brief 清空链表
 * 
 * @param list 
 */
void ListClean(List list)
{
	Position pos = list->next;

	while (pos != NULL)
	{
		Position next = pos->next;
		free(pos);
		pos = next;
	}
}

/**
 * @brief 多项式加法
 * 
 * @param list1 
 * @param list2 
 * @param new
 */
List PolyAdd(List list1, List list2, List new)
{
	Position pos1 = list1->next;
	Position pos2 = list2->next;

	ListInit(new);

	while (pos1 != NULL)
	{
		ListAdd(new, &pos1->item);
		pos1 = pos1->next;
	}
	while (pos2 != NULL)
	{
		ListAdd(new, &pos2->item);
		pos2 = pos2->next;
	}

	return new;
}

/**
 * @brief 多项式减法
 * 
 * @param list1 
 * @param list2 
 * @param new
 */
List PolyMin(List list1, List list2, List new)
{
	Position pos1 = list1->next;
	Position pos2 = list2->next;

	ListInit(new);

	while (pos1 != NULL)
	{
		ListAdd(new, &pos1->item);
		pos1 = pos1->next;
	}
	while (pos2 != NULL)
	{
		Position pos = (Position)malloc(sizeof(struct node));
		pos->item.coefficient = -pos2->item.coefficient;
		pos->item.exponent = pos2->item.exponent;
		Position last = ListLast(new);
		last->next = pos;
		pos->next = NULL;
		pos2 = pos2->next;
	}

	return new;
}

/**
 * @brief 多项式乘法
 * 
 * @param list1 
 * @param list2 
 * @param new
 */
List PolyMul(List list1, List list2, List new)
{
	ListInit(new);

	for (Position pos1 = list1->next; pos1 != NULL; pos1 = pos1->next)
		for (Position pos2 = list2->next; pos2 != NULL; pos2 = pos2->next)
		{
			Position last = ListLast(new);
			Position pos = (Position)malloc(sizeof(struct node));
			pos->item.exponent = pos1->item.exponent + pos2->item.exponent;
			pos->item.coefficient = pos1->item.coefficient * pos2->item.coefficient;
			__list_add(last, pos);
		}

	return new;
}

/**
 * @brief 合并同类项
 * 
 */
void PolyMerge(List list)
{
	for (Position i = list->next; !PosIsLast(i); i = i->next)
		for (Position j = i->next; j != NULL; j = j->next)
			if (i->item.exponent == j->item.exponent)
			{
				i->item.coefficient += j->item.coefficient;
				Position prev = ListFindPrev(list, &j->item);
				__list_del(j, prev);
			}
}
