//
//  AppController.m
//  RaiseMan
//
//  Created by zouivex on 2014/7/7.
//  Copyright (c) 2014年 zouxu. All rights reserved.
//

#import "AppController.h"
#import "PreferenceController.h"

@implementation AppController

- (IBAction)showPreferencePanel:(id)sender
{
    if(!preferenceController)
    {
        preferenceController = [[PreferenceController alloc]init];
    }
    [preferenceController showWindow:self];
}

@end
