#include "urbprocessor.h"
#include <iostream>

URBProcessor::URBProcessor()
{

}

URBProcessor::ErrorCode URBProcessor::URBNotify(URB *u) {
    std::cout << "direction: " <<
                 + u->dir() << std::endl;
    std::cout << "actual_length: " <<
                 + u->actual_length << std::endl;
    if(_SubmitOneURB(NULL, 0)) {
        return(ECUserQuit);
    }
    return(ECSuccess);
    return FX2Pipe::URBNotify(u);
}

