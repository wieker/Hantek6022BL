#ifndef URBPROCESSOR_H
#define URBPROCESSOR_H

#include "fx2pipe/fx2pipe.h"
#include "mywidget.h"


class URBProcessor : public FX2Pipe
{
    MyWidget* myGLView;

public:
    URBProcessor(MyWidget* myGLView);

    ErrorCode URBNotify(URB *u);
};

#endif // URBPROCESSOR_H
