


# Piotr Żukrowski
# 221718
# Matematyka Stosowana
# 21.06.2017
# - Projekt;
#  -- Baza Danych przechowująca historię meczy w grze "League of Legends" ;

# - Definicje Query;





use `BD LoL.historia`;


# Podgląd:
 # select * from `gracz`;
 # select * from `klasa postaci`;
 # select * from `sezon`;
 # select * from `poziom trudnosci`;
 # select * from `postac`;
 # select * from `tryb gry`;
 # select * from `historia`;










# Query:

 # Dodawanie postaci podając klasę słownie;   -- PROCEDURA
drop procedure if exists `admin_NEW_Champion`;
DELIMITER $$
CREATE PROCEDURE `admin_NEW_Champion`
 ( IN arg_nazwa varchar(20), IN arg_klasa varchar(20) ) BEGIN
  # Deklaracja zmiennych wewnętrznych;
	declare arg_IDklasa int;
    SET arg_IDklasa= ( SELECT id from `klasa postaci` where nazwa= arg_klasa );
    IF ( arg_IDklasa IS NULL ) then signal sqlstate '45000' set message_text = 'Błąd. Nie znaleziono takiej klasy.'; else

  # Ciało procedury;
    insert into postac (`nazwa`, `ID_klasa`) values ( arg_nazwa, arg_IDklasa ); END IF;


  # Wypisanie wyniku;

END;
$$
DELIMITER ;


# TEST:
call admin_NEW_Champion ( "Zyra", "Mage" );
select * from `postac`;   # ok!

# call admin_NEW_Champion ( "AAA", "Nie ma takiej klasy" );   # Podanie nieistniejącej klasy  -- nieprzeszło= ok!










 # Widok tabeli `historia` z wartościami zamiast ID;   -- WIDOK;
  # http://www.blog.bmedon.net/index.php/bazy-danych/kilkukrotny-join-do-tej-samej-tabeli/

drop view if exists `historia wartosci`;
CREATE VIEW `historia wartosci` AS
 SELECT historia.id AS ID, alias_Gracz.nick AS Gracz, alias_Duo.nick AS Duo, alias_PostGracz.nazwa AS 'Postać gracza', alias_PostDuo.nazwa AS 'Postać duo',
		alias_PostOponent.nazwa AS 'Postać Oponenta', alias_trudnosc.nazwa AS 'Poziom trudności',
        alias_tryb.nazwa AS 'Tryb gry', alias_sezon.nazwa AS 'Sezon', historia.data AS 'Data', Wygrana_Laning, Wygrana_Gra
	from historia
	Inner Join gracz alias_Gracz ON alias_Gracz.id= historia.ID_gracza
    Inner Join gracz alias_Duo ON alias_Duo.id= historia.ID_duo
    Inner Join postac alias_PostGracz ON alias_PostGracz.id= historia.ID_PostacGracza
    Inner Join postac alias_PostDuo ON alias_PostDuo.id= historia.ID_PostacDuo
    Inner Join postac alias_PostOponent ON alias_PostOponent.id= historia.ID_PostacOponenta
    Inner Join `poziom trudnosci` alias_trudnosc ON alias_trudnosc.id= historia.ID_PoziomTrudnosci
    Inner Join `tryb gry` alias_tryb ON alias_tryb.id= historia.ID_tryb
    Inner Join sezon alias_sezon ON alias_sezon.id= historia.ID_sezon;


# TEST
select * from `historia wartosci`;




 # Dodawanie historii podając argumenty słownie;   -- PROCEDURA
drop procedure if exists `admin_NEW_history`;
DELIMITER $$
CREATE PROCEDURE `admin_NEW_history`
 ( IN arg_NickGracza varchar(20), IN arg_NickDuo varchar(20),

		IN arg_PostacGracza varchar(20),
		IN arg_PostacDuo varchar(20),


		IN arg_PostacOponenta varchar(20),
		IN arg_PoziomTrudnosci varchar(20),

		IN arg_tryb varchar(20),
		IN arg_sezon varchar(20),
        IN arg_data datetime,


		IN arg_WygranaLaning ENUM ('1', '0', 'p'),
		IN arg_WygranaGra  ENUM ('1', '0', 'p')
        ) BEGIN
  # Deklaracja zmiennych wewnętrznych;
