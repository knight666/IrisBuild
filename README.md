# IrisBuild

An integrated build system for Adobe Flash Professional. IrisBuild adds a new window to Adobe Flash Professional, which allows you to manage projects in a solution, track external dependencies (like images, sounds and source files) and dependencies between projects.

# Requirements

One of these versions of Flash must be installed:

- Adobe Flash Professional CC 2015
- Adobe Flash Professional CS5.5
- Adobe Flash Professional CS5

In order to install IrisBuild as an extension, Adobe Extension Manager must be installed as well.

# Building

## Requirements

- Visual Studio 2012 or newer
- FlashDevelop 5.1 or newer
- Flex SDK + Air SDK (optional checkbox in FlashDevelop)
- Python 2.7

## Generate a solution

Use GYP to generate a Visual Studio solution:

	D:\Projects\IrisBuild>set GYP_MSVS_VERSION=2013

	D:\Projects\IrisBuild>dependencies\gyp-master\gyp --depth IrisBuild.gyp

Make sure you set the Visual Studio version correctly. GYP generates Visual Studio 2012 solutions by default.

## Building the DLL

Adobe Flash Professional CC 2015 requires a 64-bit DLL, while previous versions require a 32-bit one. Make sure you set the target and platform correctly before building.

## Building the GUI

Open "IrisBuildGUI.as3proj" in FlashDevelop and select "Test Project". This will generate the GUI's SWF file.

## Manual installation

Close all running instances of Flash Professional. Use "install.py" to copy the files to the application directory.