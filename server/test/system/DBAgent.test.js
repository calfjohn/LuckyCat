/* Test DB interface.
*   database world is a default database while mysql installed.
*   database test_dbagent is not exist in mysql.
*/

require("../../src/system/DBAgent");
require("../../src/system/Log");

var assert = require("assert")
    ,util = require("util")
    ,log = new Log("DBAgent.test");

var dbWorldCfg = {
    host       : "localhost",
    user       : "root",
    password   : "99092026",
    database   : "world",
    debug       : false
};

var dbTestDBAgentName = "test_dbagent";
var dbTestDBAgentCfg = {
    host       : "localhost",
    user       : "root",
    password   : "99092026",
    database   : dbTestDBAgentName,
    debug       : false
};

describe("=================================================================================\n" +
    "    Test DBAgent", function() {
    describe("# access the database `world` which already existed in mysql:", function() {
        it("query", function(done) {
            var dbWorld = new DBAgent(dbWorldCfg);
            dbWorld.connect(true);

            // Query all data in table city.
            dbWorld.query("SELECT * FROM city", function(err, results) {
                if (err) {
                    done(err);
                    return;
                }
                assert(results.length > 0);
            });

            // Query one row which id = 1.
            dbWorld.query("SELECT * FROM city WHERE ID = ?", 1, function(err, results) {
                if (err) {
                    done(err);
                    return;
                }
                assert(results.length > 0);
            });

            // Query several rows.
            dbWorld.query("SELECT * FROM city WHERE CountryCode = ? || CountryCode = ?", ["ABW", "AFG"], function(err, results) {
                if (err) {
                    done(err);
                    return;
                }
                assert(results.length > 0);
                dbWorld.close();
                done();
            });
        });
    });

    var dbTest = new DBAgent(dbTestDBAgentCfg).connect();

    describe(util.format("# create the database `%s` in mysql:", dbTestDBAgentName), function() {
        it ("create", function(done) {
            dbTest.createDatabase(true, function(err) {
                if (err) {
                    done(err)
                } else {
                    done();
                }
            });
        });
    });

    describe(util.format("# access the database `%s` in mysql:", dbTestDBAgentName),  function() {
        it("create table", function(done){
            dbTest.query("CREATE TABLE `a_test_table` (" +
                "intColumn      int," +
                "stringColumn   varchar(255)" +
            ") COMMENT 'this is a test table.'",
            function(err) {
                if (err) {
                    done(err);
                } else {
                    done();
                }
            })
        });
    });

    describe(util.format("# drop the database `%s` in mysql:", dbTestDBAgentName),  function() {
        it("drop", function(done) {
            dbTest.query(util.format("DROP DATABASE `%s`", dbTestDBAgentName), function(err) {
                if (err) {
                    done(err);
                } else {
                    dbTest.close();
                    done();
                }
            });
        });
    });
});
