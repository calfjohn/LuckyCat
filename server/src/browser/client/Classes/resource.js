var s_HelloWorld = "../Resources/HelloWorld.png";
var s_CloseNormal = "../Resources/CloseNormal.png";
var s_CloseSelected = "../Resources/CloseSelected.png";
var s_pngMonster_1003 = "../Resources/image/hero/monster_1003.png";
var s_png_main_rim_1003 = "../Resources/image/mainui/main_rim_1003.png";
var s_png_fuzzy = "../Resources/image/fullscreen/fuzzy.png";
var s_png_hero_1001 = "../Resources/image/hero/hero_1001.png";
var s_png_hero_1002 = "../Resources/image/hero/hero_1002.png";

var s_pngDice = "../Resources/image/battle/dice.png";
var s_pngGreenBomb = "../Resources/image/battle/greenBomb.png";
var s_pngOrangeBomb = "../Resources/image/battle/orangeBomb.png";
var s_pngPurpleBomb = "../Resources/image/battle/purpleBomb.png";
var s_pngYellowBomb = "../Resources/image/battle/yellowBomb.png";

var s_dictEquipment = "../Resources/database/dictEquipment.txt";
var s_dictCareer = "../Resources/database/dictCareer.txt";
var s_dictLevel = "../Resources/database/dictLevel.txt";
var s_dictEvent = "../Resources/database/dictEvent.txt";
var s_dictNpcDialog = "../Resources/database/dictNpcDialog.txt";
var s_dictMonster = "../Resources/database/dictMonster.txt";
var s_dictImage = "../Resources/database/dictImage.txt";
var s_dictBible = "../Resources/database/dictBible.txt";
var s_dictActorLevelUpgrade = "../Resources/database/dictActorLevelUpgrade.txt";

var s_plistAnimationsBomb = "../Resources/image/battle/animationsBomb.plist";
var s_plistAnimationsDice = "../Resources/image/battle/animationsDice.plist";
var s_plistGreenBomb = "../Resources/image/battle/greenBomb.plist";
var s_plistOrangeBomb = "../Resources/image/battle/orangeBomb.plist";
var s_plistPurpleBomb = "../Resources/image/battle/purpleBomb.plist";
var s_plistYellowBomb = "../Resources/image/battle/yellowBomb.plist";
var s_plistDice = "../Resources/image/battle/dice.plist";

var s_ccbiBasic =  "../Resources/ccb/basic.ccbi";
var s_ccbiDialog =  "../Resources/ccb/dialog.ccbi";
var s_ccbiHeroHead =  "../Resources/ccb/hero_head.ccbi";
var s_ccbiBattle =  "../Resources/ccb/battle.ccbi";
var s_ccbiOpenBoxResult =  "../Resources/ccb/box_tips.ccbi";
var s_ccbiOpenBox =  "../Resources/ccb/openbox.ccbi";
var s_ccbiBattleResult =  "../Resources/ccb/fullscreen_tips.ccbi";
var s_ccbiFuzzy =  "../Resources/ccb/fuzzy.ccbi";


//var s_ccbiOpenBox =  "../Resources/ccb/openBox.ccbi";
//var s_ccbiBoxTip =  "../Resources/ccb/box_tips.ccbi";
//var s_ccbi =  "../Resources/ccb/.ccbi";
//var s_ccbi =  "../Resources/ccb/.ccbi";
//var s_ccbi =  "../Resources/ccb/.ccbi";
//var s_ccbi =  "../Resources/ccb/.ccbi";

