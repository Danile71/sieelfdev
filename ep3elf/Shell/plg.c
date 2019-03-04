#include <swilib.h>
#include "plg.h"

PLG **plg;
int dl=-1;

void LoadPlugins(const char *dir){
    static DIR_ENTRY de;
    char path[128];
    strcpy(path,dir);
    unsigned int err;
    char *ptr=path+strlen(path)+1;
    strcat(path, "\\*.so");
    if (FindFirstFile(&de, path, &err)){
        do{
            strcpy(ptr, de.file_name);
            dl=_dlopen(path);
            if(dl!=-1){
                plg=realloc(plg, sizeof(PLG)*(dl+1));
                plg[dl]=malloc(sizeof(PLG));
                zeromem(plg[dl], sizeof(PLG));
                void (*init)(PLG *) = (void(*)(PLG*))_dlsym(dl, "_init");
                init(plg[dl]);
                if(plg[dl]->PlgOnCreate) plg[dl]->PlgOnCreate();
            }
        }
        while(FindNextFile(&de, &err));
    }
    FindClose(&de, &err);
}

void DestroyPlugins(void){
    if(dl!=-1){
        for(int i=0; i<=dl; i++){
            if(plg[i]->PlgOnClose) plg[dl]->PlgOnClose();
            _dlclose(i);
            mfree(plg[i]);
            mfree(plg);
            }
    }
}
