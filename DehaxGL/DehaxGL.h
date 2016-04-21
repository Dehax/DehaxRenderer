#ifndef DEHAXGL_H
#define DEHAXGL_H

#include "dehaxgl_global.h"
#include "IViewport.h"

class DEHAXGLSHARED_EXPORT DehaxGL
{
    
public:
    explicit DehaxGL(IViewport *viewport);
    
private:
    IViewport *m_viewport;
    
};

#endif // DEHAXGL_H
