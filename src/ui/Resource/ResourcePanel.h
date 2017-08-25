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
        ResourcePanel(wxWindow *parent, MainFrame *mainFrame, ResourceManager *resManager, bool dragAllowed = false);
        virtual ~ResourcePanel();

        void updateTiles();
        void layoutTiles();

        void onResize(wxSizeEvent &event);
        void selectTile(int id);

        ResourceTile* getCurrentTile();

        MainFrame* getMainFrame();

        wxBitmap* getDefaultBitmap();

        void beginDragAnim();
        void updateDragAnim();
        void endDragAnim();

        bool isDragAllowed();

    protected:

    private:
        MainFrame *mainFrame;
        ResourceManager *resManager;

        int width, height;

        bool animatingDrag = false;
        ResourceDragPopup *currentResourcePopup;

        bool dragAllowed = false;

        wxBitmap *defaultBitmap;

        ResourceTile *currentTile = 0;

        std::vector<ResourceTile*>tiles;
};

#endif // RESOURCEPANEL_H
