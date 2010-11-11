

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
@property (nonatomic, assign) id<SocketIoClientDelegate> delegate;

@property (nonatomic, assign) NSTimeInterval connectTimeout;
@property (nonatomic, assign) BOOL tryAgainOnConnectTimeout;

@property (nonatomic, assign) NSTimeInterval heartbeatTimeout;

- (id)initWithHost:(NSString *)host port:(int)port;

- (void)connect;
- (void)disconnect;

- (void)send:(NSString *)data isJSON:(BOOL)isJSON;

@end

@protocol SocketIoClientDelegate <NSObject>

- (void)socketIoClient:(SocketIoClient *)client didReceiveMessage:(NSString *)message isJSON:(BOOL)isJSON;
- (void)socketIoClientDidConnect:(SocketIoClient *)client;
- (void)socketIoClientDidDisconnect:(SocketIoClient *)client;

@end