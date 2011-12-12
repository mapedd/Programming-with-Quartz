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

//8.4

static size_t getBytesGrayRampDirectAccess(void *info, void *buffer, size_t offset, size_t count){
    unsigned char *p = buffer;
    int i;
    
    // This data provider privides 256 bytes total. If Quartz requests more data than available, return only available data.
    if (offset+count > 256) 
        count = 256-offset;
    for (i=offset; i<(offset+count); i++) {
        *p++=i;
    }
    return count;
}

CGDataProviderRef createGrayRampDirectAccessDP(void){
    CGDataProviderRef provider = NULL;
    CGDataProviderDirectCallbacks callbacks;
    callbacks.getBytesAtPosition = getBytesGrayRampDirectAccess;
    callbacks.getBytePointer = NULL;
    callbacks.releaseBytePointer = NULL;

    provider = CGDataProviderCreateDirect(NULL, 256, &callbacks);
    if (provider == NULL) {
        fprintf(stderr, "couldn't create data provider!\n");
    }
    return provider;
    
}

//8.5

static void myCFDataRelease(void *info, const void *data, size_t size){
    // Only called on systems where CGDataProviderCreateWithCFData is not available
    if (info) {
        CFRelease(info);
    }
}

CGDataProviderRef myCGDataProviderCreateWithCFData(CFDataRef data){
    CGDataProviderRef provider = NULL;
    // If the CFData object passed in is NULL, this code returns a NULL data provider.
    if (data == NULL) {
        return NULL;
    }
    
    // Test to see if the Quartz version is available and if so, use it.
    if (&CGDataProviderCreateWithCFData != NULL) {
        return CGDataProviderCreateWithCFData(data);
    }
    
    if (provider == NULL) {
        size_t dataSize = CFDataGetLength(data);
        const UInt8 *dataPtr = CFDataGetBytePtr(data);
        // Retain the data so that this code owns the reference.
        CFRetain(data);
        provider = CGDataProviderCreateWithData((void*)data, dataPtr, dataSize, myCFDataRelease);
        if (provider == NULL) {
            // Release the data if for some reason the data provider couldn't be created.
            CFRelease(data);
        }
    }
}

//8.6

CGDataConsumerRef createDataConsumerFromPathName(CFStringRef path){
    CFURLRef url;
    
    // Create a CFURL for the supplied file system path.
    url = CFURLCreateWithFileSystemPath(NULL, path, kCFURLPOSIXPathStyle, false);
    if (url == NULL) {
        fprintf(stderr, "Couldn't create url !\n");
    }
    
    // Create a Quartz data provider for the URL.
    CGDataConsumerRef dataConsumer = CGDataConsumerCreateWithURL(url);
    // Release the URL when code is done with it.
    CFRelease(url);
    if (dataConsumer == NULL) {
        fprintf(stderr, "Couldn't create data consumer!\n");
        return NULL;
    }
    
    return dataConsumer;
}



//8.7

size_t myCFDataConsumerPutBytes(void *info, const void* buffer, size_t count){
    CFMutableDataRef data = (CFMutableDataRef)info;
    // Append 'count' bytes from 'buffer' to the CFData object 'data'
    CFDataAppendBytes(data, buffer, count);
    return count;
}

void myCFDataConsumerRelease(void *info){
    if (info!=NULL) {
        CFRelease((CFDataRef)info);
    }
}

CGDataConsumerRef myCGDataConsumerCreateWithCFData(CFMutableDataRef data){
    CGDataConsumerRef consumer = NULL;
    // If the CFData object passed in is NULL, this code returns a NULL data consumer
    if (data == NULL) {
        return NULL;
    }
    
    // Test to see if the Quartz version is available
    if (&CGDataConsumerCreateWithCFData != NULL) {
        return CGDataConsumerCreateWithCFData(data);
    }
    
    if (consumer == NULL) {
        CGDataConsumerCallbacks callbacks;
        callbacks.putBytes = myCFDataConsumerPutBytes;
        callbacks.releaseConsumer = myCFDataConsumerRelease;
        
        // Retain the data so that this code owns
        CFRetain(data);
        consumer = CGDataConsumerCreate(data, &callbacks);
        if (consumer == NULL) {
            //Release the data if for some reason the data consumer couldn't be created.
            CFRelease(data);
        }
        
    }
    
    return consumer;
}


//9.1
void drawJPEGImage(CGContextRef ctx, CFURLRef url){
    CGRect jpgRect;
    
    CGImageRef jpgImage = NULL;
    // Create a Quartz data provider for the supplied URL.
    CGDataProviderRef jpgProvider = CGDataProviderCreateWithURL(url);
    if (jpgProvider == NULL) {
        fprintf(stderr, "Couldn't create JPEG Data provider !\n");
        return;
    }
    
    // Create the CGImageRef for the JPEG image from the data provider.
    jpgImage = CGImageCreateWithJPEGDataProvider(jpgProvider,
                                                 NULL,
                                                 true,
                                                 kCGRenderingIntentDefault);
    // CGImageCreateWithJPEGDataProvider retains the data provider.
    // Since this code created the data provider and this code no longer needs it, the code must release it.
    CGDataProviderRelease(jpgProvider);
    if (jpgImage == NULL) {
        fprintf(stderr, "Couldn't create CGImageRef for JPEG data !\n");
        return;
    }
    
    // Make a rectanglethat has it's orogin at (0,0) and has a width and the height
    // that is 1/4 the native width and height of the image
    jpgRect = CGRectMake(0., 0., CGImageGetWidth(jpgImage)/4, CGImageGetHeight(jpgImage)/4);
    
    // Draw the image into the rectangle 
    // This is image 1
    CGContextDrawImage(ctx, jpgRect, jpgImage);
    CGContextSaveGState(ctx);
        // Translate to the top-right corner of the image just drawn.
        CGContextTranslateCTM(ctx, jpgRect.size.width, jpgRect.size.height);
        // Rotate by -90 degrees
        CGContextRotateCTM(ctx, DEGREES_TO_RADIANS(-90.0f));
        // Translate in -x by the width of the drawing.
        CGContextTranslateCTM(ctx, -jpgRect.size.width, 0.);
        // Draw the image into the same rectangle as before.
        // This is image 2
        CGContextDrawImage(ctx, jpgRect, jpgImage);
    CGContextRestoreGState(ctx);
    CGContextSaveGState(ctx);
        // Translate so that the next drawing of the image appears below and to the right of the image just drawn.
        CGContextTranslateCTM(ctx, jpgRect.size.width+jpgRect.size.height, jpgRect.size.height);
        // Scale the y axis by the negative value to flip the image.
        CGContextScaleCTM(ctx, 0.75, -1.0);
        // This is image 3
        CGContextDrawImage(ctx, jpgRect, jpgImage);
    CGContextRestoreGState(ctx);
    
    // Adjust the position of the rectangle so that its origin is 
    // to the right and above where Image 3 was drawn. 
    // Adjust the size of the rectangle so that it is 1/4 the image width and 1/6 the image height
    jpgRect = CGRectMake(1.75*jpgRect.size.width+jpgRect.size.height,
                         jpgRect.size.height, 
                         CGImageGetWidth(jpgImage)/4,
                         CGImageGetHeight(jpgImage)/6);
    // This is image 4
    CGContextDrawImage(ctx, jpgRect, jpgImage);
    
    // Release the CGImageRef when is is no longer needed.
    CGImageRelease(jpgImage);
}



