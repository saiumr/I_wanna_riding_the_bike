#include "UI.h"

void UI_Init(SDL_Renderer* render){
    SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
    UIStorage = (UI_UIStorage*)malloc(sizeof(UI_UIStorage));
    UIStorage->size = 0;
    _UI_Render = render;
}

inline void UI_SetRenderer(SDL_Renderer* render){
    _UI_Render = render;
}

SDL_Point _calcuTL(UI_BasicInfo* info){
    int offsetx = info->anchor.x*info->size.w,
        offsety = info->anchor.y*info->size.h;
    SDL_Point p = {info->pos.x - offsetx, info->pos.y - offsety};
    return p;
}

void _fixButtonSize(UI_Button* button){
    int len = strlen(button->text);
    int w = button->displayinfo.fontsize/2*len + 2*button->displayinfo.xpadding;
    int h = button->displayinfo.fontsize + 2*button->displayinfo.ypadding;
    UI_SetSize(button, w, h); 
}

void _trigItemEventClick(SDL_Event* event, UI_Widget item){
    UI_BasicUIInfo* info = (UI_BasicUIInfo*)item;
    if(info->table.pClick.user_event)
        info->table.pClick.user_event(event, item);
    if(info->table.pClick.default_event)
        info->table.pClick.default_event(event, item);
}
void _trigItemEventMouseDown(SDL_Event* event, UI_Widget item){
    UI_BasicUIInfo* info = (UI_BasicUIInfo*)item;
    if(info->table.pMouseDown.user_event)
        info->table.pMouseDown.user_event(event, item);
    if(info->table.pMouseDown.default_event)
        info->table.pMouseDown.default_event(event, item);
}
void _trigItemEventMouseRelease(SDL_Event* event, UI_Widget item){
    UI_BasicUIInfo* info = (UI_BasicUIInfo*)item;
    if(info->table.pMouseRelease.user_event)
        info->table.pMouseRelease.user_event(event, item);
    if(info->table.pMouseRelease.default_event)
        info->table.pMouseRelease.default_event(event, item);
}
void _trigItemEventMouseMotion(SDL_Event* event, UI_Widget item){
    UI_BasicUIInfo* info = (UI_BasicUIInfo*)item;
    if(info->table.pMouseMotion.user_event)
        info->table.pMouseMotion.user_event(event, item);
    if(info->table.pMouseMotion.default_event)
        info->table.pMouseMotion.default_event(event, item);
}
void _trigItemEventKeyDown(SDL_Event* event, UI_Widget item){
    UI_BasicUIInfo* info = (UI_BasicUIInfo*)item;
    if(info->table.pKeyDown.user_event)
        info->table.pKeyDown.user_event(event, item);
    if(info->table.pKeyDown.default_event)
        info->table.pKeyDown.default_event(event, item);
}
void _trigItemEventKeyRelease(SDL_Event* event, UI_Widget item){
    UI_BasicUIInfo* info = (UI_BasicUIInfo*)item;
    if(info->table.pKeyRelease.user_event)
        info->table.pKeyRelease.user_event(event, item);
    if(info->table.pKeyRelease.default_event)
        info->table.pKeyRelease.default_event(event, item);
}

void _eventDeliver(SDL_Event* event, UI_Widget item){
    UI_BasicUIInfo* info = (UI_BasicUIInfo*)item;
    switch(event->type){
        case SDL_MOUSEMOTION:
            _trigItemEventMouseMotion(event, item);
            break;
        case SDL_MOUSEBUTTONDOWN:
            _trigItemEventMouseDown(event, item);
            break;
        case SDL_MOUSEBUTTONUP:
            _trigItemEventMouseRelease(event, item);
            _trigItemEventClick(event, item);
            break;
        case SDL_KEYDOWN:
            _trigItemEventKeyDown(event, item);
            break;
        case SDL_KEYUP:
            _trigItemEventKeyRelease(event, item);
            break;
    }
}

inline void UI_SetClickEvent(UI_Widget item, UI_pEventCallBack clickfunc){
    ((UI_BasicUIInfo*)item)->table.pClick.user_event = clickfunc;
}

inline void UI_SetMouseDownEvent(UI_Widget item, UI_pEventCallBack mousedownfunc){
    ((UI_BasicUIInfo*)item)->table.pMouseDown.user_event = mousedownfunc;
}

