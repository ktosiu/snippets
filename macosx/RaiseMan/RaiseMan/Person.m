//
//  Person.m
//  RaiseMan
//
//  Created by zouivex on 2014/7/6.
//  Copyright (c) 2014年 zouxu. All rights reserved.
//

#import "Person.h"

@implementation Person

- (instancetype)init
{
    self = [super init];
    if (self) {
        _expectedRaise = 0.05;
        _personName = @"New Person";
    }
    return self;
}

- (void)setNilValueForKey:(NSString *)key
{
    if([key isEqual:@"expectedRaise"])
    {
        [self setExpectedRaise:0.0];
    }
    else
    {
        [super setNilValueForKey:key];
    }
}

@end
