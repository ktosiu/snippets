//
//  xweiqiAppDelegate.h
//  xweiqi
//
//  Created by zouivex on 2014/7/8.
//  Copyright (c) 2014年 zouxu. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface xweiqiAppDelegate : NSObject <NSApplicationDelegate>

@property (assign) IBOutlet NSWindow *window;

@property (readonly, strong, nonatomic) NSPersistentStoreCoordinator *persistentStoreCoordinator;
@property (readonly, strong, nonatomic) NSManagedObjectModel *managedObjectModel;
@property (readonly, strong, nonatomic) NSManagedObjectContext *managedObjectContext;

- (IBAction)saveAction:(id)sender;

@end
