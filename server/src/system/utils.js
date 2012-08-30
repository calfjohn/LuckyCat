
require("../system/Log");
var log = new Log("utils.serverUtils");

if (! global.serverUtils) {
    serverUtils = {
        // callback: fucntion(err, ip)
        getHostIP: function(callback) {
            var socket = require("net").createConnection(80, "www.aRandomWebSite.com");
            socket.on("connect", function() {
                callback(null, socket.address().address);
                socket.end();
            });
            socket.on("error", callback);
        },
        /**
         * 按配置得概率抽取对应值
         * @param probabilityCfg 概率表，格式[概率，对应值]
         * example:
         * var cfg = [
         * [10, 1],
         * [20, 2],
         * [30, 3],
         * [20, 4],
         * [10, 5],
         * [10, 6]
         * ];
         * @return {*} 返回对应值
         */
        randomPick: function(probabilityCfg){
            var total = 0;
            for (var i=0; i < probabilityCfg.length; i++) {
                total += probabilityCfg[i][0];
            }

            var seed = Math.random()*total;
            var guard = 0;
            for (var i = 0; i < probabilityCfg.length; i++) {
                guard += probabilityCfg[i][0];
                if(seed < guard){
                    return probabilityCfg[i][1];
                }
            }
        }
    };
}


module.exports = global.serverUtils;