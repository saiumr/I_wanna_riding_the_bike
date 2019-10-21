#include "linklist.h"

int main(){
    while(1){
        LinkList root = LinkList_Create();
        int a =110, b =220;
        LinkList_Add2Head(&root, (void*)&a);
        LinkList_Add2Tail(&root, (void*)&b);
        LinkList_Destroy(&root);
    }
    return 0;
}