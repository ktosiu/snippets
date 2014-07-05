//
//  RandomController.h
//  Random
//
//  Created by zouivex on 2014/7/5.
//  Copyright (c) 2014年 zouxu. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface RandomController : NSObject
{
    IBOutlet NSTextField *textField;
}

- (IBAction)seed:(id)sender;
- (IBAction)generate:(id)sender;

@end
