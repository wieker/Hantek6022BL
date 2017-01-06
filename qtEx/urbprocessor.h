#ifndef URBPROCESSOR_H
#define URBPROCESSOR_H

#include "fx2pipe/fx2pipe.h"
#include "myglview.h"


class URBProcessor : public FX2Pipe
{
    MyGLView* myGLView;

public:
    URBProcessor(MyGLView* myGLView);

    ErrorCode URBNotify(URB *u);
};

#endif // URBPROCESSOR_H
