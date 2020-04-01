//
//  ObjCScreen.h
//  screen
//
//  Created by Malachi Holden on 3/3/20.
//  Copyright © 2020 Malachi Holden. All rights reserved.
//

#ifndef ObjCScreen_h
#define ObjCScreen_h

#import <Foundation/Foundation.h>
#include <AppKit/AppKit.h>

@interface ObjCScreen : NSObject

-(NSArray<NSScreen*>*)getObjCScreens;
-(NSScreen *)getMainScreen;
-(int)getDockLocation;

@end


#endif /* ObjCScreen_h */
