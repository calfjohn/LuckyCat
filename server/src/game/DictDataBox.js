/**
 * Created with JetBrains WebStorm.
 * User: zhuxiaozhong
 * Date: 12-8-13
 * Time: 下午5:08
 * To change this template use File | Settings | File Templates.
 */

require("../system/DBAgent");
require("../system/Log");
require("./Actor");

DictBox = {
    _dbAgent : null,
    _mapBox : null,
    _mapBoxReward : null,
    initInstance : function(dbConfig, callback) {
        DictBox._dbAgent = new DBAgent(dbConfig);
        DictBox._dbAgent.connect(true);
        process.nextTick(function() {
            callback(null);
        });
    },

    queryDictBox : function ()
    {
        Actors._dbAgent.query("SELECT * FROM dict_box", [uuid], function (err, rows) {
            if (err) {
                throw err;
                return;
            }
            var len = rows.length;
            var data = (rows.length) ? rows[0]: null;
        });
    },

    queryDictBoxWard : function ()
    {
        Actors._dbAgent.query("SELECT * FROM dict_box", [uuid], function (err, rows) {
            if (err) {
                throw err;
                return;
            }
            var len = rows.length;
            var data = (rows.length) ? rows[0]: null;
        });
    },

    initDictData: function() {
        queryDictBox();
        queryDictBoxWard();
    },
    getBoxInfoById: function (boxId)
    {
        var tBox = _mapBox[boxId];
        return tBox;
    },
    getBoxRewardById : function (rewardId)
    {

    },
    getBoxReward: function (tBox)
    {
        //
    }

};
