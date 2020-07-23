# Data from Home

Mesh network using ESP8266, ESP32, 
PainlessMesh, and some sensors to 
sense and log environmental data.

## How to use - ESP32/ESP8266 code

* **logServer.cpp** - run by the 
central server.
* **logClient.cpp** - run by the 
nodes in the mesh.

**How to upload ONE of the .cpp 
files to a board in PlatformIO?**

In platformio.ini, you have to 
use `src_filter` to exclude and 
include the files to be built and 
uploaded.  For example, 
`src_filter = +<logClient.cpp> 
-<logServer.cpp>` will exclude 
logServer.cpp.

## How to use - Raspberry Pi logger

The Raspberry Pi logger, in rpi_logger directory, runs continuously and stores messages received by the Pi (through the master node via serial connection) in a SQLite3 DB.  To run:

* Make sure master node is connected to Pi via USb using port `/dev/ttyUSB0`
* Make sure `meshlog.db` is created and initialize the schema with `schema.sql`
* Make sure you have all the dependencies:
    * sqlite3
    * libsqlite3-dev

Build using the following command:

`g++ -Wall main.cpp serialMonitor.cpp rs232.c -o a.out -std=c++11 -lsqlite3`

Run:

`./a.out`

### Attribution

* [Teuniz C RS-232 library](https://gitlab.com/Teuniz/RS-232)
* [nlohmann's C++ JSON library](https://github.com/nlohmann/json)
