#ifndef UIElements_DEF
#define UIElements_DEF

struct Element_Shape{
    int offset_X, offset_Y;
    int height;
    int *boundrary_start;
    int *boundrary_end;
} Element_Shape;

struct UI_Element
{
    int posX, posY;
    struct Element_Shape *shapes; int shapeCount;
} UI_Element;


#endif