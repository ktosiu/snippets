//
//  PreferenceController.h
//  RaiseMan
//
//  Created by zouivex on 2014/7/7.
//  Copyright (c) 2014年 zouxu. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface PreferenceController : NSWindowController
{
    IBOutlet NSColorWell *colorWell;
    IBOutlet NSButton *checkBox;
}

- (IBAction)changeBackgroundColor:(id)sender;
- (IBAction)changeNewEmptyDoc:(id)sender;

@end