//9.2
void drawImageFromURL(CGContextRef ctx, CFURLRef url, size_t width, size_t height, size_t bitsPerComponent, Boolean isRGB){
    CGImageRef image = NULL;
    CGRect imageRect;
    
    size_t bitsPerPixel = isRGB ? (bitsPerComponent * 3) : bitsPerComponent;
    size_t bytesPerRow = (width *bitsPerPixel +7)/8;
    bool shouldInterpolate = true;
    CGColorSpaceRef colorspace = NULL;
    // Create a Quartz data provider from the supplied URL.
    CGDataProviderRef dataProvider =  CGDataProviderCreateWithURL(url);
    if (dataProvider == NULL) {
        fprintf(stderr, "Couldn't create Image data provider! \n");
        return;
    }
    // Get a Quartz color space object appropriate for the image type.
    // Book version
    // colorspace = isRGB ? getTheCalibreatedRGBColorSpace() : getTheCalibreatedGrayColorSpace();
    // Working version
    colorspace = isRGB ? CGColorSpaceCreateDeviceRGB() : CGColorSpaceCreateDeviceGray();
    
    // Create an image of the width, height, and bitsPerComponent with no alpha data, 
    // the default decode array, with interpolation and the deafult rendering intent for images
    image = CGImageCreate(width,
                          height,
                          bitsPerComponent, 
                          bitsPerPixel,
                          bytesPerRow,
                          colorspace,
                          kCGImageAlphaNone,
                          dataProvider,
                          NULL,
                          shouldInterpolate,
                          kCGRenderingIntentDefault);
    // Quartz reteins the data provider with image and sinse this code does not create any more image with 
    // the data provider, it relases it
    CGDataProviderRelease(dataProvider);
    if (image == NULL) {
        fprintf(stderr, "Couldn't create CGImageRef for this data! \n");
        return;
    }
    // Create a rectangle into which the code will draw the image.
    imageRect = CGRectMake(0., 0., width, height);
    
    // Draw the image into the rectangle.
    CGContextDrawImage(ctx, imageRect, image);
    // Release the CGImage ibject when it is no longer needed.
    CGImageRelease(image);
}


//9.3
void doColorRampImage(CGContextRef ctx){
    CGImageRef image = NULL;
    CGRect imageRect;
    
    size_t width = 256, height = 256;
    size_t bitsPerComponent = 8, bitsPerPixel = 24;
    size_t bytesPerRow = width * 3;
    bool shouldInterpolate = true;
    CGColorSpaceRef colorspace = NULL;
    
    CGDataProviderRef imageDataProvider = createRGBRampDataProvider();
    if (imageDataProvider == NULL) {
        fprintf(stderr, "Couldn't create Image data provider! \n");
        return;
    }
    
    colorspace = getCalibratedRGBColorSpace();
    image = CGImageCreate(width,
                          height,
                          bitsPerComponent,
                          bitsPerPixel,
                          bytesPerRow,
                          colorspace,
                          kCGImageAlphaNone,
                          imageDataProvider,
                          NULL,
                          shouldInterpolate,
                          kCGRenderingIntentDefault);
    // No longer need the data provider
    CGDataProviderRelease(imageDataProvider);
    if (image == NULL) {
        fprintf(stderr, "Couldn't create CGImageRef fot this data! \n");
        return;
    }
    
    imageRect = CGRectMake(0., 0., width, height);
    // Draw the image.
    CGContextDrawImage(ctx, imageRect, image);
    // Release the image
    CGImageRelease(image);
}


CGColorSpaceRef getCalibratedRGBColorSpace(void){
    static CGColorSpaceRef colorspace = NULL;
    
    if (colorspace == NULL) {
        colorspace = CGColorSpaceCreateDeviceRGB();
    }
    
    return colorspace;
}

//9.4
void doGrayRamp(CGContextRef ctx){
    CGImageRef image = NULL;
    CGRect imageRect;
    
    size_t width = 256, height = 1;
    size_t bitsPerComponent = 8, bitsPerPixel = 8;
    size_t bytesPerRow = width;
    bool shouldInterpolate = true;
    CGColorSpaceRef colorspace = NULL;
    CGDataProviderRef dataProvider = NULL;
    
    dataProvider = createGrayRampDirectAccessDP();
    if (dataProvider == NULL) {
        fprintf(stderr, "Couldn't create Gray Ramp provider! \n");
        return;
    }
    colorspace = getCalibratedGrayColorSpace();
    image = CGImageCreate(width,
                          height,
                          bitsPerComponent,
                          bitsPerPixel,
                          bytesPerRow,
                          colorspace,
                          kCGImageAlphaNone,
                          dataProvider,
                          NULL,
                          shouldInterpolate,
                          kCGRenderingIntentDefault);
    CGDataProviderRelease(dataProvider);
    if (image == NULL) {
        fprintf(stderr, "Couldn't create CGImageRef for image data! \n");
        return;
    }
    
    imageRect = CGRectMake(0., 0., 256., 256.);
    // Drawing the image that is 256 samples wide and 1 scanline high 
    // into a rectangle that is 256 x 256 units on a side causes Quartz to stretch the image
    // to fill the destination rectangle
    CGContextDrawImage(ctx, imageRect, image);
    CGImageRelease(image);
}

CGColorSpaceRef getCalibratedGrayColorSpace(void){
    static CGColorSpaceRef graycolorspace = NULL;
    
    if (graycolorspace == NULL) {
        graycolorspace = CGColorSpaceCreateDeviceGray();
    }
    
    return graycolorspace;
}

