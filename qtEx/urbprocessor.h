#ifndef URBPROCESSOR_H
#define URBPROCESSOR_H

#include "fx2pipe/fx2pipe.h"


class URBProcessor : public FX2Pipe
{
public:
    URBProcessor();

    ErrorCode URBNotify(URB *u);
};

#endif // URBPROCESSOR_H
