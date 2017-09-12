#ifndef GLCANVAS_H
#define GLCANVAS_H

#include <wx/wx.h>
#include <wx/glcanvas.h>
#include "../map/Map.h"

extern "C"
{
#include "../graphics/Trackball.h"
}

#include <OGRE/Ogre.h>
#include <string>

#define KEY_W 87
#define KEY_A 65
#define KEY_S 83
#define KEY_D 68

#define KEY_O 79
#define KEY_F 70
#define KEY_G 71
#define KEY_M 77

#define KEY_X 88
#define KEY_Y 89
#define KEY_Z 90

#define KEY_ESCAPE 27

#define CANVAS_KEYS_LENGTH 350

#define MOUSE_LEFT 1
#define MOUSE_RIGHT 2


class Map;

class GLCanvas : public wxGLCanvas
{
    public:
        GLCanvas(wxWindow *parent, int *args, int id);
        virtual ~GLCanvas();

        void resized(wxSizeEvent& evt);
        void render(wxPaintEvent& evt);

        void renderFrame();
        void updateLogic();

        void setMap(Map *map);
        void setViewportSize();
        void warpCursorToCentre();

        int getMouseX();
        int getMouseY();

        int getWidth();
        int getHeight();

        int getMouseDiffX();
        int getMouseDiffY();

        bool getKey(int keyId);
        bool getMouseButton(int button);
        bool getMouseInside();
        bool getMouseMoved();

        Ogre::RenderWindow* getWindow();

        DECLARE_EVENT_TABLE()

    protected:

    private:
        wxGLContext *context;
        wxWindow *parent;

        void closeCanvas(wxCloseEvent &event);

        void makeCurrent();
        void createWindow();

        bool windowCreated = false;
        bool closed = false;
        bool mouseCaptured = false;

        Ogre::RenderWindow *window;
        int id;

        int prevMouseX = 0;
        int prevMouseY = 0;
        int mouseDiffX = 0;
        int mouseDiffY = 0;
        int mouseX = 0;
        int mouseY = 0;
        int width = 0;
        int height = 0;

        Map *map;

        void keyDown(wxKeyEvent &event);
        void keyUp(wxKeyEvent &event);

        void mouseWheel(wxMouseEvent &event);
        void mouseLeave(wxMouseEvent &event);

        bool mouseLeft = false;
        bool mouseRight = false;
        bool mouseInside = false;
        bool mouseMoved = false;

        bool keys[CANVAS_KEYS_LENGTH];
};

#endif // GLCANVAS_H
