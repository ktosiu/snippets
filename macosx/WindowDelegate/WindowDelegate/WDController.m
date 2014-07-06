//
//  WDController.m
//  WindowDelegate
//
//  Created by zouivex on 2014/7/6.
//  Copyright (c) 2014年 zouxu. All rights reserved.
//

#import "WDController.h"

@implementation WDController

- (NSSize)windowWillResize:(NSWindow *)sender
                    toSize:(NSSize)frameSize
{
    NSSize size = frameSize;
    size.height = 2 * size.width;
    return size;
}

@end
