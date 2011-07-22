//
//  Drawings.c
//  QuartzBook
//
//  Created by Mapedd on 11-04-19.
//  Copyright 2011 MapApp. All rights reserved.
//

#include "Drawings.h"

static inline CGFloat DEGREES_TO_RADIANS(CGFloat degrees){
    return degrees*M_PI/180;
}

void doAlphaRects(CGContextRef context){
    CGRect ourRect = {{0.0,0.0}, {130.0, 100.0}};
    int i, numRects = 6;
    float rotateAngle = 2*M_PI/numRects;
    float tint, tintAdjust = 1.0/numRects;
    
    
    CGContextTranslateCTM(context, 2*ourRect.size.width, 2*ourRect.size.height);
    
    for(i=0,tint=1.0;i<numRects;i++,tint-=tintAdjust){
        CGContextSetRGBFillColor(context, tint, 0.0, 0.0,tint);
        CGContextFillRect(context, ourRect);
        CGContextRotateCTM(context, rotateAngle); //cumulative;
    }
}

void drawCoordinateAxies(CGContextRef context){
    CGContextSetLineWidth(context, 2.0);
    
    //Draw the coordinate axes
    CGContextBeginPath(context);
    //First draw the x axis
    CGContextMoveToPoint(context, -2000., 0.0);
    CGContextAddLineToPoint(context, 2000., 0.0);
    CGContextDrawPath(context, kCGPathStroke);
    //Next draw the y axis
    CGContextMoveToPoint(context, 0.0, -2000.);
    CGContextAddLineToPoint(context, 0.0, 2000.);
    CGContextDrawPath(context, kCGPathStroke);
}

void drawSkewedRectangles(CGContextRef context){
    
    CGContextTranslateCTM(context, 100., 0.);
    CGRect ourRect = {{0.,0.},{72.,72.}};
    
    // Draw the coordinate axis with no rotation
    drawCoordinateAxies(context);
    
    // *** Rectangle 1 *** 
    CGContextFillRect(context,ourRect);
    
    // Make a snapshot of the CTM and other drawing parameters
    CGContextSaveGState(context);
    
        //Rotate the CTM by 30 degrees
        CGContextRotateCTM(context, M_PI/6);
        // Scale in x by 0.5, and in y by 2.0
        CGContextScaleCTM(context, 0.5, 2.0);
        CGContextSetRGBStrokeColor(context, 0.69, 0.486,0.722,1.0);
        CGContextSetRGBFillColor(context, 0.69, 0.486,0.722,0.7);
        drawCoordinateAxies(context);
        CGContextFillRect(context, ourRect);
    //Restore the snapshot of the CTM and other drawing parameters
    CGContextRestoreGState(context);
    
    // Now the coordinate system is that before any transformations
    // were aplied  and the fill and stroke colors are also   restored
    
    // Translate  to the right side of the drawing
    CGContextTranslateCTM(context, 288.0, 0.);
    drawCoordinateAxies(context);
    
    CGContextFillRect(context, ourRect);
    CGContextSaveGState(context);
    
        //This time perform scale before rotating
        CGContextScaleCTM(context, 0.5, 2.0);
        CGContextRotateCTM(context, M_PI/6);
        CGContextSetRGBStrokeColor(context, 0.965, 0.584, 0.059, 1.0);
        CGContextSetRGBFillColor(context, 0.965, 0.584, 0.059, 0.7);
        drawCoordinateAxies(context);
        CGContextFillRect(context, ourRect);
    
    CGContextRestoreGState(context);
}

void drawRotartedAndScaledRectangle(CGContextRef context){
    CGRect ourRect = {{0., 0.},{72.,72.}};
    // Draw the unrotated coordinate axes
    drawCoordinateAxies(context);
    // Fill the unscaled rectangle
    CGContextFillRect(context, ourRect);
    
    // Make a snapshot of the CTM and other drawing parameters
    CGContextSaveGState(context);
    
        // Rotate the coordinate system by 30 degrees
        CGContextRotateCTM(context, M_PI/6);
        // Scale the coordinate system by 0.5 in x and 2.0 in y
        CGContextScaleCTM(context,0.5, 2.0);
        CGContextSetRGBStrokeColor(context, 0.69, 0.486, 0.722, 1.0);
        CGContextSetRGBFillColor(context, 0.69, 0.486, 0.722, .7);
        // Draw coordinate after the transformation
        drawCoordinateAxies(context);
        // Fill the rotated and scaled rectangle
        CGContextFillRect(context, ourRect);
    
    // Restore the snapshot if the CTM and other drawing parameters
    CGContextRestoreGState(context);
    
    // Now the coordinate system is that before any transformations
    // were applied and fill and stroke color are also restored
    
    // Translate to the right for the right side of the drawing
    CGContextTranslateCTM(context, 288.0, 0.);
    drawCoordinateAxies(context);
    
    CGContextFillRect(context, ourRect);
    CGContextSaveGState(context);
    
        //This time perfrom scaling before rotating
        CGContextScaleCTM(context, 0.5, 2.0);
        CGContextRotateCTM(context, M_PI/6);
        CGContextSetRGBStrokeColor(context, 0.965, 0.584, 0.059, 1.0);
        CGContextSetRGBFillColor(context, 0.965, 0.584, 0.059, 0.7);
        drawCoordinateAxies(context);
        CGContextFillRect(context, ourRect);
    
    CGContextRestoreGState(context);
    
}

