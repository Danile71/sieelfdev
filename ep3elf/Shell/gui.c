#include <swilib.h>
#include <conf_loader.h>
#include "plg.h"


typedef struct{
    GUI gui;
} MAIN_GUI;

int gui_id;
int DESK_ID;    /*id текущего рабочего стола*/

inline int IsDrwPlg(const int desk_id){
    return (desk_id==DESK_ID || desk_id==0) ? 1 : 0;
}

static void OnRedraw(MAIN_GUI *data){
    for(int i=0; i<=dl; i++){
        if(plg[i]->OnRedraw && IsDrwPlg(plg[i]->desk_id)) plg[i]->OnRedraw();
    }
}

static void OnCreate(MAIN_GUI *data, void *(*malloc_adr)(int)){
    data->gui.state=1;
    for(int i=0; i<=dl; i++)
        if(plg[i]->OnCreate) plg[i]->OnCreate();
}

static void OnClose(MAIN_GUI *data, void (*mfree_adr)(void *)){
    gui_id=data->gui.state=0;
    for(int i=0; i<=dl; i++)
        if(plg[i]->OnClose)plg[i]->OnClose();
}

static void OnFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *)){
    data->gui.state=2;
}

static void OnUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
    if (data->gui.state!=2) return;
    data->gui.state=1;
}

static int OnKey(MAIN_GUI *data, GUI_MSG *msg){
    /*if ((msg->gbsmsg->msg==KEY_DOWN || msg->gbsmsg->msg==LONG_PRESS))
        DirectRedrawGUI_ID(gui_id);*/
    int key=msg->gbsmsg->submess;
    int style=msg->gbsmsg->msg;
    switch (style){
        case KEY_DOWN:
            if(key==LEFT_BUTTON)DESK_ID--;
            if(key==RIGHT_BUTTON)DESK_ID++;
            DirectRedrawGUI_ID(gui_id);
        break;
    }
    for(int i=0; i<=dl; i++){
        if(plg[i]->OnKey && IsDrwPlg(plg[i]->desk_id))plg[i]->OnKey(key, style);
    }
    return(0);
}

void kill_data(void *p, void (*func_p)(void *)){
    register void * p0 asm("r0")= p;
    register void * p1 asm("r1")= (void*)func_p;
    asm volatile("bx %1\n\t"::"r"(p0),"r"(p1));
}

int method8(void){return 0;}
int method9(void){return 0;}

const void * const gui_methods[11]={
    (void *)OnRedraw,
    (void *)OnCreate,
    (void *)OnClose,
    (void *)OnFocus,
    (void *)OnUnfocus,
    (void *)OnKey,
    0,
    (void *)kill_data,
    (void *)method8,
    (void *)method9,
    0
};

void CloseShellGUI(void){
    if (gui_id)
        GeneralFunc_flag1(gui_id, 0);
}

void CreateShellGUI(){
    static RECT Canvas= {0,0,0,0};
    MAIN_GUI *main_gui = malloc(sizeof(MAIN_GUI));
    zeromem(main_gui,sizeof(MAIN_GUI));
    Canvas.x2=ScreenW()-1;
    Canvas.y2=ScreenH()-1;
    main_gui->gui.canvas=(RECT *)(&Canvas);
    main_gui->gui.methods=(void *)gui_methods;
    main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
    gui_id=CreateGUI(main_gui);
}
