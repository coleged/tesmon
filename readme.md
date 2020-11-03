
<h>October 2020</h>

A working project exploring the REST API to the Tesla Electric Car.

<h>Status:</h>
<bl>
<bi>Have  REST API  worked out.</bi>
<bi>23/10/20        Streaming API. Initiation handshake seems to be working, but no data streaming yet.</bi>
<bi>2/11/20          Much tidy up of classes. Now have wakeup working reliably. Still not managed to get
                            any streaming.</bi>

</bl>
Written in C++ it is informed by https://tesla-api.timdorr.com/ description of the Tesla API, and other insight plundered from bits of others code.

Dependencies are:

restclient-cpp
nlohmann/json
IXWebSocket

See Makefile and headers for details

Working dev/build system - xcode on Apple MacOS w/ C++11

Makefile included for standalone build

To build,

    install restclient-cpp
    install nlohmann/json
    install IXWebSocket
    Edit and rename secrets.hpp.tpl
    Make

