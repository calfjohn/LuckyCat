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
    ATTACK :1,//攻击 50%
    CTRITICAL1 :2,// 爆击 10% 1.5加成攻击
    CTRITICAL2 :3,// 爆击 10% 3倍加成攻击
    CRUSH : 3,//破防 10%
    SUCK_BLOOD1 : 5,//吸血 10% 吸伤害值的血量的50%
    SUCK_BLOOD2 : 6,//吸血 10% 吸伤害值的血量100%
    HURT :7,//受击 85%
    DODGE : 8,//闪避 10%
    REVERT :9//反震 5%
}

Battle = {
    teamUp : function(data, teamdId) {
        var team = [];
        var member = {};
        member = data;
        member.hpEx = member.hp;
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
        tempMember.hpEx= -1;
        //选择生命力最弱的
        for(var i = 0; i < teamX.length; i++){
            if(teamX[i].hpEx < tempMember.hpEx || tempMember.hpEx == -1)
            {
                tempMember = teamX[i];
            }
        }

        return tempMember;
    },

    contructResult : function(team, fightType){
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
        battleResult.result.type = fightType;
        battleResult.result.state = 0;//1 success 0 failed

        return battleResult;
    },

    attakerAct: function(){
        var ret;
        var randomTemp =  Math.random();
        if(randomTemp < 0.5){
            ret = actType.ATTACK;
        }
        else if(randomTemp < 0.6){
            ret = actType.CTRITICAL1;
        }
        else if(randomTemp < 0.7){
            ret = actType.CTRITICAL2;
        }
        else if(randomTemp < 0.8){
            ret = actType.SUCK_BLOOD1;
        }
        else if(randomTemp < 0.9){
            ret = actType.SUCK_BLOOD1;
        }
        else{
            ret = actType.CRUSH;
        }

        return ret;
    },

    defenderAct: function(){
        var ret;
        var randomTemp =  Math.random();
        if(randomTemp < 0.85){
            ret = actType.HURT;
        }
        else if(randomTemp < 0.95){
            ret = actType.DODGE;
        }
        else{
            ret = actType.REVERT;
        }

        return ret;
    },

    versus : function(attacker, defender, battleResult){
        var round = [];
        battleResult.battleArray.playlist.push(round);
        //////////////////////////////////////////////
        var actionA = {};
        actionA.type = Battle.attakerAct();
        actionA.teamId = attacker.teamId;
        actionA.actId = attacker.id;
        actionA.skillId = -1;
        actionA.hurt = -1;
        actionA.fx = -1;
        round.push(actionA);

        var actionB = {};
        actionB.type = Battle.defenderAct();
        actionB.teamId = defender.teamId;
        actionB.actId = defender.id;
        actionB.skillId = -1;
        actionB.fx = -1;

//计算战斗伤害
        var tempAttack = attacker.attack;
        var tempDefence = defender.defence;
        switch(actionA.type)
        {
            case actType.CTRITICAL1:
                tempAttack *= 1.5;
                break;
            case actType.CTRITICAL2:
                tempAttack *= 1.5;
                break;
            case actType.CRUSH:
                tempDefence = 0;
                break;
            case actType.ATTACK:
            case actType.SUCK_BLOOD1:
            case actType.SUCK_BLOOD2:
            default :
                break;
        }

        //really simple, hurt = attack - defence
        var tempHurt = tempAttack - tempDefence;
        if(tempHurt < 0){
            tempHurt = 1;
        }

        var tempRevertHurt = 0;
        switch(actionB.type)
        {
            case actType.DODGE:
                tempHurt = 0;
                break;
            case actType.REVERT:
                tempRevertHurt = tempHurt*0.05;
                tempHurt = 0;
                break;
            case actType.HURT:
            default :
                break;
        }

        //处理吸血的特殊流程
        var tempSuckBlood = 0;
        switch(actionA.type)
        {
            case actType.SUCK_BLOOD1:
                tempSuckBlood = tempHurt*0.5;
                break;
            case actType.SUCK_BLOOD2:
                tempSuckBlood = tempHurt;
                break;
            default :
                break;
        }

        attacker.hpEx += tempSuckBlood;
        if(attacker.hpEx > attacker.life)
        {
            attacker.hpEx = attacker.hp;
        }
        attacker.hpEx -= tempRevertHurt;
        if(attacker.hpEx < 0)
        {
            attacker.hpEx = 0;
        }

        defender.hpEx = defender.hpEx - tempHurt;
        if(defender.hpEx < 0)
        {
            defender.hpEx = 0;
        }

        actionB.hurt = tempHurt;
        round.push(actionB);
//////////////////////////////////////////////

        if(actionA.type == actType.SUCK_BLOOD1 || actionA.type == actType.SUCK_BLOOD2){
            var action = {};
            action.type = actionA.type;
            action.teamId = attacker.teamId;
            action.actId = attacker.id;
            action.skillId = -1;
            action.hurt = tempSuckBlood;
            action.fx = -1;
            round.push(action);
        }
        else if(actionB.type == actType.REVERT){
            var action = {};
            action.type = actType.REVERT;
            action.teamId = attacker.teamId;
            action.actId = attacker.id;
            action.skillId = -1;
            action.hurt = tempRevertHurt;
            action.fx = -1;
            round.push(action);
        }

        return defender.hpEx == 0 || attacker.hpEx == 0;//死没？
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

    fight : function(team, callback, fightType) {
        //team.A The attacking side
        //team.B The defence side

        //遍历计算每个角色属性加成
        //遍历每个角色的速度，定出优先顺序
        //选择被攻击角色
        //战斗，计算伤害值（被攻击角色是否闪避、反震、爆击）
        //直到有一队全部死亡
        //否则更新相关角色属性
        //循环
        var battleResult = Battle.contructResult(team, fightType);
        while(true){
            var attacker = Battle.whoIsFast(team);
            var defender = Battle.whoIsDefender((attacker.teamId == "A")? team.B: team.A);
            if(Battle.versus(attacker, defender, battleResult))
            {
                //战斗结束
                battleResult.result.state = (defender.hpEx == 0 ? 1: 0);
                battleResult.result.type = fightType;
                break;
            }

            Battle.updateTime(team, attacker);
        }

        callback(battleResult);
    }
};

module.exports = Battle;
})();