#include "CleanUp.h"

extern void GC_Init(){
    GarbageCollector            = malloc(0);
    GarbageCollector_Windows    = malloc(0);
    GarbageCollector_Renderers  = malloc(0);
    GC_ExtraCallable            = malloc(0);

    error_identifier = ErrID_GC_Init;
    malloc_verify(GarbageCollector);
    malloc_verify(GarbageCollector_Windows);
    malloc_verify(GarbageCollector_Renderers);
    malloc_verify(GC_ExtraCallable);
}

extern void GC_Append(void *item){
    GarbageCollector = realloc(GarbageCollector, GC_Count * sizeof(void*));
    error_identifier = ErrID_GC_Append; malloc_verify(GarbageCollector);
    GarbageCollector[GC_Count] = item;

    GC_Count++;
}

extern void GC_AppendWindow(void *window){
    GarbageCollector_Windows = realloc(GarbageCollector_Windows, GC_WindowCount * sizeof(void*));
    error_identifier = ErrID_GC_AppendW; malloc_verify(GarbageCollector_Windows);
    GarbageCollector_Windows[GC_WindowCount] = window;

    GC_WindowCount++;
}

extern void GC_AppendRenderer(void *renderer){
    GarbageCollector_Renderers = realloc(GarbageCollector_Renderers, GC_RendererCount * sizeof(void*));
    error_identifier = ErrID_GC_AppendR; malloc_verify(GarbageCollector_Renderers);
    GarbageCollector_Renderers[GC_RendererCount] = renderer;

    GC_RendererCount++;
}

extern void GC_AppendExtraCallable(void *callable){
    GC_ExtraCallable = realloc(GC_ExtraCallable, GC_ExtraCallable_Count * sizeof(void*));
    error_identifier = ErrID_GC_AppendC; malloc_verify(GC_ExtraCallable);
    GC_ExtraCallable[GC_ExtraCallable_Count] = callable;

    GC_ExtraCallable_Count++;
}

extern void EXECUTE_CLEANUP(){
    for (int i = 0; i < GC_Count; i++) free(GarbageCollector[i]);
    for (int i = 0; i < GC_WindowCount; i++) SDL_DestroyWindow(GarbageCollector_Windows[i]);
    for (int i = 0; i < GC_RendererCount; i++) SDL_DestroyRenderer(GarbageCollector_Renderers[i]);
    for (int i = 0; i < GC_ExtraCallable_Count; i++) (*GC_ExtraCallable[i]) ();

    free(GarbageCollector);
    free(GarbageCollector_Windows);
    free(GarbageCollector_Renderers);
    free(GC_ExtraCallable);
}