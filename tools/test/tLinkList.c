#include <stdio.h>
#include "unittest.h"
#include "UI.h"

void outputNode(ElemType* node){
    printf("node addr:%d\npos:(%d, %d)\nsize:(%d, %d)\nisshow:%d\ntype:%d\n\n", &(*node), node->pos.x, node->pos.y, node->size.w, node->size.h, node->show, node->type);
}

int main(){
    LinkList* root = LinkList_Create(root);
    ADD_TEST_TRUE("test empty", LinkList_IsEmpty(root), true);
    ADD_TEST_TRUE("test len 0", LinkList_GetLen(root), 0);
    ElemType info1 = {{0, 0},   {100, 100}, {0.5, 0.5}, false,  NULL, BUTTON};
    ElemType info2 = {{10, 20}, {40, 100},  {0.5, 0.5}, true,   NULL, BUTTON};
    ElemType info3 = {{30, 80}, {90, 100},  {0.5, 0.5}, false,  NULL, IMAGE};
    LinkList_Add(root, info1);
    ADD_TEST_TRUE("linklist len", LinkList_GetLen(root), 1);
    ADD_TEST_TRUE("test empty", LinkList_IsEmpty(root), false);
    LinkList_Add(root, info2);
    ADD_TEST_TRUE("linklist len", LinkList_GetLen(root), 2);
    LinkList_Add(root, info3);
    ADD_TEST_TRUE("linklist len", LinkList_GetLen(root), 3);
    LinkList* node = root->next;
    ADD_TEST_TRUE("test info1 pos.x", node->data.pos.x, 0);
    ADD_TEST_TRUE("test info1 pos.y", node->data.pos.y, 0);
    ADD_TEST_TRUE("test info1 size.w", node->data.size.w, 100);
    ADD_TEST_TRUE("test info1 size.h", node->data.size.h, 100);
    ADD_TEST_TRUE("test info1 show", node->data.show, false);
    node = node->next;
    ADD_TEST_TRUE("test info2 pos.x", node->data.pos.x, 10);
    ADD_TEST_TRUE("test info2 pos.y", node->data.pos.y, 20);
    ADD_TEST_TRUE("test info2 isshow", node->data.show, true);
    node = node->next;
    ADD_TEST_TRUE("test info3 pos.x", node->data.pos.x, 30);
    ADD_TEST_TRUE("test info3 pos.y", node->data.pos.y, 80);
    ADD_TEST_TRUE("test info3 type", node->data.type, IMAGE);

    LinkList* rst = LinkList_Find(root, info1);
    ADD_TEST_TRUE("test find", rst->data.size.w, 100);

    LinkList_Remove(root, info1);
    ADD_TEST_TRUE("test remove", LinkList_GetLen(root), 2);
    node = root->next;
    ADD_TEST_TRUE("test info2 pos.x", node->data.pos.x, 10);
    ADD_TEST_TRUE("test info2 pos.y", node->data.pos.y, 20);
    ADD_TEST_TRUE("test info2 isshow", node->data.show, true);

    LinkList_Destroy(root);
    TEST_SHOW_STATISTICS()
    TEST_PAUSE_CONSOLE()
    return 0;
}