//9.5
CGImageRef myCreateImageUsingImageSource(CFURLRef url, float* xdpiP, float* ydpiP){
    CGImageRef image = NULL;
    CGImageSourceRef imageSource = NULL;
    CFDictionaryRef properties = NULL;
    CFNumberRef val;
    
    // Set to zero, indicating the property was unavailable.
    *xdpiP = *ydpiP = 0.;
    
    // Create the image source from the URL.
    imageSource = CGImageSourceCreateWithURL(url, NULL);
    if (imageSource == NULL) {
        fprintf(stderr, "Couldn't create image source from URL! \n");
        return NULL;
    }
    
    // Obtain the properties dictionary for the first image in the image source
    // This is a copy function so this code owns the reference returned.
    properties = CGImageSourceCopyPropertiesAtIndex(imageSource, 0, NULL);
    if (properties != NULL) {
        // Check for the x and y resolution of the image.
        val = CFDictionaryGetValue(properties, kCGImagePropertyDPIWidth);
        if (val != NULL) {
            CFNumberGetValue(val, kCFNumberFloatType, xdpiP);
        }

        val = CFDictionaryGetValue(properties, kCGImagePropertyDPIHeight);
        if (val != NULL) {
            CFNumberGetValue(val, kCFNumberFloatType, ydpiP);
        }
        
        CFRelease(properties);
    }
    
    // Create a CGImageRef from the first image in the CGImageSource
    image = CGImageSourceCreateImageAtIndex(imageSource, 0, NULL);
    // Release the CGImageSource object since it is no longer needed and this code created it.
    // This code uses CFRelease since a CGImageSource object is a Core Foundation object.
    CFRelease(imageSource);
    
    if (image == NULL) {
        fprintf(stderr, "Couldn't create image from image source! \n");
        return NULL;
    }
    
    return image;
}

//9.6
CGImageRef myCreateThumbnailFromImageSource(CFURLRef url){
    CGImageRef thumb = NULL;
    CGImageSourceRef imageSource = NULL;
    int maxThumbSize = 160;
    CFNumberRef maxThumbSizeRef;
    CFStringRef keys[2];
    CFTypeRef values[2];
    CFDictionaryRef options = NULL;
    
    // Create the image source from the URL.
    imageSource = CGImageSourceCreateWithURL(url, NULL);
    if (imageSource == NULL) {
        fprintf(stderr, "Couldn't create image source from URL! \n");
        return NULL;
    }
    
    // Specify the maximum size of the thumbnail for 
    // Quartz to create as 160 pixels in width and height.
    maxThumbSizeRef = CFNumberCreate(NULL, kCFNumberIntType, &maxThumbSize);
    
    // Request that Quartz create a thumbnail image if thumbnail data isn't present in the file.
    keys[0] = kCGImageSourceCreateThumbnailFromImageIfAbsent;
    values[0] = (CFTypeRef)kCFBooleanTrue;
    
    // Reqest that the maximum size of the thumbnail is that specified by maxThumbSizeRef, 160 pixels.
    keys[1] = kCGImageSourceThumbnailMaxPixelSize;
    values[1] = (CFTypeRef)maxThumbSizeRef;
    
    // Create an options dictionary with these keys.
    options = CFDictionaryCreate(NULL,
                                 (const void **)keys,
                                 (const void **)values,
                                 2,
                                 &kCFTypeDictionaryKeyCallBacks,
                                 &kCFTypeDictionaryValueCallBacks);
    
    // Release the CFNumber this code created.
    CFRelease(maxThumbSizeRef);
    
    // Create the thumbnail image for the first  image in the image source, that at index 0, 
    // using the options dictionary that the code just created.
    thumb = CGImageSourceCreateThumbnailAtIndex(imageSource, 0, options);
    
    // Release the options dictionary
    CFRelease(options);
    // Release the image source the code created.
    CFRelease(imageSource);
    
    if (thumb == NULL) {
        fprintf(stderr, "Couldn't create thumbnail from image source! \n");
        return NULL;
    }
        
    return thumb;
}

//9.8

CFDataRef myCreateAccumulatedDataSoFar(MyIncrementalData* data, bool done){
    CFDataRef accuData = NULL;
        //missing implementation
    return accuData;
}

static void MyDrawIncrementalImage(CGContextRef ctx, CGImageRef image, float fullHeight){
    // Obtain the width and height of the image that has been accimulated so far.
    float width = CGImageGetWidth(image);
    float height = CGImageGetHeight(image);
    // Adjust the location of the imageRect so that the origin is such that
    // the full image would be located at (0,0) and the partial image 
    // top-left corner does not move as the image is filled in.
    CGRect imageRect = CGRectMake(0., fullHeight-height, width, height);
    CGContextDrawImage(ctx, imageRect, image);
}

static void myDrawFirstImageIncrementally(CGContextRef ctx, MyIncrementalData *myDataP){
    bool done;
    float height = -1.0f;
    CGRect imageRect;
    CGImageSourceStatus status;
    
    // Create an incremental image source.
    CGImageSourceRef imageSource = CGImageSourceCreateIncremental(NULL);
    if (imageSource == NULL) {
        fprintf(stderr, "Couldn't create incremental image source! \n");
        return;
    }
    
    // Loop, gathering the necessary data to find the true heught of the image and draw it.
    do {
        // Accumulate the data.
        CFDataRef data = myCreateAccumulatedDataSoFar(myDataP, &done);
        CGImageSourceUpdateData(imageSource, data, done);
        // Release the data since Quartz retains and this code no longer needs it
        CFRelease(data);
        
        if (height <0) {
            // Determine the height of the full image at index 0.
            CFDictionaryRef properties  = CGImageSourceCopyPropertiesAtIndex(imageSource, 0, NULL);
            if (properties) {
                CFTypeRef val = CFDictionaryGetValue(properties, kCGImagePropertyPixelHeight);
                if (val != NULL) 
                    CFNumberGetValue(val, kCFNumberFloatType, &height);
                CFRelease(properties);
            }
        }
        
        // Once the height is obtained, go ahead and see if Quartz has enough data to create CGImage object.
        if (height > 0) {
            // Now create the CGImageRef from the image source for the first image.
            CGImageRef image = CGImageSourceCreateImageAtIndex(imageSource, 0, NULL);
            if (image){
                // Draw the image using the height of the full image to adjust 
                // the location where the partial image is drawn.
                MyDrawIncrementalImage(ctx, image, height);
                CGImageRelease(image);
                // Potentially you would wnat to flush the context so that the drawing
                // to a window would appear, even inside this loop.
                // See chapter 17 for more information about flushing.
                CGContextFlush(ctx);
            }
        }
        
        // Obtain the status for the image source for the first image.
        status = CGImageSourceGetStatus(imageSource);
        
        // Continue the loop until either all data has loaded or the status of the first image is complete.
    } while (!done && status != kCGImageStatusComplete);
    
    CFRelease(imageSource);
}

