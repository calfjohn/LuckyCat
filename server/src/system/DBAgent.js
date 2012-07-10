require("./Class");
require("./Log");

var log = new Log("DBAgent");

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
    _connection:null,                   getConnection: function() { return _connection; },
    _config:     null,                  getConfig: function() { return _config;},

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

    connect: function() {
        if (null == this._connection) {
            this._connection = require("mysql").createClient(this._config);
        }
        return this;
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

    close: function() {
        if (null != this._connection) {
            this._connection.end();
            this._connection = null;
        } else {
            log.w("function close call when connection is null.");
        }
    }
});
/*
function DBAgentQuery(response) {
    if (typeof (_connection) === "undefined") {
        _connection = {

        });
    }
        _connection.query("SELECT * FROM city", function(result, rows) {
        if (result) {
            console.log("sql query error occoured!");
        } else {
            console.log("sql query success!\n");
            response.writeHead(200, {'Content-Type': "text/plain"});
            for(var i=0; i<rows.length; i++){
                response.write("{")
                for (key in rows[i]) {
                    response.write("    " + key + " : "+ rows[i][key]);
                }
                response.write("    }\n");
            }

            response.end("\n");
        }
    });
}
*/