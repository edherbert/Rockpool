#ifndef RENDERTIMER_H
#define RENDERTIMER_H

#include <wx/timer.h>
#include "GLCanvas.h"

class GLCanvas;

class RenderTimer : public wxTimer
{
    public:
        RenderTimer(GLCanvas *canvas);
        virtual ~RenderTimer();

        void Notify();
        void start();

    private:
        GLCanvas *canvas;
};

#endif // RENDERTIMER_H
