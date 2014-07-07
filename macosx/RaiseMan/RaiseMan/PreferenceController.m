//
//  PreferenceController.m
//  RaiseMan
//
//  Created by zouivex on 2014/7/7.
//  Copyright (c) 2014年 zouxu. All rights reserved.
//

#import "PreferenceController.h"

@interface PreferenceController ()

@end

@implementation PreferenceController

- (instancetype)init
{
    self = [super initWithWindowNibName:@"Preferences"];

    return self;
}

-(void)windowDidLoad
{
    [super windowDidLoad];
}

-(void)changeBackgroundColor:(id)sender
{
    NSColor *color = [colorWell color];
    NSLog(@"Color changed:%@", color);
}

-(void)changeNewEmptyDoc:(id)sender
{
    NSInteger state = [checkBox state];
    NSLog(@"Checkbox changed:%ld", state);
}

@end