void drawElipse(CGContextRef context){
    CGAffineTransform theTransform = CGAffineTransformMakeScale(2., 1.);
    CGContextTranslateCTM(context, 100., 100.);
    CGContextConcatCTM(context, theTransform);
    CGContextBeginPath(context);
    CGContextAddArc(context, 0., 0., 45., 0., 2*M_PI, 0);
    CGContextDrawPath(context, kCGPathFill);
    
}

void drawRotatedEllipses(CGContextRef context){
    int i, totreps = 144;
    
    float tint = 1., tintIncrement =1./totreps;
    // Create a new tranform consisting of a 45-degree rotation
    CGAffineTransform theTransform = CGAffineTransformMakeRotation(M_PI/4);
    // Apply the scape to the transform just created
    theTransform = CGAffineTransformScale(theTransform, 1., 2.);
    // Place the first elliplse at a good location
    CGContextTranslateCTM(context, 100., 100.);
    
    for(i=0;i<totreps;i++){
        
        // Make a snapshot of the coordinate system
        CGContextSaveGState(context);
        // Set up the coordinate system  for the rotated ellipse
        CGContextConcatCTM(context, theTransform);
        CGContextBeginPath(context);
        CGContextAddArc(context, 0., 0., 45., 0., M_PI*2, 0);
        // Set the fill color for this instance of the ellipse
        CGContextSetRGBFillColor(context, tint, 0., 0., 1.);
        CGContextDrawPath(context, kCGPathFill);
        // Restore the coordinate system to that of the snapshot
        CGContextRestoreGState(context);
        // Compute the next tint color
        tint -= tintIncrement;
        CGContextTranslateCTM(context, 1., 0.);        
        
    }
    
}

void doRotatedEllipsesWithCGPath(CGContextRef context){
    int i, totReps = 144;
    
    CGMutablePathRef path = NULL;
    
    float tint = 1., tintIncrement = 1./totReps;
    
    // Create a new transform consisting of a 45-degree rotation
    CGAffineTransform theTransform = CGAffineTransformMakeRotation(M_PI/4);
    // Apply the scaling transformation to the transform just created.
    theTransform = CGAffineTransformScale(theTransform, 1., 2.);
    // Create a mutable CGPath object
    path = CGPathCreateMutable();
    
    if (!path) {
        fprintf(stderr, "Couldn't create path!\n");
        return;
    }
    
    // Add a circular arc  to the CGPath object, transformed
    // by an affine transform
    CGPathAddArc(path, &theTransform, 0., 0., 45., 0., M_PI*2, false);
    // Close the CGPath object
    CGPathCloseSubpath(path);
    
    // Place the first ellipse at good location
    CGContextTranslateCTM(context, 100., 100.);
    for (i=0; i<totReps; i++) {
        CGContextBeginPath(context);
        // Add the CGPath object to the current path in the context
        CGContextAddPath(context, path);
        // Set the fill color for this instance of the ellipse
        CGContextSetRGBFillColor(context, tint, 0., 0., 1.);
        CGContextFillPath(context);
        // Compute the next tint color
        tint -= tintIncrement;
        // Move over to the next ellipse
        CGContextTranslateCTM(context, 1., 0.);
    }
    // Release the path when done with it
    CGPathRelease(path);
}

void drawScewedCoordinateSystem(CGContextRef context){
    // alpha is 22.5 degres and beta is 15 degrees
    float alpha = M_PI/8, beta = M_PI/12;
    CGAffineTransform skew;
    // Create the rectangle that is 72 unit on a side
    // with its origin at (0,0)
    CGRect r = CGRectMake(0., 0., 72., 72.);
    
    CGContextTranslateCTM(context, 144., 144.);
    // Draw the coordinates axes untransformed
    drawCoordinateAxies(context);
    // Fill the rectangle
    CGContextFillRect(context, r);
    
    // Create an affine transform that skews the coordinate system
    skew = CGAffineTransformMake(1., tanf(alpha), tanf(beta), 1., 0., 0.);
    // Apply the transform to the context coordinate system
    CGContextConcatCTM(context, skew);
    
    
    // Set the fill and stroke color to dark blue
    CGContextSetRGBFillColor(context, 0.11, 0.208, 0.451, 1.0);
    CGContextSetRGBStrokeColor(context, 0.11, 0.208, 0.451, 1.);
    
    // Draw the coordinate axes again, now transformed
    drawCoordinateAxies(context);
    // Set the fill color again, but with partially transparent alpha
    CGContextSetRGBFillColor(context, 0.11, 0.208, 0.451, 0.7);
    // Fill the rectangle in the transformed coordinate system
    CGContextFillRect(context, r);
    
}

