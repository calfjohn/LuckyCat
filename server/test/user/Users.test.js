
require("../../src/system/DBAgent");
require("../../src/system/Log");

var users = require("../../src/user/Users")
    , util = require("util")
    , log = new Log("Users")
    , assert = require("assert");

var dbName = "db_test_users";
var testUsersCfg = {
    dbConfig : {
            host       : "localhost"
        ,   user       : "root"
        ,   password   : "99092026"
        ,   database   : dbName
    },
    reCreateDB : true
};

describe("=================================================================================\n" +
    "    Test Users", function() {

    var dbUsers;   // database connection for check result

    // first, create the test database
    before(function (done) {
        require("../../src/user/UserServer").initInstance(testUsersCfg, function(err) {
            if (err) {
                done(err);
            } else {
                users.initInstance(testUsersCfg);
                dbUsers = new DBAgent(testUsersCfg.dbConfig);
                dbUsers.connect(true);
                done();
            }
        });
    });

    // last, drop the test database
    after(function(done) {
        dbUsers.query(util.format("DROP DATABASE `%s`", dbName), function(err) {
            if (err) {
                done(err);
            } else {
                dbUsers.close();
                done();
            }
        });
    });

    describe("# create user:", function() {
        it("create by udid", function(done) {
            var info = {};
            info["udid"] = "1234567890";
            users.createUser(info, function(uuid) {
                assert(uuid && uuid > 0);
                done();
            });
        });
    });

});
