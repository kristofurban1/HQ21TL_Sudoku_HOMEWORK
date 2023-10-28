#include "CleanUp.h"

extern void GC_Init(){
    GarbageCollector            = malloc(0);
    GarbageCollector_Windows    = malloc(0);
    GarbageCollector_Renderers  = malloc(0);

    /*
    SetErrorIndentfyer(ErrID_GC_Init);
    malloc_verify(GarbageCollector);
    malloc_verify(GarbageCollector_Windows);
    malloc_verify(GarbageCollector_Renderers);
    */
}

extern void GC_Append(void *item){
    GC_Count++;

    GarbageCollector = realloc(GarbageCollector, GC_Count * sizeof(void*));
    SetErrorIndentfyer(ErrID_GC_Append); malloc_verify(GarbageCollector);
    GarbageCollector[GC_Count-1] = item;
}

extern void GC_AppendWindow(void *window){
    GC_WindowCount++;

    GarbageCollector_Windows = realloc(GarbageCollector_Windows, GC_WindowCount * sizeof(void*));
    SetErrorIndentfyer(ErrID_GC_AppendW); malloc_verify(GarbageCollector_Windows);
    GarbageCollector_Windows[GC_WindowCount -1] = window;
}

extern void GC_AppendRenderer(void *renderer){
    GC_RendererCount++;
 
    GarbageCollector_Renderers = realloc(GarbageCollector_Renderers, GC_RendererCount * sizeof(void*));
    SetErrorIndentfyer(ErrID_GC_AppendR); malloc_verify(GarbageCollector_Renderers);
    GarbageCollector_Renderers[GC_RendererCount -1] = renderer;
}


extern void EXECUTE_CLEANUP(){
    for (int i = 0; i < GC_Count; i++) free(GarbageCollector[i]);
    for (int i = 0; i < GC_WindowCount; i++) SDL_DestroyWindow(GarbageCollector_Windows[i]);
    for (int i = 0; i < GC_RendererCount; i++) SDL_DestroyRenderer(GarbageCollector_Renderers[i]);

    free(GarbageCollector);
    free(GarbageCollector_Windows);
    free(GarbageCollector_Renderers);
}