//
//  CarArrayController.m
//  CarLot
//
//  Created by zouivex on 2014/7/7.
//  Copyright (c) 2014年 zouxu. All rights reserved.
//

#import "CarArrayController.h"

@implementation CarArrayController

- (id)newObject
{
    id newObj = [super newObject];
    NSDate *now = [NSDate date];
    [newObj setValue:now forKey:@"datePurchased"];
    return newObj;
}

@end
