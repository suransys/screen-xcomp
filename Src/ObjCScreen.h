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

@property void (*callback)(void*);
@property void * userInfo;

-(NSArray<NSScreen*>*)getObjCScreens;
-(NSScreen *)getMainScreen;
-(int)getDockLocation;

-(void)setScreensChangedNotification:(void (*)(void*))callback withUserInfo:(void *) userInfo;

@end


#endif /* ObjCScreen_h */
