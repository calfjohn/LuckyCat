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
            var teamX = [];
            var attacker = {};
            attacker.time = -1;

            for(var i = 0; i < team.A.length; i++){
                if(team.A[i].time < attacker.time || attacker.time == -1){
                    attacker = team.A[i];
                    teamX = team.A;
                    }
            }

            for(var i = 0; i < team.B.length; i++){
                if(team.B[i].time < attacker.time || attacker.time == -1){
                    attacker = team.B[i];
                    teamX = team.B;
                }
            }

            //返回攻击者以及所属队伍
            return attacker;
        };

        var whoIsDefender = function(teamX){
            var tempMember= {};
            tempMember.hurt = -1;
            //选择生命力最弱的
            for(var i = 0; i < teamX.length; i++){
                if(teamX[i].hurt < tempMember.hurt || tempMember.hurt == -1)
                {
                    tempMember = teamX[i];
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
            battleResult.battleArray.team = team;

            battleResult.team = team;

            battleResult.result = {};
            battleResult.result.type = 0;
            battleResult.result.state = 0;

            return battleResult;
        };

        var versus = function(attacker, defender, battleResult){
            var tempHurt = attacker.attack - defender.defence;
            if(tempHurt <= 0){
                tempHurt = 1;
            }
            defender.hurt = defender.hurt - tempHurt;
            if(defender.hurt < 0)
            {
                defender.hurt = 0;
            }

            var tempPlayA = {};
            tempPlayA.type = 1;  //攻击
            tempPlayA.teamId = attacker.teamId;
            tempPlayA.actId = attacker.id;
            tempPlayA.skillId = -1;
            tempPlayA.hurt = 0;
            tempPlayA.fx = -1;
            battleResult.battleArray.playlist.push(tempPlayA);

            var tempPlayB = {};
            tempPlayB.type = 2;  //防守
            tempPlayB.teamId = defender.teamId;
            tempPlayB.actId = defender.id;
            tempPlayB.skillId = -1;
            tempPlayB.hurt = tempHurt;
            tempPlayB.fx = -1;
            battleResult.battleArray.playlist.push(tempPlayB);

            return defender.hurt == 0;//死没？
        };

        //设置队伍中每个角色的倒计时时间
        var updateTime = function(team, attacker){
            var time = attacker.time;
            var team1 = (attacker.teamId == "A")? team.A: team.B;

            for(var i = 0; i < team1.length; i++){
                if(team1[i].id == attacker.id)
                {
                    team1[i].time = 1/team1[i].speed;
                }
                else
                {
                    team1[i].time -= time;
                }
            }

            var team2 = (attacker.teamId == "A")? team.B: team.A;
            //the other team
            for(var i = 0; i < team2.length; i++){
                team2[i].time -= time;
            }
        }

        var fight  = function(team) {
            //team.A The attacking side
            //team.B The defence side

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
            var battleResult = contructResult(team);
            while(true){
                var attacker = whoIsFast(team);
                var defender = whoIsDefender((attacker.teamId == "A")? team.B: team.A);
                if(versus(attacker, defender, battleResult))
                {

                    break;
                }

                updateTime(team, attacker);
            }

            responseResult(battleResult);
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
            member.attack = 5000;
            member.defence = 3000;
            member.teamId = "A";

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
            member.attack = 6500;
            member.defence = 4000;
            member.teamId = "B";

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

            var team = {};
            team.A = teamUp1(actor);
            team.B = teamUp2(monster);
            fight(team);
        } else {
            next();
        }

    });
};