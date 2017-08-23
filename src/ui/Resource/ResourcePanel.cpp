#include "ResourcePanel.h"

#include "../../system/ResourceManager.h"
#include "ResourceTile.h"
#include "../MainFrame.h"

ResourcePanel::ResourcePanel(wxWindow *parent, MainFrame *mainFrame, ResourceManager *resManager) : wxPanel(parent){
    this->mainFrame = mainFrame;
    this->resManager = resManager;

    defaultBitmap = new wxBitmap("../media/img/icon.png");

    //SetBackgroundColour(wxColour("#0000FF"));

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
            ResourceTile *tile = new ResourceTile(this, defaultBitmap);
            tiles.push_back(tile);
        }
    }
    else if(totalSize < tiles.size()){
        //If there are less required tiles than needed ones
        for(int i = totalSize; i < tiles.size(); i++){
            if(currentTile == tiles.at(i)) currentTile = 0;
            tiles.at(i)->Destroy();
        }
        tiles.resize(totalSize);
    }

    int tileCount = 0;
    for(resourceLocation *l : locations){
        for(wxString s : l->resources){
            tiles.at(tileCount)->setLabel(s);
            tiles.at(tileCount)->setId(tileCount);
            tileCount++;
        }
    }
}

void ResourcePanel::layoutTiles(){
    //This positions all the tiles in the list.
    GetSize(&width, &height);

    //The number of tiles on the width, this is always the same
    int tileWidth = width / 100;

    int currentX = 0;
    //the y index of the current tile
    int currentY = 0;
    //The sum of all the heights so far
    int currentYPos = 0;

    //The maximum height that this layer can reach
    int maxHeight = 0;

    //This loops through all the tiles on the first row and sets the maxHeight to something.
    for(int i = 0; i < tileWidth; i++){
        if(i >= tiles.size())continue;
        ResourceTile *test = tiles[i];
        int tileWidth, tileHeight;
        tiles[i]->GetSize(&tileWidth, &tileHeight);
        if(tileHeight > maxHeight){
            maxHeight = tileHeight;
        }
    }

    for(ResourceTile *tile : tiles){
        tile->setPosition(currentX * 100, currentYPos);

        currentX++;
        //Go onto the next row.
        if(currentX >= tileWidth){
            currentX = 0;
            currentY++;
            //Increase the y position by the max height.
            currentYPos += maxHeight;
            for(int i = currentX + currentY * tileWidth; i < currentX + tileWidth + currentY * tileWidth; i++){
                if(i >= tiles.size())continue;
                ResourceTile *test = tiles[i];
                int tileWidth, tileHeight;
                tiles[i]->GetSize(&tileWidth, &tileHeight);
                if(tileHeight > maxHeight){
                    maxHeight = tileHeight;
                }
            }
        }
    }

    SetSize(wxSize(width, currentYPos+100));
}

void ResourcePanel::onResize(wxSizeEvent &event){
    layoutTiles();
}

void ResourcePanel::selectTile(int id){
    if(currentTile)currentTile->deSelectTile();
    if(id > tiles.size()) return;
    currentTile = tiles.at(id);
    currentTile->selectTile();
}

ResourceTile* ResourcePanel::getCurrentTile(){
    return currentTile;
}

MainFrame* ResourcePanel::getMainFrame(){
    return mainFrame;
}