void doStrokeWithCTM(CGContextRef context){
    CGContextTranslateCTM(context, 150., 180.);
    CGContextSetLineWidth(context, 10.);
    //Draw ellipse 1 with a uniform stroke
    CGContextSaveGState(context);
    //Scale the CTOM so that the curular arc will be elliptical
    CGContextScaleCTM(context, 2., 1.);
    CGContextBeginPath(context);
    //Create an arc that is circle
    CGContextAddArc(context, 0., 0., 45., 0, 2*M_PI, 0);
    // Restore the context parameters prior to stroking the path
    // CGContextRestoreGState does not affect path in the context
    CGContextRestoreGState(context);
    CGContextStrokePath(context);
    
    CGContextTranslateCTM(context, 220., 0.);
    // Draw ellipse 2 with nonuniform stroke
    CGContextSaveGState(context);
    //Scale the CTM so that the curcular arc will be elliptical
    CGContextScaleCTM(context, 2., 1.);
    CGContextBeginPath(context);
    // Create the arc that is a circle
    CGContextAddArc(context, 0., 0., 45., 0, 2*M_PI, 0);
    // Stroke the path with the scaled coordinate system in effect
    CGContextStrokePath(context);
    CGContextRestoreGState(context);
}

CGMutablePathRef createRoundedRectForRect(CGRect rect, CGFloat radius) {
    
    CGMutablePathRef path = CGPathCreateMutable();
    CGPathMoveToPoint(path, NULL, CGRectGetMidX(rect), CGRectGetMinY(rect));
    CGPathAddArcToPoint(path, NULL, CGRectGetMaxX(rect), CGRectGetMinY(rect), 
                        CGRectGetMaxX(rect), CGRectGetMaxY(rect), radius);
    CGPathAddArcToPoint(path, NULL, CGRectGetMaxX(rect), CGRectGetMaxY(rect), 
                        CGRectGetMinX(rect), CGRectGetMaxY(rect), radius);
    CGPathAddArcToPoint(path, NULL, CGRectGetMinX(rect), CGRectGetMaxY(rect), 
                        CGRectGetMinX(rect), CGRectGetMinY(rect), radius);
    CGPathAddArcToPoint(path, NULL, CGRectGetMinX(rect), CGRectGetMinY(rect), 
                        CGRectGetMaxX(rect), CGRectGetMinY(rect), radius);
    CGPathCloseSubpath(path);
    
    return path;        
}

void drawEgg(CGContextRef context){
    CGPoint p0 = {0.,0.}, p1 = {0.,200.};
    CGPoint c1 = {140.,5.}, c2 = {80.,198.};
    CGContextTranslateCTM(context, 100., 5.);
    CGContextBeginPath(context);
    
    CGContextMoveToPoint(context, p0.x, p0.y);
    // Create the Bezier path segment for the right side of the egg
    CGContextAddCurveToPoint(context, c1.x, c1.y, c2.x, c2.y, p1.x, p1.y);
    // Create the Bezier path segment for the left side of the egg
    CGContextAddCurveToPoint(context, -c2.x, c2.y, -c1.x, c1.y, p0.x, p0.y);
    CGContextClosePath(context);
    CGContextSetLineWidth(context, 2.);
    CGContextDrawPath(context, kCGPathStroke);
    
}

void addRoundedRectToPath(CGContextRef context, CGRect rect, CGFloat ovalWidth, CGFloat ovalHeight){
    
    CGFloat fw, fh;
    
    // If either ovalWidth or ovalHeight is 0, add aregular rectangle
    if(ovalWidth == 0. || ovalHeight == 0.){
        CGContextAddRect(context, rect);
    }
    else{
        CGContextSaveGState(context);
        // Translate to the lower-left corner of the rectangle
        CGContextTranslateCTM(context, CGRectGetMinX(rect), CGRectGetMinY(rect));
        // Scale the oval width so that 
        // each rounded corner is 0.5 in radius
        CGContextScaleCTM(context, ovalWidth, ovalHeight);
        // Unscale the rectangle width by the amount of x scalling
        fw = CGRectGetWidth(rect)/ovalWidth;
        // Unscale the rectangle height by the amount of y scalling
        fh = CGRectGetHeight(rect)/ovalHeight;
        // Start the right edge of the rectangle , at the midpoint in Y
        CGContextMoveToPoint(context, fw, fh/2);
        // **** Segment 1 **** //
        CGContextAddArcToPoint(context, fw, fh, fw/2, fh, 0.5);
        // **** Segment 2 **** //
        CGContextAddArcToPoint(context, 0., fh, 0., fh/2, 0.5);
        // **** Segment 3 **** //
        CGContextAddArcToPoint(context, 0., 0., fw/2, 0., 0.5);
        // **** Segment 4 **** //
        CGContextAddArcToPoint(context, fw, 0, fw, fh/2, 0.5);
        // Closing the path adds the last segment
        CGContextClosePath(context);
        CGContextRestoreGState(context);
    }
}

void doRoundedRects(CGContextRef context){
    CGRect rect = CGRectMake(10.,10.,210.,200.);
    CGFloat ovalWidth = 100., ovalHeight  = 150.;
    CGContextSetLineWidth(context, 2.);
    CGContextBeginPath(context);
    addRoundedRectToPath(context, rect, ovalWidth, ovalHeight);
    CGContextSetRGBStrokeColor(context, 1.0, 0., 0., 1.);
    CGContextDrawPath(context,kCGPathStroke);
    
}