//9.9
CFDictionaryRef createFloatingPointImageOptions(CGImageSourceRef imageSource){
    CFDictionaryRef properties, options = NULL;
    Boolean isFloat = false;
    CFTypeRef keys[1];
    CFTypeRef values[1];
    // Allow the image to be a floating-point image. Without this,
    // Quartz returns integer pixel data even, for floating-point images.
    keys[0] = kCGImageSourceShouldAllowFloat;
    values[0] = kCFBooleanTrue;
    
    options = CFDictionaryCreate(NULL,
                                 keys,
                                 values,
                                 1,
                                 &kCFTypeDictionaryKeyCallBacks,
                                 &kCFTypeDictionaryValueCallBacks);
    // Obtain the properties for the first image in the image source. 
    // This is a 'Copy' function, so the code owns a reference to the dictionary returned.
    properties = CGImageSourceCopyPropertiesAtIndex(imageSource, 0, options);
    
    if (properties == NULL) {
        CFTypeRef value;
        // Get the value for kCGImagePropertyIsFloat if it exists
        // and if the value is a CFBoolean, the get the corresponing Boolean result
        
        if (CFDictionaryGetValueIfPresent(properties,kCGImagePropertyIsFloat,&value) 
            && CFGetTypeID(value) == CFBooleanGetTypeID()) {
            isFloat = CFBooleanGetValue(value);
        }
        
        CFRelease(properties);
    }
    
    if (!isFloat) {
        // Release the options dictionary if the image isn't
        // a floating-point image, otherwise return it.
        CFRelease(options);
        options = NULL;
    }
    
    return options;
}

//9.10 - Apparently not working in Lion
/*
static CGImageRef createCGImageWithQuickTimeFromURL(CFURLRef url){
    OSStatus err = noErr;
    CGImageRef imagerRef = NULL;
    Handle dataRef = NULL;
    OSType dataRefType;
    GraphicsImportComponent gi;
    ComponentResult result;
    
    result = QTNewDataReferenceFromCFURL(url, 0, &dataRef, &dataRefType);
    if (NULL != dataRef) {
        err = GetGraphicsImporterForDataRefWithFlags(dataRef, dataRefType, &gi,0);
    
        if (!err && gi) {
            // Tell the graphics importer that it shouldn't perform
            // gamma correctionoand it should be create an image in
            // the original source color space rather than matching it to
            // a generic calibrated color space.
            result = GraphicsImportSetFlags(gi,(kGraphicsImporterDontDoGammaCorrection+kGraphicsImporterDontUseColorMatching));
            
            if (!result) 
                result = GraphicsImportCreateCGImage(gi,&imageRef,0);
            if (result) 
                fprintf(stderr, "Got a bad result = %d!",(int)reslut);
            DisposeHandle(dataRef);
            CloseComponent(gi);
        }

    }
    return imagerRef;
}*/

//9.11
bool imageHasFloatingPointSamples(CGImageRef image){
    if (&CGImageGetBitmapInfo!=NULL) {
        return (kCGBitmapFloatComponents & CGImageGetBitmapInfo(image));
    }
    return false;
}

//9.12

CGColorSpaceRef getTheCalibratedRGBColorSpace(void){
    CGColorSpaceRef colorSpace = NULL;
    
    return colorSpace;
}

CGColorSpaceRef getTheSRGBColorSpace(void){
    CGColorSpaceRef colorSpace = NULL;
    
    return colorSpace;
}

void drawJPEGDocumentWithMultipleProfiles(CGContextRef context, CFURLRef url){
    CGImageRef jpgImage = NULL, updatedImage1 = NULL, updatedImage2 = NULL;
    Boolean isDeviceRGBImage = false;
    CGColorSpaceRef originalColorSpace = NULL;
    CGColorSpaceRef comparisonColorSpace = NULL;
    CGRect imageRect;
    // Create a Quartz data provider for the supplied URL.
    CGDataProviderRef jpgProvider = CGDataProviderCreateWithURL(url);
    if (jpgProvider == NULL) {
        fprintf(stderr, "Couldn't create JPEG Data provider!\n");
        return;
    }
    
    
    //Create the CGImageRef for the JPEG image from the data provider.
    jpgImage = CGImageCreateWithJPEGDataProvider(jpgProvider, NULL, true, kCGRenderingIntentDefault);
    CGDataProviderRelease(jpgProvider);
    if (jpgImage == NULL) {
        fprintf(stderr, "Couldn't create CGImageRef fot the JPEG data!\n");
        return;
    }
    
    // Get the color space characterizing the image. This is a 
    // 'Get' function so the code doesn't own the reference
    // to the color space returned and must not release it.
    originalColorSpace = CGImageGetColorSpace(jpgImage);
    if (originalColorSpace == NULL) {
        fprintf(stderr, "Image is a masking image, not an image with intristic color!\n");
        return;
    }
    
    if (CGColorSpaceGetNumberOfComponents(originalColorSpace) != 3) {
        fprintf(stderr, "This example only works with three-component JPEG images!\n");
        return;
    }
    
    // Determine if the original color space is DeviceRGB. If that is
    // not the case, then return.
    comparisonColorSpace = CGColorSpaceCreateDeviceRGB();
    
    // Note that this comparison of color spaces works only on 
    // Jaguar and later versions where CGColorSpaceRef is a 
    // Core Foundation object. Otherwise this will crash!
    
    isDeviceRGBImage = CFEqual(comparisonColorSpace, originalColorSpace);
    // This code created 'comparisonColorSpace' so it must release it.
    CGColorSpaceRelease(comparisonColorSpace);
    if (!isDeviceRGBImage) {
        fprintf(stderr, "The color space for the JPEG image is not DeviceRGB!\n");
        return;
    }
    
    imageRect = CGRectMake(0., CGImageGetHeight(jpgImage)/2, CGImageGetWidth(jpgImage), CGImageGetHeight(jpgImage));
    // Draw the original image to the left of the other two.
    CGContextDrawImage(context, imageRect, jpgImage);
    // Recharacterize the original image with the generic Calibrated RGB
    // color space.
    
    updatedImage1 = CGImageCreateCopyWithColorSpace(jpgImage, getTheCalibratedRGBColorSpace());
    // Release the original image since this code is done with it.
    CGImageRelease(jpgImage);
    if (updatedImage1 == NULL) {
        fprintf(stderr, "There is no updated image to draw!\n");
        return;
    }
    
    // Draw the image characterized by the Generic profile 
    // to the right of the other image.
    imageRect = CGRectOffset(imageRect, CGRectGetWidth(imageRect)+10, 0);
    CGContextDrawImage(context, imageRect, updatedImage1);
    
    // Recharacterize the but but now wht color space created by the sRGB profile.
    updatedImage2 = CGImageCreateCopyWithColorSpace(updatedImage1, getTheSRGBColorSpace());
    // Release updatedImage1 since this code is done with it/
    CGImageRelease(updatedImage1);
    if (updatedImage2 == NULL) {
        fprintf(stderr, "There is no second updated image to draw!\n");
        return;
    }
    
    // Draw the image characterized by the sRGB profile to the right of
    // the image characterized by the generic RGB profile.
    imageRect = CGRectOffset(imageRect, CGRectGetWidth(imageRect)+10, 0);
    CGContextDrawImage(context, imageRect, updatedImage2);
    CGImageRelease(updatedImage2);
    
}


