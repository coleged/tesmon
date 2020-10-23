
October 2020

A working project exploring the REST API to the Tesla Electric Car.

Status:
                            REST API  worked out.
  23/10/20          Streaming API. Initiation handshake seems to be working, but no data streaming seen yet.


Written in C++ it is informed by https://tesla-api.timdorr.com/ description of the Tesla API, and other insight plundered from bits of others code.

Dependencies are:

restclient-cpp
nlohmann/json

See Makefile for details

Working build system xcode on Apple MacOS w/ C++11

Makefile included for simple build

To build,

    install restclient-cpp
    install nlohmann/json
    Edit and rename secrets.hpp.tpl
    Make

