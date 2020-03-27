//
//  Screen.hpp
//  screen
//
//  Created by Malachi Holden on 3/3/20.
//  Copyright © 2020 Malachi Holden. All rights reserved.
//

#ifndef Screen_hpp
#define Screen_hpp

#include <stdio.h>
#include <vector>

class Screen {
public:
    int startX;
    int startY;
    int pixelHeight;
    int pixelWidth;
    int usableX;
    int usableY;
    int usablePixelHeight;
    int usablePixelWidth;
    bool isMainMonitor;
    int resolutionMultiplier;
    
    static std::vector<Screen> screenList();
    static int dockPosition();
};



class UpdatingScreen{
    std::vector<Screen> currentScreens;
    void notifyScreensChanged();
    static void screensChangedCallback(void*);
    void (*_onScreenChanged)(std::vector<Screen>, void*);
    void * currentUserInfo;
    
    void * objCScreen;
public:
    UpdatingScreen();
    
    std::vector<Screen> getCurrentScreens();
    void setScreenChangeCallback(void (*onScreenChanged)(std::vector<Screen>, void*), void* userInfo);
    void resetCurrentScreens();
    void screenRunLoop();
    void screenEndLoop();
};

#endif /* Screen_hpp */