//9.13 
static void rgbRampSubDataRelease(void *info, const void *data, size_t size){
    free((char *)info);
}

static unsigned char * createRedGreenRampImageData(size_t width, size_t height, size_t size){
    unsigned char *p;
    unsigned char *dataP = (unsigned char *)malloc(size);
    
    if (dataP == NULL)
        return NULL;
    
    p = dataP;
    // Build an image that is RGB 24 bits per sample. This is a ramp
    // where the red component value increases in red from left to
    // right and the green component increases from top to bottom.
    int r,g;
    for (g=0; g<height; g++) {
        for (r=0; r<width; r++) {
            *p++=r; *p++=g; *p++ = 0;
        }
    }
    
    return dataP;
}

static CGDataProviderRef createRGBRampSubDataProvider(CGRect subRect){
    CGDataProviderRef dataProvider = NULL;
    size_t bytesPerSample = 3;
    size_t width = 256, height = 256;
    size_t bytesPerRow = width*bytesPerSample;
    size_t startOffsetX = subRect.origin.x;
    size_t startOffsetY = subRect.origin.y;
    size_t imageDataSize = bytesPerRow*height;
    
    // The first image sample is at
    // (startOffsetY*bytesPerRow + startOffsetX&bytesPerSample)
    // bytes intro the RGB ramp data.
    
    size_t firstByteOffset = (startOffsetY*bytesPerRow + startOffsetX&bytesPerSample);
    // The actual size of the image data provided is the full image size
    // minus the amount skipped at the beginning. This is more that the
    // total amount od data that is needed for the subimage, but it is 
    // valid and easy to calculate.
    size_t totalBytesProvided = imageDataSize-firstByteOffset;
    // Create the full color ramp.
    unsigned char *dataP = createRedGreenRampImageData(width, height, imageDataSize);

    if (dataP == NULL) {
        fprintf(stderr, "Couldn't create image data!\n");
        return NULL;
    }
    
    // Use the pointer to the first byte as the info parameter since
    // that is the pointer to the block to free when done
    dataProvider = CGDataProviderCreateWithData(dataP, dataP+firstByteOffset, totalBytesProvided, rgbRampSubDataRelease);
    
    if (dataProvider == NULL) {
        free(dataP);
        return NULL;
    }
    
    return dataProvider;
}

void doColorRampSubImage(CGContextRef context){
    CGImageRef image = NULL;
    CGRect imageSubRect, rect;
    // Start 4 scanlines from the top and 16 pixels from the left edge;
    // skip the last 40 scanlines of the image and the rightmost
    // 64 pixels.
    size_t insetLeft = 16, insetTop = 4, insetRight = 64, insetBottom = 40;
    
    size_t fullImageWidth = 256, fullImageHeight = 256;
    size_t subImageWidth = fullImageWidth-insetLeft-insetRight;
    size_t subImageHeight = fullImageHeight-insetTop-insetBottom;
    size_t bitsPerComponent = 8, bitsPerPixel = 24;
    size_t bytesPerRow = fullImageWidth*3;
    bool shouldInterpolate = true;
    CGColorSpaceRef colorspace = NULL;
    CGDataProviderRef imageDataProvider = NULL;
    imageSubRect = CGRectMake(insetLeft, insetTop,subImageWidth, subImageHeight);
    colorspace = getCalibratedRGBColorSpace();
    if (&CGImageCreateWithImageInRect != NULL) {
        CGImageRef fullImage = NULL;
        imageDataProvider = createRGBRampDataProvider();
        if (imageDataProvider == NULL) {
            fprintf(stderr, "Couldn't create Image Data provider!\n");
            return;
        }
        fullImage = CGImageCreate(fullImageWidth,
                                  fullImageHeight,
                                  bitsPerComponent,
                                  bitsPerPixel,
                                  bytesPerRow,
                                  colorspace,
                                  kCGImageAlphaNone,
                                  imageDataProvider,
                                  NULL,
                                  shouldInterpolate,
                                  kCGRenderingIntentDefault);
        if (fullImage) {
            image = CGImageCreateWithImageInRect(fullImage, imageSubRect);
            CGImageRelease(fullImage);
        }
    }
    
    // If the image hasn't been created yet, this uses the customized data provider to do so.
    if (image == NULL) {
        imageDataProvider = createRGBRampSubDataProvider(imageSubRect);
        if (imageDataProvider == NULL) {
            fprintf(stderr, "Couldn't create Image Data provider!\n");
            return;
        }
        
        // By supplying bytesPerRow, the extra data at the end of 
        // each scanline and the beginning of the next is properly skipped.
        image = CGImageCreate(subImageWidth,
                              subImageHeight,
                              bitsPerComponent,
                              bitsPerPixel,
                              bytesPerRow,
                              colorspace,
                              kCGImageAlphaNone,
                              imageDataProvider,
                              NULL,
                              shouldInterpolate,
                              kCGRenderingIntentDefault);
    }
    
    // This code no longer needs the data provider.
    CGDataProviderRelease(imageDataProvider);
    if (image == NULL) {
        fprintf(stderr, "Couldn't create CGImageRef for this data!\n");
        return;
    }
    
    // Draw the subimage
    rect = CGRectMake(0., 0., subImageWidth, subImageHeight);
    CGContextDrawImage(context, rect, image);
    CGImageRelease(image);
}


//9.14 
void exportCGImageToPNGFileWithDestination(CGImageRef image, CFURLRef url){
    float resolution = 144.;
    CFTypeRef keys[2];
    CFTypeRef values[2];
    CFDictionaryRef options = NULL;
    
    //Create an image destination at the supplied URL that corresponds to the PNG image format.
    CGImageDestinationRef imageDestination = CGImageDestinationCreateWithURL(url, kUTTypePNG, 1, NULL);
    
    if (imageDestination == NULL) {
        fprintf(stderr, "Couldn't create image destination!\n");
        return;
    }
    
    // Set the keys to be x and y resolution of the image.
    keys[0] = kCGImagePropertyDPIWidth;
    keys[1] = kCGImagePropertyDPIHeight;
    
    // Create a CFNumber for the resolution and is it as the x and y resolution
    values[0] = CFNumberCreate(NULL, kCFNumberFloatType, &resolution);
    values[1] = values[0];
    
    // Create an options dictionary with these keys.
    options = CFDictionaryCreate(NULL,
                                 (const void **)keys,
                                 (const void **)values,
                                 2,
                                 &kCFTypeDictionaryKeyCallBacks,
                                 &kCFTypeDictionaryValueCallBacks);
    
    // Release the CFNumber the code created.
    CFRelease(values[0]);
    
    // Add the image with options dictionary to the destination.
    CGImageDestinationAddImage(imageDestination, image, options);
    
    // Release the options dictionary this code created.
    CFRelease(options);
    
    // When all images are added to the destination, finalize it.
    CGImageDestinationFinalize(imageDestination);
    
    // Release the destination when done with it.
    CFRelease(imageDestination);
}

