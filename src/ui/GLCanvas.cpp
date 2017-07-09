#include "GLCanvas.h"

BEGIN_EVENT_TABLE(GLCanvas, wxGLCanvas)
    EVT_SIZE(GLCanvas::resized)
    EVT_PAINT(GLCanvas::render)
    EVT_CLOSE(GLCanvas::closeCanvas)

    EVT_MOUSEWHEEL(GLCanvas::mouseWheel)
    EVT_LEAVE_WINDOW(GLCanvas::mouseLeave)

    EVT_KEY_DOWN(GLCanvas::keyDown)
    EVT_KEY_UP(GLCanvas::keyUp)
END_EVENT_TABLE()

GLCanvas::GLCanvas(wxWindow *parent, int *args, int id) : wxGLCanvas(parent, wxID_ANY, args, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE){
    context = new wxGLContext(this);
    this->parent = parent;
    this->id = id;
    map = 0;
    //Blank out all the keys to start with.
    for(int i = 0; i < CANVAS_KEYS_LENGTH; i++){
        keys[i] = false;
    }
}

GLCanvas::~GLCanvas(){
    window->destroy();
    delete context;
}

void GLCanvas::resized(wxSizeEvent& evt){
    Refresh();
    if(windowCreated) setViewportSize();
}

void GLCanvas::setViewportSize(){
    if(!windowCreated || closed) return;

    //int width, height;
    GetSize(&width, &height);
    if(map) map->getCamera()->setAspectRatio(Ogre::Real(width) / Ogre::Real(height));

    window->resize(width, height);
}

void GLCanvas::makeCurrent(){
    wxGLCanvas::SetCurrent(*context);
}


void GLCanvas::render(wxPaintEvent& evt){
    renderFrame();
}

void GLCanvas::renderFrame(){
    if(!IsShown() || closed) return;

    if(!windowCreated){
        makeCurrent();
        createWindow();
    }
    if(map){
        if(!map->getMapStarted()) map->start(this);
    }

    window->setActive(true);

    setViewportSize();

    Ogre::Root::getSingleton().renderOneFrame();

    //glFlush();
    //SwapBuffers();
    window->update(true);
}

void GLCanvas::createWindow(){
    if(windowCreated) return;
    Ogre::NameValuePairList params;

    params["currentGLContext"] = "true";
    window = Ogre::Root::getSingleton().createRenderWindow("Window" + std::to_string(id), 100, 100, false, &params);
    windowCreated = true;
}


void GLCanvas::setMap(Map *map){
    this->map = map;
}

Ogre::RenderWindow* GLCanvas::getWindow(){
    return window;
}

void GLCanvas::closeCanvas(wxCloseEvent &event){
    std::cout << "Canvas " + std::to_string(id) + " closing!" << std::endl;
    closed = true;
    window->removeAllViewports();
    map->destroy();
    delete map;
    //The window and things are deleted in the destuctor
}

void GLCanvas::mouseLeave(wxMouseEvent &event){
    if(mouseCaptured && map){
        warpCursorToCentre();
        //map->pointCamera(prevMouseX - mouseX, prevMouseY - mouseY);
    }
}

bool GLCanvas::getMouseButton(const int id){
    if(id == MOUSE_LEFT) return mouseLeft;
    else if(id == MOUSE_RIGHT) return mouseRight;
    else return false;
}

void GLCanvas::warpCursorToCentre(){
    int width, height;
    GetSize(&width, &height);

    int newWidth = width / 2;
    int newHeight = height / 2;
    WarpPointer(newWidth, newHeight);

    prevMouseX = newWidth;
    prevMouseY = newHeight;
    mouseX = newWidth;
    mouseY = newHeight;
}

void GLCanvas::captureMouse(bool capture){
    if(capture){
        mouseCaptured = true;
        parent->SetCursor(wxCursor(wxCURSOR_BLANK));
    }else{
        mouseCaptured = false;
        parent->SetCursor(wxCursor(wxCURSOR_ARROW));
    }
    warpCursorToCentre();
}

void GLCanvas::mouseWheel(wxMouseEvent &event){
    if(map){
        int ammount = 0;
        if(event.GetWheelRotation() < 0) ammount = -5;
        else ammount = 5;
        //changezom
    }
}

void GLCanvas::keyDown(wxKeyEvent &event){
    int val = (int)event.GetKeyCode();
    if(val >= 0 && val < CANVAS_KEYS_LENGTH) keys[val] = true;
}

void GLCanvas::keyUp(wxKeyEvent &event){
    int val = (int)event.GetKeyCode();
    if(val >= 0 && val < CANVAS_KEYS_LENGTH) keys[val] = false;
}

void GLCanvas::updateLogic(){
    //Failsafes for the map and things
    if(!map) return;
    if(!map->getMapStarted()) return;

    if(switchCameraCount > 0) switchCameraCount--;

    //Figure out the position of the mouse each frame.
    //This prevents issues with the callbacks not being fired with the timer.
    if(HasFocus()){
        wxMouseState state = wxGetMouseState();
        int newMouseX = state.GetPosition().x - GetScreenPosition().x;
        int newMouseY = state.GetPosition().y - GetScreenPosition().y;

        //If the mouse is within the bounds of the canvas...
        if(newMouseX > 0 && newMouseY > 0 && newMouseX <= width && newMouseY <= height){
            //Mouse moved
            if(prevMouseX != mouseX || prevMouseY != mouseY){
                if(mouseCaptured){
                    map->pointCamera(mouseX - prevMouseX, -(mouseY - prevMouseY));
                    renderFrame();
                }else{
                    map->updateCursor(mouseX, mouseY);
                    renderFrame();
                }
            }

            mouseInside = true;
            prevMouseX = mouseX;
            prevMouseY = mouseY;

            mouseX = newMouseX;
            mouseY = newMouseY;

            mouseLeft = state.LeftDown();
            mouseRight = state.RightDown();

            if(keys[wxKeyCode::WXK_TAB])switchCameraMode();

            map->updateInput();
        }else{
            mouseInside = false;
        }
    }else{
        mouseInside = false;
    }
}

bool GLCanvas::getKey(const int keyId){
    if(keyId >= 0 && keyId < CANVAS_KEYS_LENGTH) return keys[keyId];
    else return false;
}

void GLCanvas::switchCameraMode(){
    if(switchCameraCount > 0) return;

    switchCameraCount = 10;
    captureMouse(!mouseCaptured);
}

int GLCanvas::getMouseX(){
    return mouseX;
}

int GLCanvas::getMouseY(){
    return mouseY;
}

int GLCanvas::getWidth(){
    return width;
}

int GLCanvas::getHeight(){
    return height;
}

bool GLCanvas::getMouseInside(){
    return mouseInside;
}