void myCGContextAddEllipseInRect(CGContextRef context, CGRect rect){
    // If the Quartz built-in function is defined, use it
    // otherwise user emulation
//    if(&CGContextAddEllipseInRect(context, rect) != NULL){
//        CGContextAddEllipseInRect(context, rect);
//    }
//    else{
        CGContextSaveGState(context);
        // Translate to the center of the ellipse
        CGContextTranslateCTM(context, CGRectGetMidX(rect), CGRectGetMidY(rect));
        // Scale by half the width and half the height
        CGContextScaleCTM(context, CGRectGetWidth(rect)/2, CGRectGetHeight(rect)/2);
        // Establish the current point athe first point
        // of the ellipse
        CGContextMoveToPoint(context, 1.0, 0.0);
        // Add a circular arc around the ellipse center
        CGContextAddArc(context, 0., 0., 1., 0., M_PI*2, 1);
        CGContextRestoreGState(context);
//quick    }
}

CGMutablePathRef createScroll(CGRect rect) {
    
    CGMutablePathRef path = CGPathCreateMutable();
    
    if(CGRectGetMaxX(rect) >= CGRectGetMaxY(rect)){
        CGPathAddEllipseInRect(path, NULL, CGRectMake(CGRectGetMinX(rect), CGRectGetMinY(rect), CGRectGetMaxX(rect), CGRectGetMaxX(rect)));
        return path;
    }
    
    
    CGPathMoveToPoint(path, NULL, CGRectGetMidX(rect), CGRectGetMinY(rect));
    CGPathAddArcToPoint(path, NULL, CGRectGetMaxX(rect), CGRectGetMinY(rect), CGRectGetMaxX(rect), CGRectGetMaxX(rect)/2, CGRectGetMaxX(rect)/2);
    CGPathAddLineToPoint(path, NULL, CGRectGetMaxX(rect), CGRectGetMaxY(rect)-CGRectGetMaxX(rect)/2);
    CGPathAddArcToPoint(path, NULL, CGRectGetMaxX(rect), CGRectGetMaxY(rect), CGRectGetMidX(rect), CGRectGetMaxY(rect), CGRectGetMaxX(rect)/2);
    CGPathAddArcToPoint(path, NULL, CGRectGetMinX(rect), CGRectGetMaxY(rect), CGRectGetMinX(rect), CGRectGetMaxX(rect)- CGRectGetMaxX(rect)/2, CGRectGetMaxX(rect)/2);
    CGPathAddLineToPoint(path, NULL, CGRectGetMinX(rect), CGRectGetMinY(rect)+ CGRectGetMaxX(rect)/2);
    CGPathAddArcToPoint(path, NULL, CGRectGetMinX(rect), CGRectGetMinY(rect), CGRectGetMidX(rect), CGRectGetMinY(rect), CGRectGetMaxX(rect)/2);
    
    return path;        
}

CGMutablePathRef createTriangle(CGRect rect) {
    
    CGMutablePathRef path = CGPathCreateMutable();
    CGPathMoveToPoint(path, NULL, CGRectGetMidX(rect), CGRectGetMinY(rect));
    CGPathAddLineToPoint(path, NULL, CGRectGetMaxX(rect), CGRectGetMaxY(rect));
    CGPathAddLineToPoint(path, NULL, CGRectGetMinX(rect), CGRectGetMaxY(rect));
    CGPathCloseSubpath(path);
    return path;        
}

//6.6

static CGPoint alignPointToUserSpace(CGContextRef context, CGPoint point){
    // Compute the coordinates of the point in the device space
    point = CGContextConvertPointToDeviceSpace(context, point);
    // Ensure that coordinates are exactly at the corner of the device pixel.
    point.x = floor(point.x);
    point.y = floor(point.y);
    
    // Convert the device aligned coordinate bach to user space.
    return CGContextConvertPointToUserSpace(context, point);
}

static CGSize alignSizeToUserSpace(CGContextRef context, CGSize size){
    // Compute the size in device space
    size = CGContextConvertSizeToDeviceSpace(context, size);
    // Ensure that size is an integer multiple of device pixels
    size.width = floor(size.width);
    size.height = floor(size.height);
    // Convert back to user space
    return CGContextConvertSizeToUserSpace(context, size);
}

static CGRect alignRectToUserSpace(CGContextRef context, CGRect rect){
    // Compute the coordinates of the rectangle in the device space.
    rect = CGContextConvertRectToDeviceSpace(context, rect);
    // Ensure that the x and y coordinates are at a pixel corner.
    rect.origin.x=  floor(rect.origin.x);
    rect.origin.y=  floor(rect.origin.y);
    // Ensure that width and height are an integer  number of device pixels
    rect.size.width = floor(rect.size.width);
    rect.size.height = floor(rect.size.height);
    
    //Convert back to the user space
    return CGContextConvertRectToUserSpace(context, rect);
}

