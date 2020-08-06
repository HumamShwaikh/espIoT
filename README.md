# Data from Home

Mesh network of IoT devices to sense and report environmental data.  Made using ESP8266, ESP32, PainlessMesh, and various sensors to measure temperature, humidity, ambient noise, vibration, and whatever else you want.

## Authors

* Ivor Benderavage - [@ivorysoap](github.com/ivorysoap)
* Humam Shwaikh - [@HumamShwaikh](github.com/HumamShwaikh)

### How to use - Raspberry Pi logger

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

## How to flash code to one of the ESP nodes

All the nodes run one of the following .cpp files:

* `logServer.cpp` - run by the 
central server.
* `logClient.cpp` - run by the 
nodes in the mesh.

### How to upload ONE of the .cpp files to a board in PlatformIO?

In `platformio.ini`, you have to 
use the `src_filter` option to exclude and 
include the files to be built and 
uploaded.  For example, 
`src_filter = +<logClient.cpp> 
-<logServer.cpp>` will exclude 
logServer.cpp.



## Attribution

* [Painless Mesh](https://github.com/gmag11/painlessMesh)
* [Teuniz C RS-232 library](https://gitlab.com/Teuniz/RS-232)
* [nlohmann's C++ JSON library](https://github.com/nlohmann/json)
