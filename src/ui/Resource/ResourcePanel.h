#ifndef RESOURCEPANEL_H
#define RESOURCEPANEL_H

#include <wx/wx.h>
#include <vector>

class ResourceManager;
class ResourceTile;
class MainFrame;
class ResourceDragPopup;

class ResourcePanel : public wxPanel
{
    public:
        ResourcePanel(wxWindow *parent, MainFrame *mainFrame, ResourceManager *resManager);
        virtual ~ResourcePanel();

        void updateTiles();
        void layoutTiles();

        void onResize(wxSizeEvent &event);
        void selectTile(int id);

        ResourceTile* getCurrentTile();

        MainFrame* getMainFrame();

        void beginDragAnim();
        void updateDragAnim();
        void endDragAnim();

    protected:

    private:
        MainFrame *mainFrame;
        ResourceManager *resManager;

        int width, height;

        bool animatingDrag = false;
        ResourceDragPopup *currentResourcePopup;

        wxBitmap *defaultBitmap;

        ResourceTile *currentTile = 0;

        std::vector<ResourceTile*>tiles;
};

#endif // RESOURCEPANEL_H
