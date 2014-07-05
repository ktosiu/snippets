//
//  CountLineController.m
//  CountLine
//
//  Created by zouivex on 2014/7/5.
//  Copyright (c) 2014年 zouxu. All rights reserved.
//

#import "CountLineController.h"

@implementation CountLineController

- (IBAction)count:(NSButton *)sender
{
    NSUInteger len = [self.textField.stringValue length];
    NSString *string = [NSString stringWithFormat:@"'%@' has %lu characters.",
                        self.textField.stringValue, len];
    
    [self.resultTextField setStringValue:string];
}

- (void)awakeFromNib
{
    self.resultTextField.stringValue = @"";
}

@end
