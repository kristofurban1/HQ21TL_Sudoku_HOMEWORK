/*
    Cleanup handles loose allocated memory to prevent memory leaks.
    This will collect long term allocated memory, like windows, or frequently used strings, and collects their pointers.

    When Cleanup is executed, all the appended allocations will be freed.
*/

#ifndef CLEANUP_DEF
#define CLEANUP_DEF

#include "debugmalloc.h"
#include "ErrorHandler.h"

#include <SDL2/SDL.h>

static int GC_Count = 0;
static void **GarbageCollector;

static int GC_WindowCount = 0;
static void **GarbageCollector_Windows;

static int GC_RendererCount = 0;
static void **GarbageCollector_Renderers;

static int GC_ExtraCallable_Count = 0;
static void (**GC_ExtraCallable) (void);

/*
    @brief Initialize
    @note Call before attemplting to use garbage collector.
    @exception Handles errors with ErrorHandler
*/
extern void GC_Init();

/*
    @breaf Append generic pointer to garbage collector.
    @param item Pointer to string, array, struct, etc.
    @note This is only used to track long lifespan allocations on heap. Do not append anything you wish to free in the near future.
    @note ---
    @note Total memory usage: Number of tracked allocations * 8 (*4 on 32bit systems) 
    @exception Handles errors with ErrorHandler
*/
extern void GC_Append(void *item);

/*
    @brief Append window.
    @param window Pointer to window.
    @note These are freed with special commands, so they are traced separately.
    @note ---
    @note Total memory usage: Number of tracked windows * 8 (*4 on 32bit systems) 
    @exception Handles errors with ErrorHandler
*/
extern void GC_AppendWindow(void *window);

/*
    @brief Append renderer.
    @param renderer Pointer to renderer.
    @note These are freed with special commands, so they are traced separately.
    @note ---
    @note Total memory usage: Number of tracked renderers * 8 (*4 on 32bit systems) 
    @exception Handles errors with ErrorHandler
*/
extern void GC_AppendRenderer(void *renderer);

/*
    @bried Append pointer to function to call during cleanup.
    @param callable Function pointer with no arguments.
*/
extern void GC_AppendExtraCallable(void *callable);

/*
    @brief Frees every appended item. Call at the end of the program.
    @note Uninitializes Cleanup!
*/
extern void EXECUTE_CLEANUP();


#define ErrID_GC_Init       "Cleanup.c: GC_Init\n"

#define ErrID_GC_Append     "Cleanup.c: GC_Append\n"
#define ErrID_GC_AppendW    "Cleanup.c: GC_AppendWindow\n"
#define ErrID_GC_AppendR    "Cleanup.c: GC_AppendRenderer\n"
#define ErrID_GC_AppendC    "Cleanup.c: GC_AppendExtraCallable\n"

#endif