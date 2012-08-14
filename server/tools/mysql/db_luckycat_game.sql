-- phpMyAdmin SQL Dump
-- version 3.4.5
-- http://www.phpmyadmin.net
--
-- 主机: localhost
-- 生成日期: 2012 年 08 月 13 日 11:22
-- 服务器版本: 5.5.16
-- PHP 版本: 5.3.8

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- 数据库: `db_luckycat_game`
--

-- --------------------------------------------------------

--
-- 表的结构 `actor`
--

CREATE TABLE IF NOT EXISTS `actor` (
  `id` int(8) NOT NULL,
  `uuid` int(8) NOT NULL COMMENT '玩家唯一标识',
  `nickname` text COMMENT '昵称',
  `image_id` int(8) DEFAULT NULL COMMENT '头像',
  `level` int(8) DEFAULT NULL COMMENT '等级',
  `exp` double DEFAULT NULL COMMENT '经验',
  `hp` double DEFAULT NULL COMMENT '生命值',
  `career_id` int(8) DEFAULT NULL COMMENT '职业',
  PRIMARY KEY (`id`),
  KEY `actor_image_id` (`image_id`),
  KEY `actor_level` (`level`),
  KEY `actor_career_id` (`career_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `actor`
--

INSERT INTO `actor` (`id`, `uuid`, `nickname`, `image_id`, `level`, `exp`, `hp`, `career_id`) VALUES
(0, 1234567, 'lihex', 1, 1, 100, 9999, 1);

-- --------------------------------------------------------

--
-- 表的结构 `actor_equipment`
--

CREATE TABLE IF NOT EXISTS `actor_equipment` (
  `id` int(11) NOT NULL,
  `actor_id` int(11) NOT NULL COMMENT '玩家id',
  `equip_id` int(11) DEFAULT NULL COMMENT '装备id',
  `level` int(11) DEFAULT NULL COMMENT '等级',
  `rank` int(11) DEFAULT NULL COMMENT '星级',
  `color` int(11) DEFAULT NULL COMMENT '颜色',
  `buff_id1` int(11) DEFAULT NULL COMMENT '关联buff',
  `buff_value1` double DEFAULT NULL COMMENT '关联buff值',
  `buff_id2` int(11) DEFAULT NULL COMMENT '关联buff',
  `buff_value2` double DEFAULT NULL COMMENT '关联buff值',
  `buff_id3` int(11) DEFAULT NULL COMMENT '关联buff',
  `buff_value3` double DEFAULT NULL COMMENT '关联buff值',
  `buff_id4` int(11) DEFAULT NULL COMMENT '关联buff',
  `buff_value4` double DEFAULT NULL COMMENT '关联buff值',
  `buff_id5` int(11) DEFAULT NULL COMMENT '关联buff',
  `buff_value5` double DEFAULT NULL COMMENT '关联buff值',
  PRIMARY KEY (`id`),
  KEY `actor_equip_actor_id` (`actor_id`),
  KEY `actor_equip_equip_id` (`equip_id`),
  KEY `actor_equip_buff_id1` (`buff_id1`),
  KEY `actor_equip_buff_id2` (`buff_id2`),
  KEY `actor_equip_buff_id3` (`buff_id3`),
  KEY `actor_equip_buff_id4` (`buff_id4`),
  KEY `actor_equip_buff_id5` (`buff_id5`),
  KEY `actor_equip_level` (`level`),
  KEY `actor_equip_rank` (`rank`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- 表的结构 `dict_actor_level_upgrade`
--

CREATE TABLE IF NOT EXISTS `dict_actor_level_upgrade` (
  `level` int(11) NOT NULL AUTO_INCREMENT COMMENT '人物等级',
  `xp` double DEFAULT NULL COMMENT '基础经验值',
  `attack` double DEFAULT NULL COMMENT '基础攻击值',
  `defence` double DEFAULT NULL COMMENT '基础防御值',
  `life` double DEFAULT NULL COMMENT '基础生命值',
  `speed` double DEFAULT NULL COMMENT '基础速度值',
  `title` text COMMENT '升级提示标题',
  `content` text COMMENT '升级提示内容',
  `bonus` text COMMENT '升级奖励 总数量,id,类型(钱/经验/物品/奖励),数量',
  PRIMARY KEY (`level`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;

--
-- 转存表中的数据 `dict_actor_level_upgrade`
--

INSERT INTO `dict_actor_level_upgrade` (`level`, `xp`, `attack`, `defence`, `life`, `speed`, `title`, `content`, `bonus`) VALUES
(1, NULL, NULL, NULL, NULL, NULL, '你升到1级了', '快点去点点看这个哪个的页面吧', '2,2231,900,3422,544'),
(2, NULL, NULL, NULL, NULL, NULL, '你升到2级了', '开心吧…,哪就去充点钱什么的,支持一下.', '1,1101,222');

-- --------------------------------------------------------

--
-- 表的结构 `dict_bible`
--

CREATE TABLE IF NOT EXISTS `dict_bible` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` text COMMENT '名称',
  `bg_id` int(11) DEFAULT NULL COMMENT '背景图片',
  `chapter_bg_id` int(11) DEFAULT NULL COMMENT '章节背景图片',
  PRIMARY KEY (`id`),
  KEY `dict_bible_bg_id` (`bg_id`),
  KEY `dict_bible_chapter_bg_id` (`chapter_bg_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

--
-- 转存表中的数据 `dict_bible`
--

INSERT INTO `dict_bible` (`id`, `name`, `bg_id`, `chapter_bg_id`) VALUES
(1, '求生之路', 1, 2);

-- --------------------------------------------------------

--
-- 表的结构 `dict_box`
--

CREATE TABLE IF NOT EXISTS `dict_box` (
  `id` int(11) NOT NULL COMMENT '宝箱id',
  `reward_min` int(11) NOT NULL COMMENT '奖励的最小数',
  `reward_max` int(11) NOT NULL COMMENT '奖励的最大数',
  `range` text NOT NULL COMMENT '???ID??.?,(1,2,6,7,8)'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- 转存表中的数据 `dict_box`
--

INSERT INTO `dict_box` (`id`, `reward_min`, `reward_max`, `range`) VALUES
(1, 1, 2, '1,2,3'),
(2, 1, 2, '2,3,4');

-- --------------------------------------------------------

--
-- 表的结构 `dict_box_reward`
--

CREATE TABLE IF NOT EXISTS `dict_box_reward` (
  `id` int(11) NOT NULL COMMENT '奖励的id',
  `reward_type` int(11) NOT NULL COMMENT '奖励的物品的类型',
  `reward_id` int(11) NOT NULL COMMENT '奖励的物品的id',
  `reward_num` int(11) NOT NULL COMMENT '奖励的物品的数量',
  `probability` double NOT NULL COMMENT '????'
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='奖励物品表';

--
-- 转存表中的数据 `dict_box_reward`
--

INSERT INTO `dict_box_reward` (`id`, `reward_type`, `reward_id`, `reward_num`, `probability`) VALUES
(1, 1, 123, 400, 0.7),
(2, 3, 2001, 500, 0.6),
(3, 1, 2002, 502, 0.8),
(4, 5, 2004, 507, 0.9),
(5, 2, 2005, 502, 0.8),
(6, 4, 2006, 502, 0.8);

-- --------------------------------------------------------

--
-- 表的结构 `dict_buff`
--

CREATE TABLE IF NOT EXISTS `dict_buff` (
  `id` int(11) NOT NULL,
  `name` text COMMENT '名称',
  `class` int(11) DEFAULT NULL COMMENT '影响属性 1生命 2 攻击 3 防御 4 速度 ',
  `add_value` double DEFAULT NULL COMMENT '累加值',
  `multiply_value` double DEFAULT NULL COMMENT '累乘值',
  `time` double DEFAULT NULL COMMENT 'buff持续时间',
  `inerval` double DEFAULT NULL COMMENT 'buff影响的时间间隔，与count互斥使用',
  `count` double DEFAULT NULL COMMENT 'buff影响的行动次数，与interval互斥使用',
  `description` text COMMENT '描述性文字（策划填写）',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `dict_buff`
--

INSERT INTO `dict_buff` (`id`, `name`, `class`, `add_value`, `multiply_value`, `time`, `inerval`, `count`, `description`) VALUES
(1, NULL, NULL, NULL, NULL, NULL, NULL, NULL, ' 防御增量'),
(2, NULL, NULL, NULL, NULL, NULL, NULL, NULL, '攻击增量'),
(3, NULL, NULL, NULL, NULL, NULL, NULL, NULL, '血量增量'),
(4, NULL, NULL, NULL, NULL, NULL, NULL, NULL, ' 速度增量'),
(5, NULL, NULL, NULL, NULL, NULL, NULL, NULL, '力量增量'),
(6, NULL, NULL, NULL, NULL, NULL, NULL, NULL, ' 体质增量'),
(7, NULL, NULL, NULL, NULL, NULL, NULL, NULL, ' 耐力增量'),
(8, NULL, NULL, NULL, NULL, NULL, NULL, NULL, ' 敏捷增量'),
(9, NULL, NULL, NULL, NULL, NULL, NULL, NULL, '攻击百分比加'),
(10, NULL, NULL, NULL, NULL, NULL, NULL, NULL, ' 防守百分比加'),
(11, NULL, NULL, NULL, NULL, NULL, NULL, NULL, ' 命中率的'),
(12, NULL, NULL, NULL, NULL, NULL, NULL, NULL, '闪避率'),
(13, NULL, NULL, NULL, NULL, NULL, NULL, NULL, ' 速度加成百分比'),
(14, NULL, NULL, NULL, NULL, NULL, NULL, NULL, ' 暴击伤害百分比'),
(15, NULL, NULL, NULL, NULL, NULL, NULL, NULL, ' 暴击率'),
(16, NULL, NULL, NULL, NULL, NULL, NULL, NULL, '破击率'),
(17, NULL, NULL, NULL, NULL, NULL, NULL, NULL, '追击率'),
(18, NULL, NULL, NULL, NULL, NULL, NULL, NULL, ' 反击率'),
(19, NULL, NULL, NULL, NULL, NULL, NULL, NULL, ' 反弹率'),
(20, NULL, NULL, NULL, NULL, NULL, NULL, NULL, '反弹伤害百分比'),
(21, NULL, NULL, NULL, NULL, NULL, NULL, NULL, ' 吸血概率'),
(22, NULL, NULL, NULL, NULL, NULL, NULL, NULL, ' 吸血占伤害百分比'),
(23, NULL, NULL, NULL, NULL, NULL, NULL, NULL, ' 复活回血比率'),
(24, NULL, NULL, NULL, NULL, NULL, NULL, NULL, ' 复活概率'),
(25, NULL, NULL, NULL, NULL, NULL, NULL, NULL, '援护概率'),
(26, NULL, NULL, NULL, NULL, NULL, NULL, NULL, ' 援护受到伤害百分比'),
(27, NULL, NULL, NULL, NULL, NULL, NULL, NULL, '最大伤害范围'),
(28, NULL, NULL, NULL, NULL, NULL, NULL, NULL, ' 最小伤害范围');

-- --------------------------------------------------------

--
-- 表的结构 `dict_career`
--

CREATE TABLE IF NOT EXISTS `dict_career` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` text COMMENT '名称',
  `attack` double DEFAULT NULL COMMENT '基础攻击值',
  `attack_growth` double DEFAULT NULL COMMENT '基础增长率',
  `defence` double DEFAULT NULL COMMENT '基础防御值',
  `defence_growth` double DEFAULT NULL COMMENT '基础增长率',
  `life` double DEFAULT NULL COMMENT '基础生命值',
  `life_growth` double DEFAULT NULL COMMENT '基础增长率',
  `speed` double DEFAULT NULL COMMENT '基础速度值',
  `speed_growth` double DEFAULT NULL COMMENT '基础增长率',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

--
-- 转存表中的数据 `dict_career`
--

INSERT INTO `dict_career` (`id`, `name`, `attack`, `attack_growth`, `defence`, `defence_growth`, `life`, `life_growth`, `speed`, `speed_growth`) VALUES
(1, NULL, 3, 0.2, 5, 0.2, 8, 0.2, 10, 0.2);

-- --------------------------------------------------------

--
-- 表的结构 `dict_chapter`
--

CREATE TABLE IF NOT EXISTS `dict_chapter` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `bible_id` int(11) DEFAULT NULL,
  `name` text COMMENT '名称',
  `image_id` int(11) DEFAULT NULL COMMENT '前景图片',
  `position_x` double DEFAULT '0' COMMENT '地图位置',
  `position_y` double DEFAULT '0' COMMENT '地图位置',
  PRIMARY KEY (`id`),
  KEY `dict_chapter_bible_id` (`bible_id`),
  KEY `dict_chapter_image_id` (`image_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=4 ;

--
-- 转存表中的数据 `dict_chapter`
--

INSERT INTO `dict_chapter` (`id`, `bible_id`, `name`, `image_id`, `position_x`, `position_y`) VALUES
(1, 1, '玄机', 13, 87, 30),
(2, 1, '追杀', 16, 27, 43),
(3, 1, '突围', 19, 8, 0);

-- --------------------------------------------------------

--
-- 表的结构 `dict_equipment`
--

CREATE TABLE IF NOT EXISTS `dict_equipment` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` text COMMENT '名称',
  `image_id` int(11) DEFAULT NULL COMMENT '图片',
  `class` int(11) DEFAULT NULL COMMENT '1 头 2 武器 3 衣服  4 鞋子 ',
  `level_limit` int(11) DEFAULT NULL COMMENT '使用等级',
  `life` double DEFAULT NULL COMMENT '基础生命值',
  `attack` double DEFAULT NULL COMMENT '基础攻击值',
  `defence` double DEFAULT NULL COMMENT '基础防御值',
  `speed` double DEFAULT NULL COMMENT '基础速度值',
  `description` text COMMENT '描述文字（策划填写)',
  PRIMARY KEY (`id`),
  KEY `dict_equipment_image_id` (`image_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- 表的结构 `dict_equipment_level_growth`
--

CREATE TABLE IF NOT EXISTS `dict_equipment_level_growth` (
  `level` int(11) NOT NULL COMMENT '装备等级',
  `gowth` double DEFAULT NULL COMMENT '等级对应增长率',
  PRIMARY KEY (`level`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `dict_equipment_level_growth`
--

INSERT INTO `dict_equipment_level_growth` (`level`, `gowth`) VALUES
(1, 0.1),
(2, 0.15),
(3, 0.23),
(50, 0.7),
(100, 2.3);

-- --------------------------------------------------------

--
-- 表的结构 `dict_equipment_rank_growth`
--

CREATE TABLE IF NOT EXISTS `dict_equipment_rank_growth` (
  `rank` int(11) NOT NULL COMMENT '星级',
  `gowth` double DEFAULT NULL COMMENT '增长率',
  PRIMARY KEY (`rank`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `dict_equipment_rank_growth`
--

INSERT INTO `dict_equipment_rank_growth` (`rank`, `gowth`) VALUES
(1, 0.1),
(2, 0.15),
(3, 0.2),
(4, 0.25),
(5, 0.3);

-- --------------------------------------------------------

--
-- 表的结构 `dict_event`
--

CREATE TABLE IF NOT EXISTS `dict_event` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `type` int(11) DEFAULT '0' COMMENT '0 普通战斗 1 对话 2 特殊战斗',
  `target` int(11) DEFAULT NULL COMMENT '目标怪物id',
  `next_event_id` int(11) DEFAULT NULL COMMENT '关联事件',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=7 ;

--
-- 转存表中的数据 `dict_event`
--

INSERT INTO `dict_event` (`id`, `type`, `target`, `next_event_id`) VALUES
(1, 0, 1, -1),
(2, 0, 1, -1),
(3, 0, 1, -1),
(4, 0, 1, -1),
(5, 1, 2, 6),
(6, 2, 2, -1);

-- --------------------------------------------------------

--
-- 表的结构 `dict_image`
--

CREATE TABLE IF NOT EXISTS `dict_image` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `description` text COMMENT '图片注释（策划使用）',
  `type` int(11) DEFAULT '0' COMMENT '0 单图 1 打包图',
  `name` text COMMENT '关键字，命名保持唯一',
  `file_path` text COMMENT '全路径',
  `plist_path` text COMMENT '全路径',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1002 ;

--
-- 转存表中的数据 `dict_image`
--

INSERT INTO `dict_image` (`id`, `description`, `type`, `name`, `file_path`, `plist_path`) VALUES
(1, '底图', 0, 'common_1.png', 'image/common/1.png', NULL),
(2, '底图放大', 1, 'page_back_1.png', 'image/common/common.png', 'image/common/common.plist'),
(3, '底图灰', 1, 'page_back_2.png', 'image/common/common.png', 'image/common/common.plist'),
(4, '装备按钮', 1, 'main_1.png', 'image/main/main.png', 'image/main/main.plist'),
(5, '装备按钮放大', 1, 'main_11.png', 'image/main/main.png', 'image/main/main.plist'),
(6, '装备按钮灰', 1, 'main_111.png', 'image/main/main.png', 'image/main/main.plist'),
(7, '副本按钮', 1, 'main_2.png', 'image/main/main.png', 'image/main/main.plist'),
(8, '副本按钮大', 1, 'main_22.png', 'image/main/main.png', 'image/main/main.plist'),
(9, '副本按钮灰', 1, 'main_222.png', 'image/main/main.png', 'image/main/main.plist'),
(10, '主线按钮', 1, 'main_3.png', 'image/main/main.png', 'image/main/main.plist'),
(11, '主线按钮大', 1, 'main_33.png', 'image/main/main.png', 'image/main/main.plist'),
(12, 'chapter地图', 0, 'chapter_0.png', 'image/chapter/0.png', NULL),
(13, '地图部件1', 1, 'chapter_1.png', 'image/chapter/chapter.png', 'image/chapter/chapter.plist'),
(14, NULL, 1, 'chapter_11.png', 'image/chapter/chapter.png', 'image/chapter/chapter.plist'),
(15, NULL, 1, 'chapter_111.png', 'image/chapter/chapter.png', 'image/chapter/chapter.plist'),
(16, NULL, 1, 'chapter_2.png', 'image/chapter/chapter.png', 'image/chapter/chapter.plist'),
(17, NULL, 1, 'chapter_22.png', 'image/chapter/chapter.png', 'image/chapter/chapter.plist'),
(18, NULL, 1, 'chapter_222.png', 'image/chapter/chapter.png', 'image/chapter/chapter.plist'),
(19, NULL, 1, 'chapter_3.png', 'image/chapter/chapter.png', 'image/chapter/chapter.plist'),
(20, NULL, 1, 'chapter_33.png', 'image/chapter/chapter.png', 'image/chapter/chapter.plist'),
(21, NULL, 1, 'chapter_333.png', 'image/chapter/chapter.png', 'image/chapter/chapter.plist'),
(22, NULL, 0, 'page_1.png', 'image/page/1.png', NULL),
(23, NULL, 1, 'page_2.png', 'image/page/page.png', 'image/page/page.plist'),
(24, NULL, 1, 'page_22.png', 'image/page/page.png', 'image/page/page.plist'),
(25, NULL, 1, 'page_222.png', 'image/page/page.png', 'image/page/page.plist'),
(26, NULL, 1, 'page_3.png', 'image/page/page.png', 'image/page/page.plist'),
(27, NULL, 1, 'page_33.png', 'image/page/page.png', 'image/page/page.plist'),
(28, NULL, 1, 'page_333.png', 'image/page/page.png', 'image/page/page.plist'),
(29, NULL, 1, 'page_4.png', 'image/page/page.png', 'image/page/page.plist'),
(30, NULL, 1, 'page_44.png', 'image/page/page.png', 'image/page/page.plist'),
(31, NULL, 1, 'page_444.png', 'image/page/page.png', 'image/page/page.plist'),
(32, '黄软泥怪', 1, 'monster_1.png', 'image/monster/monster.png', 'image/monster/monster.plist'),
(33, '红软泥怪', 1, 'monster_2.png', 'image/monster/monster.png', 'image/monster/monster.plist'),
(34, '树精', 1, 'monster_3.png', 'image/monster/monster.png', 'image/monster/monster.plist'),
(35, '老树精', 1, 'monster_4.png', 'image/monster/monster.png', 'image/monster/monster.plist'),
(36, NULL, 0, 'common_4.png', 'image/common/4.png', NULL),
(37, '临时主角', 0, 'hero_1.png', 'image/icon/hero_1.png', NULL),
(38, '玩家', 0, 'main_4.png', 'image/main/master', NULL),
(39, '玩家头像1', 1, 'icon_head001a.png', 'image/icon/icon_head.png', 'image/icon/icon_head.plist'),
(40, '玩家头像2', 1, 'icon_head001b.png', 'image/icon/icon_head.png', 'image/icon/icon_head.plist'),
(1001, NULL, 0, 'sliderProgress.png', 'image/extensions/sliderProgress.png', NULL);

-- --------------------------------------------------------

--
-- 表的结构 `dict_item`
--

CREATE TABLE IF NOT EXISTS `dict_item` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` text COMMENT '物品名称',
  `image_id` int(11) DEFAULT NULL COMMENT '物品图片',
  `buff_id` int(11) DEFAULT NULL COMMENT '关联buff',
  `buff_value` double DEFAULT NULL COMMENT 'buff值',
  PRIMARY KEY (`id`),
  KEY `dict_item_image_id` (`image_id`),
  KEY `dict_item_buff_id` (`buff_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

--
-- 转存表中的数据 `dict_item`
--

INSERT INTO `dict_item` (`id`, `name`, `image_id`, `buff_id`, `buff_value`) VALUES
(1, '金钱', 1, NULL, NULL);

-- --------------------------------------------------------

--
-- 表的结构 `dict_monster`
--

CREATE TABLE IF NOT EXISTS `dict_monster` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` text COMMENT '怪物名称',
  `image_id` int(11) DEFAULT NULL COMMENT '怪物头像',
  PRIMARY KEY (`id`),
  KEY `dict_monster_image_id` (`image_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=6 ;

--
-- 转存表中的数据 `dict_monster`
--

INSERT INTO `dict_monster` (`id`, `name`, `image_id`) VALUES
(1, '史莱姆', 32),
(2, '红色史莱姆', 33),
(3, '大树怪', 35),
(4, '小树怪', 34),
(5, 'boss怪', 35);

-- --------------------------------------------------------

--
-- 表的结构 `dict_npc_talk`
--

CREATE TABLE IF NOT EXISTS `dict_npc_talk` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `event_id` int(11) DEFAULT NULL COMMENT '所属事件id',
  `content` text COMMENT '对话内容',
  `npc_id` int(11) DEFAULT NULL COMMENT '对话对象id',
  `npc_name` text COMMENT '对话人名称',
  PRIMARY KEY (`id`),
  KEY `dict_npc_talk_task_id` (`event_id`),
  KEY `dict_npc_talk_npc_id` (`npc_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=7 ;

--
-- 转存表中的数据 `dict_npc_talk`
--

INSERT INTO `dict_npc_talk` (`id`, `event_id`, `content`, `npc_id`, `npc_name`) VALUES
(1, 5, '你是谁？||Who a u?||你是哪只?', 38, '玩家'),
(2, 5, '你不认识我？||气死我了\n作为第一个出场的Boss\n居然有人不认识我', 33, '？？？'),
(3, 5, '谁要认识你这种红色的软趴趴\n的东西啊', 38, '玩家'),
(4, 5, '我就是远近闻名的\n红色史莱姆', 33, '？？？'),
(5, 5, '什么破名字,真没水平.||这个名字还真是差劲呀\n直白是直白\n但是怎么着都透着一股\n偷懒的味道～！', 38, '玩家'),
(6, 5, '口胡，你准备和我打架么？\n侮辱我就算了\n居然侮辱我爸爸给我取的名字\n看招', 33, '红色史莱姆');

-- --------------------------------------------------------

--
-- 表的结构 `dict_page`
--

CREATE TABLE IF NOT EXISTS `dict_page` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `chapter_id` int(11) DEFAULT NULL COMMENT '所属章节id',
  `name` text COMMENT '本页名称',
  `content` text COMMENT '本页内容',
  `image_id` int(11) DEFAULT NULL COMMENT '前景图片',
  `event_id` int(11) DEFAULT NULL COMMENT '关联事件',
  `state` int(11) DEFAULT '0' COMMENT '0:未通过 1:通过',
  `position_x` double DEFAULT '0' COMMENT '地图位置',
  `position_y` double DEFAULT '0' COMMENT '地图位置',
  `bonus` text COMMENT '总数量,id,类型(钱/经验/物品/奖励),数量',
  `bonus_repeat` int(11) DEFAULT NULL COMMENT '是否能重复领取',
  `box_id` int(11) DEFAULT NULL COMMENT '箱子id',
  PRIMARY KEY (`id`),
  KEY `dict_page_chapter_id` (`chapter_id`),
  KEY `dict_page_task_id` (`event_id`),
  KEY `dict_page_image_id` (`image_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=6 ;

--
-- 转存表中的数据 `dict_page`
--

INSERT INTO `dict_page` (`id`, `chapter_id`, `name`, `content`, `image_id`, `event_id`, `state`, `position_x`, `position_y`, `bonus`, `bonus_repeat`, `box_id`) VALUES
(1, 1, '玄机', '这是一个伸手不见黑夜的五指\n啊不，伸手不见五指的黑夜\n我总感觉有些什么事情会发生', 32, 1, 0, 0, 0, '', 0, 0),
(2, 1, '玄机', '没想到真的发生了呀\n不过为什么是这种恶心东西啊\n我要去找个有光的地方才好', 32, 4, 0, 0, 0, '', 0, 0),
(3, 1, '玄机', '这里是什么倒霉地方啊\n我要离开\n但是好像一直走都在原处', 32, 3, 0, 0, 0, '', 0, 0),
(4, 1, '玄机', '终于看到一点点亮光了\n不会再有恶心物了吧', 32, 4, 0, 0, 0, '', 0, 0),
(5, 1, '玄机', '事实上，确实没有恶心物\n只有更恶心的物体\n挖，我吐。', 33, 5, 0, 0, 0, '', 0, 0);

--
-- 限制导出的表
--

--
-- 限制表 `actor`
--
ALTER TABLE `actor`
  ADD CONSTRAINT `actor_career_id` FOREIGN KEY (`career_id`) REFERENCES `dict_career` (`id`) ON DELETE SET NULL ON UPDATE CASCADE,
  ADD CONSTRAINT `actor_image_id` FOREIGN KEY (`image_id`) REFERENCES `dict_image` (`id`) ON DELETE SET NULL ON UPDATE CASCADE,
  ADD CONSTRAINT `actor_level` FOREIGN KEY (`level`) REFERENCES `dict_actor_level_upgrade` (`level`) ON DELETE SET NULL ON UPDATE CASCADE;

--
-- 限制表 `actor_equipment`
--
ALTER TABLE `actor_equipment`
  ADD CONSTRAINT `actor_equip_actor_id` FOREIGN KEY (`actor_id`) REFERENCES `actor` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `actor_equip_buff_id1` FOREIGN KEY (`buff_id1`) REFERENCES `dict_buff` (`id`) ON DELETE SET NULL ON UPDATE CASCADE,
  ADD CONSTRAINT `actor_equip_buff_id2` FOREIGN KEY (`buff_id2`) REFERENCES `dict_buff` (`id`) ON DELETE SET NULL ON UPDATE CASCADE,
  ADD CONSTRAINT `actor_equip_buff_id3` FOREIGN KEY (`buff_id3`) REFERENCES `dict_buff` (`id`) ON DELETE SET NULL ON UPDATE CASCADE,
  ADD CONSTRAINT `actor_equip_buff_id4` FOREIGN KEY (`buff_id4`) REFERENCES `dict_buff` (`id`) ON DELETE SET NULL ON UPDATE CASCADE,
  ADD CONSTRAINT `actor_equip_buff_id5` FOREIGN KEY (`buff_id5`) REFERENCES `dict_buff` (`id`) ON DELETE SET NULL ON UPDATE CASCADE,
  ADD CONSTRAINT `actor_equip_equip_id` FOREIGN KEY (`equip_id`) REFERENCES `dict_equipment` (`id`) ON DELETE SET NULL ON UPDATE CASCADE,
  ADD CONSTRAINT `actor_equip_level` FOREIGN KEY (`level`) REFERENCES `dict_equipment_level_growth` (`level`) ON DELETE SET NULL ON UPDATE CASCADE,
  ADD CONSTRAINT `actor_equip_rank` FOREIGN KEY (`rank`) REFERENCES `dict_equipment_rank_growth` (`rank`) ON DELETE SET NULL ON UPDATE CASCADE;

--
-- 限制表 `dict_bible`
--
ALTER TABLE `dict_bible`
  ADD CONSTRAINT `dict_bible_bg_id` FOREIGN KEY (`bg_id`) REFERENCES `dict_image` (`id`) ON DELETE SET NULL ON UPDATE CASCADE,
  ADD CONSTRAINT `dict_bible_chapter_bg_id` FOREIGN KEY (`chapter_bg_id`) REFERENCES `dict_image` (`id`) ON DELETE SET NULL ON UPDATE CASCADE;

--
-- 限制表 `dict_chapter`
--
ALTER TABLE `dict_chapter`
  ADD CONSTRAINT `dict_chapter_bible_id` FOREIGN KEY (`bible_id`) REFERENCES `dict_bible` (`id`) ON DELETE SET NULL ON UPDATE CASCADE,
  ADD CONSTRAINT `dict_chapter_image_id` FOREIGN KEY (`image_id`) REFERENCES `dict_image` (`id`) ON DELETE SET NULL ON UPDATE CASCADE;

--
-- 限制表 `dict_equipment`
--
ALTER TABLE `dict_equipment`
  ADD CONSTRAINT `dict_equipment_image_id` FOREIGN KEY (`image_id`) REFERENCES `dict_image` (`id`) ON DELETE SET NULL ON UPDATE CASCADE;

--
-- 限制表 `dict_item`
--
ALTER TABLE `dict_item`
  ADD CONSTRAINT `dict_item_buff_id` FOREIGN KEY (`buff_id`) REFERENCES `dict_buff` (`id`) ON DELETE SET NULL ON UPDATE CASCADE,
  ADD CONSTRAINT `dict_item_image_id` FOREIGN KEY (`image_id`) REFERENCES `dict_image` (`id`) ON DELETE SET NULL ON UPDATE CASCADE;

--
-- 限制表 `dict_monster`
--
ALTER TABLE `dict_monster`
  ADD CONSTRAINT `dict_monster_image_id` FOREIGN KEY (`image_id`) REFERENCES `dict_image` (`id`) ON DELETE SET NULL ON UPDATE CASCADE;

--
-- 限制表 `dict_npc_talk`
--
ALTER TABLE `dict_npc_talk`
  ADD CONSTRAINT `dict_npc_talk_event_id` FOREIGN KEY (`event_id`) REFERENCES `dict_event` (`id`) ON DELETE SET NULL ON UPDATE CASCADE,
  ADD CONSTRAINT `dict_npc_talk_npc_id` FOREIGN KEY (`npc_id`) REFERENCES `dict_image` (`id`) ON DELETE SET NULL ON UPDATE CASCADE;

--
-- 限制表 `dict_page`
--
ALTER TABLE `dict_page`
  ADD CONSTRAINT `dict_page_chapter_id` FOREIGN KEY (`chapter_id`) REFERENCES `dict_chapter` (`id`) ON DELETE SET NULL ON UPDATE CASCADE,
  ADD CONSTRAINT `dict_page_event_id` FOREIGN KEY (`event_id`) REFERENCES `dict_event` (`id`) ON DELETE SET NULL ON UPDATE CASCADE,
  ADD CONSTRAINT `dict_page_image_id` FOREIGN KEY (`image_id`) REFERENCES `dict_image` (`id`) ON DELETE SET NULL ON UPDATE CASCADE;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
