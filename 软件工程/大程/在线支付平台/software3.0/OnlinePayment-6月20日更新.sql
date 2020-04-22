/*******************************************************************************
   Online Payment Database - Version 0.1
   Script: OnlinePayment.sql
   Description: Creates and populates the Online Payment database.
   DB Server: MySQL
********************************************************************************/

/*******************************************************************************
   Previous Setting
********************************************************************************/
SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS=0;

/*******************************************************************************
   Drop database
********************************************************************************/
DROP DATABASE IF EXISTS `OnlinePayment`;

/*******************************************************************************
   Create database
********************************************************************************/
CREATE DATABASE `OnlinePayment`;

USE `OnlinePayment`;

/*******************************************************************************
   Create Tables
********************************************************************************/
CREATE TABLE `Buyer`(
    `BuyerId` INT NOT NULL AUTO_INCREMENT,
    `LoginPassword` VARCHAR(120) NOT NULL,
    `PayPassword` VARCHAR(120) NOT NULL,
    `Balance` DECIMAL(25,2) NOT NULL,
    `UserName` VARCHAR(40) NOT NULL,
    `RealName` VARCHAR(20) NOT NULL,
    `CitizenId` VARCHAR(40) NOT NULL,
    `TypeId` INT NOT NULL,
    `Email` VARCHAR(60) NOT NULL,
    `Phone` VARCHAR(24) NOT NULL,
    `Point` INT NOT NULL,
    `Valid` INT NOT NULL,
    CONSTRAINT `PK_Buyer` PRIMARY KEY (`BuyerId`)
);

CREATE TABLE `Seller`(
    `SellerId` INT NOT NULL AUTO_INCREMENT,
    `LoginPassword` VARCHAR(120) NOT NULL,
    `PayPassword` VARCHAR(120) NOT NULL,
    `Balance` DECIMAL(25,2) NOT NULL,
    `UserName` VARCHAR(40) NOT NULL,
    `RealName` VARCHAR(20) NOT NULL,
    `CitizenId` VARCHAR(40) NOT NULL,
    `Email` VARCHAR(60) NOT NULL,
    `Phone` VARCHAR(24) NOT NULL,
	`Valid` INT NOT NULL,
    CONSTRAINT `PK_Seller` PRIMARY KEY (`SellerId`)
);

CREATE TABLE `Administrator`(
    `AdministratorId` INT NOT NULL AUTO_INCREMENT,
    `LoginPassword` VARCHAR(150) NOT NULL,
    `AuthenticationPassword` VARCHAR(150) NOT NULL,
    `UserName` VARCHAR(40) NOT NULL,
    `TypeId` INT NOT NULL,
    `Permission` INT NOT NULL,
    CONSTRAINT `PK_Administrator` PRIMARY KEY (`AdministratorId`)
);

CREATE TABLE `CitizenIdentity`(
    `RealName` VARCHAR(20) NOT NULL,
    `CitizenId` VARCHAR(40) NOT NULL,
    CONSTRAINT `PK_CitizenIdentity` PRIMARY KEY (`CitizenId`)
);

CREATE TABLE `UserType`(
    `TypeId` INT NOT NULL,
    `TypeName` VARCHAR(20) NOT NULL,
    `RequirementPoints` INT NOT NULL,
    `UpgradePoints` INT NOT NULL,
    CONSTRAINT `PK_UserType` PRIMARY KEY (`TypeId`)
);

CREATE TABLE `RechargeCard`(
    `Number` VARCHAR(50) NOT NULL,
    `Password` VARCHAR(120) NOT NULL,
    `Value` INT NOT NULL,
    `Used` INT NOT NULL
);

/*
CREATE TABLE `AdministratorType`(
	`AdministratorId` INT NOT NULL ,
    `TypeId` INT NOT NULL,
    `TypeName` VARCHAR(20) NOT NULL,
    `DeleteRight` BOOLEAN NOT NULL,
    `AddRight` BOOLEAN NOT NULL,
    `ArbitrationRight` BOOLEAN NOT NULL,
    `BlacklistRight` BOOLEAN NOT NULL,
    `ViewRight` BOOLEAN NOT NULL,
    CONSTRAINT `PK_AdministratorType` PRIMARY KEY (`AdministratorId`)
);*/

/*******************************************************************************
   Create Foreign Keys
********************************************************************************/
ALTER TABLE `Buyer` ADD CONSTRAINT `FK_BuyerTypeId`
    FOREIGN KEY (`TypeId`) REFERENCES `UserType` (`TypeId`) ON DELETE NO ACTION ON UPDATE NO ACTION;

