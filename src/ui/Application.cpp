#include "Application.h"
#include "MainFrame.h"

#include "../graphics/OgreComponent.h"
#include "../map/Main.h"
#include "../system/ResourceManager.h"
#include "../system/Command/CommandManager.h"
#include "../system/SkyBoxManager.h"

#include "../map/SkyBox.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit(){
    OgreComponent *ogreComponent = new OgreComponent();
    Main *main = new Main();

    ResourceManager *resourceManager = new ResourceManager(main);
	main->setResourceManager(resourceManager);

	SkyBoxManager *skyBoxManager = new SkyBoxManager();

	/*for(int i = 0; i < 5; i++){
        SkyBox *skyBox = new SkyBox();
        skyBox->setName("Test" + std::to_string(i));
        for(int i = 0; i < 6; i++){
            skyBox->setSkyBoxValue(i, "Hello");
        }
        skyBoxManager->addSkyBox(skyBox);
    }*/

	main->setSkyBoxManager(skyBoxManager);

	MainFrame *mainFrame = new MainFrame(main, wxT("Rockpool"));

	CommandManager *commandManager = new CommandManager(mainFrame);
	main->setCommandManager(commandManager);

	mainFrame->Show(true);
    main->loadMap(mainFrame, "/home/edward/Documents/Rockpool/tests/test/test.rockpool", "/home/edward/Documents/Rockpool/tests/test");
    //main->loadMap(mainFrame, "/home/edward/Documents/Rockpool/tests/New Map/New Map.rockpool", "/home/edward/Documents/Rockpool/tests/New Map");
    //main->loadMap(mainFrame, "/home/edward/Documents/Rockpool/tests/Something/Something.rockpool", "/home/edward/Documents/Rockpool/tests/Something");

	return true;
}
