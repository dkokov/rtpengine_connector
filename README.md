## <u>rtpengine_connector</u>

A <b>rtpengine_connector</b> is a small C library which is done rtpengine connectivity.
The rtpengine is a project by [SIP:WISE](https://www.sipwise.com/). 
It's a free software. You can be found in [github](https://github.com/sipwise/rtpengine).

In the <b>rtpengine_connector</b> is implemented a part of [ng_control_protocol](https://github.com/sipwise/rtpengine/blob/master/docs/ng_control_protocol.md) .
It's based on [bencode](https://en.wikipedia.org/wiki/Bencode) and it's transporting over UDP.


##### <u>Installation </u>

``` bash
cd /usr/src/

https://github.com/dkokov/rtpengine_connector.git

cd rtpengine_connector/src

make

make install
```


##### <u>Test console tool</u>

``` bash
./rtpengine_connector_cli 127.0.0.1 2223 ping|offer|answer|delete
```

This tool is using only for tests. If you don't add options,it will add '127.0.0.1 2223 ping' options.

##### <u>How to use in your own code</u>

You can be reviewed a source code in 'cli/main.c' - my test console tool above. 
Use it as example how to use this C .

You have to include in your source code follow: 

``` C
#include "rtpcengc.h"

```

... and also when you compile you have to use **'-lrtpengc'**

``` bash
gcc -o main.c your_prog -lrtpengc
```