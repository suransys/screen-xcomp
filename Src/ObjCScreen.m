//
//  ObjCScreen.m
//  screen
//
//  Created by Malachi Holden on 3/3/20.
//  Copyright © 2020 Malachi Holden. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ObjCScreen.h"
#import <limits.h>

@implementation ObjCScreen

-(NSArray<NSScreen*>*)getObjCScreens{
    return [NSScreen screens];
}

-(NSScreen*)getMainScreen{
    return [NSScreen mainScreen];
}

-(int)getDockLocation{
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSString * name = [[defaults persistentDomainForName:@"com.apple.dock"] valueForKey:@"orientation"];
    if ([name isEqualToString:@"left"]) return -1;
    if ([name isEqualToString:@"bottom"]) return 0;
    if ([name isEqualToString:@"right"]) return 1;
    return INT_MAX;
}

+(void)setScreensChangedListener:(CGDisplayReconfigurationCallBack)callback withUserInfo:(void *)userInfo{
    CGDisplayRegisterReconfigurationCallback(callback, userInfo);
}

+(void)removeScreensChangedListener:(CGDisplayReconfigurationCallBack)callback{
    CGDisplayRemoveReconfigurationCallback(callback, nil);
}

-(void)setScreensChangedNotification:(void (*)(void*))callback withUserInfo:(void *)userInfo{
    self.callback = callback;
    self.userInfo = userInfo;
    [[NSDistributedNotificationCenter defaultCenter] addObserver:self selector:@selector(onScreenChanged:) name:NSApplicationDidChangeScreenParametersNotification object:nil];
}

-(void)onScreenChanged:(NSNotification*)notification{
    
    NSException* myException = [NSException

    exceptionWithName:@"notification called" reason:@"this is for debugging" userInfo:nil];
    [myException raise];
    self.callback(self.userInfo);
}

@end
