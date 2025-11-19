# Minimal TCP Server & Client

Minimal TCP server and client implementations in C++.

## Build

```bash
make
```

This builds both `server` and `client`.

## Run

**Terminal 1 - Start the server:**
```bash
./server
```

**Terminal 2 - Run the client:**
```bash
./client
```

## Test with other tools

You can also test the server using `telnet` or `nc`:

```bash
telnet localhost 8080
# or
nc localhost 8080
```

Type a message and press Enter. The server will echo it back.

## Features

**Server:**
- Listens on port 8080
- Accepts one client connection
- Echoes received data back to client
- Closes when client disconnects

**Client:**
- Connects to localhost:8080
- Sends a message
- Receives and displays the echo
- Closes connection