//9.15
void exportCGImageToJPEGFile(CGImageRef image, CFURLRef url);

//10.1

static const unsigned char *getMaskData1(){
    static const unsigned char data[] = {
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFE, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x03, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0xF8, 0xE7, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x40, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0,
        0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xFF,
        0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF,
        0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF,
        0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xFE, 0x00, 0x00,
        0x00, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xF8,
        0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xF8, 0x00, 0x00, 0x7F, 0xFF,
        0xFF, 0xFE, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xFC, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xFE, 0x00, 0x00,
        0x00, 0x7F, 0xFF, 0xFC, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFC,
        0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF,
        0xFF, 0xF0, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xF8, 0x00, 0x00,
        0x0F, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFF,
        0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF,
        0xFF, 0xE0, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0x80, 0x01, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x00,
        0x7F, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x1F, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xFF,
        0x80, 0x00, 0x1F, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x1F, 0xFF,
        0xFF, 0xF8, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x1F, 0xFF, 0xFF, 0xF8, 0x00, 0x00,
        0x7F, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x1F, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xFE,
        0x40, 0x00, 0x0F, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x1F, 0xFF,
        0xFF, 0xFC, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xFC, 0x00, 0x01,
        0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xFC, 0x00, 0x05, 0xEF, 0xFF, 0xFE, 0x00,
        0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xF0, 0x00, 0x3F, 0x00, 0x03, 0xFC, 0x00, 0x00, 0x00, 0x3F, 0xFF,
        0xFF, 0xE0, 0x00, 0x7C, 0x00, 0x00, 0x78, 0x1F, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xC0, 0x00, 0x38,
        0x00, 0x00, 0x78, 0x3C, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x78, 0x00, 0x00, 0x70, 0x18,
        0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x78, 0x1F, 0x00, 0x30, 0x00, 0x00, 0x01, 0xFF, 0xFF,
        0xFF, 0xFE, 0x00, 0x7C, 0x3F, 0x00, 0x18, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00,
        0x00, 0x00, 0x38, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x80, 0x00, 0x3C, 0x00,
        0x0C, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x20, 0x1C, 0x03, 0xFF, 0xFF,
        0xFF, 0xFF, 0x00, 0x00, 0x04, 0x00, 0x3C, 0x00, 0x3C, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x70,
        0xBF, 0x86, 0x3C, 0x1F, 0xFC, 0x0B, 0xFF, 0xFF, 0xFF, 0xFF, 0xA0, 0x11, 0xF0, 0x0E, 0x3C, 0x1F,
        0xFE, 0x8B, 0xFF, 0xFF, 0xFF, 0xFF, 0xA0, 0x19, 0xF0, 0x0C, 0x3C, 0x0F, 0xFF, 0x0B, 0xFF, 0xFF,
        0xFF, 0xFF, 0xB0, 0x1D, 0xFE, 0x1C, 0x7E, 0x0F, 0xFF, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xB8, 0x1C,
        0xFF, 0x3C, 0xFE, 0x03, 0xFE, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x1E, 0x7F, 0xF8, 0xDE, 0x00,
        0x7C, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x1E, 0x7F, 0xF1, 0xDF, 0x30, 0x03, 0x83, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFE, 0x1F, 0x3F, 0xE3, 0x9F, 0x10, 0x3F, 0x83, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x0F,
        0xFF, 0x83, 0xDF, 0x80, 0x1F, 0x83, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x03, 0xFC, 0x03, 0xDF, 0x81,
        0x8F, 0x83, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x07, 0xFE, 0x1F, 0x8F, 0x00, 0x07, 0x83, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0x07, 0xFE, 0x3C, 0x06, 0x00, 0x01, 0x83, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x03,
        0xFC, 0x7C, 0x00, 0x00, 0x01, 0x83, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0xF8, 0x7F, 0x00, 0x00,
        0x01, 0x83, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0xF8, 0xFF, 0xE0, 0x30, 0x01, 0x83, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0x00, 0xF1, 0xEF, 0xF9, 0xE0, 0x03, 0x83, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80,
        0xF1, 0xFF, 0xFF, 0x80, 0x0F, 0x83, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x03, 0xE2, 0xFF, 0xFE, 0x00,
        0x1F, 0x87, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x83, 0xF0, 0x00, 0x00, 0x1C, 0x3F, 0x87, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xC3, 0xF0, 0x00, 0x01, 0xF8, 0x0F, 0x87, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC3,
        0xF0, 0x03, 0xFF, 0xF0, 0x5F, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC1, 0xFF, 0xC7, 0xFF, 0xE0,
        0x7F, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE1, 0xFF, 0xF1, 0xFF, 0x80, 0x2F, 0x0F, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xE1, 0xFF, 0xF8, 0x0F, 0xC0, 0x06, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF4,
        0xFF, 0xFE, 0x0F, 0xF8, 0x44, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF4, 0xFF, 0xFF, 0xFF, 0xF8,
        0x64, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF9, 0xFF, 0xFF, 0xFF, 0x3C, 0xE4, 0x7F, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFD, 0x9F, 0xFF, 0xFC, 0x1F, 0xC0, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD,
        0x1F, 0xFF, 0xFC, 0x03, 0xC0, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x01, 0xFF, 0xFF, 0xFF,
        0xC0, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x7F, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE,
        0x80, 0x7F, 0xFF, 0xFF, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x80, 0x1F, 0xFF, 0xFF,
        0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xC0, 0x0F, 0xFF, 0xFF, 0x00, 0x1F, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x07, 0xFF, 0xFF, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xF0, 0x03, 0xFF, 0xFF, 0x00, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x70, 0x01, 0xFF, 0xFC,
        0x00, 0x17, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x78, 0x00, 0x7F, 0xF0, 0x00, 0x07, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xF0, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x03,
        0xFE, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x1F, 0xFF, 0x80, 0x00, 0x00,
        0x00, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x7F, 0x7F, 0xC0, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF
    };
    return data;
}

