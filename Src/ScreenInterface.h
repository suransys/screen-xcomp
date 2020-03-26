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

#endif /* Screen_hpp */
