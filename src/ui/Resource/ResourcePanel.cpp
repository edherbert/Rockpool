#include "ResourcePanel.h"

ResourcePanel::ResourcePanel(wxWindow *parent, ResourceManager *resManager) : wxPanel(parent){
    this->parent = parent;
    this->resManager = resManager;

    SetBackgroundColour(wxColour("#0000FF"));

    Connect(wxEVT_SIZE, wxSizeEventHandler(ResourcePanel::onResize));
}

ResourcePanel::~ResourcePanel(){

}

void ResourcePanel::updateTiles(){
//This creates all the tiles and sets their data, however does not position them.
    std::vector<resourceLocation*> locations = resManager->getResources();

    int totalSize = 0;
    for(resourceLocation *l : locations){
        totalSize += l->resources.size();
    }

    if(totalSize > tiles.size()){
        int ammountToAdd = totalSize - tiles.size();
        for(int i = 0; i < ammountToAdd; i++){
            ResourceTile *tile = new ResourceTile(this);
            tiles.push_back(tile);
        }
    }
    else if(totalSize < tiles.size()){
        tiles.resize(totalSize);
    }

    int tileCount = 0;
    for(resourceLocation *l : locations){
        for(wxString s : l->resources){
            tiles.at(tileCount)->setLabel(s);
            tileCount ++;
        }
    }
}

void ResourcePanel::layoutTiles(){
    int width, height;
    GetSize(&width, &height);

    int tileWidth = width / 100;

    int currentX = 0;
    int currentY = 0;
    for(ResourceTile *tile : tiles){
        tile->SetPosition(wxPoint(currentX * 100, currentY * 100));

        currentX++;
        if(currentX >= tileWidth){
            currentX = 0;
            currentY++;
        }
    }
}

void ResourcePanel::onResize(wxSizeEvent &event){
    layoutTiles();
}