inline void UI_SetMouseReleaseEvent(UI_Widget item, UI_pEventCallBack mousereleasefunc){
    ((UI_BasicUIInfo*)item)->table.pMouseRelease.user_event = mousereleasefunc;
}

inline void UI_SetMouseMotionEvent(UI_Widget item, UI_pEventCallBack mousemotionfunc){
    ((UI_BasicUIInfo*)item)->table.pMouseMotion.user_event = mousemotionfunc;
}
inline void UI_SetKeyDownEvent(UI_Widget item, UI_pEventCallBack keydownfunc){
    ((UI_BasicUIInfo*)item)->table.pKeyDown.user_event = keydownfunc;
}
inline void UI_SetKeyReleaseEvent(UI_Widget item, UI_pEventCallBack keyreleasefunc){
    ((UI_BasicUIInfo*)item)->table.pKeyRelease.user_event = keyreleasefunc;
}

void UI_MoveItem(UI_Widget item, int x, int y){
    UI_BasicUIInfo* info = (UI_BasicUIInfo*)item;
    info->info.pos.x = x;
    info->info.pos.y = y;
}

inline SDL_Size UI_GetSize(UI_Widget item){
    SDL_Size size = {((UI_BasicUIInfo*)item)->info.size.w, ((UI_BasicUIInfo*)item)->info.size.h};
    return size;
}

inline SDL_Point UI_GetPosition(UI_Widget item){
   SDL_Point p = {((UI_BasicUIInfo*)item)->info.pos.x, ((UI_BasicUIInfo*)item)->info.pos.y}; 
   return p;
}
inline SDL_Pointf  UI_GetAnchor(UI_Widget item){
    SDL_Pointf p = {((UI_BasicUIInfo*)item)->info.anchor.x, ((UI_BasicUIInfo*)item)->info.anchor.y};
    return p;
}

SDL_Rect UI_GetRect(UI_Widget item){
    SDL_Point lt = _calcuTL((UI_BasicInfo*)item);
    SDL_Size size = UI_GetSize(item);
    SDL_Rect rect = {lt.x, lt.y, size.w, size.h};
    return rect;
}

void UI_SetSize(UI_Widget item, int w, int h){
    UI_BasicUIInfo* info = (UI_BasicUIInfo*)item;
    info->info.size.w = w;
    info->info.size.h = h;
}

void UI_SetAnchor(UI_Widget item, float x, float y){
    UI_BasicUIInfo* info = (UI_BasicUIInfo*)item;
    info->info.anchor.x = x;
    info->info.anchor.y = y;
}

inline void UI_ShowItem(UI_Widget item){
    ((UI_BasicInfo*)item)->show = true;
}

inline void UI_HideItem(UI_Widget item){
    ((UI_BasicInfo*)item)->show = false;
}

void UI_SetParent(UI_Widget item, UI_Widget parent){
    UI_BasicInfo* info = (UI_BasicInfo*)item;
    info->parent = parent;
    //TODO add itself to parent
    /*example code
    if(parent)
        UI_ContainerAddChild(parent, item);
    */
}

inline UI_Widget UI_GetParent(UI_Widget item){
    return ((UI_BasicInfo*)item)->parent;
}

inline bool UI_GetVisiable(UI_Widget item){
    return ((UI_BasicInfo*)item)->show;
}

void _createDefaultBasicUIInfo(UI_BasicUIInfo* info){
    info->info = _UI_DEFAULT_BASIC_INFO;
    info->table.pClick.default_event        = NULL;
    info->table.pClick.user_event           = NULL;
    info->table.pMouseDown.default_event    = NULL;
    info->table.pMouseDown.user_event       = NULL;
    info->table.pMouseMotion.default_event  = NULL;
    info->table.pMouseMotion.user_event     = NULL;
    info->table.pMouseRelease.default_event = NULL;
    info->table.pMouseRelease.user_event    = NULL;
    info->table.pKeyDown.default_event      = NULL;
    info->table.pKeyDown.user_event         = NULL;
    info->table.pKeyRelease.default_event   = NULL;
    info->table.pKeyRelease.user_event      = NULL;
    info->table.bubble                      = false;
}

