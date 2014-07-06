//
//  TodoListController.m
//  TodoList
//
//  Created by zouivex on 2014/7/6.
//  Copyright (c) 2014年 zouxu. All rights reserved.
//

#import "TodoListController.h"

@implementation TodoListController

- init
{
    if(self)
    {
        _items = [[NSMutableArray alloc]init];
    }
    return self;
}

- (IBAction)createNewItem:(id)sender
{
    NSString *item = _inputTextField.stringValue;
    [_items addObject:item];
    [_toDoTableView reloadData];
}

- (NSInteger)numberOfRowsInTableView:(NSTableView *)tableView
{
    return (NSInteger)[_items count];
}

- (id)tableView:(NSTableView *)tableView
objectValueForTableColumn:(NSTableColumn *)tableColumn
            row:(NSInteger)row
{
    return (NSString*)[_items objectAtIndex:row];
}

@end
