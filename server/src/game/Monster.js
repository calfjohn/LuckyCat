/**
 * Created with JetBrains WebStorm.
 * User: cocos2d
 * Date: 12-8-10
 * Time: 下午4:16
 * To change this template use File | Settings | File Templates.
 */
/**
 * Monster controller for cache、 sync with database.
 */
(function(){
    if (global.Monster) {
    module.exports = Monster;
    return;
}

require("../system/Log");
require("./DictManager");

var log = new Log("Monster");

Monster = {
    initInstance : function(callback) {
        Monster.caculateCapability();
        callback();
    },

    caculateCapability : function(){
        var monster = DictManager._cacheDictMonster;
        for (var key in monster) {
            var career = DictManager.getCareerByID(monster[key].career_id);
            monster[key].attack = career.attack*Math.pow(1 + career.attack_growth, monster[key].level) * monster[key].rank;
            monster[key].defence = career.defence*Math.pow(1 + career.defence_growth, monster[key].level) * monster[key].rank;
            monster[key].hp = career.life*Math.pow(1 + career.life_growth, monster[key].level) * monster[key].rank;
            monster[key].speed = career.speed*Math.pow(1 + career.speed_growth, monster[key].level) * monster[key].rank;
        }
    }
};

module.exports = Monster;
})();