var g_ressources = [
    //image
    {type:"image", src:s_HelloWorld},
    {type:"image", src:s_CloseNormal},
    {type:"image", src:s_CloseSelected},
    {type:"image", src:s_pngDice},
    {type:"image", src:s_pngGreenBomb},
    {type:"image", src:s_pngOrangeBomb},
    {type:"image", src:s_pngPurpleBomb},
    {type:"image", src:s_pngYellowBomb},
    {type:"image", src:s_pngMonster_1003},
    {type:"image", src:s_png_main_rim_1003},
    {type:"image", src:s_png_fuzzy},
    {type:"image", src:s_png_hero_1001},
    {type:"image", src:s_png_hero_1002},

    //plist
    {type:"plist", src: s_dictEquipment},
    {type:"plist", src: s_dictCareer},
    {type:"plist", src: s_dictLevel},
    {type:"plist", src: s_dictEvent},
    {type:"plist", src: s_dictNpcDialog},
    {type:"plist", src: s_dictMonster},
    {type:"plist", src: s_dictImage},
    {type:"plist", src: s_dictBible},
    {type:"plist", src: s_dictActorLevelUpgrade},

    {type:"plist", src:s_plistGreenBomb},
    {type:"plist", src:s_plistOrangeBomb},
    {type:"plist", src:s_plistPurpleBomb},
    {type:"plist", src:s_plistYellowBomb},
    {type:"plist", src:s_plistDice},
    {type:"plist", src:s_plistAnimationsDice},
    {type:"plist", src:s_plistAnimationsBomb},
    //fnt

    //tmx

    //bgm

    //effect

    //ccbi
    {type:"ccbi", src:s_ccbiFuzzy},
    {type:"ccbi", src:s_ccbiBasic},
    {type:"ccbi", src:s_ccbiDialog},
    {type:"ccbi", src:s_ccbiHeroHead},
    {type:"ccbi", src:s_ccbiBattle},
    {type:"ccbi", src:s_ccbiOpenBoxResult},
    {type:"ccbi", src:s_ccbiOpenBox},
    {type:"ccbi", src:s_ccbiBattleResult},





    //scan resource
    {type:"image", src:"../Resources/CloseNormal.png"},
    {type:"image", src:"../Resources/CloseSelected.png"},
    {type:"image", src:"../Resources/Default.png"},
    {type:"image", src:"../Resources/HelloWorld.png"},
    {type:"image", src:"../Resources/Icon-72.png"},
    {type:"image", src:"../Resources/Icon-Small-50.png"},
    {type:"image", src:"../Resources/Icon-Small.png"},
    {type:"image", src:"../Resources/Icon-Small@2x.png"},
    {type:"image", src:"../Resources/Icon.png"},
    {type:"image", src:"../Resources/Icon@2x.png"},
    {type:"plist", src:"../Resources/Info.plist"},
    {type:"ccbi", src:"../Resources/ccb/basic.ccbi"},
    {type:"ccbi", src:"../Resources/ccb/battle.ccbi"},
    {type:"ccbi", src:"../Resources/ccb/battle_special.ccbi"},
    {type:"ccbi", src:"../Resources/ccb/box_tips.ccbi"},
    {type:"ccbi", src:"../Resources/ccb/chapter.ccbi"},
    {type:"ccbi", src:"../Resources/ccb/confirm.ccbi"},
    {type:"ccbi", src:"../Resources/ccb/desk.ccbi"},
    {type:"ccbi", src:"../Resources/ccb/dialog.ccbi"},
    {type:"ccbi", src:"../Resources/ccb/equip.ccbi"},
    {type:"ccbi", src:"../Resources/ccb/equip_scroll.ccbi"},
    {type:"ccbi", src:"../Resources/ccb/fullscreen_tips.ccbi"},
    {type:"ccbi", src:"../Resources/ccb/fuzzy.ccbi"},
    {type:"ccbi", src:"../Resources/ccb/hero_head.ccbi"},
    {type:"ccbi", src:"../Resources/ccb/openbox.ccbi"},
    {type:"ccbi", src:"../Resources/ccb/page.ccbi"},
    {type:"ccbi", src:"../Resources/ccb/pageEx.ccbi"},
    {type:"ccbi", src:"../Resources/ccb/page_cover.ccbi"},
    {type:"ccbi", src:"../Resources/ccb/pagelist.ccbi"},
    {type:"ccbi", src:"../Resources/ccb/pagelist_scroll.ccbi"},
    {type:"ccbi", src:"../Resources/ccb/pklist.ccbi"},
    {type:"ccbi", src:"../Resources/ccb/pklist_scroll.ccbi"},
    {type:"ccbi", src:"../Resources/ccb/playerinfo.ccbi"},
    {type:"ccbi", src:"../Resources/ccb/skill.ccbi"},
    {type:"plist", src:"../Resources/database/dictActorLevelUpgrade.txt"},
    {type:"plist", src:"../Resources/database/dictBible.txt"},
    {type:"plist", src:"../Resources/database/dictCareer.txt"},
    {type:"plist", src:"../Resources/database/dictEquipment.txt"},
    {type:"plist", src:"../Resources/database/dictEquipmentLevelGrowth.txt"},
    {type:"plist", src:"../Resources/database/dictEquipmentRankGrowth.txt"},
    {type:"plist", src:"../Resources/database/dictEvent.txt"},
    {type:"plist", src:"../Resources/database/dictImage.txt"},
    {type:"plist", src:"../Resources/database/dictLevel.txt"},
    {type:"plist", src:"../Resources/database/dictMonster.txt"},
    {type:"plist", src:"../Resources/database/dictNpcDialog.txt"},
    {type:"plist", src:"../Resources/database/dictSkill.txt"},
    {type:"image", src:"../Resources/fps_images-hd.png"},
    {type:"image", src:"../Resources/fps_images-ipadhd.png"},
    {type:"image", src:"../Resources/fps_images.png"},
    {type:"plist", src:"../Resources/image/battle/animationsBomb.plist"},
    {type:"plist", src:"../Resources/image/battle/animationsDice.plist"},
    {type:"image", src:"../Resources/image/battle/battle_actor_move.png"},
    {type:"image", src:"../Resources/image/battle/battle_enemy_move.png"},
    {type:"image", src:"../Resources/image/battle/battle_round_number.png"},
    {type:"image", src:"../Resources/image/battle/battle_skill_1.png"},
    {type:"image", src:"../Resources/image/battle/battle_skill_2.png"},
    {type:"image", src:"../Resources/image/battle/battle_skill_3.png"},
    {type:"image", src:"../Resources/image/battle/battle_skill_4.png"},
    {type:"image", src:"../Resources/image/battle/battle_skill_5.png"},
    {type:"image", src:"../Resources/image/battle/battle_skill_6.png"},
    {type:"image", src:"../Resources/image/battle/battle_skill_8.png"},
    {type:"image", src:"../Resources/image/battle/battle_skill_9.png"},
    {type:"image", src:"../Resources/image/battle/battle_start.png"},
    {type:"image", src:"../Resources/image/battle/battle_vs.png"},
    {type:"image", src:"../Resources/image/battle/count_time_1.png"},
    {type:"image", src:"../Resources/image/battle/count_time_2.png"},
    {type:"image", src:"../Resources/image/battle/count_time_3.png"},
    {type:"image", src:"../Resources/image/battle/count_time_4.png"},
    {type:"image", src:"../Resources/image/battle/count_time_5.png"},
    {type:"plist", src:"../Resources/image/battle/dice.plist"},
    {type:"image", src:"../Resources/image/battle/dice.png"},
    {type:"plist", src:"../Resources/image/battle/greenBomb.plist"},
    {type:"image", src:"../Resources/image/battle/greenBomb.png"},
    {type:"plist", src:"../Resources/image/battle/orangeBomb.plist"},
    {type:"image", src:"../Resources/image/battle/orangeBomb.png"},
    {type:"plist", src:"../Resources/image/battle/purpleBomb.plist"},
    {type:"image", src:"../Resources/image/battle/purpleBomb.png"},
    {type:"plist", src:"../Resources/image/battle/yellowBomb.plist"},
    {type:"image", src:"../Resources/image/battle/yellowBomb.png"},
    {type:"image", src:"../Resources/image/chapter/0.png"},
    {type:"plist", src:"../Resources/image/chapter/chapter.plist"},
    {type:"image", src:"../Resources/image/chapter/chapter.png"},
    {type:"image", src:"../Resources/image/common/1.png"},
    {type:"image", src:"../Resources/image/common/4.png"},
    {type:"plist", src:"../Resources/image/common/common.plist"},
    {type:"image", src:"../Resources/image/common/common.png"},
    {type:"image", src:"../Resources/image/common/sliderProgress.png"},
    {type:"image", src:"../Resources/image/effect/paw_tear.png"},
    {type:"image", src:"../Resources/image/extensions/sliderProgress.png"},
    {type:"image", src:"../Resources/image/fullscreen/full_1001.png"},
    {type:"image", src:"../Resources/image/fullscreen/fuzzy.png"},
    {type:"image", src:"../Resources/image/fullscreen/page_1001.png"},
    {type:"image", src:"../Resources/image/fullscreen/page_1002.png"},
    {type:"image", src:"../Resources/image/fullscreen/page_1003.png"},
    {type:"image", src:"../Resources/image/hero/hero_1001.png"},
    {type:"image", src:"../Resources/image/hero/hero_1002.png"},
    {type:"image", src:"../Resources/image/hero/monster_1001.png"},
    {type:"image", src:"../Resources/image/hero/monster_1002.png"},
    {type:"image", src:"../Resources/image/hero/monster_1003.png"},
    {type:"image", src:"../Resources/image/icon/addsitem.png"},
    {type:"image", src:"../Resources/image/icon/hero_1.png"},
    {type:"plist", src:"../Resources/image/icon/icon_head.plist"},
    {type:"image", src:"../Resources/image/icon/icon_head.png"},
    {type:"image", src:"../Resources/image/icon/skill01_d.png"},
    {type:"image", src:"../Resources/image/icon/skill01_n.png"},
    {type:"image", src:"../Resources/image/icon/skill01_s.png"},
    {type:"image", src:"../Resources/image/icon/skill02_d.png"},
    {type:"image", src:"../Resources/image/icon/skill02_n.png"},
    {type:"image", src:"../Resources/image/icon/skill02_s.png"},
    {type:"image", src:"../Resources/image/icon/skill03_d.png"},
    {type:"image", src:"../Resources/image/icon/skill03_n.png"},
    {type:"image", src:"../Resources/image/icon/skill03_s.png"},
    {type:"image", src:"../Resources/image/icon/skill04_d.png"},
    {type:"image", src:"../Resources/image/icon/skill04_n.png"},
    {type:"image", src:"../Resources/image/icon/skill04_s.png"},
    {type:"image", src:"../Resources/image/icon/skill05_d.png"},
    {type:"image", src:"../Resources/image/icon/skill05_n.png"},
    {type:"image", src:"../Resources/image/icon/skill05_s.png"},
    {type:"image", src:"../Resources/image/icon/skill06_d.png"},
    {type:"image", src:"../Resources/image/icon/skill06_n.png"},
    {type:"image", src:"../Resources/image/icon/skill06_s.png"},
    {type:"image", src:"../Resources/image/icon/skill07_d.png"},
    {type:"image", src:"../Resources/image/icon/skill07_n.png"},
    {type:"image", src:"../Resources/image/icon/skill07_s.png"},
    {type:"image", src:"../Resources/image/icon/skill08_d.png"},
    {type:"image", src:"../Resources/image/icon/skill08_n.png"},
    {type:"image", src:"../Resources/image/icon/skill08_s.png"},
    {type:"image", src:"../Resources/image/icon/skill09_d.png"},
    {type:"image", src:"../Resources/image/icon/skill09_n.png"},
    {type:"image", src:"../Resources/image/icon/skill09_s.png"},
    {type:"image", src:"../Resources/image/icon/skill10_d.png"},
    {type:"image", src:"../Resources/image/icon/skill10_n.png"},
    {type:"image", src:"../Resources/image/icon/skill10_s.png"},
    {type:"image", src:"../Resources/image/icon/skill11_d.png"},
    {type:"image", src:"../Resources/image/icon/skill11_n.png"},
    {type:"image", src:"../Resources/image/icon/skill11_s.png"},
    {type:"image", src:"../Resources/image/icon/skill12_d.png"},
    {type:"image", src:"../Resources/image/icon/skill12_n.png"},
    {type:"image", src:"../Resources/image/icon/skill12_s.png"},
    {type:"plist", src:"../Resources/image/main/main.plist"},
    {type:"image", src:"../Resources/image/main/main.png"},
    {type:"image", src:"../Resources/image/mainui/battle_order.png"},
    {type:"image", src:"../Resources/image/mainui/button_1001_d.png"},
    {type:"image", src:"../Resources/image/mainui/button_1001_h.png"},
    {type:"image", src:"../Resources/image/mainui/button_1001_n.png"},
    {type:"image", src:"../Resources/image/mainui/button_1002_d.png"},
    {type:"image", src:"../Resources/image/mainui/button_1002_h.png"},
    {type:"image", src:"../Resources/image/mainui/button_1002_n.png"},
    {type:"image", src:"../Resources/image/mainui/button_1003_d.png"},
    {type:"image", src:"../Resources/image/mainui/button_1003_h.png"},
    {type:"image", src:"../Resources/image/mainui/button_1003_n.png"},
    {type:"image", src:"../Resources/image/mainui/button_1004_d.png"},
    {type:"image", src:"../Resources/image/mainui/button_1004_h.png"},
    {type:"image", src:"../Resources/image/mainui/button_1004_n.png"},
    {type:"image", src:"../Resources/image/mainui/button_1005_d.png"},
    {type:"image", src:"../Resources/image/mainui/button_1005_h.png"},
    {type:"image", src:"../Resources/image/mainui/button_1005_n.png"},
    {type:"image", src:"../Resources/image/mainui/button_control_001_d.png"},
    {type:"image", src:"../Resources/image/mainui/button_control_001_h.png"},
    {type:"image", src:"../Resources/image/mainui/button_control_001_n.png"},
    {type:"image", src:"../Resources/image/mainui/button_scoll_1001_h.png"},
    {type:"image", src:"../Resources/image/mainui/button_scoll_1001_n.png"},
    {type:"image", src:"../Resources/image/mainui/button_scoll_1002_h.png"},
    {type:"image", src:"../Resources/image/mainui/button_scoll_1002_n.png"},
    {type:"image", src:"../Resources/image/mainui/main_ball_d.png"},
    {type:"image", src:"../Resources/image/mainui/main_ball_h.png"},
    {type:"image", src:"../Resources/image/mainui/main_ball_n.png"},
    {type:"image", src:"../Resources/image/mainui/main_bg_1001.png"},
    {type:"image", src:"../Resources/image/mainui/main_dice_1001_d.png"},
    {type:"image", src:"../Resources/image/mainui/main_dice_1001_h.png"},
    {type:"image", src:"../Resources/image/mainui/main_dice_1001_n.png"},
    {type:"image", src:"../Resources/image/mainui/main_hp_d.png"},
    {type:"image", src:"../Resources/image/mainui/main_hp_n.png"},
    {type:"image", src:"../Resources/image/mainui/main_line_1001.png"},
    {type:"image", src:"../Resources/image/mainui/main_rim_1001.png"},
    {type:"image", src:"../Resources/image/mainui/main_rim_1002.png"},
    {type:"image", src:"../Resources/image/mainui/main_rim_1003.png"},
    {type:"image", src:"../Resources/image/mainui/main_rim_1003_d.png"},
    {type:"image", src:"../Resources/image/mainui/main_rim_1004.png"},
    {type:"image", src:"../Resources/image/mainui/main_rim_1005.png"},
    {type:"image", src:"../Resources/image/mainui/main_setting_d.png"},
    {type:"image", src:"../Resources/image/mainui/main_setting_h.png"},
    {type:"image", src:"../Resources/image/mainui/main_setting_n.png"},
    {type:"image", src:"../Resources/image/mainui/main_sword_d.png"},
    {type:"image", src:"../Resources/image/mainui/main_sword_h.png"},
    {type:"image", src:"../Resources/image/mainui/main_sword_n.png"},
    {type:"image", src:"../Resources/image/mainui/mian_book_d.png"},
    {type:"image", src:"../Resources/image/mainui/mian_book_h.png"},
    {type:"image", src:"../Resources/image/mainui/mian_book_n.png"},
    {type:"image", src:"../Resources/image/mainui/mian_box_1001_d.png"},
    {type:"image", src:"../Resources/image/mainui/mian_box_1001_h.png"},
    {type:"image", src:"../Resources/image/mainui/mian_box_1001_n.png"},
    {type:"image", src:"../Resources/image/mainui/order_1.png"},
    {type:"image", src:"../Resources/image/mainui/order_2.png"},
    {type:"image", src:"../Resources/image/mainui/ui_goal_1001.png"},
    {type:"image", src:"../Resources/image/map/map_1001_d.png"},
    {type:"image", src:"../Resources/image/map/map_1001_h.png"},
    {type:"image", src:"../Resources/image/map/map_1001_n.png"},
    {type:"image", src:"../Resources/image/map/map_2001_d.png"},
    {type:"image", src:"../Resources/image/map/map_2001_h.png"},
    {type:"image", src:"../Resources/image/map/map_2001_n.png"},
    {type:"image", src:"../Resources/image/map/map_2002_d.png"},
    {type:"image", src:"../Resources/image/map/map_2002_h.png"},
    {type:"image", src:"../Resources/image/map/map_2002_n.png"},
    {type:"image", src:"../Resources/image/map/map_2003_d.png"},
    {type:"image", src:"../Resources/image/map/map_2003_h.png"},
    {type:"image", src:"../Resources/image/map/map_2003_n.png"},
    {type:"plist", src:"../Resources/image/monster/monster.plist"},
    {type:"image", src:"../Resources/image/monster/monster.png"},
    {type:"image", src:"../Resources/image/page/1.png"},
    {type:"plist", src:"../Resources/image/page/page.plist"},
    {type:"image", src:"../Resources/image/page/page.png"},
    {type:"plist", src:"../Resources/image/scene/scene.plist"},
    {type:"image", src:"../Resources/image/scene/scene.png"},
    {type:"image", src:"../Resources/image/scene/scene_1001.png"},
    {type:"image", src:"../Resources/image/scene/scene_1002.png"},
    {type:"image", src:"../Resources/image/scene/scene_1003.png"},
    {type:"image", src:"../Resources/image/scene/scene_1004.png"},
    {type:"image", src:"../Resources/image/scene/scene_1005.png"},
    {type:"image", src:"../Resources/image/scene/scene_1006_b.png"},
    {type:"image", src:"../Resources/image/scene/scene_1006_s.png"},
    {type:"plist", src:"../Resources/image/skills/skills.plist"},
    {type:"image", src:"../Resources/image/skills/skills.png"},
    {type:"image", src:"../Resources/menu1.png"},
    {type:"image", src:"../Resources/menu2.png"}


];