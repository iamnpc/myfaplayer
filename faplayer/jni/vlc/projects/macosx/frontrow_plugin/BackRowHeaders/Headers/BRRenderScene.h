/*
 *     Generated by class-dump 3.1.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2006 by Steve Nygard.
 */

#import <BackRow/BRSingleton.h>

#import "BREventResponderProtocol.h"

@class BRLayer, BRRenderContext, CARenderer, NSMutableArray;

@interface BRRenderScene : BRSingleton <BREventResponder>
{
    BRLayer *_root;
    CARenderer *_renderer;
    BRRenderContext *_context;
    NSMutableArray *_windowList;
    struct CGRect _previousUpdate;
    struct CGSize _sceneSize;
    id <BRRenderScenePlaybackDelegate> _delegate;
    struct BRRenderSceneFrameCountParams _countParams;
    BOOL _opaque;
    BOOL _drawSafeRegions;
    BOOL _drawFrameRate;
    BOOL _backgroundRemoved;
}

+ (id)singleton;
+ (void)setSingleton:(id)fp8;
- (id)init;
- (void)dealloc;
- (void)setDrawableContext:(id)fp8;
- (id)drawableContext;
- (void)setPlaybackDelegate:(id)fp8;
- (id)playbackDelegate;
- (struct CGRect)interfaceFrame;
- (void)setSize:(struct CGSize)fp8;
- (struct CGSize)size;
- (void)setOpaque:(BOOL)fp8;
- (BOOL)opaque;
- (void)setBackgroundRemoved:(BOOL)fp8;
- (BOOL)backgroundRemoved;
- (BOOL)brEventAction:(id)fp8;

@end