void doPixelAlignedFillAndStroke(CGContextRef context){
    CGPoint p1 = CGPointMake(16.7, 17.8);
    CGPoint p2 = CGPointMake(116.7, 17.8);
    CGRect r = CGRectMake(16.7, 20.8, 100.6, 100.6);
    CGSize s;
    
    CGContextSetLineWidth(context, 2.);
    CGContextSetRGBFillColor(context, 1., 0., 0., 1.);
    CGContextSetRGBStrokeColor(context, 1., 0., 0., 1.);
    
    // ***** Unaligned Drawing *****//
    CGContextBeginPath(context);
    CGContextMoveToPoint(context, p1.x, p1.y);
    CGContextAddLineToPoint(context, p2.x, p2.y);
    CGContextStrokePath(context);
    CGContextFillRect(context, r);
    
    // Translate to the right before drawing along aligned coordinates
    CGContextTranslateCTM(context, 115.0, 0.0);
    
    
    // ***** Aligned Drawing *****//
    // Compute the length of the line in user space
    s = CGSizeMake(p2.x-p1.x, p2.y-p1.y);
    
    CGContextBeginPath(context);
    // Align the starting point to the device pixel boundary
    p1 = alignPointToUserSpace(context, p1);
    // Establish the starting point of the line 
    CGContextMoveToPoint(context, p1.x, p1.y);
    // Compute the line length as an integer number of device pixels
    s = alignSizeToUserSpace(context, s);
    CGContextAddLineToPoint(context, p1.x+s.width, p1.y+s.height);
    CGContextStrokePath(context);
    // Compute the rect that is aligned to device space with a width that is an integer number of device pixels
    r = alignRectToUserSpace(context, r);
    CGContextFillRect(context, r);
}

//7.1
CGColorSpaceRef getTheRGBColorSpace(void){
    static CGColorSpaceRef deviceRGB = NULL;
    
    //Set once, the first time this function is called.
    if (deviceRGB == NULL) {
        deviceRGB = CGColorSpaceCreateDeviceRGB();
    }
    
    return deviceRGB;
}

void doColorSpaceFillAndStroke(CGContextRef context){
    CGColorSpaceRef theColorSpace = getTheRGBColorSpace();
    CGFloat opaqueRed[4] = {0.662, 0.0, 0.031,1.0};    // ref, green, blue, alpha
    CGFloat  aBlue[4] = {0.482,0.62,0.871,1.0};         // ref, green, blue, alpha
    
    // Set the fill color space to be the device RGB color space
    CGContextSetFillColorSpace(context, theColorSpace);
    // Set the fill color to opaque red. The number of elements in the 
    // array is passed to this function must be a number of color
    // components in the current fill color space plus one for alpha
    CGContextSetFillColor(context, opaqueRed);
    
    // Set the stroke color space to be the device RGB color space.
    CGContextSetStrokeColorSpace(context, theColorSpace);
    // Set the stroke color to opaque red. The number of elements in the 
    // array is passed to this function must be a number of color
    // components in the current fill color space plus one for alpha
    CGContextSetStrokeColor(context, aBlue);
    
    CGContextSetLineWidth(context, 8.);
    // Rectangle 1
    CGContextBeginPath(context);
    CGRect rect = CGRectMake(20., 20., 100., 100.);
    CGContextAddRect(context,rect);
    CGContextDrawPath(context, kCGPathFillStroke);
    
    // Continue to use the stroke color space already set 
    // but change the stroke alpha value to a semitransparent blue.
    aBlue[3] = 0.5;
    CGContextSetStrokeColor(context, aBlue);
    // Rectangle 2
    CGContextBeginPath(context);
    rect.origin.x = 140.;
    CGContextAddRect(context, rect);
    CGContextDrawPath(context, kCGPathFillStroke);
    
    // Don't release the color since this routine
    // didn't create it.
    
}

//7.2
void drawWithColorRefs(CGContextRef context){
    static CGColorRef opaqueRedColor  = NULL, opaqueBlueColor = NULL, transparentBlueColor = NULL;
    
    // initialize the CGColorRefs if necessary
    if (opaqueRedColor == NULL) {
        // Initialize the color arrya to an opaque red
        // in a RGB color space
        CGFloat color[4] = {0.662, 0.0, 0.031,1.0};
        CGColorSpaceRef colorSpace = getTheRGBColorSpace();
        // Create a CGColorRf for opaque red.
        opaqueRedColor = CGColorCreate(colorSpace, color);
        // Make the color array correspond to an opaque blue color.
        color[0] = 0.482; color[1] = 0.62; color[2] = 0.871;
        // Create another CGColorRef for opaque blue
        opaqueBlueColor = CGColorCreate(colorSpace, color);
        // Create a new CGColorRef form opaque blue but wuth different alpha value
        transparentBlueColor = CGColorCreateCopyWithAlpha(opaqueBlueColor, 0.5);
        
        if (!(opaqueRedColor && opaqueBlueColor && transparentBlueColor)) {
            fprintf(stderr, "could't create one the CGColorRefs ! \n");
            return;
        }
    }
    
    // Set the fill color to the opaque red CGColorRef object.
    CGContextSetFillColorWithColor(context, opaqueRedColor);
    // Set the stroke color to the opaque blue CGColorRef object
    CGContextSetStrokeColorWithColor(context, opaqueBlueColor);
    
    CGContextSetLineWidth(context, 8.);
    // Rectangle 1
    CGContextBeginPath(context);
    CGRect rect = CGRectMake(20., 20., 100., 100.);
    CGContextAddRect(context,rect);
    CGContextDrawPath(context, kCGPathFillStroke);
    
    // Continue to use the stroke color space already set 
    // but change the stroke alpha value to a semitransparent blue.
    CGContextSetStrokeColorWithColor(context, transparentBlueColor);
    // Rectangle 2
    CGContextBeginPath(context);
    rect.origin.x = 140.;
    CGContextAddRect(context, rect);
    CGContextDrawPath(context, kCGPathFillStroke);
    
    // Don't release the color since this routine
    // didn't create it.
}


