cmake_minimum_required(VERSION 2.8.9)
project (rockpool)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -pthread")

set(${LIBS_DIR} "/home/edward/Documents/wxWidgets-3.0.2/static/lib/")

link_directories(/home/edward/Documents/wxWidgets-3.0.2/static/lib/)

include_directories(/home/edward/Documents/wxWidgets-3.0.2/include)
include_directories(/home/edward/Documents/wxWidgets-3.0.2/static/lib/wx/include/gtk3-unicode-static-3.0)

include_directories(/usr/include/gtk-3.0)
include_directories(/usr/include/at-spi2-atk/2.0)
include_directories(/usr/include/at-spi-2.0)
include_directories(/usr/include/dbus-1.0)
include_directories(/usr/lib/x86_64-linux-gnu/dbus-1.0/include)
include_directories(/usr/include/gtk-3.0)
include_directories(/usr/include/gio-unix-2.0/)
include_directories(/usr/include/mirclient)
include_directories(/usr/include/mircommon)
include_directories(/usr/include/mircookie)
include_directories(/usr/include/cairo)
include_directories(/usr/include/pango-1.0)
include_directories(/usr/include/harfbuzz)
include_directories(/usr/include/pango-1.0)
include_directories(/usr/include/atk-1.0)
include_directories(/usr/include/pixman-1)
include_directories(/usr/include/freetype2)
include_directories(/usr/include/libpng12)
include_directories(/usr/include/gdk-pixbuf-2.0)
include_directories(/usr/include/glib-2.0)
include_directories(/usr/lib/x86_64-linux-gnu/glib-2.0/include)

include_directories(/usr/include/gio-unix-2.0)
include_directories(/usr/include/pango-1.0)
include_directories(/usr/include/gdk-pixbuf-2.0)
include_directories(/usr/include/pixman-1)

include_directories(/usr/local/include/OGRE)


add_executable(rockpool
src/ui/Application.cpp
src/ui/GLCanvas.cpp
src/ui/MainFrame.cpp
src/ui/RenderTimer.cpp
src/ui/TerrainInfoHandler.cpp
src/ui/TerrainInfoLayerBox.cpp

src/ui/Hierarchy/ObjectHierarchy.cpp
src/ui/Hierarchy/HierarchyTree.cpp
src/ui/Hierarchy/HierarchyRightClickMenu.cpp
src/ui/Hierarchy/HierarchyRightClickNew.cpp

src/ui/Dialogs/MapPropertiesDialog.cpp
src/ui/Dialogs/NewMapDialog.cpp
src/ui/Dialogs/MapLoadProgressDialog.cpp
src/ui/Dialogs/TerrainLayerResourceDialog.cpp

src/ui/Resource/ResourceBrowser.cpp
src/ui/Resource/ResourcePanel.cpp
src/ui/Resource/ResourceTile.cpp
src/ui/Resource/ResourceTileCover.cpp

src/ui/Tools/ToolPreferencesHandler.cpp
src/ui/Tools/TerrainEditToolPreferences.cpp
src/ui/Tools/TerrainTextureToolPreferences.cpp
src/ui/Tools/TerrainHeightToolPreferences.cpp
src/ui/Tools/TerrainSmoothToolPreferences.cpp
src/ui/Tools/ToolPreferences.cpp
src/ui/Tools/ToolsPanelHandler.cpp

src/system/ResourceManager.cpp

src/system/Command/CommandManager.cpp
src/system/Command/Command.cpp
src/system/Command/TerrainCommand.cpp
src/system/Command/TerrainEditCommand.cpp
src/system/Command/TerrainTextureCommand.cpp

src/system/Command/Object/ObjectCommand.cpp
src/system/Command/Object/AddObjectCommand.cpp
src/system/Command/Object/DeleteObjectCommand.cpp
src/system/Command/Object/DuplicateObjectCommand.cpp
src/system/Command/Object/ArrangeObjectCommand.cpp

src/graphics/OgreComponent.cpp
src/graphics/Trackball

src/map/Terrain.cpp
src/map/Map.cpp
src/map/Main.cpp
src/map/MapDecal.cpp

src/map/Object/Object.cpp

src/util/tinyxml2.cpp
)

target_link_libraries(
rockpool
libwx_gtk3u_aui-3.0.a
libwx_gtk3u_xrc-3.0.a
libwx_gtk3u_qa-3.0.a
libwx_baseu_net-3.0.a
libwx_gtk3u_html-3.0.a
libwx_gtk3u_adv-3.0.a
libwx_gtk3u_core-3.0.a
libwx_baseu_xml-3.0.a
libwx_baseu-3.0.a
libwx_gtk3u_gl-3.0.a
gthread-2.0
X11
Xxf86vm
SM
gtk-3
gdk-3
pangocairo-1.0
pango-1.0
atk-1.0
cairo-gobject
cairo
gdk_pixbuf-2.0
gio-2.0
gobject-2.0
glib-2.0
png
expat
wxregexu-3.0
wxtiff-3.0
wxjpeg-3.0
z
dl
m
OgreMain
OgreTerrain
boost_system
GL
OIS
)
