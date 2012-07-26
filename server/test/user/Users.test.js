require("../../src/system/DBAgent");
require("../../src/system/Log");

var users = require("../../src/user/Users")
    , util = require("util")
    , log = new Log("Users");

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

    var dbUsers = new DBAgent(testUsersCfg.dbConfig);   // database connection for check result

    // first, create the test database
    before(function (done) {
        require("../../src/user/UserServer").initInstance(testUsersCfg, function(err) {
            if (err) {
                done(err);
            } else {
                dbUsers.connect(true);
                users.initInstance(testUsersCfg);
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
        it ("create by uuid", function(done) {
            //var uuid = users.createUser({"uuid":"1234567890"});
            done();
        });

    });

});