//7.3
CGColorSpaceRef getTheGenericRGBColorSpace(void){
    static CGColorSpaceRef genericRGBColorSpace = NULL;
    if (genericRGBColorSpace == NULL) {
        CMProfileRef genericRGBProfile = NULL;
        OSStatus err= noErr;
        CMProfileLocation loc;
        // Build up a profile location for ColorSync
        loc.locType = cmPathBasedProfile;
        strcpy(loc.u.pathLoc.path, kGenericRGBProfilePathStr);
        // Open the profile with ColorSync
        err = CMOpenProfile(&genericRGBProfile, &loc);
        if (err == noErr) {
            genericRGBColorSpace = CGColorSpaceCreateWithPlatformColorSpace(genericRGBProfile);
            if (genericRGBColorSpace == NULL)
                fprintf(stderr, "Couldn't create the generic RGB color space'n");
                // This code opened the profile so it is up to it to close it.
            CMCloseProfile(genericRGBProfile);
        }
        else{
            // ColorSync couldn't open the profile so log a message to the console
            fprintf(stderr, "Couldn't open generic profile due to error %d'n", (int)err);
        }
    }
    return genericRGBColorSpace;
}

//7.5
CGColorSpaceRef updatedGetTheRGBColorSpace(void){
    static CGColorSpaceRef genericRGBColorSpace = NULL;
    
    if (genericRGBColorSpace == NULL) {
        // Test the symbol kCGColorSpaceGenericRGB to siee if it is available, if so, use it.
        if (&kCGColorSpaceGenericRGB != NULL) {
            genericRGBColorSpace = CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB);
            // If genericRGBColorSpace is still NULL, use the techinque of using ColorSync to open the disk based profile from listing 7.2
            if (genericRGBColorSpace == NULL) {
                genericRGBColorSpace = getTheGenericRGBColorSpace();
            }
        }
    }
    
    return genericRGBColorSpace;
}

//7.6
void drawWithGlobalAlpha(CGContextRef context){
    int i;
    
    CGRect rect = CGRectMake(40., 210., 100., 100.);
    CGFloat color[4] = {1.0,0.0,0.0,1.0}; // opaque red
    // Set the fill color space to the returned by getTheRGBColorSpace
    CGContextSetFillColorSpace(context, getTheRGBColorSpace());
    
    CGContextSetFillColor(context, color);
    
    for (i =0; i<2; i++) {
        CGContextSaveGState(context);
        // Paint the left rectangle on this row with 100% opaque red
        CGContextFillRect(context, rect);
        CGContextTranslateCTM(context, rect.size.width+70., 0.);
        // Set the alpha value of this rgba color to 0.5
        color[3] = 0.5;
        // Use the new color as the fill color in the graphics state
        CGContextSetFillColor(context, color);
        // Paint the center rectangle on this row with 50% opaque red
        CGContextFillRect(context, rect);
        
        CGContextTranslateCTM(context, rect.size.width+70., 0.);
        // Set the alpha value value of this rgba color to 0.25
        color[3] = 0.25;
        // Use the new color as the fill coor in the graphics state.
        CGContextSetFillColor(context, color);
        // Paint the right rectangle in this row with  25% opaque red.
        CGContextFillRect(context, rect);
        CGContextRestoreGState(context);
        
        // After restoring the graphics state, the fill color is set to that prior to calling CGContextSaveGState,
        // that is, opaque red. The coordinate system is also restored.
        // Now set the context global alphha value to 50% opaque
        CGContextSetAlpha(context, 0.5);
        // Translate down for second row of rectangles.
        CGContextTranslateCTM(context, 0., -(rect.size.height+70.));
        // Reset the alpha value of the color array to fully opaque
        color[3] = 1.;
    }
}


//7.7
void drawWithColorBlendMode(CGContextRef context, CFURLRef url){
    // A green color.
    CGFloat green[4] = {0.548, 0.871,0.318,1.0};
    CGRect insetRect, pdfRect;
    
    // Create a CGPDFDocument object from the URL
    CGPDFDocumentRef pdfDoc = CGPDFDocumentCreateWithURL(url);
    
    if (pdfDoc == NULL) {
        fprintf(stderr, "Couldn't create CGPDFDocument from URL!'n");
        return;
    }
    
    
    // Obtain the media box for page 1 of the PDF document.

    //pdfRect =  CGPDFPageGetBoxRect(<#CGPDFPageRef page#>, <#CGPDFBox box#>)
    pdfRect = CGPDFDocumentGetMediaBox(pdfDoc, 1);
    // Set the origin od the reactangle to (0,0)
    pdfRect.origin = CGPointZero;
    
    // Graphic 1 , the left side of the figure
    CGContextTranslateCTM(context, 20., 10+CGRectGetHeight(pdfRect)/2);
    
    // Draw the PDF document
    CGContextDrawPDFDocument(context,pdfRect, pdfDoc, 1);
    
    // Set the fill color spac eto that returned by getTheRGBColorSpace.
    CGContextSetFillColorSpace(context, getTheRGBColorSpace());
    // Set the fill color to green.
    CGContextSetFillColor(context, green);
    
    // Graphic 2, the top- right portion of the figure.
    CGContextTranslateCTM(context, CGRectGetWidth(pdfRect)+10, CGRectGetHeight(pdfRect)/2+10);
    
    // Draw the PDF document again.
    CGContextDrawPDFDocument(context, pdfRect, pdfDoc, 1);
    
    // Make the fill rectangle that si the same size as the PDF document
    // but inset each by 80 units un x and 20 units in y
    insetRect = CGRectInset(pdfRect, 80, 20);
    // Fill the rectangle with green, Becouse the fill color is opaque and blend mode is normal
    // this obscures the drawing underneath.
    CGContextFillRect(context, insetRect);
    
    // Graphic 3, the bottom-right part of the figure
    CGContextTranslateCTM(context, 0, -(10+CGRectGetHeight(pdfRect)));
    
    // Draw the PDF document again
    CGContextDrawPDFDocument(context, pdfRect, pdfDoc, 1);
    
    // Set the blend mode to  kCGBlendModeColor, which will
    // colorize the destination with the subsequent drawing.
    CGContextSetBlendMode(context, kCGBlendModeColor);
    // Draw the rectangle on top of the PDF document.
    CGContextFillRect(context, insetRect);
    
    // Release the CGPDFDocumentRef that the code created.
    CGPDFDocumentRelease(pdfDoc); 
}


