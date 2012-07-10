/* helper for logger. */

require("./Class");

var util = require("util");

LogLevelDebug = 10;
LogLevelWarning = 20;
LogLevelError = 30;

Log = Class.extend({
    tag: "Log",

    init: function (newTag) {
        if (arguments.length == 1) {
            this.tag = newTag;
        }
    },

    d: function(msgs) {
        _outputLog(LogLevelDebug, this.tag, Array.prototype.slice.call(arguments), false);
    },

    w: function(msgs) {
        _outputLog(LogLevelWarning, this.tag, Array.prototype.slice.call(arguments), true);
    },

    e: function(msgs) {
        _outputLog(LogLevelError, this.tag, Array.prototype.slice.call(arguments), true);
    }
});

Log.CurrentLevel = LogLevelDebug;

var _outputLog = function(level, tag, msgArr, doTrace) {
    if (level < Log.CurrentLevel) return;

    // translate level number to string.
    switch (level) {
        case LogLevelDebug:
            level = "debug";
            break;
        case LogLevelWarning:
            level = "warning";
            break;
        case LogLevelError:
            level = "error";
            break;
    }

    // output log info in format.
    for (var i = 0; i < msgArr.length; ++i) {
        msgArr[i] = util.format(msgArr[i]).replace(/\n[ ]*/g, " ");
    }
    var logHeader = {
        level: level,
        time: new Date().toLocaleTimeString(),
        tag: tag,
        message: msgArr.join("")
    };
    if (doTrace) {
        console.trace(util.inspect(logHeader));
    } else {
        console.log(logHeader);
    }
};