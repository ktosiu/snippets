//
//  SpeakLineAppDelegate.h
//  SpeakLine
//
//  Created by zouivex on 2014/7/5.
//  Copyright (c) 2014年 zouxu. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface SpeakLineAppDelegate : NSObject <NSApplicationDelegate>
{
    NSSpeechSynthesizer *_speechSynth;
}

@property (assign) IBOutlet NSWindow *window;
@property (weak) IBOutlet NSTextField *textField;

- (IBAction)sayIt:(NSButton *)sender;
- (IBAction)stop:(NSButton *)sender;

@end
