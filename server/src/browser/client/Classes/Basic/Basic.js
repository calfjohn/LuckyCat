var lc = lc = lc || {};

lc.platfrom = function(){
    var obj = new Object();
    obj.desktop = "desktop";
    obj.mobile = "mobile";

    return obj;
};

//a page is a game level
lc.stPage = function (){
    var obj = new Object();
    
    obj.id = 0;                     //index of page
    obj.name = 0;                   //page's titlecontent;
    obj.content = "";               //page's content
    obj.image_id = 0;                //page's image
    obj.event_id = 0;                //page's event
    obj.position = cc.PointZero();  //position on page map
    obj.postion_x = 0;
    obj.postion_y = 0;
    obj.state = 0;                  //fight result 0:new 1:success 2: failed
    obj.image = "";                 //the background of page
    obj.end = false;                //is last page of chapter

    return obj;
};

//a chapter consist lot of page
lc.stChapter = function (){
    var obj = new Object();

    obj.id = 0;                         //index of chapter
    obj.bible_id = 0;
    obj.name = "";                      //chapter's title
    obj.image_id = 0;                    //chapter's image
    obj.position = cc.PointZero();      //position on chapter scene
    obj.position_x = 0;
    obj.position_y = 0;
    obj.listPage = new Array();         //a set of pages in chapter

    return obj;
};

//a bible consist lot of stChapter
lc.stBible = function () {
    var obj = new Object();

    obj.id = 0;                         //index of bible
    obj.name = "";                      //bible name
    obj.bg_id = 0;                       //bible background image
    obj.chapter_bg_id = 0;                //chapter background image
    obj.listChapter = new Array();

    return obj;
};

lc.stMonster = function () {
    var obj = new Object();

    obj.id = 0;                 //monster id
    obj.name = "";              //monster name
    obj.image_id = 0;            //monster image id
    obj.rank = 0;               //rank of monster
    obj.career_id = 0;

    return obj;
};

lc.stImage = function () {
    var obj = new Object();

    obj.id = 0;
    obj.type = 0;
    obj.name = "";
    obj.file_path = "";
    obj.plist_path = "";
    obj.description = "";

    return obj;
};

lc.stGood = function () {
    var obj = new Object();

    obj.id = 0;
    obj.count = 0;
    obj.type = 0;

    return obj;
};

lc.stActorLevelUpgrade = function () {
    var obj = new Object();

    obj.level = 0;                  //level of actor
    obj.xp = 0;
    obj.attack = 0;
    obj.defence = 0;
    obj.life = 0;
    obj.speed = 0;
    obj.title = "";                 //title of notification
    obj.content = "";               //content of notification
    obj.bonus = new Array();        //bouns of level upgrade reaward

    return obj;
};

lc.stActorEquipInfo = function () {
    var obj = new Object();

    obj.id = 0;             //equipId
    obj.name = "";          //equipName
    obj.image_id = 0;       //equipImageId
    obj.class = 0;          //equipType
    obj.life = 0;           //equipLife
    obj.level_limit = 0;   //equipLevelLimit
    obj.attack = 0;         //equipAttack
    obj.defence = 0;        //equipDefence
    obj.speed = 0;          //equipSpeed
    obj.description = "";   //equipDescription

    return obj;
};

lc.stActorUserEquipInfo = function () {
    var obj = new Object();
    obj.userPutOn = false;
    obj.userListId = 0;
    obj.userEquipId = 0;
    obj.userEquipType = 0;
    obj.equipInfo = null;

    return obj;
};

lc.stActorUserInfo = function () {
    var obj = new Object();
    obj.userUuid = 0;
    obj.userNickName = "";
    obj.userImageId = 0;
    obj.userLevel = 0;
    obj.userExp = 0;
    obj.userHp = 0;
    obj.userCareerId = 0;
    obj.userChapterId = 0;
    obj.userPageId = 0;
    obj.userAttack = 0;
    obj.userDefence = 0;
    obj.userSpeed = 0;
    obj.userMaxHp = 0;

    return obj;
};

lc.stEvent = function () {
    var obj = new Object();
    obj.id = 0;
    obj.targetId = 0;

    return obj;
};

lc.stPKInfo = function () {
    var obj = new Object();
    obj.pkUserId = 0;
    obj.pkUserNickName = 0;
    obj.pkUserLevel = 0;

    return obj;
};