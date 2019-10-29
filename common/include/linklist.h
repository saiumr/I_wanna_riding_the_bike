#ifndef __LINKLIST_H__
#define __LINKLIST_H__
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/*这个链表会将数据拷贝一份放到data中*/
typedef void* ElemType;

struct _LinkList{
    ElemType            data;
    struct _LinkList*   next;
};

typedef struct _LinkList* LinkList;
static struct _LinkList EmptyLinkList = {NULL, NULL, NULL};

LinkList    LinkList_Create();
int         LinkList_GetLen(LinkList* root);
void        LinkList_Add2Head(LinkList* root, ElemType elem, unsigned int sizeof_elem);
void        LinkList_Add2Tail(LinkList* root, ElemType elem, unsigned int sizeof_elem);
void        LinkList_Remove(LinkList* root, ElemType elem);
bool        LinkList_IsEmpty(LinkList* root);
void        LinkList_Destroy(LinkList* root);

#endif