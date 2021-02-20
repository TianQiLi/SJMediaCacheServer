//
//  HLSParser.h
//  SJMediaCacheServer_Example
//
//  Created by 畅三江 on 2020/6/9.
//  Copyright © 2020 changsanjiang@gmail.com. All rights reserved.
//

#import <Foundation/Foundation.h>
@protocol HLSParserDelegate;
@class HLSAsset;

NS_ASSUME_NONNULL_BEGIN
@protocol HLSURIItem <NSObject>
@property (nonatomic, copy, readonly) NSString *URI;
@property (nonatomic, copy, readonly, nullable) NSDictionary *HTTPAdditionalHeaders;
@end

@interface HLSParser : NSObject
+ (nullable instancetype)parserInAsset:(HLSAsset *)asset;

- (instancetype)initWithAsset:(HLSAsset *)asset request:(NSURLRequest *)request networkTaskPriority:(float)networkTaskPriority delegate:(id<HLSParserDelegate>)delegate;

- (void)prepare;

- (void)close;

@property (nonatomic, weak, readonly, nullable) HLSAsset *asset;
@property (nonatomic, readonly) NSUInteger allItemsCount;
@property (nonatomic, readonly) NSUInteger tsCount;
@property (nonatomic, readonly) NSUInteger streamCount;

- (nullable id<HLSURIItem>)itemAtIndex:(NSUInteger)index;
- (nullable id<HLSURIItem>)tsAtIndex:(NSUInteger)index;
- (nullable id<HLSURIItem>)streamAtIndex:(NSUInteger)index;

@property (nonatomic, readonly) BOOL isClosed;
@property (nonatomic, readonly) BOOL isDone;
@end


@protocol HLSParserDelegate <NSObject>
- (void)parserParseDidFinish:(HLSParser *)parser;
- (void)parser:(HLSParser *)parser anErrorOccurred:(NSError *)error;
@end

NS_ASSUME_NONNULL_END