static const unsigned char *getMaskData2(){
    static const unsigned char data[] = {
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
        0xFF, 0xFF, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, 0x1F, 
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
        0xFF, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 
        0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
        0xE0, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x00, 
        0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 
        0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x01, 
        0x80, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x03, 0xC0, 0x07, 0xFF, 0xFF, 
        0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x0B, 0xE0, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 
        0x00, 0x00, 0x00, 0x07, 0xF0, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x1F, 
        0xF4, 0x83, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x3F, 0xE4, 0x03, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x3F, 0xE4, 0x43, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 
        0x00, 0x00, 0x00, 0x3F, 0xE4, 0x4B, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x02, 0xFF,
        0xE4, 0x5B, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x02, 0xFF, 0xE0, 0x5B, 0xFF, 0xFF, 
        0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x07, 0xC1, 0xFF, 0xE0, 0x59, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x18,
        0x00, 0x7F, 0xF0, 0xFE, 0x00, 0x79, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x18, 0x00, 0x78, 0x0F, 0xFE, 
        0x04, 0xE1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x18, 0x00, 0xB0, 0x47, 0xFF, 0xFF, 0xE1, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFE, 0x10, 0x00, 0xC4, 0x69, 0xFF, 0xFF, 0xC3, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x10, 
        0x01, 0xFF, 0xE1, 0xFC, 0x07, 0xC1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, 0x01, 0xFF, 0xF8, 0x78,
        0x01, 0xC5, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x04, 0x01, 0xFF, 0xF0, 0x78, 0x01, 0xC5, 0xFF, 0xFF, 
        0xFF, 0xFF, 0xFC, 0x0C, 0x00, 0xFF, 0xF8, 0x7E, 0x3F, 0xC1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x0C,
        0x00, 0x7F, 0xF0, 0x18, 0xFF, 0xC3, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x07, 0x00, 0x7F, 0xF4, 0x1F, 
        0xFF, 0xE3, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x23, 0x00, 0x7F, 0xE0, 0x3E, 0xFF, 0xE3, 0xFF, 0xFF,
        0xFF, 0xFF, 0xF8, 0x11, 0x00, 0x7F, 0xEC, 0x5F, 0xBF, 0xE3, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x01, 
        0x00, 0x3F, 0xCE, 0x7E, 0x3F, 0xE3, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x08, 0x00, 0x7F, 0x80, 0x2E,
        0x3F, 0xE3, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x06, 0x00, 0x7F, 0x00, 0x6E, 0x3F, 0xEB, 0xFF, 0xFF, 
        0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x7E, 0x0D, 0xFE, 0xFF, 0xEB, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00,
        0x00, 0x3C, 0x00, 0xFE, 0x3F, 0xEB, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x50, 0x00, 0xFE, 
        0x3F, 0xCB, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x01, 0x98, 0xFF, 0x3F, 0xCB, 0xFF, 0xFF,
        0xFF, 0xFF, 0xF0, 0x00, 0x00, 0xC7, 0xE1, 0xFF, 0x3F, 0x8B, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 
        0x00, 0x40, 0xFF, 0xFF, 0xBF, 0x8B, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0xE0, 0x1F, 0xFF,
        0xDF, 0x0B, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0xE8, 0x63, 0xFF, 0xDF, 0x0F, 0xFF, 0xFF, 
        0xFF, 0xFF, 0xF0, 0x00, 0x02, 0xFC, 0xF9, 0xFF, 0xEF, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00,
        0x03, 0xFE, 0x7F, 0xF8, 0x1E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x03, 0x7E, 0x0F, 0xF9, 
        0xBE, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x01, 0x7F, 0xC1, 0xF3, 0xFC, 0x05, 0xFF, 0xFF,
        0xFF, 0xFF, 0xE0, 0x00, 0x01, 0x3D, 0xF8, 0x0F, 0x7C, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 
        0x01, 0xBC, 0x7F, 0xFF, 0xF8, 0x02, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0xBE, 0xFF, 0xFF,
        0xF8, 0x02, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x1D, 0xFF, 0xFF, 0xF0, 0x00, 0xFF, 0xFF, 
        0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x0F, 0xF7, 0xFF, 0xE0, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xC0, 0x00,
        0x00, 0x0F, 0xF3, 0xFF, 0xE0, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x03, 0xF3, 0xFF, 
        0xC0, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x01, 0xF7, 0xFF, 0x80, 0x00, 0x3F, 0xFF,
        0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 
        0x00, 0x00, 0x1F, 0xFF, 0x00, 0x20, 0x3F, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF,
        0x00, 0x10, 0x3F, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0x00, 0x10, 0x3F, 0xFF, 
        0xFF, 0xFC, 0x00, 0x00, 0x02, 0x00, 0x0F, 0xFF, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xFC, 0x00, 0x00,
        0x04, 0x00, 0x1F, 0xFE, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x07, 0x81, 0x7F, 0xFE, 
        0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x03, 0xDF, 0xFF, 0xFE, 0x00, 0x00, 0x1F, 0xFF,
        0xFF, 0xF8, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 
        0x07, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xF0, 0x00, 0x40, 0x07, 0xFF, 0xFF, 0xFE,
        0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xF0, 0x00, 0xC0, 0x03, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x0F, 0xFF, 
        0xFF, 0xE0, 0x00, 0xE0, 0x07, 0xFF, 0xFF, 0xFE, 0x81, 0x00, 0x07, 0xFF, 0xFF, 0xC0, 0x01, 0xE0,
        0x07, 0xFF, 0xFF, 0xFE, 0x01, 0x00, 0x07, 0xFF, 0xFF, 0x80, 0x0F, 0xF0, 0x03, 0xFF, 0xFF, 0xFE, 
        0x83, 0x80, 0x03, 0xFF, 0xFF, 0x00, 0x1F, 0xF0, 0x13, 0xFF, 0xFF, 0xFE, 0x03, 0xE0, 0x01, 0xFF,
        0xFC, 0x03, 0x3F, 0xF0, 0x21, 0xFF, 0xFF, 0xFE, 0x03, 0xFC, 0x00, 0x3F, 0xF0, 0x3F, 0x3F, 0xF8, 
        0x3B, 0xFF, 0xFF, 0xFE, 0x03, 0xFE, 0xC0, 0x0F, 0xE3, 0xFB, 0x7F, 0xF8, 0x3B, 0xFF, 0xFF, 0xFF, 
        0x07, 0xFF, 0xFF, 0x07, 0x9F, 0xFB, 0x7F, 0xFC, 0x79, 0xFF, 0xFF, 0xFF, 0x07, 0xFF, 0xFF, 0xFF, 
        0xFF, 0xFF, 0x7F, 0xFC, 0x39, 0xFF, 0xFF, 0xFF, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFE,
        0x3F, 0xFF, 0xFF, 0xFE, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFE, 0x1F, 0xFF, 0xFF, 0xFE, 
        0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFE, 0x1F, 0x7F, 0xFF, 0xFE, 0x0F, 0xFF, 0xFF, 0xFF, 
        0xFF, 0xFF, 0x7F, 0xFF, 0x1F, 0xFE, 0xFF, 0xFC, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
        0x0F, 0xFF, 0xFF, 0xFF, 0x1F, 0xFF, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x87, 0xFF, 0xFF, 0xFE, 
        0x1F, 0xFF, 0xEF, 0xFF, 0xFF, 0xFF, 0xBF, 0xFF, 0x82, 0xFF, 0xFF, 0xFC, 0x3F, 0xFF, 0xFF, 0xFF, 
        0xFF, 0xFF, 0xBF, 0xFF, 0x83, 0xFF, 0xFF, 0xFC, 0x3F, 0xFF, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
        0xC1, 0xFF, 0xFF, 0xF8, 0x7F, 0xFF, 0xBF, 0xFF, 0xFF, 0xFF, 0xBF, 0xFF, 0xE0, 0xFF, 0xFF, 0xF0, 
        0xFF, 0xFF, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
    };
    return data;
}

