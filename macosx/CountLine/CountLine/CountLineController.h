//
//  CountLineController.h
//  CountLine
//
//  Created by zouivex on 2014/7/5.
//  Copyright (c) 2014年 zouxu. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface CountLineController : NSObject
@property (weak) IBOutlet NSTextField *textField;
@property (weak) IBOutlet NSTextField *resultTextField;

- (IBAction)count:(NSButton *)sender;
@end
