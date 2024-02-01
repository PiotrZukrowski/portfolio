


# Piotr Żukrowski
# 221718
# Matematyka Stosowana
# 21.06.2017
# - Projekt;
#  -- Baza Danych przechowująca historię meczy w grze "League of Legends" ;

# - Definicje tabel;


drop database if exists `BD LoL.historia`;

CREATE DATABASE `BD LoL.historia` ;
use `BD LoL.historia`;


# Podgląd:
 # select * from `gracz`;
 # select * from `klasa postaci`;
 # select * from `sezon`;
 # select * from `poziom trudnosci`;
 # select * from `postac`;
 # select * from `tryb gry`;
 # select * from `historia`;










# Tabele:

drop table if exists `gracz`;
CREATE TABLE `gracz`(
  # Nicki graczy;

 `id` int AUTO_INCREMENT primary key,
 `nick` varchar(20) unique,
 `imie` varchar(20),
 `nazwisko` varchar(20)

);



drop table if exists `klasa postaci`;
CREATE TABLE `klasa postaci`(
  # Klasy postaci;

 `id` int AUTO_INCREMENT primary key,
 `nazwa` varchar(20) unique NOT NULL

);



drop table if exists `sezon`;
CREATE TABLE `sezon`(
  # ;

 `id` int AUTO_INCREMENT primary key,
 `nazwa` varchar(20) unique NOT NULL

);


drop table if exists `poziom trudnosci`;
CREATE TABLE `poziom trudnosci`(
  # Poziom zaawansowania przeciwnika;

 `id` int AUTO_INCREMENT primary key,
 `nazwa` varchar(20) unique NOT NULL

);



drop table if exists `postac`;
CREATE TABLE `postac`(
  # Postacie dostępne w grze;

 `id` int AUTO_INCREMENT primary key,
 `nazwa` varchar(20) unique NOT NULL,
 `ID_klasa` int,

 foreign key (`ID_klasa`) references `klasa postaci`(`id`)

);



drop table if exists `tryb gry`;
CREATE TABLE `tryb gry`(
  # Dostępny tryby gry;

 `id` int AUTO_INCREMENT primary key,
 `nazwa` varchar(20) unique NOT NULL

);





drop table if exists `historia`;
CREATE TABLE `historia`(
  # Historia meczy;

 `id` int AUTO_INCREMENT primary key,
 `ID_gracza` int,
 `ID_duo` int,

 `ID_PostacGracza` int,
 `ID_PostacDuo` int,


 `ID_PostacOponenta` int,
 `ID_PoziomTrudnosci` int,

 `ID_tryb` int,
 `ID_sezon` int,
 `data` datetime,


 `Wygrana_Laning` ENUM ('1', '0', 'p'),
 `Wygrana_Gra` ENUM ('1', '0', 'p'),


 foreign key (`ID_gracza`) references `gracz`(`id`),
 foreign key (`ID_duo`) references `gracz`(`id`),   # !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! none

 foreign key (`ID_PostacGracza`) references `postac`(`id`),
 foreign key (`ID_PostacDuo`) references `postac`(`id`),   # !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! none
 foreign key (`ID_PostacOponenta`) references `postac`(`id`),


 foreign key (`ID_PoziomTrudnosci`) references `poziom trudnosci`(`id`),
 foreign key (`ID_tryb`) references `tryb gry`(`id`),
 foreign key (`ID_sezon`) references `sezon`(`id`)

);










 # (Workbench);
# CTRL+Z   -- Undo
# CTRL+Y   -- Redo

