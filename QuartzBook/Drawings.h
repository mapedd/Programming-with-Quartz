//
//  Drawings.h
//  QuartzBook
//
//  Created by Mapedd on 11-04-19.
//  Copyright 2011 MapApp. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>

// The full path to the generic RGB ICC progile.

#define kGenericRGBProfilePathStr "/System/Library/ColorSync/Profiles/Generic RGB Profile.icc"

static inline CGFloat DEGREES_TO_RADIANS(CGFloat degrees);


void doAlphaRects(CGContextRef context);

void drawCoordinateAxies(CGContextRef context);

void drawSkewedRectangles(CGContextRef context);

//5.1
void drawRotartedAndScaledRectangle(CGContextRef context);

//5.3
void drawElipse(CGContextRef context);

//5.5
void drawRotatedEllipses(CGContextRef context);

//5.6
void drawScewedCoordinateSystem(CGContextRef context);

//6.1
void drawEgg(CGContextRef context);

//6.2
void addRoundedRectToPath(CGContextRef context, CGRect rect, CGFloat ovalWidth, CGFloat ovalHeight);
void doRoundedRects(CGContextRef context);

//6.3
void myCGContextAddEllipseInRect(CGContextRef context, CGRect rect);

//6.4
void doStrokeWithCTM(CGContextRef context);

//6.5
void doRotatedEllipsesWithCGPath(CGContextRef context);

//6.6
static CGPoint alignPointToUserSpace(CGContextRef context, CGPoint point);

static CGSize alignSizeToUserSpace(CGContextRef context, CGSize size);

static CGRect alignRectToUserSpace(CGContextRef context, CGRect rect);

void doPixelAlignedFillAndStroke(CGContextRef context);


//7.1
CGColorSpaceRef getTheRGBColorSpace(void);

void doColorSpaceFillAndStroke(CGContextRef context);


// antother drawing functions
CGMutablePathRef createRoundedRectForRect(CGRect rect, CGFloat radius) ;

CGMutablePathRef createScroll(CGRect rect);

CGMutablePathRef createTriangle(CGRect rect);

//7.2
void drawWithColorRefs(CGContextRef context);


//7.3
CGColorSpaceRef getTheGenericRGBColorSpace(void);

//7.5
CGColorSpaceRef updatedGetTheRGBColorSpace(void);


//7.6
void drawWithGlobalAlpha(CGContextRef context);


//7.7
void drawWithColorBlendMode(CGContextRef context, CFURLRef url);

//7.9
void createEllipsePath(CGContextRef context, CGPoint center, CGSize ellipseSize);

void doClippedEllipse(CGContextRef context);

// ******************************** //

//8.1
CGDataProviderRef createDataProviderFromPathName(CFStringRef path);

//8.2
static void rgbReleaseRampData(void *info, const void *data, size_t size);

CGDataProviderRef createRGBRampDataProvider(void);

//8.3
typedef struct MyImageDataInfo{
    FILE *fp;
#if DEBUG
    size_t totalBytesRead;
    size_t skippedBytes;
    size_t numRewinds;
#endif
}MyImageDataInfo;

static size_t getBytesSequentialAccessDP(void *data, void *buffer, size_t count);

static void skipBytesSequentialAccessDP(void *data, size_t count);

static void rewindSequentialAccessDP(void *data);

static void releaseSequentialAccessDP(void *data);

CGDataProviderRef createSequentialAccessDPForURL(CFURLRef url);

//8.4

static size_t getBytesGrayRampDirectAccess(void *info, void *buffer, size_t offset, size_t count);

CGDataProviderRef createGrayRampDirectAccessDP(void);

//8.5

static void myCFDataRelease(void *info, const void *data, size_t size);

CGDataProviderRef myCGDataProviderCreateWithCFData(CFDataRef data);

// MallocDebug!

//8.6

CGDataConsumerRef createDataConsumerFromPathName(CFStringRef path);

//8.7

size_t myCFDataConsumerPutBytes(void *info, const void* buffer, size_t count);

void myCFDataConsumerRelease(void *info);

CGDataConsumerRef myCGDataConsumerCreateWithCFData(CFMutableDataRef data);

//9.1
void drawJPEGImage(CGContextRef ctx, CFURLRef url);

//9.2
void drawImageFromURL(CGContextRef ctx, CFURLRef url, size_t width, size_t height, size_t bitsPerComponent, Boolean isRGB);

void doColorRampImage(CGContextRef ctx);

CGColorSpaceRef getCalibratedRGBColorSpace(void);