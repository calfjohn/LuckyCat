-- phpMyAdmin SQL Dump
-- version 3.4.5
-- http://www.phpmyadmin.net
--
-- 主机: localhost
-- 生成日期: 2012 年 08 月 29 日 07:51
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
CREATE DATABASE `db_luckycat_game` DEFAULT CHARACTER SET latin1 COLLATE latin1_swedish_ci;
USE `db_luckycat_game`;

-- --------------------------------------------------------

--
-- 表的结构 `actor`
--

DROP TABLE IF EXISTS `actor`;
CREATE TABLE IF NOT EXISTS `actor` (
  `id` int(8) NOT NULL AUTO_INCREMENT,
  `uuid` int(8) NOT NULL COMMENT '玩家唯一标识',
  `nickname` varchar(20) DEFAULT NULL COMMENT '昵称',
  `image_id` int(8) DEFAULT NULL COMMENT '头像',
  `level` int(8) DEFAULT NULL COMMENT '等级',
  `exp` double DEFAULT NULL COMMENT '经验',
  `hp` double DEFAULT NULL COMMENT '生命值',
  `career_id` int(8) DEFAULT NULL COMMENT '职业',
  `chapter_id` int(11) DEFAULT NULL COMMENT '当前进度章节id',
  `page_id` int(11) DEFAULT NULL COMMENT '当前进度页面id',
  `eq_head_id` int(11) DEFAULT NULL,
  `eq_body_id` int(11) DEFAULT NULL,
  `eq_hand_id` int(11) DEFAULT NULL,
  `eq_foot_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `actor_image_id` (`image_id`),
  KEY `actor_level` (`level`),
  KEY `actor_career_id` (`career_id`),
  KEY `chapter_id` (`chapter_id`),
  KEY `page_id` (`page_id`),
  KEY `eq_head_id` (`eq_head_id`),
  KEY `eq_body_id` (`eq_body_id`),
  KEY `eq_hand_id` (`eq_hand_id`),
  KEY `eq_foot_id` (`eq_foot_id`),
  KEY `eq_head_id_2` (`eq_head_id`),
  KEY `eq_body_id_2` (`eq_body_id`),
  KEY `eq_hand_id_2` (`eq_hand_id`),
  KEY `eq_foot_id_2` (`eq_foot_id`),
  KEY `eq_head_id_3` (`eq_head_id`),
  KEY `eq_body_id_3` (`eq_body_id`),
  KEY `eq_hand_id_3` (`eq_hand_id`),
  KEY `eq_foot_id_3` (`eq_foot_id`),
  KEY `eq_head_id_4` (`eq_head_id`),
  KEY `eq_body_id_4` (`eq_body_id`),
  KEY `eq_hand_id_4` (`eq_hand_id`),
  KEY `eq_foot_id_4` (`eq_foot_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=7 ;

--
-- 转存表中的数据 `actor`
--

INSERT INTO `actor` (`id`, `uuid`, `nickname`, `image_id`, `level`, `exp`, `hp`, `career_id`, `chapter_id`, `page_id`, `eq_head_id`, `eq_body_id`, `eq_hand_id`, `eq_foot_id`) VALUES
(-1, -1, 'nobody', NULL, NULL, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(1, 1, 'lihex', 1, 1, 110, 9990, 1, 1, 2, -1, NULL, -1, NULL),
(3, 3, 'will', 1, 1, 200, 8888, 1, 1, 3, NULL, NULL, NULL, NULL),
(4, 4, 'will2', 1, 1, 200, 8888, 1, 1, 4, NULL, NULL, NULL, NULL);

-- --------------------------------------------------------

--
-- 表的结构 `actor_equipment`
--

DROP TABLE IF EXISTS `actor_equipment`;
CREATE TABLE IF NOT EXISTS `actor_equipment` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `actor_id` int(11) NOT NULL COMMENT '玩家id',
  `equip_id` int(11) DEFAULT NULL COMMENT '装备id',
  `level` int(11) DEFAULT NULL COMMENT '等级',
  `rank` int(11) DEFAULT NULL COMMENT '星级',
  `color` int(11) DEFAULT NULL COMMENT '颜色',
  `item1_id` int(11) DEFAULT NULL COMMENT '关联buff',
  `item2_id` int(11) DEFAULT NULL COMMENT '关联buff',
  `item3_id` int(11) DEFAULT NULL COMMENT '关联buff',
  `item4_id` int(11) DEFAULT NULL COMMENT '关联buff',
  `item5_id` int(11) DEFAULT NULL COMMENT '关联buff',
  PRIMARY KEY (`id`),
  KEY `actor_equip_actor_id` (`actor_id`),
  KEY `actor_equip_equip_id` (`equip_id`),
  KEY `actor_equip_buff_id1` (`item1_id`),
  KEY `actor_equip_buff_id2` (`item2_id`),
  KEY `actor_equip_buff_id3` (`item3_id`),
  KEY `actor_equip_buff_id4` (`item4_id`),
  KEY `actor_equip_buff_id5` (`item5_id`),
  KEY `actor_equip_level` (`level`),
  KEY `actor_equip_rank` (`rank`),
  KEY `item1_id` (`item1_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=14 ;

--
-- 转存表中的数据 `actor_equipment`
--

INSERT INTO `actor_equipment` (`id`, `actor_id`, `equip_id`, `level`, `rank`, `color`, `item1_id`, `item2_id`, `item3_id`, `item4_id`, `item5_id`) VALUES
(-1, -1, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(1, 0, 1001, 1, 1, 1, NULL, NULL, NULL, NULL, NULL),
(2, 1, 1001, 1, 1, 1, 1, 2, 3, 4, 5),
(3, 0, 1002, 1, 1, 1, 1, 2, 3, 4, 5),
(4, 1, 2001, 1, 1, 1, 1, 1, 1, 1, 1),
(5, 1, 2002, 1, 1, 1, 1, 1, 1, 1, 1),
(6, 1, 3001, 1, 1, 1, 1, 1, 1, 1, 1),
(7, 1, 3002, 1, 1, 1, 1, 1, 1, 1, 1),
(8, 1, 4001, 1, 1, 1, 1, 1, 1, 1, 1),
(9, 1, 4002, 1, 1, 1, 1, 1, 1, 1, 1),
(11, 0, 1001, 1, 1, 1, 4, 2, 3, 4, 5),
(12, 0, 2001, 1, 1, 1, NULL, NULL, NULL, NULL, NULL),
(13, 0, 2001, 1, 1, 1, NULL, NULL, NULL, NULL, NULL);

-- --------------------------------------------------------

--
-- 表的结构 `actor_skill`
--

DROP TABLE IF EXISTS `actor_skill`;
CREATE TABLE IF NOT EXISTS `actor_skill` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `actor_id` int(11) NOT NULL,
  `buff_id` int(11) NOT NULL,
  `buff_value` float NOT NULL,
  `skill_id` int(8) NOT NULL COMMENT '技能id',
  PRIMARY KEY (`id`),
  KEY `actor_skill_actor_id` (`actor_id`),
  KEY `actor_skill_buff_id` (`buff_id`),
  KEY `skill_id` (`skill_id`),
  KEY `actor_skill_skill_id` (`skill_id`) USING BTREE
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COMMENT='玩家技能表' AUTO_INCREMENT=3 ;

-- --------------------------------------------------------

--
-- 表的结构 `dict_actor_level_upgrade`
--

DROP TABLE IF EXISTS `dict_actor_level_upgrade`;
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
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=70 ;

--
-- 转存表中的数据 `dict_actor_level_upgrade`
--

INSERT INTO `dict_actor_level_upgrade` (`level`, `xp`, `attack`, `defence`, `life`, `speed`, `title`, `content`, `bonus`) VALUES
(1, 90, 0, 0, 0, 0, '你升到1级了', '', '2,2231,900,3422,544'),
(2, 117, 0, 0, 0, 0, '你升到2级了', '', '1,1101,222'),
(3, 150, 0, 0, 0, 0, '你升到3级了', '', ''),
(4, 195, 0, 0, 0, 0, '你升到4级了', '', ''),
(5, 264, 0, 0, 0, 0, '你升到5级了', '', ''),
(6, 360, 0, 0, 0, 0, '你升到6级了', '', ''),
(7, 450, 0, 0, 0, 0, '你升到7级了', '', ''),
(8, 540, 0, 0, 0, 0, '你升到8级了', '', ''),
(9, 690, 0, 0, 0, 0, '你升到9级了', '', ''),
(10, 870, 0, 0, 0, 0, '你升到10级了', '', ''),
(11, 1020, 0, 0, 0, 0, '你升到11级了', '', ''),
(12, 1260, 0, 0, 0, 0, '你升到12级了', '', ''),
(13, 1500, 0, 0, 0, 0, '你升到13级了', '', ''),
(14, 1830, 0, 0, 0, 0, '你升到14级了', '', ''),
(15, 2160, 0, 0, 0, 0, '你升到15级了', '', ''),
(16, 2580, 0, 0, 0, 0, '你升到16级了', '', ''),
(17, 3000, 0, 0, 0, 0, '你升到17级了', '', ''),
(18, 3510, 0, 0, 0, 0, '你升到18级了', '', ''),
(19, 4080, 0, 0, 0, 0, '你升到19级了', '', ''),
(20, 4770, 0, 0, 0, 0, '你升到20级了', '', ''),
(21, 5490, 0, 0, 0, 0, '你升到21级了', '', ''),
(22, 6330, 0, 0, 0, 0, '你升到22级了', '', ''),
(23, 7230, 0, 0, 0, 0, '你升到23级了', '', ''),
(24, 8220, 0, 0, 0, 0, '你升到24级了', '', ''),
(25, 9390, 0, 0, 0, 0, '你升到25级了', '', ''),
(26, 10620, 0, 0, 0, 0, '你升到26级了', '', ''),
(27, 12030, 0, 0, 0, 0, '你升到27级了', '', ''),
(28, 13530, 0, 0, 0, 0, '你升到28级了', '', ''),
(29, 15180, 0, 0, 0, 0, '你升到29级了', '', ''),
(30, 17040, 0, 0, 0, 0, '你升到30级了', '', ''),
(31, 18960, 0, 0, 0, 0, '你升到31级了', '', ''),
(32, 21180, 0, 0, 0, 0, '你升到32级了', '', ''),
(33, 23520, 0, 0, 0, 0, '你升到33级了', '', ''),
(34, 26100, 0, 0, 0, 0, '你升到34级了', '', ''),
(35, 28920, 0, 0, 0, 0, '你升到35级了', '', ''),
(36, 32100, 0, 0, 0, 0, '你升到36级了', '', ''),
(37, 35400, 0, 0, 0, 0, '你升到37级了', '', ''),
(38, 39000, 0, 0, 0, 0, '你升到38级了', '', ''),
(39, 42600, 0, 0, 0, 0, '你升到39级了', '', ''),
(40, 46800, 0, 0, 0, 0, '你升到40级了', '', ''),
(41, 51300, 0, 0, 0, 0, '你升到41级了', '', ''),
(42, 56100, 0, 0, 0, 0, '你升到42级了', '', ''),
(43, 61200, 0, 0, 0, 0, '你升到43级了', '', ''),
(44, 66600, 0, 0, 0, 0, '你升到44级了', '', ''),
(45, 72600, 0, 0, 0, 0, '你升到45级了', '', ''),
(46, 78600, 0, 0, 0, 0, '你升到46级了', '', ''),
(47, 85200, 0, 0, 0, 0, '你升到47级了', '', ''),
(48, 92400, 0, 0, 0, 0, '你升到48级了', '', ''),
(49, 100200, 0, 0, 0, 0, '你升到49级了', '', ''),
(50, 108300, 0, 0, 0, 0, '你升到50级了', '', ''),
(51, 117000, 0, 0, 0, 0, '你升到51级了', '', ''),
(52, 126000, 0, 0, 0, 0, '你升到52级了', '', ''),
(53, 135900, 0, 0, 0, 0, '你升到53级了', '', ''),
(54, 146400, 0, 0, 0, 0, '你升到54级了', '', ''),
(55, 157200, 0, 0, 0, 0, '你升到55级了', '', ''),
(56, 168900, 0, 0, 0, 0, '你升到56级了', '', ''),
(57, 181500, 0, 0, 0, 0, '你升到57级了', '', ''),
(58, 194400, 0, 0, 0, 0, '你升到58级了', '', ''),
(59, 208500, 0, 0, 0, 0, '你升到59级了', '', ''),
(60, 223200, 0, 0, 0, 0, '你升到60级了', '', ''),
(61, 238800, 0, 0, 0, 0, '你升到61级了', '', ''),
(62, 255300, 0, 0, 0, 0, '你升到62级了', '', ''),
(63, 272400, 0, 0, 0, 0, '你升到63级了', '', ''),
(64, 291000, 0, 0, 0, 0, '你升到64级了', '', ''),
(65, 309900, 0, 0, 0, 0, '你升到65级了', '', ''),
(66, 330600, 0, 0, 0, 0, '你升到66级了', '', ''),
(67, 352200, 0, 0, 0, 0, '你升到67级了', '', ''),
(68, 374700, 0, 0, 0, 0, '你升到68级了', '', ''),
(69, 398400, 0, 0, 0, 0, '你升到69级了', '', '');

-- --------------------------------------------------------

--
-- 表的结构 `dict_bible`
--

DROP TABLE IF EXISTS `dict_bible`;
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
(1, '勇者之路', 1, 2);

-- --------------------------------------------------------

--
-- 表的结构 `dict_box`
--

DROP TABLE IF EXISTS `dict_box`;
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
(1, 2, 4, '1,2,3,4,5,6,7,8,9,10,11'),
(2, 1, 2, '2,3,4');

-- --------------------------------------------------------

--
-- 表的结构 `dict_box_reward`
--

DROP TABLE IF EXISTS `dict_box_reward`;
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
(6, 4, 2006, 502, 0.8),
(7, 4, 2007, 666, 0.8),
(8, 4, 2008, 502, 0.8),
(9, 4, 2009, 502, 0.8),
(10, 4, 20010, 502, 0.8),
(11, 4, 20011, 502, 0.8);

-- --------------------------------------------------------

--
-- 表的结构 `dict_buff`
--

DROP TABLE IF EXISTS `dict_buff`;
CREATE TABLE IF NOT EXISTS `dict_buff` (
  `id` int(11) NOT NULL,
  `name` varchar(50) DEFAULT NULL COMMENT '名称',
  `class` int(11) DEFAULT NULL COMMENT '影响属性 1生命 2 攻击 3 防御 4 速度 ',
  `add_value` double DEFAULT NULL COMMENT '累加值',
  `multiply_value` double DEFAULT NULL COMMENT '累乘值',
  `time` double DEFAULT NULL COMMENT 'buff持续时间',
  `interval` double DEFAULT NULL COMMENT 'buff影响的时间间隔，与count互斥使用',
  `count` double DEFAULT NULL COMMENT 'buff影响的行动次数，与interval互斥使用',
  `description` text COMMENT '描述性文字（策划填写）',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `dict_buff`
--

INSERT INTO `dict_buff` (`id`, `name`, `class`, `add_value`, `multiply_value`, `time`, `interval`, `count`, `description`) VALUES
(1, '加血', 1, 1, 0, 0, 0, 5, ''),
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

DROP TABLE IF EXISTS `dict_career`;
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
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=101 ;

--
-- 转存表中的数据 `dict_career`
--

INSERT INTO `dict_career` (`id`, `name`, `attack`, `attack_growth`, `defence`, `defence_growth`, `life`, `life_growth`, `speed`, `speed_growth`) VALUES
(1, '法师', 15, 0.2, 5, 0.2, 15, 0.2, 8, 0.2),
(2, '战士', 10, 0.5, 8, 0.5, 25, 0.2, 10, 0.2),
(3, '刺客', 13, 0.6, 5, 0.15, 20, 0.2, 15, 0.5),
(100, '怪物', 5, 0.2, 7, 0.3, 30, 0.2, 5, 0.2);

-- --------------------------------------------------------

--
-- 表的结构 `dict_chapter`
--

DROP TABLE IF EXISTS `dict_chapter`;
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

DROP TABLE IF EXISTS `dict_equipment`;
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
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=4003 ;

--
-- 转存表中的数据 `dict_equipment`
--

INSERT INTO `dict_equipment` (`id`, `name`, `image_id`, `class`, `level_limit`, `life`, `attack`, `defence`, `speed`, `description`) VALUES
(1, '黄金甲', 4, 1, 1, 50, 0, 100, 5, '满城尽带黄金甲，你懂得'),
(1001, '新手盔', 0, 1, 1, 100, 0, 50, 10, '新手使用的头盔'),
(1002, '铁盔', 0, 1, 5, 200, 0, 100, 20, '普通的头盔，灰不拉几的'),
(2001, '新手剑', 0, 2, 1, 0, 100, 0, 0, '新手使用的剑'),
(2002, '铁剑', 0, 2, 5, 0, 150, 0, 5, '普通的剑，连穗子都没有'),
(3001, '新手铠', 0, 3, 1, 50, 0, 100, 0, '新手使用的铠甲'),
(3002, '铁甲', 0, 3, 5, 100, 0, 200, 0, '普通的铠甲，聊胜于无'),
(4001, '新手靴', 0, 4, 1, 0, 0, 0, 50, '新手使用的靴子'),
(4002, '皮靴', 0, 4, 5, 0, 0, 0, 100, '普通的靴子，晋江产的吧');

-- --------------------------------------------------------

--
-- 表的结构 `dict_equipment_level_growth`
--

DROP TABLE IF EXISTS `dict_equipment_level_growth`;
CREATE TABLE IF NOT EXISTS `dict_equipment_level_growth` (
  `level` int(11) NOT NULL COMMENT '装备等级',
  `growth` double DEFAULT NULL COMMENT '等级对应增长率',
  PRIMARY KEY (`level`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `dict_equipment_level_growth`
--

INSERT INTO `dict_equipment_level_growth` (`level`, `growth`) VALUES
(1, 0.1),
(2, 0.15),
(3, 0.23),
(50, 0.7),
(100, 2.3);

-- --------------------------------------------------------

--
-- 表的结构 `dict_equipment_rank_growth`
--

DROP TABLE IF EXISTS `dict_equipment_rank_growth`;
CREATE TABLE IF NOT EXISTS `dict_equipment_rank_growth` (
  `rank` int(11) NOT NULL COMMENT '星级',
  `growth` double DEFAULT NULL COMMENT '增长率',
  PRIMARY KEY (`rank`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `dict_equipment_rank_growth`
--

INSERT INTO `dict_equipment_rank_growth` (`rank`, `growth`) VALUES
(1, 0.1),
(2, 0.15),
(3, 0.2),
(4, 0.25),
(5, 0.3);

-- --------------------------------------------------------

--
-- 表的结构 `dict_event`
--

DROP TABLE IF EXISTS `dict_event`;
CREATE TABLE IF NOT EXISTS `dict_event` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `type` int(11) DEFAULT '0' COMMENT '0 普通战斗 1 对话 2 特殊战斗',
  `target` text COMMENT '目标怪物id',
  `next_event_id` int(11) DEFAULT NULL COMMENT '关联事件',
  `bonus` text COMMENT '总数量,类型(钱/经验/物品/装备),id,数量',
  `bonus_repeat` int(11) DEFAULT NULL COMMENT '是否能重复领取',
  `box_id` int(11) DEFAULT NULL COMMENT '箱子id',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=7 ;

--
-- 转存表中的数据 `dict_event`
--

INSERT INTO `dict_event` (`id`, `type`, `target`, `next_event_id`, `bonus`, `bonus_repeat`, `box_id`) VALUES
(1, 2, '1', -1, '[{"type":1,"id":NaN,"count":100},\n{"type":2,"id":NaN,"count":50},\n{"type":4,"id":1001,"count":1}]', 0, -1),
(2, 2, '2', -1, '[{"type":1,"id":NaN,"count":100},\n{"type":2,"id":NaN,"count":50},\n{"type":4,"id":2001,"count":1}]', 0, -1),
(3, 2, '3', -1, '[{"type":1,"id":NaN,"count":100},\n{"type":2,"id":NaN,"count":50},\n{"type":4,"id":3001,"count":1}]', 0, -1),
(4, 2, '4', -1, '[{"type":1,"id":NaN,"count":100},\n{"type":2,"id":NaN,"count":50},\n{"type":4,"id":4001,"count":1}]', 0, -1),
(5, 1, '5', 6, '[{"type":1,"id":NaN,"count":100},\n{"type":2,"id":NaN,"count":50},\n{"type":4,"id":2001,"count":1}]', 0, -1),
(6, 2, '5', -1, '[{"type":1,"id":NaN,"count":100},\n{"type":2,"id":NaN,"count":50},\n{"type":4,"id":1002,"count":1}]', 0, 1);

-- --------------------------------------------------------

--
-- 表的结构 `dict_image`
--

DROP TABLE IF EXISTS `dict_image`;
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
(1, '底图', 0, 'common_1.png', 'image/common/1.png', ''),
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
(12, 'chapter地图', 0, 'chapter_0.png', 'image/chapter/0.png', ''),
(13, '地图部件1', 1, 'chapter_1.png', 'image/chapter/chapter.png', 'image/chapter/chapter.plist'),
(14, '', 1, 'chapter_11.png', 'image/chapter/chapter.png', 'image/chapter/chapter.plist'),
(15, '', 1, 'chapter_111.png', 'image/chapter/chapter.png', 'image/chapter/chapter.plist'),
(16, '', 1, 'chapter_2.png', 'image/chapter/chapter.png', 'image/chapter/chapter.plist'),
(17, '', 1, 'chapter_22.png', 'image/chapter/chapter.png', 'image/chapter/chapter.plist'),
(18, '', 1, 'chapter_222.png', 'image/chapter/chapter.png', 'image/chapter/chapter.plist'),
(19, '', 1, 'chapter_3.png', 'image/chapter/chapter.png', 'image/chapter/chapter.plist'),
(20, '', 1, 'chapter_33.png', 'image/chapter/chapter.png', 'image/chapter/chapter.plist'),
(21, '', 1, 'chapter_333.png', 'image/chapter/chapter.png', 'image/chapter/chapter.plist'),
(22, '', 0, 'page_1.png', 'image/page/1.png', ''),
(23, '', 1, 'page_2.png', 'image/page/page.png', 'image/page/page.plist'),
(24, '', 1, 'page_22.png', 'image/page/page.png', 'image/page/page.plist'),
(25, '', 1, 'page_222.png', 'image/page/page.png', 'image/page/page.plist'),
(26, '', 1, 'page_3.png', 'image/page/page.png', 'image/page/page.plist'),
(27, '', 1, 'page_33.png', 'image/page/page.png', 'image/page/page.plist'),
(28, '', 1, 'page_333.png', 'image/page/page.png', 'image/page/page.plist'),
(29, '', 1, 'page_4.png', 'image/page/page.png', 'image/page/page.plist'),
(30, '', 1, 'page_44.png', 'image/page/page.png', 'image/page/page.plist'),
(31, '', 1, 'page_444.png', 'image/page/page.png', 'image/page/page.plist'),
(32, '黄软泥怪', 1, 'monster_1.png', 'image/monster/monster.png', 'image/monster/monster.plist'),
(33, '红软泥怪', 1, 'monster_2.png', 'image/monster/monster.png', 'image/monster/monster.plist'),
(34, '树精', 1, 'monster_3.png', 'image/monster/monster.png', 'image/monster/monster.plist'),
(35, '老树精', 1, 'monster_4.png', 'image/monster/monster.png', 'image/monster/monster.plist'),
(36, '', 0, 'common_4.png', 'image/common/4.png', ''),
(37, '临时主角', 0, 'hero_1.png', 'image/icon/hero_1.png', ''),
(38, '玩家', 0, 'main_4.png', 'image/main/master', ''),
(39, '玩家头像1', 1, 'icon_head001a.png', 'image/icon/icon_head.png', 'image/icon/icon_head.plist'),
(40, '玩家头像2', 1, 'icon_head001b.png', 'image/icon/icon_head.png', 'image/icon/icon_head.plist'),
(41, '场景背景图01', 1, 'scene_1001.png', 'image/scene/scene.png', 'image/scene/scene.plist'),
(42, '场景背景图02', 1, 'scene_1002.png', 'image/scene/scene.png', 'image/scene/scene.plist'),
(43, '场景背景图03', 1, 'scene_1003.png', 'image/scene/scene.png', 'image/scene/scene.plist'),
(44, '场景背景图04', 1, 'scene_1004.png', 'image/scene/scene.png', 'image/scene/scene.plist'),
(45, '场景背景图05', 1, 'scene_1005.png', 'image/scene/scene.png', 'image/scene/scene.plist'),
(46, '镶嵌物品', 0, 'addsitem.png', 'image/icon/addsitem.png', NULL),
(1001, '', 0, 'sliderProgress.png', 'image/extensions/sliderProgress.png', '');

-- --------------------------------------------------------

--
-- 表的结构 `dict_item`
--

DROP TABLE IF EXISTS `dict_item`;
CREATE TABLE IF NOT EXISTS `dict_item` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` text COMMENT '物品名称',
  `image_id` int(11) DEFAULT NULL COMMENT '物品图片',
  `buff_id` int(11) DEFAULT NULL COMMENT '关联buff',
  `buff_value` double DEFAULT NULL COMMENT 'buff值',
  PRIMARY KEY (`id`),
  KEY `dict_item_image_id` (`image_id`),
  KEY `dict_item_buff_id` (`buff_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=5 ;

--
-- 转存表中的数据 `dict_item`
--

INSERT INTO `dict_item` (`id`, `name`, `image_id`, `buff_id`, `buff_value`) VALUES
(1, '金钱', 1, NULL, NULL),
(2, '经验', NULL, NULL, NULL),
(3, '大力丸', 1, NULL, NULL),
(4, '镶嵌物品', 46, 1, 100);

-- --------------------------------------------------------

--
-- 表的结构 `dict_monster`
--

DROP TABLE IF EXISTS `dict_monster`;
CREATE TABLE IF NOT EXISTS `dict_monster` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` text COMMENT '怪物名称',
  `image_id` int(11) DEFAULT NULL COMMENT '怪物头像',
  `career_id` int(11) DEFAULT NULL COMMENT '职业，dict_career里面读取',
  `level` int(11) DEFAULT NULL COMMENT '等级（影响基本属性，同actor）',
  `rank` float(11,2) DEFAULT NULL COMMENT '星级（影响基本属性）1:1.0 2:1.2 3:1.4',
  PRIMARY KEY (`id`),
  KEY `dict_monster_image_id` (`image_id`),
  KEY `career_id` (`career_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=6 ;

--
-- 转存表中的数据 `dict_monster`
--

INSERT INTO `dict_monster` (`id`, `name`, `image_id`, `career_id`, `level`, `rank`) VALUES
(1, '史莱姆', 32, 100, 1, 1.00),
(2, '红色史莱姆', 33, 100, 2, 1.00),
(3, '大树怪', 35, 100, 3, 1.00),
(4, '小树怪', 34, 100, 4, 1.00),
(5, 'boss怪', 35, 100, 5, 1.20);

-- --------------------------------------------------------

--
-- 表的结构 `dict_npc_talk`
--

DROP TABLE IF EXISTS `dict_npc_talk`;
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

DROP TABLE IF EXISTS `dict_page`;
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
  PRIMARY KEY (`id`),
  KEY `dict_page_chapter_id` (`chapter_id`),
  KEY `dict_page_task_id` (`event_id`),
  KEY `dict_page_image_id` (`image_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=17 ;

--
-- 转存表中的数据 `dict_page`
--

INSERT INTO `dict_page` (`id`, `chapter_id`, `name`, `content`, `image_id`, `event_id`, `state`, `position_x`, `position_y`) VALUES
(1, 1, 'Chapter 01', '歌唱吧，女神！歌唱裴琉斯之子阿\n基琉斯的愤怒——\n他的暴怒招致了这场凶险的灾祸，\n给阿开亚人带来了受之不尽的苦难', 41, 1, 0, 0, 0),
(2, 1, 'Chapter 01', '将许多豪杰强健的魂魄\n打入了哀地斯，而把他们的躯体，\n作为美食，扔给了狗和兀鸟，\n从而实践了宙斯的意志', 41, 1, 0, 0, 0),
(3, 1, 'Chapter 01', '从初时的一场争执开始，\n当事的双方是\n阿特柔斯之子、民众的王阿伽门农\n和卓越的阿基琉斯', 41, 1, 0, 0, 0),
(4, 1, 'Chapter 01', '哪位神祗挑起了二者间的这场争斗\n是宙斯和莱托之子阿波罗，\n因阿特桑斯之子侮辱了克鲁塞斯\n他的祭司，而对这位王者大发其火', 41, 1, 0, 0, 0),
(5, 1, 'Chapter 01', '他在兵群中降下可怕的瘟疫，\n吞噬众人的生命。\n为了赎回女儿，克鲁塞斯曾身临阿\n开亚人的快船，带着难以数计的礼', 42, 2, 0, 0, 0),
(6, 1, 'Chapter 01', '手握黄金节杖，杖上系着远射手\n阿波罗的条带，恳求所有的\n阿开亚人', 42, 2, 0, 0, 0),
(7, 1, 'Chapter 01', '首先是阿特柔斯的两个儿子，\n军队的统帅：\n“阿特柔斯之子，其他胫甲坚固的\n阿开亚人！', 42, 2, 0, 0, 0),
(8, 1, 'Chapter 01', '但愿家住俄林波斯的众神\n答应让你们洗劫\n普里阿摩斯的城堡，\n然后平安地回返家园。', 42, 2, 0, 0, 0),
(9, 1, 'Chapter 01', '请你们接受赎礼，交还我的女儿\n我的宝贝，\n以示对宙斯之子、\n远射手阿波罗的崇爱。”', 43, 3, 0, 0, 0),
(10, 1, 'Chapter 01', '其他阿开亚人\n全都发出赞同的呼声，\n表示应该尊重祭司，\n收下这份光灿灿的赎礼；', 43, 3, 0, 0, 0),
(11, 1, 'Chapter 01', '然而，此事却没有给\n阿特柔斯之子阿伽门农带来愉悦，\n他用严厉的命令\n粗暴地赶走了老人：', 44, 4, 0, 0, 0),
(12, 1, 'Chapter 01', '老家伙，不要再让我见到你的出现，\n在这深旷的海船边！\n现在不许倘留，\n以后也不要再来——', 44, 4, 0, 0, 0),
(13, 1, 'Chapter 01', '否则，你的节杖和神的条\n带将不再为你保平信安！\n我不会交还这位姑娘；', 45, 5, 0, 0, 0);

-- --------------------------------------------------------

--
-- 表的结构 `dict_skill`
--

DROP TABLE IF EXISTS `dict_skill`;
CREATE TABLE IF NOT EXISTS `dict_skill` (
  `id` int(11) NOT NULL,
  `icon_id` int(11) NOT NULL COMMENT '技能图标',
  `effect_id` int(11) NOT NULL COMMENT '特效动画id',
  `name` varchar(20) NOT NULL COMMENT '技能名称',
  `description` varchar(100) NOT NULL COMMENT '描述',
  PRIMARY KEY (`id`),
  KEY `dict_skill_icon_id` (`icon_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `dict_skill`
--

INSERT INTO `dict_skill` (`id`, `icon_id`, `effect_id`, `name`, `description`) VALUES
(1, 1, 1, '阿修罗之怒', '');

--
-- 限制导出的表
--

--
-- 限制表 `actor`
--
ALTER TABLE `actor`
  ADD CONSTRAINT `actor_career_id` FOREIGN KEY (`career_id`) REFERENCES `dict_career` (`id`) ON DELETE SET NULL ON UPDATE CASCADE,
  ADD CONSTRAINT `actor_chapter_id` FOREIGN KEY (`chapter_id`) REFERENCES `dict_page` (`chapter_id`) ON DELETE SET NULL ON UPDATE CASCADE,
  ADD CONSTRAINT `actor_eq_body_id` FOREIGN KEY (`eq_body_id`) REFERENCES `actor_equipment` (`id`) ON DELETE SET NULL ON UPDATE CASCADE,
  ADD CONSTRAINT `actor_eq_foot_id` FOREIGN KEY (`eq_foot_id`) REFERENCES `actor_equipment` (`id`) ON DELETE SET NULL ON UPDATE CASCADE,
  ADD CONSTRAINT `actor_eq_hand_id` FOREIGN KEY (`eq_hand_id`) REFERENCES `actor_equipment` (`id`) ON DELETE SET NULL ON UPDATE CASCADE,
  ADD CONSTRAINT `actor_eq_head_id` FOREIGN KEY (`eq_head_id`) REFERENCES `actor_equipment` (`id`) ON DELETE SET NULL ON UPDATE CASCADE,
  ADD CONSTRAINT `actor_image_id` FOREIGN KEY (`image_id`) REFERENCES `dict_image` (`id`) ON DELETE SET NULL ON UPDATE CASCADE,
  ADD CONSTRAINT `actor_level` FOREIGN KEY (`level`) REFERENCES `dict_actor_level_upgrade` (`level`) ON DELETE SET NULL ON UPDATE CASCADE,
  ADD CONSTRAINT `actor_page_id` FOREIGN KEY (`page_id`) REFERENCES `dict_page` (`id`) ON DELETE SET NULL ON UPDATE CASCADE;

--
-- 限制表 `actor_equipment`
--
ALTER TABLE `actor_equipment`
  ADD CONSTRAINT `actor_equip_actor_id` FOREIGN KEY (`actor_id`) REFERENCES `actor` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `actor_equip_equip_id` FOREIGN KEY (`equip_id`) REFERENCES `dict_equipment` (`id`) ON DELETE SET NULL ON UPDATE CASCADE,
  ADD CONSTRAINT `actor_equip_item1_id` FOREIGN KEY (`item1_id`) REFERENCES `dict_item` (`id`) ON DELETE SET NULL ON UPDATE CASCADE,
  ADD CONSTRAINT `actor_equip_level` FOREIGN KEY (`level`) REFERENCES `dict_equipment_level_growth` (`level`) ON DELETE SET NULL ON UPDATE CASCADE,
  ADD CONSTRAINT `actor_equip_rank` FOREIGN KEY (`rank`) REFERENCES `dict_equipment_rank_growth` (`rank`) ON DELETE SET NULL ON UPDATE CASCADE;

--
-- 限制表 `actor_skill`
--
ALTER TABLE `actor_skill`
  ADD CONSTRAINT `actor_skill_skill_id` FOREIGN KEY (`skill_id`) REFERENCES `dict_skill` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `actor_skill_actor_id` FOREIGN KEY (`actor_id`) REFERENCES `actor` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `actor_skill_buff_id` FOREIGN KEY (`buff_id`) REFERENCES `dict_buff` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

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
  ADD CONSTRAINT `dict_monster_career_id` FOREIGN KEY (`career_id`) REFERENCES `dict_career` (`id`) ON DELETE SET NULL ON UPDATE CASCADE,
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

--
-- 限制表 `dict_skill`
--
ALTER TABLE `dict_skill`
  ADD CONSTRAINT `dict_skill_icon_id` FOREIGN KEY (`icon_id`) REFERENCES `dict_image` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;
--
-- 数据库: `db_luckycat_user`
--
CREATE DATABASE `db_luckycat_user` DEFAULT CHARACTER SET latin1 COLLATE latin1_swedish_ci;
USE `db_luckycat_user`;

-- --------------------------------------------------------

--
-- 表的结构 `users`
--

DROP TABLE IF EXISTS `users`;
CREATE TABLE IF NOT EXISTS `users` (
  `uuid` bigint(8) NOT NULL AUTO_INCREMENT COMMENT '自增长ID',
  `udid` varchar(127) DEFAULT NULL,
  `91id` varchar(127) DEFAULT NULL,
  PRIMARY KEY (`uuid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='用户表' AUTO_INCREMENT=1 ;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
