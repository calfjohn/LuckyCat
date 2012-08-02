/**
 * Config game server here.
 */

/*  Export database's config for DBAgent.
 Connection parameters formed like this:
 host: The hostname of the database you are connecting to. (Default: localhost)
 port: The port number to connect to. (Default: 3306)
 socketPath: The path to a unix domain socket to connect to. When used host and port are ignored.
 user: The MySQL user to authenticate as.
 password: The passqword of that MySQL user.
 database: Name of the database to use for this connection (Optional).
 charset: The charset for the connection. (Default: 'UTF8_GENERAL_CI')
 insecureAuth: Allow connecting to MySQL instances that ask for the old (insecure) authentication method. (Default: false)
 typeCast: Determines if column values should be converted to native JavaScript types. (Default: true)
 debug: Prints protocol details to stdout. (Default: false)
 multipleStatements: Allow multiple mysql statements per query. Be careful with this, it exposes you to SQL injection attacks. (Default: `false)
 */

module.exports = {
        db_actors  : {
          host      : "192.168.0.51"
        , user      : "root"
        , password : "123456"
        , database : "db_luckycat"
        , recreate  : true              // recreate the database on database server
    }
}
