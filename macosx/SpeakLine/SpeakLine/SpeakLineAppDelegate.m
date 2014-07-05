//
//  SpeakLineAppDelegate.m
//  SpeakLine
//
//  Created by zouivex on 2014/7/5.
//  Copyright (c) 2014年 zouxu. All rights reserved.
//

#import "SpeakLineAppDelegate.h"

@implementation SpeakLineAppDelegate

- (id)init
{
    self = [super init];
    if(self)
    {
        _speechSynth = [[NSSpeechSynthesizer alloc] init];
    }
    return self;
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    // Insert code here to initialize your application
}

- (IBAction)sayIt:(NSButton *)sender
{
    NSString *string = [self.textField stringValue];
    if([string length] != 0)
    {
        [_speechSynth startSpeakingString:string];
    }
}

- (IBAction)stop:(NSButton *)sender
{
    [_speechSynth stopSpeaking];
}
@end
