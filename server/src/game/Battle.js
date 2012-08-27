/**
 * Created with JetBrains WebStorm.
 * User: cocos2d
 * Date: 12-8-27
 * Time: 下午5:25
 * To change this template use File | Settings | File Templates.
 */
(function(){
    if (global.Battle) {
    module.exports = Battle;
    return;
}

require("../system/Log");

var log = new Log("Battle");
var actType = {
    ATTACK :1,//攻击
    CTRITICAL :2,// 爆击
    CRUSH : 3,//破防
    SUCK_BLOOD : 4,//吸血
    HURT :5,//受击
    DODGE : 6,//闪避
    REVERT :7,//反震
    DEAD : 8//死亡
}

Battle = {
    teamUp : function(data, teamdId) {
        var team = [];
        var member = {};
        member = data;
        member.hurt = member.hp;
        member.time = 1/member.speed;
        member.teamId = teamdId;
        team.push(member);
        return team;
    },

    whoIsFast: function(team){
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
    },

    whoIsDefender : function(teamX){
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
    },

    contructResult : function(team){
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
    },

    versus : function(attacker, defender, battleResult){
        //really simple, hurt = attack - defence
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
        tempPlayA.type = actType.ATTACK;
        tempPlayA.teamId = attacker.teamId;
        tempPlayA.actId = attacker.id;
        tempPlayA.skillId = -1;
        tempPlayA.hurt = 0;
        tempPlayA.fx = -1;
        battleResult.battleArray.playlist.push(tempPlayA);

        var tempPlayB = {};
        tempPlayB.type = actType.HURT;
        tempPlayB.teamId = defender.teamId;
        tempPlayB.actId = defender.id;
        tempPlayB.skillId = -1;
        tempPlayB.hurt = tempHurt;
        tempPlayB.fx = -1;
        battleResult.battleArray.playlist.push(tempPlayB);

        return defender.hurt == 0;//死没？
    },

    //设置队伍中每个角色的倒计时时间
    updateTime : function(team, attacker){
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
    },

    fight : function(team, callback) {
        //team.A The attacking side
        //team.B The defence side

        //遍历计算每个角色属性加成
        //遍历每个角色的速度，定出优先顺序
        //选择被攻击角色
        //被攻击角色是否闪避             //被攻击角色是否反震
        //攻击角色是否爆击
        //攻击，计算伤害值
        //更新相关角色属性
        //直到有一队全部死亡
        //否则下一个
        var battleResult = Battle.contructResult(team);
        while(true){
            var attacker = Battle.whoIsFast(team);
            var defender = Battle.whoIsDefender((attacker.teamId == "A")? team.B: team.A);
            if(Battle.versus(attacker, defender, battleResult))
            {
                battleResult.result.state = (defender.teamId == "A" ? 1: 0);
                battleResult.result.type = 3;
                break;
            }

            Battle.updateTime(team, attacker);
        }

        callback(battleResult);
    }
};

module.exports = Battle;
})();