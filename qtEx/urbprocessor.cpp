#include "urbprocessor.h"
#include <iostream>

URBProcessor::URBProcessor(MyGLView* myGLView)
{
    this->myGLView = myGLView;
}

URBProcessor::ErrorCode URBProcessor::URBNotify(URB *u) {
    std::cout << "direction: " <<
                 + u->dir() << std::endl;
    std::cout << "actual_length: " <<
                 + u->actual_length << std::endl;
    if(_SubmitOneURB(NULL, 0)) {
        return(ECUserQuit);
    }
    if (u->dir() < 0) {
        myGLView->_update((unsigned char*) u->buffer, u->actual_length);
    }
    return(ECSuccess);
    return FX2Pipe::URBNotify(u);
}