ALTER TABLE `Administrator` ADD CONSTRAINT `FK_AdministratorTypeId`
    FOREIGN KEY (`TypeId`) REFERENCES `AdministratorType` (`TypeId`) ON DELETE NO ACTION ON UPDATE NO ACTION;

/*******************************************************************************
   Populate Tables
********************************************************************************/

INSERT INTO `Buyer` (`LoginPassword`, `PayPassword`, `Balance`, `UserName`, `RealName`, `CitizenId`, `TypeId`, `Email`, `Phone`, `Point`, `Valid`) VALUES ('pbkdf2:sha256:150000$qh9hFsP2$bc380c20ad440afbae00c15ed33e103e1b73724bc6d78115f2f60766b1ee0e26', 'pbkdf2:sha256:150000$qh9hFsP2$bc380c20ad440afbae00c15ed33e103e1b73724bc6d78115f2f60766b1ee0e26', 0, 'Zhang', 'ZhangSan', '110000199801011010', 0, '123456@qq.com', '13112345678', 0, 0);
INSERT INTO `Seller` (`LoginPassword`, `PayPassword`, `Balance`, `UserName`, `RealName`, `CitizenId`, `Email`, `Phone`, `Valid`) VALUES ('pbkdf2:sha256:150000$qh9hFsP2$bc380c20ad440afbae00c15ed33e103e1b73724bc6d78115f2f60766b1ee0e26', 'pbkdf2:sha256:150000$qh9hFsP2$bc380c20ad440afbae00c15ed33e103e1b73724bc6d78115f2f60766b1ee0e26', 0, 'Li', 'LiSi', '110000199801011012', '123457@qq.com', '13112345679', 0);

INSERT INTO `Administrator` (`LoginPassword`, `AuthenticationPassword`, `UserName`, `TypeId`, `Permission`) VALUES ('pbkdf2:sha256:150000$qh9hFsP2$bc380c20ad440afbae00c15ed33e103e1b73724bc6d78115f2f60766b1ee0e26', 'pbkdf2:sha256:150000$qh9hFsP2$bc380c20ad440afbae00c15ed33e103e1b73724bc6d78115f2f60766b1ee0e26', 'white',  2,  1);
INSERT INTO `Administrator` (`LoginPassword`, `AuthenticationPassword`, `UserName`, `TypeId`, `Permission`) VALUES ('pbkdf2:sha256:150000$qh9hFsP2$bc380c20ad440afbae00c15ed33e103e1b73724bc6d78115f2f60766b1ee0e26', 'pbkdf2:sha256:150000$qh9hFsP2$bc380c20ad440afbae00c15ed33e103e1b73724bc6d78115f2f60766b1ee0e26', 'black',  3,  1);
INSERT INTO `Administrator` (`LoginPassword`, `AuthenticationPassword`, `UserName`, `TypeId`, `Permission`) VALUES ('pbkdf2:sha256:150000$qh9hFsP2$bc380c20ad440afbae00c15ed33e103e1b73724bc6d78115f2f60766b1ee0e26', 'pbkdf2:sha256:150000$qh9hFsP2$bc380c20ad440afbae00c15ed33e103e1b73724bc6d78115f2f60766b1ee0e26', 'blue',  4,  1);
INSERT INTO `Administrator` (`LoginPassword`, `AuthenticationPassword`, `UserName`, `TypeId`, `Permission`) VALUES ('pbkdf2:sha256:150000$qh9hFsP2$bc380c20ad440afbae00c15ed33e103e1b73724bc6d78115f2f60766b1ee0e26', 'pbkdf2:sha256:150000$qh9hFsP2$bc380c20ad440afbae00c15ed33e103e1b73724bc6d78115f2f60766b1ee0e26', 'Wang',  3,  1);
INSERT INTO `Administrator` (`LoginPassword`, `AuthenticationPassword`, `UserName`, `TypeId`, `Permission`) VALUES ('pbkdf2:sha256:150000$qh9hFsP2$bc380c20ad440afbae00c15ed33e103e1b73724bc6d78115f2f60766b1ee0e26', 'pbkdf2:sha256:150000$qh9hFsP2$bc380c20ad440afbae00c15ed33e103e1b73724bc6d78115f2f60766b1ee0e26', 'Wang',  4,  1);

