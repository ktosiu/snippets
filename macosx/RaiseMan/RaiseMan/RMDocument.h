//
//  RMDocument.h
//  RaiseMan
//
//  Created by zouivex on 2014/7/6.
//  Copyright (c) 2014年 zouxu. All rights reserved.
//

#import <Cocoa/Cocoa.h>
@class Person;

@interface RMDocument : NSDocument

@property (readwrite) NSMutableArray *employees;

- (void)insertObject:(Person *)p inEmployeesAtIndex:(NSUInteger)index;
- (void)removeObjectFromEmployeesAtIndex:(NSUInteger)index;

@end
