#include "Application.h"
#include "MainFrame.h"

#include "../graphics/OgreComponent.h"
#include "../map/Main.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit(){
    OgreComponent ogre;
    Main *main = new Main();

	MainFrame *mainFrame = new MainFrame(main, wxT("Rockpool"));
	mainFrame->Show(true);
    //main->loadMap(mainFrame, "/home/edward/Documents/Rockpool/tests/New Map/New Map.rockpool", "/home/edward/Documents/Rockpool/tests/New Map");
    //main->loadMap(mainFrame, "/home/edward/Documents/Rockpool/tests/Something/Something.rockpool", "/home/edward/Documents/Rockpool/tests/Something");

	return true;
}
