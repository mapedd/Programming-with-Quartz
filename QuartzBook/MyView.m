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

    doClippedEllipse(context);
}




- (void)dealloc
{
    [super dealloc];
}

@end
