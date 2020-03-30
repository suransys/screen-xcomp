#  Screen Xcomp

Screen is a C++ and Objective C library that exposes mac hardware attributes to omnis code, so that you can access attributes like screen height, width, and dock position from within Omnis code.

## Compiling

You must compile Screen using Xcode on a Mac

Go to https://omnis.net/developers/resources/download/tools/buildyourown.jsp. If the link doesn't work, find the downloads page on Omnis.net and go to Component SDK
Find the section called *External Components and Java Objects*. Click the link to download the Mac OSX source.
When the .dmg file downloads, open it with Disk Image Mounter. Inside is a folder called something like *OSX-SDK-10.1*. Copy this folder and paste it somewhere in your files, wherever you want your working directory to be.

Open a command line tool and cd into the new directory you just pasted, something like

`cd ~/Documents/OSX-SDK-10.1`

Now copy the package tools/omnisrc64.app to xcode's tools folder, like this:

`sudo cp -rf tools/omnisrc64.app /Applications/Xcode.app/Contents/Developer/Tools`

Still in OSX-SDK-10.1, clone the git repo

`git clone git@github.com:suransys/screen-xcomp.git`

In Finder, open the new cloned directory, called screen-xcomp. Open the package Screen.xcodeproj using Xcode (Clicking on this file should open it with Xcode automatically)

In Xcode, the build target should say *UnicodeCore > My Mac*. Click the triangle play button (or go to Product > Build) to build the project

In the directory OSX-SDK-10.1, open _OSXUnicodeDbg. The build output should be there, a package called *Screen.u_xcomp*

the build output will NOT automatically appear in Build. If there is a file there, it was there already before you ran the xcode build. If you make a change to the xcode build and want your new build to appear in the git repository, make sure to delete Screen.u_xcomp from Build and replace it with the version in _OSXUnicodeDbg


## Running

To use Screen in Omnis, copy the build output *Screen.u_xcomp* to the contents folder in the Omnis app by running the following command, substituting `OMNIS_APP_FILE_NAME` for the omnis app file name (*Omnis Studio 10.1 24136.app* in my case)

`cp -rf _OSXUnicodeDbg/Screen.u_xcomp /Applications/OMNIS_APP_FILE_NAME/Contents/MacOS/xcomp/`

open Omnis, or restart it if it is already open

open the library you want to include Screen in

In the studio browser, under libraries, click on your library and click External Components

In the Component Libraries box, Click the External Components dropdown and find the xcomp called Screen

Select the radio button to load the xcomp


## Using in Omnis

The code `Screen.$screens()` and `Screen.$dock()` will retrieve the screens and dock information, respectively

`$screens()` returns an omnis list with a row for each screen in use by the mac. It has the following columns:

`startX` -- the horizontal distance from the left side of the screen to the left side of the main monitor

`startY` -- the vertical distance from the top of the screen to the top of the main monitor

`pixelHeight` -- the height of the screen

`pixelWidth` -- the width of the screen

`usableX` -- the horizontal distance from the left side of the usable screen area to the left side of the main monitor

`usableY` --the vertical distance from the top of the usable screen area to the top of the main monitor

`usablePixelHeight` -- the height of the usable screen area

`usablePixelWidth` -- the width of the usable screen area

`isMainMonitor` -- whether the screen is the main monitor or not

`resolutionScale` -- currently this is either 1 or 2. If it is a 2, that means the monitor is a retina high density display, meaning that the x and y pixel density is double that of the pixel height and width. Future mac versions might allow for higher density scales than 2

________________

`$dock()` returns an omnis list with a single row, and two columns

`position` is an integer, either -1, 0, or 1. This tells you whether the dock is on the left, bottom, or right side of the screen, respectively

`height` is the height of the dock, measured from its anchoring wall. So if the dock is anchored to the right or left side, then "height" will technically be the width, since the dock is sideways

## Contributing
Please see our [guide to contributing](https://github.com/suransys/contributing).

