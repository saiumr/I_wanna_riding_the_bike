#ifndef __LINKLIST_H__
#define __LINKLIST_H__
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef void* ElemType;
struct _LinkList{
    ElemType            data;
    struct _LinkList*   next;
};

typedef struct _LinkList* LinkList;
static struct _LinkList EmptyLinkList = {NULL, NULL};

LinkList    LinkList_Create();
int         LinkList_GetLen(LinkList* root);
void        LinkList_Add2Head(LinkList* root, ElemType elem);
void        LinkList_Add2Tail(LinkList* root, ElemType elem);
void        LinkList_Remove(LinkList* root, ElemType elem);
bool        LinkList_IsEmpty(LinkList* root);
void        LinkList_Destroy(LinkList* root);

#endif