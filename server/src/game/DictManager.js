/**
 * Created with JetBrains WebStorm.
 * User: lihex
 * Date: 12-8-16
 * Time: 下午12:07
 * To change this template use File | Settings | File Templates.
 */
(function(){
if (global.DictManager) {
    module.exports = DictManager;
    return 0;
}
require("../system/DBAgent");
require("../system/Log");
require("./Actor");

var log = new Log("DictManager");
var util = require("util");

DictManager = {
    _dbAgent : null,
    _cacheEquipment: null,
    _cacheCareer:null,
    _cacheMonster:null,
    _cacheLevel:null,
    _cacheEquipmentLevelGrowth: null,
    _cacheEquipmentRankGrowth: null,
    _cacheActorLevelUpgrade: null,
    _cacheSkill: null,
    _cacheEvent: null,
    _cacheNpcDialog: null,
    _cacheImage: null,
    _cacheBible: null,
    _cacheChapter: null,
    _cachePage: null,
    initInstance:function (dbConfig, callback) {
        DictManager._dbAgent = new DBAgent(dbConfig);
        DictManager._dbAgent.connect(true);

        var getEquipData = function(err, rows){
            if (! err) {
                DictManager._cacheEquipment = {};
                for(var i = 0; i < rows.length; ++i){
                    var data = rows[i];
                    var id= "" + data.id;
                    DictManager._cacheEquipment[id] = data;
                }
            }
        };

        var getCareerData = function(err, rows){
            if (! err) {
                DictManager._cacheCareer = {};
                for(var i = 0; i < rows.length; ++i){
                    var data = rows[i];
                    var id= "" + data.id;
                    DictManager._cacheCareer[id] = data;
                }
            }
        };

        var getMonsterData = function(err, rows){
            if (! err) {
                DictManager._cacheMonster = {};
                for(var i = 0; i < rows.length; ++i){
                    var data = rows[i];
                    var id= "" + data.id;
                    DictManager._cacheMonster[id] = data;
                }
            }
        };

        var getLevelData = function(err, rows){
            if (!err) {
                DictManager._cacheLevel = {};
                for(var i = 0; i < rows.length; ++i){
                    var data = rows[i];
                    var strID = "" + data.id + "-" + data.chapter_id;
                    DictManager._cacheLevel[strID] = data;
                }
            }
        };


        var getEquipmentLevelGrowth = function(err, rows){
            if (! err) {
                DictManager._cacheEquipmentLevelGrowth = {};
                for(var i = 0; i < rows.length; ++i){
                    var data = rows[i];
                    var level= "" + data.level;
                    DictManager._cacheEquipmentLevelGrowth[level] = data;
                }
            }
        };

        var getEquipmentRankGrowth = function(err, rows){
            if (! err) {
                DictManager._cacheEquipmentRankGrowth = {};
                for(var i = 0; i < rows.length; ++i){
                    var data = rows[i];
                    var rank = "" + data.rank;
                    DictManager._cacheEquipmentRankGrowth[rank] = data;
                }
            }
        };

        var getActorLevelUpgrade = function(err, rows){
            if (! err) {
                DictManager._cacheActorLevelUpgrade = {};
                for(var i = 0; i < rows.length; ++i){
                    var data = rows[i];
                    var level = "" + data.level;
                    DictManager._cacheActorLevelUpgrade[level] = data;
                }
            }
        };

        var getEvent = function(err, rows){
            if(!err){
                DictManager._cacheEvent = {};
                for(var i = 0; i < rows.length; ++i){
                    var data = rows[i];
                    var id = "" + data.id;
                    DictManager._cacheEvent[id] = data;
                }
            }
        };

        var getImage = function(err, rows){
            if(!err){
                DictManager._cacheImage = {};
                for(var i = 0; i < rows.length; ++i){
                    var data = rows[i];
                    var id = "" + data.id;
                    DictManager._cacheImage[id] = data;
                }
            }
        };

        var getBible = function(err, rows){
            if(!err){
                DictManager._cacheBible = {};
                for(var i = 0; i < rows.length; ++i){
                    var data = rows[i];
                    var id = "" + data.id;
                    DictManager._cacheBible[id] = data;
                }
            }
        };

        var getChapter = function(err, rows){
            if(!err){
                DictManager._cacheChapter = {};
                for(var i = 0; i < rows.length; ++i){
                    var data = rows[i];
                    var id = "" + data.id;
                    DictManager._cacheChapter[id] = data;
                }
            }
        };

        var getPage = function(err, rows){
            if(!err){
                DictManager._cachePage = {};
                for(var i = 0; i < rows.length; ++i){
                    var data = rows[i];
                    var id = "" + data.id;
                    DictManager._cachePage[id] = data;
                }
            }
        };

        var getNpcDialog = function(err, rows){
            if(!err){
                DictManager._cacheNpcDialog = {};
                for(var i = 0; i < rows.length; ++i){
                    var data = rows[i];
                    var id = "" + data.id;
                    DictManager._cacheNpcDialog[id] = data;
                }
            }
        };

        var getSkill = function(err, rows){
            if(!err){
                DictManager._cacheSkill = {};
                for(var i = 0; i < rows.length; ++i){
                    var data = rows[i];
                    var id = "" + data.id;
                    DictManager._cacheSkill[id] = data;
                }
            }
        };

        var dictToFiles = function() {
            var fs = require('fs');
            //var filePath = process.cwd() + '/server/src/game/www/database/';
            console.log(__dirname);
            var filePath = __dirname + '/../browser/client/Resources/database/';

            var dictEquipment = JSON.stringify(DictManager._cacheEquipment);
            fs.writeFile(filePath + 'dictEquipment.txt', dictEquipment,function(err){
                if(err) throw err;
                console.log('has finished');
            });

            var dictCareer = JSON.stringify(DictManager._cacheCareer);
            fs.writeFile(filePath + 'dictCareer.txt', dictCareer,function(err){
                if(err) throw err;
                console.log('has finished');
            });

            var dictMonster = JSON.stringify(DictManager._cacheMonster);
            fs.writeFile(filePath + 'dictMonster.txt', dictMonster,function(err){
                if(err) throw err;
                console.log('has finished');
            });

            var dictLevel= JSON.stringify(DictManager._cacheLevel);
            fs.writeFile(filePath + 'dictLevel.txt', dictLevel,function(err){
                if(err) throw err;
                console.log('has finished');
            });

            var dictEquipmentLevelGrowth = JSON.stringify(DictManager._cacheEquipmentLevelGrowth);
            fs.writeFile(filePath + 'dictEquipmentLevelGrowth.txt', dictEquipmentLevelGrowth,function(err){
                if(err) throw err;
                console.log('has finished');
            });

            var dictEquipmentRankGrowth = JSON.stringify(DictManager._cacheEquipmentRankGrowth);
            fs.writeFile(filePath + 'dictEquipmentRankGrowth.txt', dictEquipmentRankGrowth,function(err){
                if(err) throw err;
                console.log('has finished');
            });

            var dictActorLevelUpgrade = JSON.stringify(DictManager._cacheActorLevelUpgrade);
            fs.writeFile(filePath + 'dictActorLevelUpgrade.txt', dictActorLevelUpgrade,function(err){
                if(err) throw err;
                console.log('has finished');
            });

            var dictSkill = JSON.stringify(DictManager._cacheSkill);
            fs.writeFile(filePath + 'dictSkill.txt', dictSkill,function(err){
                if(err) throw err;
                console.log('has finished');
            });

            var dictEvent = JSON.stringify(DictManager._cacheEvent);
            fs.writeFile(filePath + 'dictEvent.txt', dictEvent,function(err){
                if(err) throw err;
                console.log('dictEvent has finished');
            });

            var dictNpcDialog = JSON.stringify(DictManager._cacheNpcDialog);
            fs.writeFile(filePath + 'dictNpcDialog.txt', dictNpcDialog,function(err){
                if(err) throw err;
                console.log('dictNpcDialog has finished');
            });

            var dictImage = JSON.stringify(DictManager._cacheImage);
            fs.writeFile(filePath + 'dictImage.txt', dictImage,function(err){
                if(err) throw err;
                console.log('dictImage has finished');
            });

            var dictBible = JSON.stringify(DictManager._cacheBible);
            fs.writeFile(filePath + 'dictBible.txt', dictBible,function(err){
                if(err) throw err;
                console.log('dictBible has finished');
            });

            var dictChapter = JSON.stringify(DictManager._cacheChapter);
            fs.writeFile(filePath + 'dictChapter.txt', dictChapter,function(err){
                if(err) throw err;
                console.log('dictChapter has finished');
            });

            var dictPage = JSON.stringify(DictManager._cachePage);
            fs.writeFile(filePath + 'dictPage.txt', dictPage,function(err){
                if(err) throw err;
                console.log('dictPage has finished');
            });
        };


        // Cache all equipment data on server start
        // second, do query operation for get data from db, thus cache all actors data on server start
        // step 1, query actor data
        DictManager._dbAgent.query("SELECT * FROM `dict_equipment`", function (err, rows) {
            // step 1 done, cache actor data
            getEquipData(err, rows);
            // step 2, query actor_equipment data
            DictManager._dbAgent.query("SELECT * FROM `dict_career`", function (err, rows) {
                // step 2 done, cache actor_equipment data
                getCareerData(err, rows);
                DictManager._dbAgent.query("SELECT * FROM `dict_monster`", function (err, rows) {
                    getMonsterData(err, rows);
                    DictManager._dbAgent.query("SELECT * FROM `dict_equipment_level_growth`", function (err, rows) {
                        getEquipmentLevelGrowth(err, rows);
                        DictManager._dbAgent.query("SELECT * FROM `dict_equipment_rank_growth`", function (err, rows) {
                            getEquipmentRankGrowth(err, rows);
                            DictManager._dbAgent.query("SELECT * FROM `dict_page`", function (err, rows) {
                                getLevelData(err, rows);
                                DictManager._dbAgent.query("SELECT * FROM `dict_actor_level_upgrade`", function (err, rows) {
                                    getActorLevelUpgrade(err, rows);
                                    DictManager._dbAgent.query("SELECT * FROM `dict_skill`", function (err, rows) {
                                        getSkill(err, rows);
                                        DictManager._dbAgent.query("SELECT * FROM `dict_event`", function (err, rows) {
                                            getEvent(err, rows);
                                            DictManager._dbAgent.query("SELECT * FROM `dict_npc_talk`", function (err, rows) {
                                                getNpcDialog(err, rows);
                                                DictManager._dbAgent.query("SELECT * FROM `dict_image`", function (err, rows) {
                                                    getImage(err, rows);
                                                    DictManager._dbAgent.query("SELECT * FROM `dict_bible`", function (err, rows) {
                                                        getBible(err, rows);
                                                        DictManager._dbAgent.query("SELECT * FROM `dict_chapter`", function (err, rows) {
                                                            getChapter(err, rows);
                                                            DictManager._dbAgent.query("SELECT * FROM `dict_page`", function (err, rows) {
                                                                getPage(err, rows);
                                                                // all data cached, call callback
                                                                dictToFiles();
                                                                callback(err);
                                                            });
                                                        });
                                                    });
                                                });
                                            });
                                        });
                                    });
                                });
                            });

                        });

                    });

                });
            });
        });
    },

    getEquipmentByID: function(id) {
        //get a actor basic info by uuid
        var equipment = DictManager._cacheEquipment[""+id];
        if(undefined == equipment){
            equipment = null;
        }
        return equipment;
    },

    getMonsterById: function(id) {
        var monster = DictManager._cacheMonster["" + id];
        if (monster)
        {
            return monster;
        }
        else
        {
            return null;
        }
    },


    getCareerByID: function(id) {
        //get a Creer basic info by id
        var career = DictManager._cacheCareer[""+id];
        if(undefined == career){
            career = null;
        }

        return career;
    },

    getLevel: function(chapterId, pageId) {
        var strID = "" + pageId + "-" + chapterId;
        var level =  DictManager._cacheLevel[strID];
        if(undefined == level){
            level = null;
        }

        return level;
    },

    getEquipLevelGrowthByLevel: function(level){
        //get a Growth  by level
        var growth = DictManager._cacheEquipmentLevelGrowth[""+level];
        if(undefined == growth){
            growth = null;
        }

        return growth;
    },

    getEquipRankGrowthByRank: function(rank){
        //get a Growth by rank
        var growth = DictManager._cacheEquipmentRankGrowth[""+rank];
        if(undefined == growth){
            growth = null;
        }

        return growth;
    },

    getActorLevelUpgradeByLevel: function(level){
        //get actor level upgrade by level
        var ret = DictManager._cacheActorLevelUpgrade[""+level];
        if(undefined == ret){
            ret = null;
        }
        return ret;
    },

    getSkillByID: function(id){
        var ret = DictManager._cacheSkill["" + id];
        if(undefined == ret){
            ret = null;
        }
        return ret;
    }
};

    module.exports = DictManager;
})();