UI_Button* UI_CreateButton(const char* title, UI_pEventCallBack clickfunc, UI_Widget parent){ 
    //TODO 添加默认的Click事件
    UI_Button* button = (UI_Button*)malloc(sizeof(UI_Button));
    _createDefaultBasicUIInfo(&button->basicinfo);
    button->displayinfo = _UI_DEFAULT_DISPLAY_INFO;
    UI_SetParent(button, parent);
    button->basicinfo.info.type = BUTTON;

    strcpy(button->text, title);
    UI_SetClickEvent(button, clickfunc);
    _fixButtonSize(button);

    return button;
}

UI_Image* UI_CreateImage(const char* path, UI_Widget parent){
    UI_Image* image = (UI_Image*)malloc(sizeof(UI_Image*));
    _createDefaultBasicUIInfo(&image->basicinfo);
    SDL_Surface* surface = IMG_Load(path);
    UI_SetParent(image, parent);
    if(!surface){
        log_error("surface not found");
        free(surface);
        free(image);
        return NULL;
    }
    UI_SetSize(image, surface->w, surface->h);
    image->image = SDL_CreateTextureFromSurface(_UI_Render, surface);
    if(!image->image){
        log_error("texture create failed");
        free(image->image);
        free(image);
        return NULL;
    }
    image->basicinfo.info.type = IMAGE;
    return image;
}

void UI_DestroyButton(UI_Button* button){
    if(button)
        free(button);
    button = NULL;
}

void UI_DestroyImage(UI_Image* image){
    if(image)
        free(image);
    image = NULL;
}

void UI_DrawButton(UI_Button* button){
    if(UI_GetVisiable(button) == false)
        return ;
    SDL_Point lt = _calcuTL((UI_BasicInfo*)button);
    SDL_Rect rect = UI_GetRect(button);
    SDL_Color color;
    SDL_Color* backcolor = &button->displayinfo.backcolor;
    Uint8 xpadding = button->displayinfo.xpadding,
        ypadding = button->displayinfo.ypadding;
    SDL_GetRenderDrawColor(_UI_Render, &color.r, &color.g, &color.b, &color.a);
    SDL_SetRenderDrawColor(_UI_Render, backcolor->r, backcolor->g, backcolor->b, backcolor->a);
    SDL_RenderFillRect(_UI_Render, &rect);
    SDL_SetRenderDrawColor(_UI_Render, 0, 0, 0, 255);
    SDL_RenderDrawRect(_UI_Render, &rect);
    FC_Font* font = FC_CreateFont();
    FC_LoadFont(font, _UI_Render, "Fangsong.ttf", button->displayinfo.fontsize, button->displayinfo.forecolor, TTF_STYLE_NORMAL);
    FC_Draw(font, _UI_Render, lt.x+xpadding, lt.y+ypadding, button->text);
    FC_FreeFont(font);
}

void UI_DrawImage(UI_Image* image){
    if(UI_GetVisiable(image) == false)
        return ;
    SDL_Rect rect = UI_GetRect(image);
    SDL_RenderCopy(_UI_Render, image->image, NULL, &rect);
}

void UI_ContainerAddChild(UI_Widget container, UI_BasicInfo child){
    UI_BasicContainerInfo* continfo = (UI_BasicContainerInfo*)container;

    //malloc new content to container
    if(continfo->num >= continfo->size){
        realloc(continfo->children, sizeof(continfo->children)*(continfo->size+CONTAINER_INC_NUM));
        continfo->size += CONTAINER_INC_NUM;
    }
    //TODO这里采用链表的方式来完成，需要改写这里的代码了
    //continfo->children[continfo->num++] = child;
}

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

inline void UI_DestroyContainer(UI_Widget container){
    free(container);
}

//TODO 这里的函数还没有完成
void UI_StorageAddComponent(UI_Widget item){}

void UI_DAKER_MOUSEDOWN_FUNC(SDL_Event* event, UI_Widget item){
    if(UI_GetVisiable(item) == false)
        return ;
    SDL_Color color;
    SDL_GetRenderDrawColor(_UI_Render, &color.r, &color.g, &color.b, &color.a);
    SDL_SetRenderDrawColor(_UI_Render, 100, 100, 100, 100);
    SDL_Rect rect = UI_GetRect(item);
    SDL_RenderFillRect(_UI_Render, &rect); 
    SDL_SetRenderDrawColor(_UI_Render, color.r, color.g, color.b, color.a);
}

void UI_Quit(){
    free(UIStorage);
    UIStorage = NULL;
}