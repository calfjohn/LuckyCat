var ModeRequestType = {
    kModeTask : 0,
    kModeEvent : 1,
    kModeActor : 2,
    kModeBox : 3,
    kModeBattle : 4,
    kModePK : 5

    //add more
};

var g_modNames = Array(
    "task",
    "event",
    "actor",
    "box",
    "battle",
    "pk"

    //add more
);

var DoRequestType = {
    kDoGetActorInfo:0,
    kDoOpenBox:1,
    kDoGetUserInfo:2,
    kDoFight1:3,
    kDoFight2:4,
    kDoFight3:5,
    kDoGetBasicInfo:6,
    kDoGetAllEquipment:7,
    kDoGetEquippedEquipment:8,
    kDoGetEventList:9,
    kDoChangeEquipmentInfo:10,
    kDoGetPKList:11

    //add more
};

var g_doNames = Array(
    "getActorInfo",
    "openBox",
    "getUserInfo",
    "fight1",
    "fight2",
    "fight3",
    "getBasicInfo",
    "getAllEquipment",
    "getEquippedEquipment",
    "getEventList",
    "changeEquipmentInfo",
    "getPKList"

    //add more
);

var g_url = Array(
    "actor/getActorInfo/",
    "box/openBox/",
    "getUserInfo/",
    "battle/fight1/",
    "battle/fight2/",
    "battle/fight3/",
    "actor/getBasicInfo/",
    "actor/getAllEquipmentInfo",
    "actor/getEquippedEquipment",
    "event/getEventList/",
    "actor/changeEquipmentInfo",
    "pk/getPKList"

    //add more
);


var g_doVersion = Array(
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1

    //add more
);