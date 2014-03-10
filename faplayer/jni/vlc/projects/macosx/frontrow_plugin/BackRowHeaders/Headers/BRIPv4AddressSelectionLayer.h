/*
 *     Generated by class-dump 3.1.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2006 by Steve Nygard.
 */

#import <BackRow/BRLayer.h>

@class BRIPv4AddressSelectionWidget, BRImageLayer, BRTextLayer, NSArray;

@interface BRIPv4AddressSelectionLayer : BRLayer
{
    NSArray *_octetBackgroundLayers;
    NSArray *_digitLayers;
    NSArray *_dotLayers;
    BRImageLayer *_arrowsLayer;
    BRIPv4AddressSelectionWidget *_selectionWidget;
    BRTextLayer *_doneLayer;
    int _selection;
}

- (id)init;
- (void)dealloc;
- (struct CGRect)preferredFrameForScreenSize:(struct CGSize)fp8;
- (BOOL)moveSelectionRight;
- (BOOL)moveSelectionLeft;
- (BOOL)incrementSelection;
- (BOOL)decrementSelection;
- (id)ipAddress;
- (BOOL)doneButtonSelected;
- (void)reset;
- (void)setIPAddress:(id)fp8;
- (void)setFrame:(struct CGRect)fp8;

@end
