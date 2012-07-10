/* Test DB interface.
*   dbTest is a default database while mysql installed.
*/

require("../../src/system/DBAgent");
require("../../src/system/Log");

var assert = require("assert");
var util = require("util");
var log = new Log("DBAgent.test");

var dbTest = {
    host       : "localhost",
    user       : "root",
    password   : "99092026",
    database   : "world",
    debug       : false
};

describe("=================================================================================\n" +
    "    Test DBAgent", function(done) {
    it("query", function(done) {
        var testDB = new DBAgent(dbTest).connect();
        var queryCBCount = 0;
        var dbcb = function(err, results) {
            if (err) {
                done(err);
                return;
            }
            assert(results.length > 0);
            if (results.length <= 6) {
                log.d(results);
            }
            queryCBCount++;
            if (queryCBCount >= 3) {
                testDB.close();
                done();
            }
        };

        // Query all data in table city.
        testDB.query("SELECT * FROM city", dbcb);

        // Query one row which id = 1.
        testDB.query("SELECT * FROM city WHERE ID = ?", 1, dbcb);

        // Query several rows.
        testDB.query("SELECT * FROM city WHERE CountryCode = ? || CountryCode = ?", ["ABW", "AFG"], dbcb);
    });
});
