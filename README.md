# Rockpool
A 3d world building application designed for use across multiple game engines.

## Dependencies
Rockpool has two main dependencies:
 * [Ogre3D 1.10](http://ogre3d.org) - 3D library used.
 * [WxWidgets](https://wxwidgets.org) - Cross Platform GUI library.

These can be compiled from source, or used as shared libraries.
The Ogre libraries must be compiled dynamically, as I haven't implemented support for static ogre yet.

On Arch Linux
```
sudo pacman -S ogre wxgtk3
```

## Building
If you are compiling from source, then be sure to provide the paths to the appropriate libraries through the CMake file.
This is best done through the CMake gui by setting:
 * OGRE_MAIN_INCLUDE 
 * OGRE_MAIN_LIB
 * OGRE_TERRAIN_INCLUDE
 * OGRE_TERRAIN_LIB

to their appropriate paths.
The CMake file will hopefully find wx by itself.

I have only tested it on Linux at this point, so the CMake file might require some modification on other systems.

**Note** - There are problems with the terrain on certain systems. If a segmentation fault occurs during runtime in the terrain creation, you can disable the terrain altogether in the CMake document.

## Running
In order for the programme to run correctly, the config files need to be setup correctly. This tells Ogre where it's plugins are located. In setup/plugins.cfg, make sure the line PluginFolder=/usr/lib/OGRE is configured to the correct location of your ogre plugins directory.
This is the directory that contains files such as RenderSystem_GL.so.