INSERT INTO `CitizenIdentity` (`RealName`, `CitizenId`) VALUES ('ZhangSan', '110000199801011010');
INSERT INTO `CitizenIdentity` (`RealName`, `CitizenId`) VALUES ('LiSi', '110000199801011012');
INSERT INTO `CitizenIdentity` (`RealName`, `CitizenId`) VALUES ('WangWu', '110000199801011014');

INSERT INTO `UserType` (`TypeId`, `TypeName`, `RequirementPoints`, `UpgradePoints`) VALUES (0, 'Normal', 0, 100);
INSERT INTO `UserType` (`TypeId`, `TypeName`, `RequirementPoints`, `UpgradePoints`) VALUES (1, 'VIP', 100, 10000);

INSERT INTO `RechargeCard` (`Number`, `Password`, `Value`, `Used`) VALUES ('1', 'pbkdf2:sha256:150000$qh9hFsP2$bc380c20ad440afbae00c15ed33e103e1b73724bc6d78115f2f60766b1ee0e26', 100, 0);

INSERT INTO `RechargeCard` (`Number`, `Password`, `Value`, `Used`) VALUES ('2', 'pbkdf2:sha256:150000$qh9hFsP2$bc380c20ad440afbae00c15ed33e103e1b73724bc6d78115f2f60766b1ee0e26', 100, 0);

INSERT INTO `RechargeCard` (`Number`, `Password`, `Value`, `Used`) VALUES ('3', 'pbkdf2:sha256:150000$qh9hFsP2$bc380c20ad440afbae00c15ed33e103e1b73724bc6d78115f2f60766b1ee0e26', 100, 0);

/*
INSERT INTO `AdministratorType` (`TypeId`, `TypeName`, `DeleteRight`, `AddRight`, `ArbitrationRight`, `BlacklistRight`, `ViewRight`) VALUES (0, 'Root', true, true, true, true, true);
INSERT INTO `AdministratorType` (`TypeId`, `TypeName`, `DeleteRight`, `AddRight`, `ArbitrationRight`, `BlacklistRight`, `ViewRight`) VALUES (1, 'Checker', false, false, true, false, true);
*/

/* for test, yejl */


DROP TABLE IF EXISTS `Order`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Order` (
  `OrderNo` int(11) NOT NULL AUTO_INCREMENT,
  `BuyerId` int(11) NOT NULL,
  `SellerId` int(11) NOT NULL,
  `GoodName` varchar(255) NOT NULL,
  `GoodDescription` varchar(1023) NOT NULL,
  `OrderState` int(11) NOT NULL,
  `OrderTime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `PayTime` timestamp NULL DEFAULT NULL,
  `DeliverTime` timestamp NULL DEFAULT NULL,
  `CancelTime` timestamp NULL DEFAULT NULL,
  `SuccessTime` timestamp NULL DEFAULT NULL,
  `Amount` decimal(25,2) NOT NULL,
  PRIMARY KEY (`OrderNo`),
  KEY `BuyerId` (`BuyerId`),
  KEY `SellerId` (`SellerId`),
  CONSTRAINT `order_ibfk_1` FOREIGN KEY (`BuyerId`) REFERENCES `Buyer` (`BuyerId`),
  CONSTRAINT `order_ibfk_2` FOREIGN KEY (`SellerId`) REFERENCES `Seller` (`SellerId`)
) ENGINE=InnoDB AUTO_INCREMENT=1368 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Order`
--

CREATE TABLE `Blacklists`(
    `UserName`  VARCHAR(40) NOT NULL,
    `TypeId`  INT NOT NULL,
    `Balance`  DECIMAL(25,2) NOT NULL,
    `RealName`  VARCHAR(20) NOT NULL,
    `CitizenId`  VARCHAR(40) NOT NULL,
    `Email`  VARCHAR(60) NOT NULL,
    `Phone`  VARCHAR(24) NOT NULL
);



/* 1表示买家 0表示卖家*/
 INSERT INTO `Blacklists` (`UserName`, `TypeId`, `Balance`, `RealName`, `CitizenId`, `Email`, `Phone`) VALUES ('happy','1','0','ZhangSan','110000199801011010','123456@qq.com','13112345678');

 INSERT INTO `Blacklists` (`UserName`, `TypeId`, `Balance`, `RealName`, `CitizenId`, `Email`, `Phone`) VALUES ('Li','0','0','LiSi','110000199801011012','123457@qq.com','13112345679');