
require("../../src/system/DBAgent");
require("../../src/system/Log");

var users = require("../../src/user/Users")
    , util = require("util")
    , log = new Log("Users")
    , assert = require("assert");

var dbName = "test_users";
var testUsersCfg = {
    host      : "192.168.0.51"
    , user      : "root"
    , password : "123456"
    , database   : dbName
    , recreate    : true
};

describe("=================================================================================\n" +
    "    Test Users", function() {

    var dbUsers;   // database connection for check result

    // first, create the test database
    before(function (done) {
        users.initInstance(testUsersCfg, function(err) {
            dbUsers = new DBAgent(testUsersCfg);
            dbUsers.connect(true);
            done();
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
