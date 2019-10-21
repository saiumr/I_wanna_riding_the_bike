#include "linklist.h"

LinkList LinkList_Create(){
    return &EmptyLinkList;
}

void LinkList_Add2Head(LinkList* root, ElemType elem){
    if(root == NULL || *root == NULL){
        perror("linklist is not init"); 
        return;
    }
    if((*root) == &EmptyLinkList){
        *root = (LinkList)malloc(sizeof(struct _LinkList));
        if(*root == NULL){
            perror("<LinkList_Add>：memory not enough");
            *root = &EmptyLinkList;
        }else{
            (*root)->data = elem;
            (*root)->next = NULL;
        }
        return;

    }
    LinkList node = (LinkList)malloc(sizeof(struct _LinkList));
    node->next = *root;
    node->data = elem;
    *root = node;
}

void LinkList_Add2Tail(LinkList* root, ElemType elem){
    if(root == NULL || *root == NULL){
        perror("linklist is not init"); 
        return;
    }
    if(*root == &EmptyLinkList){
        *root = (LinkList)malloc(sizeof(struct _LinkList));
        if(*root == NULL){
            perror("<LinkList_Add>：memory not enough");
            *root = &EmptyLinkList;
        }else{
            (*root)->next = NULL;
            (*root)->data = elem;
        }
    }else{
        LinkList head = *root;
        while(head->next!=NULL)
            head = head->next;
        LinkList newnode = (LinkList)malloc(sizeof(struct _LinkList));
        newnode->data = elem;
        newnode->next = NULL;
        head->next = newnode;
    }

}

inline bool LinkList_IsEmpty(LinkList* root){
    if(root == NULL || *root == NULL || *root == &EmptyLinkList)
        return true;
    return false;
}

int LinkList_GetLen(LinkList* root){
    unsigned int num = 0;
    LinkList head = *root;
    if(head != NULL && head != &EmptyLinkList){
        num++;
        while(head->next!=NULL){
            head = head->next;
            num++;
        }
    }
    return num;
}

void LinkList_Remove(LinkList* root, ElemType elem){
    if(root == NULL || *root == NULL || LinkList_IsEmpty(root) == true)
        return ;
    LinkList rear = *root,
             prev = rear;
    while(rear->data != elem && rear->next!=NULL){
        prev = rear;
        rear = rear->next;
    }
    if(rear == NULL)
        return;
    LinkList node = rear;
    rear = rear->next;
    free(node);
    prev->next = rear;
}

void LinkList_Destroy(LinkList* root){
    if(root != NULL && *root != NULL && *root != &EmptyLinkList){
        LinkList_Destroy(&((*root)->next));
        free(*root);
        *root = NULL;
    }
}