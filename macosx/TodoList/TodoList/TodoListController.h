//
//  TodoListController.h
//  TodoList
//
//  Created by zouivex on 2014/7/6.
//  Copyright (c) 2014年 zouxu. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface TodoListController : NSObject<NSTableViewDataSource>

@property (strong) NSMutableArray *items;
@property (weak) IBOutlet NSTableView *toDoTableView;

@property (weak) IBOutlet NSTextField *inputTextField;
- (IBAction)createNewItem:(id)sender;

@end