# zmienne przechowujące ID, jeśli nie znalezlismy, to wyrzucamy blad i nie wstawiamy...
			## (nie) warunek powinien być sprawdzany w oddzielnym triggerze
	declare arg_IDNickGracza int;
    declare arg_IDNickDuo int;

	declare arg_IDPostacGracza int;
	declare arg_IDPostacDuo int;


	declare arg_IDPostacOponenta int;
	declare arg_IDPoziomTrudnosci int;

	declare arg_IDtryb int;
	declare arg_IDsezon int;


	SET arg_IDNickGracza= ( SELECT id from gracz where nick= arg_NickGracza );
    SET arg_IDNickDuo= ( SELECT id from gracz where nick= arg_NickDuo );
    SET arg_IDPostacGracza= ( SELECT id from postac where nazwa= arg_PostacGracza );
    SET arg_IDPostacDuo= ( SELECT id from postac where nazwa= arg_PostacDuo );
    SET arg_IDPostacOponenta= ( SELECT id from postac where nazwa= arg_PostacOponenta );
    SET arg_IDPoziomTrudnosci= ( SELECT id from `poziom trudnosci` where nazwa= arg_PoziomTrudnosci );
    SET arg_IDTryb= ( SELECT id from `tryb gry` where nazwa= arg_tryb );
    SET arg_IDSezon= ( SELECT id from sezon where nazwa= arg_sezon );



# If'y ;
	IF ( arg_IDNickGracza IS NULL ) then signal sqlstate '45000' set message_text = 'Błąd. arg_NickGracza nie istnieje.';
    ELSEIF ( arg_IDNickDuo IS NULL ) then signal sqlstate '45000' set message_text = 'Błąd. arg_NickDuo nie istnieje.';
    ELSEIF ( arg_IDPostacGracza IS NULL ) then signal sqlstate '45000' set message_text = 'Błąd. arg_PostacGracza nie istnieje.';
    ELSEIF ( arg_IDPostacDuo IS NULL ) then signal sqlstate '45000' set message_text = 'Błąd. arg_PostacDuo nie istnieje.';
    ELSEIF ( arg_IDPostacOponenta IS NULL ) then signal sqlstate '45000' set message_text = 'Błąd. arg_PostacOponenta nie istnieje.';
    ELSEIF ( arg_IDPoziomTrudnosci IS NULL ) then signal sqlstate '45000' set message_text = 'Błąd. arg_PoziomTrudnosci nie istnieje.';
    ELSEIF ( arg_IDTryb IS NULL ) then signal sqlstate '45000' set message_text = 'Błąd. arg_IDTryb nie istnieje.';
    ELSEIF ( arg_IDSezon IS NULL ) then signal sqlstate '45000' set message_text = 'Błąd. arg_IDSezon nie istnieje.'; else



  # Ciało procedury;
	insert into historia (
		`ID_gracza`, `ID_duo`,
		`ID_PostacGracza`, `ID_PostacDuo`,
		`ID_PostacOponenta`, `ID_PoziomTrudnosci`,
		`ID_tryb`, `ID_sezon`, `data`,
		`Wygrana_Laning`, `Wygrana_Gra` )
	#values ( arg_IDNickGracza , arg_IDNickDuo,
	#		arg_IDPostacGracza , arg_IDPostacDuo,
    #        arg_IDPostacOponenta, arg_IDPoziomTrudnosci,
    #        ( SELECT id from `tryb gry` where nazwa= arg_tryb ), ( SELECT id from sezon where nazwa= arg_sezon ), arg_data,
    #        arg_WygranaLaning, arg_WygranaGra);
	values ( arg_IDNickGracza , arg_IDNickDuo,
			arg_IDPostacGracza , arg_IDPostacDuo,
            arg_IDPostacOponenta, arg_IDPoziomTrudnosci,
            arg_IDTryb, arg_IDSezon, arg_data,
            arg_WygranaLaning, arg_WygranaGra);
	END IF;


  # Wypisanie wyniku;

END;
$$
DELIMITER ;


# TEST:
  # NickGracza, NickDuo, PostacGracza, PostacDuo, PostacOponenta, PoziomTrudnosci, tryb, sezon, data, WygranaLaning, WygranaGra ;
call admin_NEW_history ( "NoNammer", "none", "Vel'Koz", "none", "Twisted Fate", "none", "Normal Draft", "Mid S7", "2017-04-25", '1', '0' );
# select * from historia;   #
select * from `historia wartosci`;   # ok!











 # (Workbench);
# CTRL+Z   -- Undo
# CTRL+Y   -- Redo

