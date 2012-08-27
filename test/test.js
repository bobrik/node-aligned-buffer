(function() {
    var assert  = require("assert"),
        aligned = require("../index.js");

    (function testFree() {
        var size   = 1024 * 64,
            buffer = aligned.buffer(aligned.alignment(), size),
            i      = 0;

        for (; i < buffer.length; i++) {
            buffer[i] = i % 10;
        }

        assert.equal(i, size);
    })();

    (function testThrows() {
        try {
            aligned.buffer(aligned.alignment() - 1, 1024);
        } catch (e) {
            return;
        }

        assert.ok(false);
    })();
})(module);
