//
//  MyView.m
//  QuartzBook
//
//  Created by Mapedd on 11-04-19.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "MyView.h"
#import "Drawings.h"


@implementation MyView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
    }
    return self;
}


// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
    NSGraphicsContext *currentContext = [NSGraphicsContext currentContext];
    CGContextRef context = (CGContextRef)[currentContext graphicsPort]; 

    
    doGrayRamp(context);

    
    
}

void drawSampleJPEGImage(CGContextRef ctx){
    NSBundle *mainBundle = [NSBundle mainBundle];
    
    NSString *path = [mainBundle pathForImageResource:@"skiing.jpg"];
    
    CFURLRef url = NULL;
    
    url =  (CFURLRef) [[NSURL alloc] initFileURLWithPath:path];
    
    if (url == NULL) {
        fprintf(stderr, "Couldn't create CFURLRef for JPEG data !\n");
        return;
    }
    
    drawJPEGImage(ctx, url);
}



- (void)dealloc
{
    [super dealloc];
}

@end
