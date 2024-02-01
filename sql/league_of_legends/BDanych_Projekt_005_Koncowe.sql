


# Piotr Żukrowski
# 221718
# Matematyka Stosowana
# 21.06.2017
# - Projekt;
#  -- Baza Danych przechowująca historię meczy w grze "League of Legends" ;

# - TRIGGER, FUNCTION;





use `BD LoL.historia`;


# Podgląd:
 # select * from `gracz`;
 # select * from `klasa postaci`;
 # select * from `sezon`;
 # select * from `poziom trudnosci`;
 # select * from `postac`;
 # select * from `tryb gry`;
 # select * from `historia`;

 # select * from `historia wartosci`;










# Trigger:

 # Administracyjne usuwanie postaci z tabeli `postac' wraz z usunieciem wpisów w tabeli `hstoria`;   -- TRIGGER
drop trigger if exists `admin_DEL_Champion`;
DELIMITER $$
CREATE TRIGGER `admin_DEL_Champion`
 BEFORE DELETE ON `BD LoL.historia`.postac for each row BEGIN
  DELETE FROM historia where ID_PostacGracza= OLD.id or ID_PostacDuo= OLD.id or ID_PostacOponenta= OLD.id;

END;
$$
DELIMITER ;


# TEST:
select * from `historia wartosci`;
delete from postac where nazwa= "Vel'Koz";
select * from `historia wartosci`;   # ok!










# Frunkcja:

 # Średnia ilość zwycięstw dla pary {Gracz, Postać};   -- Funkcja
drop function if exists `f_Srednia`;
DELIMITER $$
CREATE FUNCTION `f_Srednia` ( arg_nick varchar(20), arg_postac varchar(20) )
 RETURNS float BEGIN

	declare arg_IDnick int;
    declare arg_IDpostac int;

	SET arg_IDnick= (select id from gracz where nick= arg_nick);
    SET arg_IDpostac= (select id from postac where nazwa= arg_postac);

	IF (arg_IDnick IS NULL) then signal sqlstate '45000' set message_text = 'Błąd. arg_NickGracza nie istnieje.';
    ELSEIF (arg_IDpostac IS NULL) then signal sqlstate '45000' set message_text = 'Błąd. arg_postac nie istnieje.';
    ELSE
 RETURN (
	(select count(Wygrana_Gra)
    from historia
		inner join gracz ON historia.ID_gracza= gracz.id
        inner join postac ON historia.ID_PostacGracza= postac.id
    where gracz.nick= arg_nick and postac.nazwa= arg_postac and historia.Wygrana_Gra='1'
     )/
    (select count(Wygrana_Gra)
    from historia
		inner join gracz ON historia.ID_gracza= gracz.id
        inner join postac ON historia.ID_PostacGracza= postac.id
    where gracz.nick= arg_nick and postac.nazwa= arg_postac
     )
    );
    END IF;


END;
$$
DELIMITER ;


# TEST:
select f_Srednia ( "NoNammer", "Vel'Koz" );
select f_Srednia ( "NoNammer", "Swain" );
select f_Srednia ( "NoNammer", "Pantheon" );










 # (Workbench);
# CTRL+Z   -- Undo
# CTRL+Y   -- Redo

