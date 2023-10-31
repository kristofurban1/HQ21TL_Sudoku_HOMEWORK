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

void TryFree(void *ptr){
    if (ptr != NULL) free(ptr);
}

extern void EXECUTE_CLEANUP(){
    for (int i = 0; i < GC_Count; i++) 
        if (GarbageCollector[i] != NULL) free(GarbageCollector[i]);
    for (int i = 0; i < GC_WindowCount; i++) 
        if (GarbageCollector_Windows[i] != NULL) SDL_DestroyWindow(GarbageCollector_Windows[i]);
    for (int i = 0; i < GC_RendererCount; i++) 
        if (GarbageCollector_Renderers[i] != NULL) SDL_DestroyRenderer(GarbageCollector_Renderers[i]);

    free(GarbageCollector);
    free(GarbageCollector_Windows);
    free(GarbageCollector_Renderers);
}