#include "RenderTimer.h"

RenderTimer::RenderTimer(GLCanvas *canvas) : wxTimer(){
    this->canvas = canvas;
}

RenderTimer::~RenderTimer(){

}

void RenderTimer::Notify(){
    canvas->updateLogic();
}

void RenderTimer::start(){
    wxTimer::Start(1000/60);
}
