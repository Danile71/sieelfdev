#include <swilib.h>
#include "../../plg.h"

/*фон, иконки запуска*/

IMGHDR *bg;

void DrawIMG(IMGHDR *img, int x, int y/*, int x2, int y2*/)
{
	RECT rc;
	DRWOBJ drwobj;
	/*if(!x2 && !y2)
	{
		StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
		SetPropTo_Obj5(&drwobj, &rc, 0, img);
	}
	else
	{
		StoreXYXYtoRECT(&rc, x, y, x2, y2);
		SetProp2ImageOrCanvas(&drwobj, &rc, 0, img, x, y);
	}*/
	StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
    SetPropTo_Obj5(&drwobj, &rc, 0, img);
	SetColor(&drwobj, NULL, NULL);
	DrawObject(&drwobj);
}

void OnRedraw(void){
    if(bg)  DrawIMG(bg, 0, 0);
    else    DrawRectangle(0, 0, 131, 175, 0, GetPaletteAdrByColorIndex(0), GetPaletteAdrByColorIndex(1));
}

void OnCreate(void){
    //ShowMSG(1,(int)"Create");
}

void OnKey(int key, int type){
    //ShowMSG(1, (int)key);
}

void PlgOnClose(void){
    if(bg){
        mfree(bg->bitmap);
        mfree(bg);
    }
}

void PlgOnCreate(void){
    /*zeromem(bg, sizeof(IMGHDR));
    bg=malloc(sizeof(IMGHDR));*/
    FSTATS fs;
    unsigned int err;
    if(GetFileStats("0:\\Zbin\\bg.png", &fs, &err)!=-1)
        bg=CreateIMGHDRFromPngFile("0:\\Zbin\\bg.png", 0);
}

void _init(PLG *plg){
    plg->OnRedraw=(void*)OnRedraw;
    plg->OnCreate=(void*)OnCreate;
    /*plg->OnClose=(void*)OnClose;*/
    plg->OnKey=(void(*)(int,int))OnKey;
    plg->PlgOnCreate=(void*)PlgOnCreate;
    plg->PlgOnClose=(void*)PlgOnClose;
    plg->desk_id=0;
}


// Если с++ либа то в либы добаляем ещё supc++
