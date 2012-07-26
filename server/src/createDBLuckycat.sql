
CREATE DATABASE IF NOT EXISTS `db_luckycat`;

USE `db_luckycat`;

CREATE TABLE IF NOT EXISTS `users` (
uuid       bigint(8)       PRIMARY KEY AUTO_INCREMENT  COMMENT '自增长ID',
udid       varchar(127)    COMMENT '设备ID',
91id       varchar(127)    COMMENT '91平台的ID'
) AUTO_INCREMENT=10000  DEFAULT CHARSET=utf8 COMMENT='用户表';