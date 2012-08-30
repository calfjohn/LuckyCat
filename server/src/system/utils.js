
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
         * 按配置得概率获取对应得值
         * @param probabilityCfg{total总概率, table{key,value}概率表
         * example:
         * var cfg = {
         *      total: 1,
         *      table: {
         *      "0.1":1,
         *      "0.2":2,
         *      "0.3":3,
         *      "0.4":4
         *      }
         * };
         * @return {*} 返回table中击中的key对应的value
         */
        randomNumber: function(probabilityCfg){
            var table = null;
            var total = 0;
            if (probabilityCfg.table) {
                table = probabilityCfg.table;
                if(!probabilityCfg.total){
                    for(var key in table){
                        total += parseFloat(key);
                    }
                }else{
                    total = probabilityCfg.total;
                }
            } else {
                table = probabilityCfg;
            }

            var seed = Math.random()*total;
            var guard = 0;
            for(var key in table){
                guard += parseFloat(key);
                if(seed < guard){
                    return table[key];
                }
            }
            throw new Error("Invalid argument!");
        }
    };
}


module.exports = global.serverUtils;