//7.9
void createEllipsePath(CGContextRef context, CGPoint center, CGSize ellipseSize){
    CGContextSaveGState(context);
    
    // Translate the coordinate origin to the center point.
    CGContextTranslateCTM(context, center.x, center.y);
    // Scale the coordinate system to half the width and height.
    CGContextScaleCTM(context, ellipseSize.width/2, ellipseSize.height/2);
    CGContextBeginPath(context);
    // Add a circular arc to the path, centered at the orogin and with radius of 1.0
    // This radius , together with the scaling above fot the width and height, produces ellipse of the correct size
    CGContextAddArc(context, 0., 0., 1.0, 0., 2*M_PI, 0);
    // Close the path so that is suitable for stroking, should that be desired.
    CGContextClosePath(context);
    
    CGContextRestoreGState(context);
}

void doClippedEllipse(CGContextRef context){
    CGPoint theCenterPoint = {120.,120.};
    CGSize theEllipsesSize = {100.,200.,};
    CGFloat dash[1] = {2};
    static CGColorRef opaqueBrownColor = NULL, opaqueOrangeColor = NULL;
    // Initialize the CGColorRefs if necessary.
    if (opaqueBrownColor == NULL) {
        // The  initial value of the color array is an opaque brown in an RGB color space
        CGFloat color[4] = {0.325,0.208,0.157,1.};
        CGColorSpaceRef theColorSpace  = getTheRGBColorSpace();
        // Create a CGColorRef for opaque brown.
        opaqueBrownColor = CGColorCreate(theColorSpace, color);
        // Make a color array correspond to an opaque orange color.
        color[0] = 0.965; color[1] = 0.584; color[2] = 0.059;
        // Create another CGColorRef for opaque orange.
        opaqueOrangeColor = CGColorCreate(theColorSpace, color);
    }
    
    // Draw two ellipses centered about the same point, one rotated 45 degrees from another
    CGContextSaveGState(context);
        // *** Ellipse 1 *** //
        createEllipsePath(context, theCenterPoint, theEllipsesSize);
        CGContextSetFillColorWithColor(context, opaqueBrownColor);
        CGContextFillPath(context);
        // Translate and rotate about the center point of the ellipse
        CGContextTranslateCTM(context, theCenterPoint.x, theCenterPoint.y);
        // Rotate by 45 degrees
        CGContextRotateCTM(context, DEGREES_TO_RADIANS(45.0f));
        // CGPointZero is a predefined Quartz point corresponding to coordinate (0,0).
        // *** Ellipse 2 *** //
        createEllipsePath(context, CGPointZero, theEllipsesSize);
        CGContextSetFillColorWithColor(context, opaqueOrangeColor);
        CGContextFillPath(context);
    CGContextRestoreGState(context);
    
    CGContextTranslateCTM(context, 170., 0.);
    // Now use the first ellipse as a clipping area prior to painting the second ellipse.
    CGContextSaveGState(context);
        // *** Ellipse 3 *** //
        createEllipsePath(context, theCenterPoint, theEllipsesSize);
        CGContextSetStrokeColorWithColor(context, opaqueBrownColor);
        CGContextSetLineDash(context, 0, dash, 1);
        // Stroke the path with a dash.
        CGContextStrokePath(context);
        // *** Ellipse 4 *** //
        createEllipsePath(context, theCenterPoint, theEllipsesSize);
        // Clop to the elliptical path.
        CGContextClip(context);
        CGContextTranslateCTM(context, theCenterPoint.x, theCenterPoint.y);
        // Rotate by 45 degrees.
        CGContextRotateCTM(context, DEGREES_TO_RADIANS(45.0f));
        // *** Ellipse 5 *** //
        createEllipsePath(context, CGPointZero, theEllipsesSize);
        CGContextSetFillColorWithColor(context, opaqueOrangeColor);
        CGContextFillPath(context);
    CGContextRestoreGState(context);
}

// ******************************** //