void doOneBitMaskImages(CGContextRef context){
    static const size_t bitsPerComponent = 1, bitsPerPixel = 1;
    static const size_t width = 96, height = 96;
    static const size_t bytesPerRow = 12;
    
    CGImageRef mask1, invertedMask1, mask2, invertedMask2;
    CGRect imageRect, backRect;
    
    size_t imageDataSize = bytesPerRow * height;
    Boolean shouldInterpolate = true;
    
	static const float lightBlue[] = { 0.482, 0.62, 0.871, 1. };	
	static const float black[] = { 0., 0., 0., 1. };
	static const float darkRed[] = { 0.663, 0., 0.031, 1. };
	static const float darkGreen[] = { 0.404, 0.808, 0.239, 1. };
	static const float darkBlue[] = { 0.11, 0.208, 0.451, 1. };
	float purple[] = { 0.69, 0.486, 0.722, 1. };
	float darkOrange[] = { 0.965, 0.584, 0.059, 1. };
    
	CGColorSpaceRef colorSpace = NULL;
    float decode[2] = {1, 0};
    
    // Create a Quart data provider for the image data. Becouse this
    // data is static data, there is no need to release ot, sot the data relase function is NULL.
    unsigned const char *data = getMaskData1();
    CGDataProviderRef dataProvider = CGDataProviderCreateWithData(NULL, data, imageDataSize, NULL);
    if (dataProvider == NULL) {
        fprintf(stderr, "Couldn't create Mask Data provider!\n");
        return;
    }
    
    // Create a mask from the data
    mask1 = CGImageMaskCreate(width, height, bitsPerComponent, bitsPerPixel, bytesPerRow, dataProvider, NULL, shouldInterpolate);
    
    // Create the same mask but with a decode array that
    // inverts the sense of the mask
    
    invertedMask1 = CGImageMaskCreate(width, height, bitsPerComponent, bitsPerPixel, bytesPerRow, dataProvider, decode, shouldInterpolate);
    // Release the data provider now that this code no longer needs it.
    CGDataProviderRelease(dataProvider);
    
    if (mask1 == NULL || invertedMask1 == NULL) {
        if (mask1 == NULL)
            fprintf(stderr, "Couldn't create CGImageRef for mask data 1!\n");
        else
            CGImageRelease(mask1);
        
        if (invertedMask1 == NULL)
            fprintf(stderr, "Couldn't create CGImageRef for inverted mask data 1!\n");
        else
            CGImageRelease(invertedMask1);
        
        return;
    }
    
    // Get the pointer to the data for the second mask/
    data = getMaskData2();
    dataProvider = CGDataProviderCreateWithData(NULL, data, imageDataSize, NULL);
    if (dataProvider == NULL) {
        fprintf(stderr, "Couldn't create Mask2 data provider!\n");
        return;
    }
    
    mask2 = CGImageMaskCreate(width, height, bitsPerComponent, bitsPerPixel, bytesPerRow, dataProvider, NULL, shouldInterpolate);
    
    // Create the same mask but with a decode array that
    // inverts the sense of the mask
    
    invertedMask2 = CGImageMaskCreate(width, height, bitsPerComponent, bitsPerPixel, bytesPerRow, dataProvider, decode, shouldInterpolate);
    
    // Release the data provider now that this code no longer needs it.
    CGDataProviderRelease(dataProvider);
    
    if (mask2 == NULL || invertedMask2 == NULL) {
        if (mask2 == NULL)
            fprintf(stderr, "Couldn't create CGImageRef for mask data 2!\n");
        else
            CGImageRelease(mask2);
        
        if (invertedMask2 == NULL)
            fprintf(stderr, "Couldn't create CGImageRef for inverted mask data 2!\n");
        else
            CGImageRelease(invertedMask2);
        
        return;
    }
    
    CGContextScaleCTM(context, 1.5, 1.5);
    colorSpace = getCalibratedRGBColorSpace();
    CGContextSetFillColorSpace(context, colorSpace);
    
    // Set the fill color to a light blue
    CGContextSetFillColor(context, lightBlue);
    // Paint part of the background
    backRect = CGRectMake(width/2, height/2, width*3, height);
    CGContextFillRect(context, backRect);
    
    imageRect = CGRectMake(0., height, width, height);
    CGContextSaveGState(context);
    
        // Set the fill color to opaque black.
        CGContextSetFillColor(context, black);
        // **** Mask 1 ****
        CGContextDrawImage(context, imageRect, mask1);
        
        CGContextTranslateCTM(context, width, 0);
        // Set the fill color to opaque red
        CGContextSetFillColor(context, darkRed);
        // **** Mask 2 ****
        CGContextDrawImage(context, imageRect, mask2);
        CGContextTranslateCTM(context, width, 0);
        // Set the fill color to dark orange.
        CGContextSetFillColor(context, darkOrange);
        // **** Mask 3 ****
        CGContextDrawImage(context, imageRect, mask1);
        
        CGContextTranslateCTM(context, width, 0);
        // Make the orange 50% transparent
        darkOrange[3] = 0.5;
        CGContextSetFillColor(context, darkOrange);
        // **** Mask 4 ****
        CGContextDrawImage(context, imageRect, mask2);
    
    CGContextRestoreGState(context);
    
    
    // Translate down the page. The cast is necessary
    // since height is typed as size_t which is unsigned.
    CGContextTranslateCTM(context, 0, -(signed)height);
    // Set the fill color to an opaque green.
    CGContextSetFillColor(context, darkGreen);
    // **** Mask 5 ****
    CGContextDrawImage(context, imageRect, invertedMask2);
    
    CGContextTranslateCTM(context, width, 0);
    // Set the fill color to a dark blue.
    CGContextSetFillColor(context, darkBlue);
    // **** Mask 6 ****
    CGContextDrawImage(context, imageRect, invertedMask1);
    // Set the fill color to purple
    CGContextSetFillColor(context, purple);
    // **** Mask 7 ****
    CGContextDrawImage(context, imageRect, invertedMask2);
    CGContextTranslateCTM(context, width, 0);
    
    // Make the purple 50% transparent.
    purple[3] = 0.5;
    CGContextSetFillColor(context, purple);
    // **** Mask 8 ****
    CGContextDrawImage(context, imageRect, invertedMask1);
    // Release the CGImageRef's when they are no longer needed.
    CGImageRelease(mask1);
    CGImageRelease(invertedMask1);
    CGImageRelease(mask2);
    CGImageRelease(invertedMask2);
    


} 









