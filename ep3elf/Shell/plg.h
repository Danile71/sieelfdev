typedef struct{
    void(*OnRedraw)();
    void(*OnCreate)();
    void(*OnClose)();
    void(*OnKey)(int key, int type);
    int desk_id;    //id рабочего стола

    void(*PlgOnCreate)();   //действия при загрузке плагина(например подгрузить графику)
    void(*PlgOnClose)();    //действия при выгрузке плагина(например очистить память от графики)
}PLG;

extern PLG **plg;
extern int dl;

void LoadPlugins(const char *dir);
void DestroyPlugins(void);
