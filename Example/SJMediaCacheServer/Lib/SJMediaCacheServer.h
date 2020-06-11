//
//  SJMediaCacheServer.h
//  SJMediaCacheServer_Example
//
//  Created by BlueDancer on 2020/5/30.
//  Copyright © 2020 changsanjiang@gmail.com. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface SJMediaCacheServer : NSObject
+ (instancetype)shared;

/// Convert the URL to the playback URL.
///
/// @param URL      An instance of NSURL that references a media resource.
///
/// @return         It may return the local cache playback URL or HTTP proxy URL, but when there is no cache file and the proxy service is not running, it will return the parameter URL.
///
- (NSURL *)playbackURLWithURL:(NSURL *)URL; // 获取播放地址

@end


@interface SJMediaCacheServer (Request)

/// Add a request header or something to a request.
///
///     This block will be invoke when the download server creates each new download task.
///
@property (nonatomic, copy, nullable) NSMutableURLRequest *_Nullable(^requestHandler)(NSMutableURLRequest *request);

@end


@interface SJMediaCacheServer (Convert)

/// Resolve the identifier of the resource referenced by the URL.
///
///     The resource identifier represents a unique resource. When different URLs references the same resource, you can set the block to resolve the identifier.
///
///     This identifier will be used to identify the local cache. The same identifier will references the same cache.
///
@property (nonatomic, copy, nullable) NSString *(^resolveResourceIdentifier)(NSURL *URL); // URL参数不固定时, 请设置该block返回一个唯一标识符

/// Encode the received data.
///
///     This block will be invoked when the download server receives the data, where you can perform some encoding operations on the data.
///
@property (nonatomic, copy, nullable) NSData *(^writeDataEncoder)(NSURLRequest *request, NSUInteger offset, NSData *data); // 对下载的数据进行编码

/// Decode the read data.
///
///     This block will be invoked when the reader reads the data, where you can perform some decoding operations on the data.
///
@property (nonatomic, copy, nullable) NSData *(^readDataDecoder)(NSURLRequest *request, NSUInteger offset, NSData *data); // 对读取的数据进行解码

@end


@interface SJMediaCacheServer (Log)

/// Whether to open the console log, only in debug mode. release mode will not generate any logs.
///
///     If yes, the log will be output on the console. The default value is NO.
///
@property (nonatomic, getter=isEnabledConsoleLog) BOOL enabledConsoleLog; // 是否开启控制日志

@end


@interface SJMediaCacheServer (Cache)

/// The maximum number of resources the cache should hold.
///
///     If 0, there is no count limit. The default value is 0.
///
///     This is not a strict limit—if the cache goes over the limit, a resource in the cache could be evicted instantly, later, or possibly never, depending on the usage details of the resource.
///
@property (nonatomic) NSUInteger cacheCountLimit; // 个数限制

/// The maximum length of time to keep a resource in the cache, in seconds.
///
///     If 0, there is no expiring limit.  The default value is 0.
///
@property (nonatomic) NSTimeInterval maxDiskAgeForCache; // 保存时长限制

/// The maximum size of the disk cache, in bytes.
///
///     If 0, there is no cache size limit. The default value is 0.
///
@property (nonatomic) NSUInteger maxDiskSizeForCache; // 缓存占用的磁盘空间限制

/// The maximum length of free disk space the device should reserved, in bytes.
///
///     When the free disk space of device is less than or equal to this value, some resources will be removed.
///
///     If 0, there is no disk space limit. The default value is 0.
///
@property (nonatomic) NSUInteger reservedFreeDiskSpace; // 剩余磁盘空间限制

/// Empties the cache. This method may blocks the calling thread until file delete finished.
///
- (void)removeAllCaches; // 删除全部缓存
@end
NS_ASSUME_NONNULL_END
