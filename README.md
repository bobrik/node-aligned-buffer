# Aligned buffers for node.js

Aligned buffers will allow you to read data from disk much faster than you think you can.
For example, if you read 64k blocks from disk to aligned buffers, you may get 50% speed-up.

## Installation

Install it as usual from npm:

```
npm install aligned-buffer
```

## API

Require module:

```javascript
var aligned = require("aligned-buffer");
```

Getting alignment:

```javascript
var alignment = aligned.alignment();
```

Getting aligned buffer:

```javascript
var buf = aligned.buffer(/* alignment, don't change*/ aligned.alignment(), /* size */ 1024 * 64);
```

## Usage

You will need at least node-0.8.9 to support O_DIRECT flag.
If you want to use it with older node, you need to find out O_DIRECT
value by yourself (`fgrep O_DIRECT /usr/include` for linux).

```javascript
var fs        = require("fs"),
    aligned   = require("aligned-buffer"),
    constants = process.binding("constants"),
    fd        = fs.openSync("/my_big_file", constants.O_RDONLY | constants.O_DIRECT),
    size      = 64 * 1024, // 64k blocks
    buf       = aligned.buffer(aligned.alignment(), size),
    offset    = 0;

// offset should be aligned to buf.length,
// so allowed values are: 0, 64k, 128k, 172k
// if offset is not aligned you will receive no boost

fs.read(fd, buf, 0, buf.length, offset, function(error) {
    if (error) {
        console.log(error);
        return;
    }

    console.log("successful read!");
});
```

## Authors

* [Ian Babrou](https://github.com/bobrik)
