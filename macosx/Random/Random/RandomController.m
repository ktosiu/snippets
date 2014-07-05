//
//  RandomController.m
//  Random
//
//  Created by zouivex on 2014/7/5.
//  Copyright (c) 2014年 zouxu. All rights reserved.
//

#import "RandomController.h"

@implementation RandomController

- (IBAction)generate:(id)sender
{
    int generated = (int)(random()%100) + 1;
    [textField setIntValue:generated];
}

- (IBAction)seed:(id)sender
{
    srandom((unsigned int) time(NULL));
    [textField setStringValue:@"Generator seeded"];
}

- (void) awakeFromNib
{
    NSDate *now = [NSDate date];
    [textField setObjectValue:now];
}

@end
