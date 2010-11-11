# Socket.IO Client for Cocoa

A Cocoa interface to Socket.IO by way of web sockets.  If you're already using Socket.IO stuff for your web site, you might find it convenient to use the same architecture for your mobile stuff, too.

## Usage

    SocketIoClient *client = [[SocketIoClient alloc] initWithHost:host port:port];
    client.delegate = self;

    [client connect];
    
    [client send:@"Hello Socket.IO" isJSON:NO];

You'll get sweet callbacks on your delegate when stuff goes down...

    - (void)socketIoClientDidConnect:(SocketIoClient *)client {
        NSLog(@"Connected.");
    }

    - (void)socketIoClientDidDisconnect:(SocketIoClient *)client {
        NSLog(@"Disconnected.");
    }

    - (void)socketIoClient:(SocketIoClient *)client didReceiveMessage:(NSString *)message isJSON:(BOOL)isJSON {
        NSLog(@"Received: %@", message);
    }

## Depends on

* AsyncSocket [http://code.google.com/p/cocoaasyncsocket/](http://code.google.com/p/cocoaasyncsocket/)
* Cocoa WebSocket [https://github.com/erichocean/cocoa-websocket](https://github.com/erichocean/cocoa-websocket)
* SocketIo Client for Cocoa [https://github.com/fpotter/socketio-cocoa](https://github.com/fpotter/socketio-cocoa)

## Getting the code

    git clone git://github.com/fpotter/socketio-cocoa.git socketio-cocoa && cd socketio-cocoa && git submodule init && git submodule update
 
## Adding to your project

Copy the `AsyncSocket.h`, `AsyncSocket.m`, `WebSocket.h`, `WebSocket.m`, `SocketIoClient.h`, `SocketIoClient.m` files to your project.

**If you're building for iOS**, make sure you add a reference to the `CFNetwork` framework or you'll see compile errors from AsyncSocket.

