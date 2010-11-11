//
//  SocketIoClient.h
//  SocketIoCocoa
//
//  Created by Fred Potter on 11/11/10.
//  Copyright 2010 Fred Potter. All rights reserved.
//

#import <Foundation/Foundation.h>

@class WebSocket;
@protocol SocketIoClientDelegate;

@interface SocketIoClient : NSObject {
  NSString *_host;
  NSInteger _port;
  WebSocket *_webSocket;
  
  NSTimeInterval _connectTimeout;
  BOOL _tryAgainOnConnectTimeout;
  
  NSTimeInterval _heartbeatTimeout;
  
  NSTimer *_timeout;

  BOOL _isConnected;
  BOOL _isConnecting;
  NSString *_sessionId;
  
  id<SocketIoClientDelegate> _delegate;
  
  NSMutableArray *_queue;
}

@property (nonatomic, retain) NSString *sessionId;
@property (nonatomic, readonly) BOOL isConnected;
@property (nonatomic, readonly) BOOL isConnecting;

@property (nonatomic, assign) id<SocketIoClientDelegate> delegate;

@property (nonatomic, assign) NSTimeInterval connectTimeout;
@property (nonatomic, assign) BOOL tryAgainOnConnectTimeout;

@property (nonatomic, assign) NSTimeInterval heartbeatTimeout;

- (id)initWithHost:(NSString *)host port:(int)port;

- (void)connect;
- (void)disconnect;

/**
 * Rather than coupling this with any specific JSON library, you always
 * pass in a string (either _the_ string, or the the JSON-encoded version
 * of your object), and indicate whether or not you're passing a JSON object.
 */
- (void)send:(NSString *)data isJSON:(BOOL)isJSON;

@end

@protocol SocketIoClientDelegate <NSObject>

/**
 * Message is always returned as a string, even when the message was meant to come
 * in as a JSON object.  Decoding the JSON is left as an exercise for the receiver.
 */
- (void)socketIoClient:(SocketIoClient *)client didReceiveMessage:(NSString *)message isJSON:(BOOL)isJSON;

- (void)socketIoClientDidConnect:(SocketIoClient *)client;
- (void)socketIoClientDidDisconnect:(SocketIoClient *)client;

@optional

- (void)socketIoClient:(SocketIoClient *)client didSendMessage:(NSString *)message isJSON:(BOOL)isJSON;

@end