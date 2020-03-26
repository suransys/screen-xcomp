//
//  Screen.cpp
//  screen
//
//  Created by Malachi Holden on 3/3/20.
//  Copyright © 2020 Malachi Holden. All rights reserved.
//

#include "ScreenInterface.h"
#include "ObjCScreen.h"
#include <iostream>

std::vector<Screen> Screen::screenList(){
    std::vector<Screen> screenList = std::vector<Screen>();
    
    ObjCScreen * objCScreen = [[ObjCScreen alloc] init];
    NSArray<NSScreen*>* nsScreens = [objCScreen getObjCScreens];
    NSScreen *mainScreen = [objCScreen getMainScreen];
    
    for (int i = 0; i < [nsScreens count]; i ++){
        NSScreen * nsScreen = [nsScreens objectAtIndex:i];
        Screen screen = Screen();
        screen.pixelHeight = [nsScreen frame].size.height;
        screen.pixelWidth = [nsScreen frame].size.width;
        screen.startX = [nsScreen frame].origin.x;
        int bottomLeftY = [nsScreen frame].origin.y;
        screen.startY = bottomLeftY + mainScreen.frame.size.height - screen.pixelHeight;
        screen.usablePixelWidth =[nsScreen visibleFrame].size.width;
        screen.usablePixelHeight = [nsScreen visibleFrame].size.height;
        screen.usableX = [nsScreen visibleFrame].origin.x;
        int bottomLeftUsableY = [nsScreen visibleFrame].origin.y;
        screen.usableY = screen.startY + screen.pixelHeight - screen.usablePixelHeight - ABS(bottomLeftY - bottomLeftUsableY);
        screen.isMainMonitor = [nsScreen isEqual:mainScreen];
        screen.resolutionMultiplier =[nsScreen backingScaleFactor];
        
        screenList.push_back(screen);
    }
    return screenList;
}

int Screen::dockPosition(){
    ObjCScreen * objCScreen = [[ObjCScreen alloc] init];
    return [objCScreen getDockLocation];
}



