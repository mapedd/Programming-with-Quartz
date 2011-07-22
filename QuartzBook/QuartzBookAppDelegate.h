//
//  QuartzBookAppDelegate.h
//  QuartzBook
//
//  Created by Mapedd on 11-04-19.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface QuartzBookAppDelegate : NSObject <NSApplicationDelegate> {
@private
    NSWindow *window;
}

@property (assign) IBOutlet NSWindow *window;

@end
