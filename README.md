# CourierCXX
##### v0.2.1 (23.10.2018)
C++ framework for standart operations simplification

### Requirements
[1] libevent-dev
[2] libpq-dev
[3] libpqxx-dev

### Documentation
To generate documentation, execute command:
$ doxygen config.doxygen
After generation it will be placed in /docs folder

#### module Logger
Contains simple logger with daemon-mode option

#### module Connector
Contains classes for communication though different interfaces

##### core
Base classes

##### serial port
Serial port class

##### i2c
I2C class

##### gpio
GPIO class

##### tcp
TCP class

#### module Util
Contains additional classes and functions
 