//8.1
CGDataProviderRef createDataProviderFromPathName(CFStringRef path){
    CFURLRef url;
    // Create a CFURL for the supplied file system path.
    url = CFURLCreateWithFileSystemPath(NULL, path, kCFURLPOSIXPathStyle, false);
    if (url == NULL) {
        fprintf(stderr, "Couldn't create url! \n");
        return NULL;
    }
    // Create a Quartz data provider for the URL.
    CGDataProviderRef dataProvider = CGDataProviderCreateWithURL(url);
    // Release the URL when done with it
    CFRelease(url);
    if (dataProvider == NULL) {
        fprintf(stderr, "Coulnd't create data provider! \n");
        return NULL;
    }
    
    return dataProvider;
}



//8.2
static void rgbReleaseRampData(void *info, const void *data, size_t size){
    free((char *)data);
}

CGDataProviderRef createRGBRampDataProvider(void){
    CGDataProviderRef dataProvider = NULL;
    size_t width = 256, height = 256;
    size_t imageDataSize = width*height*3;
    unsigned char *p;
    unsigned char *dataP = (unsigned char*)malloc(imageDataSize);
    if (dataP == NULL) {
        return NULL;
    }
    p = dataP;
    // Build an image that is RGB 24 bits per sample. This is a ramp where the red component value 
    // increases in red from left to right and green component increases from top to bottom.
    int r,g;
    for (g = 0; g<height; g++) {
        for (r = 0; r<width; r++) {
            *p++ = r; *p++=g; *p++ = 0;
        }
    }
    // Once the data provider is created, the data assiocaited with dataP MUST be available until Quartz calls the data release function 'rgbReleaseRampData'
    dataProvider = CGDataProviderCreateWithData(NULL, dataP, imageDataSize, rgbReleaseRampData);
    return dataProvider;
}

//8.3
static size_t getBytesSequentialAccessDP(void *data, void *buffer, size_t count){
    size_t readSize = 0;
    FILE *fp = ((MyImageDataInfo *)data)->fp;
    // This reads 'count' 1-byte objext and returns the number of objects (i.e. bytes) read.
    readSize = fread(buffer, 1, count, fp);
#if DEBUG
    ((MyImageDataInfo *)data)->totalBytesRead += readSize;
#endif
    return readSize;
}

static void skipBytesSequentialAccessDP(void *data, size_t count){
    int result = fseek(((MyImageDataInfo *)data)->fp, count, SEEK_CUR);
    if (result != 0)
        fprintf(stderr, "Coulnd't seek %zd bytes becouse of : %s!\n",count,strerror(errno));
#if DEBUG
    ((MyImageDataInfo *)data)->skippedBytes += count;
#endif
}

static void rewindSequentialAccessDP(void *data){
    // Rewind the beginning of the data;
    rewind(((MyImageDataInfo *)data)->fp);
#if DEBUG
    ((MyImageDataInfo *)data)->numRewinds++;
#endif
}

static void releaseSequentialAccessDP(void *data){
    if (data) {
        MyImageDataInfo *imageDataInfoP = (MyImageDataInfo *)data;
#if DEBUG
        fprintf(stderr, "read %zd bytes, skipped %zd bytes, rewind called %zd times \n", imageDataInfoP->totalBytesRead, imageDataInfoP->skippedBytes, imageDataInfoP->numRewinds);
#endif
        if (imageDataInfoP->fp != NULL)
            fclose(imageDataInfoP->fp);
        free(imageDataInfoP);
    }
}

CGDataProviderRef createSequentialAccessDPForURL(CFURLRef url){
    MyImageDataInfo *imageDataInfoP = NULL;
    CGDataProviderRef provider = NULL;
    FILE *fp = NULL;
    
    CGDataProviderCallbacks callbacks;
//    CGDataProviderSequentialCallbacks callbacks;
    char pathString[PATH_MAX+1];
    Boolean success = CFURLGetFileSystemRepresentation(url,true, pathString, sizeof(pathString));
    if (!success) {
        fprintf(stderr, "Couldn't get the path name C string!\n");
        return NULL;
    }
    
    fp = fopen(pathString, "r");
    if (fp == NULL) {
        fprintf(stderr, "Couldn't open path to file %s! ", pathString);
        return NULL;
    }
    imageDataInfoP = (MyImageDataInfo *)malloc(sizeof(MyImageDataInfo));
    if (imageDataInfoP == NULL) {
        fprintf(stderr, "Couln't malloc block for info data!\n");
        return NULL;
    }
    
    imageDataInfoP->fp = fp;
    
#if DEBUG
    imageDataInfoP->totalBytesRead = 
    imageDataInfoP->skippedBytes = 
    imageDataInfoP->numRewinds = 0;
#endif
    
    callbacks.getBytes = getBytesSequentialAccessDP;
    callbacks.skipBytes = skipBytesSequentialAccessDP;
    callbacks.rewind = rewindSequentialAccessDP;
    callbacks.releaseProvider = releaseSequentialAccessDP;
        provider = CGDataProviderCreate(imageDataInfoP, &callbacks);
//    provider = CGDataProviderCreateSequential(imageDataInfoP, &callbacks);
    
    if(provider == NULL){
        fprintf(stderr, "Couldn't create data provider!\n");
        // Release the info data and clean up
        releaseSequentialAccessDP(imageDataInfoP);
        return NULL;
    }
    return provider;
    
    
    
}
