#include <stdio.h>
#include "linklist.h"
#include "unittest.h"

int main(){
    LinkList root = LinkList_Create();
    ADD_TEST_TRUE("is empty", LinkList_IsEmpty(&root), true);
    {
    int a = 110;
    LinkList_Destroy(&root);
    ADD_TEST_TRUE("get length", LinkList_GetLen(&root), 0);
    LinkList_Add2Head(&root, (void*)&a, sizeof(a));
    }
    ADD_TEST_TRUE("get length", LinkList_GetLen(&root), 1);
    ADD_TEST_TRUE("test inner data", *((int*)root->data), 110);
    ADD_TEST_TRUE("is empty", LinkList_IsEmpty(&root), false);
    int b = 340;
    LinkList_Add2Tail(&root, (void*)&b, sizeof(b));
    ADD_TEST_TRUE("add to tail", *((int*)root->next->data), b);
    ADD_TEST_TRUE("get len", LinkList_GetLen(&root), 2);
    LinkList_Remove(&root, (void*)&b);
    ADD_TEST_TRUE("removed a node", LinkList_GetLen(&root), 1);
    ADD_TEST_TRUE("test inner data after remove", root->next, NULL);
    ADD_TEST_TRUE("test inner data after remove", *((int*)root->data), 110);

    LinkList_Destroy(&root);
    TEST_SHOW_STATISTICS()
    TEST_PAUSE_CONSOLE()
    printf("now test memory, press Ctrl-C to stop\n");
    //test memory 
    while(1){
        int a = 110, b = 220;
        root = LinkList_Create();
        LinkList_Add2Head(&root, &a, sizeof(a));
        LinkList_Add2Tail(&root, &b, sizeof(b));
        LinkList_Destroy(&root);
    }
    return 0;
}