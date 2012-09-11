/**
 * Created with JetBrains WebStorm.
 * User: cocos2d
 * Date: 12-9-6
 * Time: 下午5:22
 * To change this template use File | Settings | File Templates.
 */
require("../DictManager");
require("../../system/Log");

module.exports.handler = function (req, res, next) {
    var dictEquipment = JSON.stringify(DictManager._cacheEquipment);
    var out = "var dictEquipment = JSON.parse('"+dictEquipment+"');";
    console.log(dictEquipment);
    res.end(out);
};