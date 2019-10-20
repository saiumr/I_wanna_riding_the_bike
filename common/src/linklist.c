#include "linklist.h"

LinkList* LinkList_Create(){
    LinkList* root = (LinkList*)malloc(sizeof(LinkList));
    if(root == NULL)
        perror("memory not enough");
    else
        root->next = NULL;
    return root;
}

void LinkList_Add(LinkList* root, ElemType elem){
    LinkList* node = root;
    while(node->next!=NULL)
        node = node->next;
    LinkList* newnode = (LinkList*)malloc(sizeof(LinkList));
    newnode->data = elem;
    newnode->next = NULL;
    node->next = newnode;
}

inline bool LinkList_IsEmpty(LinkList* root){
    return root->next?false:true;
}

int LinkList_GetLen(LinkList* root){
    LinkList* node = root->next;
    int num = 0;
    while(node != NULL){
        node = node->next;
        num++;
    }
    return num;
}

void LinkList_Remove(LinkList* root, ElemType elem){
    LinkList *rear = root,
             *prev = rear;
    while(memcmp(&rear->data, &elem, sizeof(elem))!=0){
        prev = rear;
        rear = rear->next;
    }
    if(rear == NULL)
        return;
    LinkList* node = rear;
    rear = rear->next;
    free(node);
    prev->next = rear;
}

LinkList* LinkList_Find(LinkList* root, ElemType elem){
    LinkList* node = root->next;
    while(memcmp(&node->data, &elem, sizeof(elem))!=0 && node!=NULL)
        node = node->next;
    return node;
}

void LinkList_Destroy(LinkList* root){
    if(root->next != NULL)
        LinkList_Destroy(root->next);
    free(root);
    root = NULL;
}