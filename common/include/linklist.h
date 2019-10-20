#ifndef __LINKLIST_H__
#define __LINKLIST_H__
#include <stdlib.h>
#include <stdbool.h>

typedef void* ElemType;
struct _LinkList{
    ElemType            data;
    struct _LinkList*   next;
};

typedef struct _LinkList LinkList;

LinkList*   LinkList_Create();
int         LinkList_GetLen(LinkList* root);
void        LinkList_Add(LinkList* root, ElemType elem);
void        LinkList_Remove(LinkList* root, ElemType elem);
LinkList*   LinkList_Find(LinkList* root, ElemType elem);
bool        LinkList_IsEmpty(LinkList* root);
void        LinkList_Destroy(LinkList* root);

#endif