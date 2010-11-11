#import <Foundation/Foundation.h>

#import "SocketIoClient.h"

@interface SocketIoHandler : NSObject <SocketIoClientDelegate> {
}
@end

@implementation SocketIoHandler

- (void)socketIoClientDidConnect:(SocketIoClient *)client {
  printf("SocketIO Connected.\n");
}

- (void)socketIoClientDidDisconnect:(SocketIoClient *)client {
  printf("SocketIO Disconnected.\n");
}

- (void)socketIoClient:(SocketIoClient *)client didReceiveMessage:(NSString *)message isJSON:(BOOL)isJSON {
  printf("SocketIO Received %s Message:\n%s\n", isJSON ? "JSON" : "TEXT", [message UTF8String]);
}

@end

int main (int argc, const char * argv[]) {
  NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];

  NSString *command = nil;
  
  NSString *host = nil;
  int port = 0;

  if (argc > 1) {
    host = [NSString stringWithUTF8String:argv[1]];
  }
  
  if (argc > 2) {
    port = [[NSString stringWithUTF8String:argv[2]] intValue];
  }

  if (argc > 3) {
    command = [NSString stringWithUTF8String:argv[3]];
  }
  
  if ([command isEqualToString:@"listen"]) {
    printf("Listening on %s:%d...\n", [host UTF8String], port);
    
    SocketIoClient *client = [[SocketIoClient alloc] initWithHost:host port:port];
    
    SocketIoHandler *handler = [[SocketIoHandler alloc] init];
    client.delegate = handler;
    
    [client connect];
    
    
    // Sleep forever
    NSRunLoop *runLoop = [NSRunLoop currentRunLoop];
    while (YES) {
      [runLoop runUntilDate:[NSDate dateWithTimeIntervalSinceNow:1.0]];
    }
    
  } else if ([command isEqualToString:@"send"]) {
    NSString *message = [NSString stringWithUTF8String:argv[4]];
    
    printf("Sending '%s' to %s:%d...\n", [message UTF8String], [host UTF8String], port);
    
    SocketIoClient *client = [[SocketIoClient alloc] initWithHost:host port:port];
    
    SocketIoHandler *handler = [[SocketIoHandler alloc] init];
    client.delegate = handler;
    
    [client connect];
    
    [client send:message isJSON:NO];
    
    // The message gets sent, then we just sleep forever...
    NSRunLoop *runLoop = [NSRunLoop currentRunLoop];
    while (YES) {
      [runLoop runUntilDate:[NSDate dateWithTimeIntervalSinceNow:1.0]];
    }
    
  } else {
    printf("usage: %s <host> <port> listen\n", argv[0]);
    printf("       %s <host> <port> send <message>\n", argv[0]);
  }
    
  [pool drain];
  return 0;
}
