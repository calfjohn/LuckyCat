/**
 * Created with JetBrains WebStorm.
 * User: cocos2d
 * Date: 12-8-16
 * Time: 上午9:47
 * To change this template use File | Settings | File Templates.
 */

require("../../system/Log");

module.exports = function (req, res, next) {
    var log = new Log("battle.fight2");

    var chunks = [];
    req.on("data", function(chunk) {
        chunks.push(chunk);
    });

    req.on("end", function () {
        var info = JSON.parse(Buffer.concat(chunks));
        chunks = undefined;
        log.d("request:", info);

        var responseResult = function (ret) {
            var respData={};
            var out = ret;
            var header = info.header;
            var meta = info.meta;
            respData.header = header;
            respData.meta = meta;
            respData.meta.out = out;
            log.d("responseResult", respData);
            res.write(JSON.stringify(respData));
            res.end();
        };

        var whoIsFast = function(team){
            var teamId = -1;
            var attacker = {};
            attacker.time = -1;

            for(var i = 0; i < team.length; i++){
                var tempTeam = team[i];
                for(var j = 0; j < tempTeam.length; j++){
                    if(tempTeam[j].time < attacker.time || attacker.time == -1)
                    {
                        attacker = tempTeam[j];
                        teamId = i;
                    }
                }
            }

            var ret = {};
            ret.attacker = attacker;
            ret.teamId = teamId;
            return ret;
        };

        var whoIsDefender = function(teamId){
            var tempMember= {};
            tempMember.hurt = -1;
            //选择生命力最弱的
            for(var i = 0; i < team[teamId].length; i++){
                if(team[i].hurt < tempMember.hurt || tempMember.hurt == -1)
                {
                    tempMember = team[teamId][i];
                }
            }

            return tempMember;
        };

        var contructResult = function(team){
            var battleResult = {};
            battleResult.awardArray = {};
            battleResult.awardArray.gold = 0;
            battleResult.awardArray.exp = 0;
            battleResult.awardArray.item = [];

            battleResult.battleArray = {};
            battleResult.battleArray.playlist = [];
            battleResult.battleArray.team1Final = [];
            battleResult.battleArray.team1Fina2 = [];

            battleResult.team1 = [];
            battleResult.team2 = [];

            battleResult.result = {};
            battleResult.result.type = 0;
            battleResult.result.state = 0;

            return battleResult;
        };

        var versus = function(attacker, defender){
            var tempHurt = attacker.attack - defender.defence;
            if(tempHurt <= 0){
                tempHurt = 1;
            }
            defender.hurt = defender.hurt - tempHurt;
            if(defender.hurt < 0)
            {
                defender.hurt = 0;
            }

            return defender.hurt == 0;//死没？
        };

        var updateTime = function(team, attacker, teamId){
            var time = attacker.time;
            for(var i = 0; i < team.length; i++){
                var tempTeam = team[i];
                for(var j = 0; j < tempTeam.length; j++){
                    if(tempTeam[j].id == attacker.id && i == teamId)
                    {
                        tempTeam[j].time = 1/tempTeam[j].speed;
                    }
                    else
                    {
                        tempTeam[j].time -= time;
                    }
                }
            }
        }

        var fight  = function(team) {
            //team1 The attacking side
            //team2 The defence side

            //遍历计算每个角色属性加成
            //遍历每个角色的速度，定出优先顺序
            //选择被攻击角色
            //被攻击角色是否闪避
            //被攻击角色是否反震
            //攻击角色是否爆击
            //攻击，计算伤害值
            //更新相关角色属性
            //直到有一队全部死亡
            //否则下一个
            var battleResult;
            while(true){
                var ret = whoIsFast(team);
                var attacker = ret.attacker;
                var teamId = ret.teamId;
                var defender = whoIsDefender((teamId)? 0: 1);//only two team, one is 0, the orther is 1
                if(versus(attacker, defender))
                {
                    break;
                }

                updateTime(team, attacker, teamId);
            }

            responseResult(contructResult(team));
        };

        var teamUp1 = function(data) {
            var team = [];
            var member = {};

            member.id = data.id;
            member.imageId = data.image_id;
            member.level = data.level;
            member.name = data.nickname;
            member.equip = [];
            member.skill = [];
            member.hp = data.hp;
            member.hurt = member.hp;
            member.speed = 200;
            member.time = 1/member.speed;
            member.attack = 500;
            member.defence = 800;

            team.push(member);
            return team;
        };

        var teamUp2 = function(data) {
            var team = [];
            var member = {};

            member.id = data.id;
            member.imageId = data.image_id;
            member.level = data.level;
            member.name = data.name;
            member.equip = [];
            member.skill = [];
            member.hp = 8000;
            member.hurt = member.hp;
            member.speed = 150;
            member.time = 1/member.speed;
            member.attack = 800;
            member.defence = 1000;

            team.push(member);
            return team;
        };


        if (info) {
            //receive input parameter
            var uuid = parseInt(info.header.token);
            var actor = require("../Actors").getActorFromCache(uuid);

            // test code, 组装成队伍战斗
            var monsterId = parseInt(info.meta.in.monsterId);
            var monster = require("../Monster").getMonster(monsterId);

            var team = [];
            team.push(teamUp1(actor));
            team.push(teamUp2(monster));
            fight(team);
        } else {
            next();
        }

    });
};