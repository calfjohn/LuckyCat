require("./Class");
require("./Log");

var log     = new Log("DBAgent")
    , util  = require("util");

var cbDefault = function () {
    log.d("createDatabase return:", arguments);
}
/**
 * <p>
 *     The class is an agent for database query.<br/>
 *
 *     The database backend is mysql, the node module for it is "mysql".</br>
 * </p>
 * @class
 * @extends Class
 */
DBAgent = Class.extend({/** @lends DBAgent */
    _connection:null,                   getConnection: function() { return this._connection; },
    _config:     null,                  getConfig: function() { return this._config;},
    _database:  null,
    /**
     * Initializes a connection to database use specific config.
     * @param dbConfig
     * <p>
     *     Formed like this:</br>
     *     host: The hostname of the database you are connecting to. (Default: localhost)</br>
     *     port: The port number to connect to. (Default: 3306)</br>
     *     socketPath: The path to a unix domain socket to connect to. When used host and port are ignored.</br>
     *     user: The MySQL user to authenticate as.</br>
     *     password: The passqword of that MySQL user.</br>
     *     database: Name of the database to use for this connection (Optional).</br>
     *     charset: The charset for the connection. (Default: 'UTF8_GENERAL_CI')</br>
     *     insecureAuth: Allow connecting to MySQL instances that ask for the old (insecure) authentication method. (Default: false)</br>
     *     typeCast: Determines if column values should be converted to native JavaScript types. (Default: true)</br>
     *     debug: Prints protocol details to stdout. (Default: false)</br>
     *     multipleStatements: Allow multiple mysql statements per query. Be careful with this, it exposes you to SQL injection attacks. (Default: `false)</br>
     * </p>
     */
    init: function(dbConfig) {
        this._config = dbConfig;
    },

    connect: function(bCertainExisting) {
        do {
            if (this._connection) break;    // has establish connection yet
            if (this._config == null) throw new Error("Hasn't set database config yet.");
            // if database bCertainExisting, needn't call createDatabase to create it
            if (arguments.length != 1 || bCertainExisting === false) {
                // split database name in to other member
                var dbName = this._config["database"];
                if (dbName != undefined) {
                    delete this._config["database"];
                }
                this._database = dbName;
            }
            this._connection = require("mysql").createClient(this._config);
        } while (false);
        return this;
    },

    close: function() {
        if (null != this._connection) {
            this._connection.end();
            this._connection = null;
        } else {
            log.w("function close call when connection is null.");
        }
    },

    query: function(sqlCmd, sqlParams, callback) {
        if (arguments.length < 2 || arguments.length > 3 || typeof sqlCmd != "string") {
            throw new Error("function query receive error arguments!!");
        }
        // if sqlParams is function, the arguments is not have sqlParams.
        if (typeof sqlParams == "function") {
            callback = arguments[1];
            sqlParams = [];
        } else if (! Array.isArray(sqlParams)) {
            sqlParams = [arguments[1]];
        }
        log.d("doQuery: ", sqlCmd, " params: ", sqlParams);
        this._connection.query(sqlCmd, sqlParams, callback);
    },

    createDatabase: function(dbName, bReCreateIfExist, callback) {
        var name = this._database;
        var reCreate = false;
        var cb = cbDefault;
        for (var i = 0; i < arguments.length; ++i) {
            var arg = arguments[i];
            switch (typeof arg) {
                case "string"   : name = arg;       break;
                case "boolean"  : reCreate = arg;   break;
                case "function" : cb = arg;         break;
                default: throw new Error("Invalid arguments");
            }
        }
        if (null == name) {
            throw new Error("Invalid database name argument");
            return;
        } else {
            this._database = name;  // save the database name
        }
        var sqlCmds = [];
        if (reCreate) {
            sqlCmds[sqlCmds.length] = util.format("DROP DATABASE IF EXISTS `%s`", name);
        }
        sqlCmds[sqlCmds.length] = util.format("CREATE DATABASE IF NOT EXISTS `%s`", name);

        var conn = this._connection;
        var config = this._config;
        conn.query(sqlCmds.join(";"), function (err) {
            if (err) {
                cb.call(arguments);
            } else {
                // create database successful, use it.
                config["database"] = name;
                conn.query(util.format("USE `%s`", name), cb);
            }
        });
    }
});
