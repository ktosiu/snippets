//
//  AppController.h
//  RaiseMan
//
//  Created by zouivex on 2014/7/7.
//  Copyright (c) 2014年 zouxu. All rights reserved.
//

#import <Foundation/Foundation.h>
@class PreferenceController;

@interface AppController : NSObject
{
    PreferenceController *preferenceController;
}

- (IBAction)showPreferencePanel:(id)sender;
@end
