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
        Log._outputLog(LogLevelDebug, this.tag, Array.prototype.slice.call(arguments), false);
    },

    w: function(msgs) {
        Log._outputLog(LogLevelWarning, this.tag, Array.prototype.slice.call(arguments), true);
    },

    e: function(msgs) {
        Log._outputLog(LogLevelError, this.tag, Array.prototype.slice.call(arguments), true);
    }
});

Log.CurrentLevel = LogLevelDebug;

Log._outputDebugString = function (str) {
    process.stdout.write(str, "utf8");
};
Log._outputWarningString = Log._outputDebugString;
Log._outputErrorString = Log._outputDebugString;

Log._outputLog = function(level, tag, msgArr, doTrace) {
    if (level < Log.CurrentLevel) return;
    var outputStringFunc = null;
    // translate level number to string.
    switch (level) {
        case LogLevelDebug: level = "debug";        outputStringFunc = Log._outputDebugString;          break;
        case LogLevelWarning: level = "warning";    outputStringFunc = Log._outputWarningString;    break;
        case LogLevelError: level = "error";        outputStringFunc = Log._outputErrorString;      break;
    }
    // output log header
    outputStringFunc(util.format("{\n    level: %s\n    time: %s\n    tag: %s\n    message: ", level, new Date().toLocaleTimeString(), tag));

    // output log message
    for (var i = 0; i < msgArr.length; ++i) {
        outputStringFunc(util.format(msgArr[i]));
        if (msgArr[i] instanceof Error) {
            outputStringFunc("\n");
            outputStringFunc(util.format(msgArr[i].stack));
        }
    }
    outputStringFunc("\n");

    // output log trace
    if (doTrace) {
        var err = new Error;
        err.name = 'Trace:';
        err.message = '';
        Error.captureStackTrace(err, arguments.callee);
        outputStringFunc(util.format(err.stack));
        outputStringFunc("\n");
    }

    // output log tail
    outputStringFunc("}\n");
};
