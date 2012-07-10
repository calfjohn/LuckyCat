require("../../src/system/Class");

var assert = require("assert");

describe("=================================================================================\n" +
    "    Test Class:", function(){
    describe("# extend", function(){

        it("should return -1 when the value is not present", function(){
            var Person = Class.extend({
                init: function(isDancing){
                    this.dancing = isDancing;
                },
                dance: function(){
                    return this.dancing;
                }
            });
            var Ninja = Person.extend({
                init: function(){
                    this._super( false );
                },
                dance: function(){
                    // Call the inherited version of dance()
                    return this._super();
                },
                swingSword: function(){
                    return true;
                }
            });
            console.log(p);
            var p = new Person(true);
            assert.equal(p.dance(), true, "should be true"); // => true
            var n = new Ninja();
            assert.equal(n.dance(), false); // => false
            assert.equal(n.swingSword(), true); // => true

            // Should all be true
            assert.equal(p instanceof Person && p instanceof Class &&
                n instanceof Ninja && n instanceof Person && n instanceof Class, true);

        });
    });
});
