


# Piotr Żukrowski
# 221718
# Matematyka Stosowana
# 21.06.2017
# - Projekt;
#  -- Baza Danych przechowująca historię meczy w grze "League of Legends" ;

# - Wpisy w tabelach;





use `BD LoL.historia`;


# Podgląd:
 # select * from `gracz`;
 # select * from `klasa postaci`;
 # select * from `sezon`;
 # select * from `poziom trudnosci`;
 # select * from `postac`;
 # select * from `tryb gry`;
 # select * from `historia`;










# Wpisy w tabelach:

 # Tabela  `gracz`
insert into gracz (`nick`) values ("none");
insert into gracz (`nick`, `imie`, `nazwisko`) values ("NoNammer", "Piotr", "Żukrowski");
insert into gracz (`nick`) values ("IR TCA Kamikadze");



 # Tabela  `klasa postaci`
insert into `klasa postaci` (`nazwa`) values ("none");   # 1
insert into `klasa postaci` (`nazwa`) values ("Marksman");   # 2
insert into `klasa postaci` (`nazwa`) values ("Support");   # 3
insert into `klasa postaci` (`nazwa`) values ("Mage");   # 4
insert into `klasa postaci` (`nazwa`) values ("Assassin");    # 5
insert into `klasa postaci` (`nazwa`) values ("Warrior");    # 6
insert into `klasa postaci` (`nazwa`) values ("Tank");   # 7
insert into `klasa postaci` (`nazwa`) values ("Juggernaut");   # 8



 # Tabela  `sezon`
insert into sezon (`nazwa`) values ("Early S7");
insert into sezon (`nazwa`) values ("Mid S7");
insert into sezon (`nazwa`) values ("Late S7");



 # Tabela  `poziom trudnosci`
insert into `poziom trudnosci` (`nazwa`) values ("none");
insert into `poziom trudnosci` (`nazwa`) values ("(High)");
insert into `poziom trudnosci` (`nazwa`) values ("High Experienced");
insert into `poziom trudnosci` (`nazwa`) values ("(Low)");
insert into `poziom trudnosci` (`nazwa`) values ("Low Experienced");
insert into `poziom trudnosci` (`nazwa`) values ("(Medium)");
insert into `poziom trudnosci` (`nazwa`) values ("Medium Experienced");



 # Tabela  `postac`
# Ręcznie można wpisywać klasy= NULL;
insert into postac (`nazwa`, `ID_klasa`) values ("none", 1);

 # Wstawianie ręczne (po ID);   ### Spr. żę działa;
insert into postac (`nazwa`, `ID_klasa`) values ("Aatrox", 6);   # !!!!!!! Warrior
insert into postac (`nazwa`, `ID_klasa`) values ("Ahri", 5);   # !!!!!!! Assassin
insert into postac (`nazwa`, `ID_klasa`) values ("Akali", 5);
insert into postac (`nazwa`, `ID_klasa`) values ("Alistar", 7);
insert into postac (`nazwa`, `ID_klasa`) values ("Amumu", 7);
insert into postac (`nazwa`, `ID_klasa`) values ("Anivia", 4);
insert into postac (`nazwa`, `ID_klasa`) values ("Annie", 4);
insert into postac (`nazwa`, `ID_klasa`) values ("Ashe", 2);
insert into postac (`nazwa`, `ID_klasa`) values ("Aurelion Sol", 4);
insert into postac (`nazwa`, `ID_klasa`) values ("Azir", 4);

insert into postac (`nazwa`, `ID_klasa`) values ("Bard", 3);
insert into postac (`nazwa`, `ID_klasa`) values ("Blitzcrank", 3);
insert into postac (`nazwa`, `ID_klasa`) values ("Brand", 4);



insert into postac (`nazwa`, `ID_klasa`) values ("Swain", 4);
insert into postac (`nazwa`, `ID_klasa`) values ("Vel'Koz", 4);
insert into postac (`nazwa`, `ID_klasa`) values ("Pantheon", 5);
insert into postac (`nazwa`, `ID_klasa`) values ("Lux", 4);
insert into postac (`nazwa`, `ID_klasa`) values ("Renekton", 6);

insert into postac (`nazwa`, `ID_klasa`) values ("Riven", 6);
insert into postac (`nazwa`, `ID_klasa`) values ("Twisted Fate", 4);
insert into postac (`nazwa`, `ID_klasa`) values ("Yasuo", 6);
insert into postac (`nazwa`, `ID_klasa`) values ("Gangplank", 6);
insert into postac (`nazwa`, `ID_klasa`) values ("Kog'Maw", 2);
insert into postac (`nazwa`, `ID_klasa`) values ("Diana", 5);
insert into postac (`nazwa`, `ID_klasa`) values ("Morgana", 3);
insert into postac (`nazwa`, `ID_klasa`) values ("Ekko", 5);
insert into postac (`nazwa`, `ID_klasa`) values ("Taliyah", 6);
insert into postac (`nazwa`, `ID_klasa`) values ("Ziggs", 4);
insert into postac (`nazwa`, `ID_klasa`) values ("Kassadin", 5);
insert into postac (`nazwa`, `ID_klasa`) values ("Vladimir", 4);
insert into postac (`nazwa`, `ID_klasa`) values ("Galio", 7);
insert into postac (`nazwa`, `ID_klasa`) values ("Le Blanc", 5);
insert into postac (`nazwa`, `ID_klasa`) values ("Veigar", 4);
insert into postac (`nazwa`, `ID_klasa`) values ("Xerath", 4);
insert into postac (`nazwa`, `ID_klasa`) values ("Karma", 4);
insert into postac (`nazwa`, `ID_klasa`) values ("Ezreal", 2);
insert into postac (`nazwa`, `ID_klasa`) values ("Cassiopeia", 4);
insert into postac (`nazwa`, `ID_klasa`) values ("Oriana", 4);
insert into postac (`nazwa`, `ID_klasa`) values ("Zed", 5);





 # Tabela  `tryb gry`
insert into `tryb gry` (`nazwa`) values ("Ranked Solo/Duo");
insert into `tryb gry` (`nazwa`) values ("Ranked Flex");
insert into `tryb gry` (`nazwa`) values ("Normal Draft");
insert into `tryb gry` (`nazwa`) values ("Normal Blind");

insert into `tryb gry` (`nazwa`) values ("ARAM");





 # Tabela  `historia`
 # Wstawianie ręczne (po ID);   ### Spr. że działa;
# Ręcznie można niektóre FK ustawić jako NULL;
insert into `historia` (
		`ID_gracza`,
		`ID_duo`,

		`ID_PostacGracza`,
		`ID_PostacDuo`,


		`ID_PostacOponenta`,
		`ID_PoziomTrudnosci`,

		`ID_tryb`,
		`ID_sezon`,
        `data`,


		`Wygrana_Laning`,
		`Wygrana_Gra`)
	values (2, 1,
			15, 1,
            20, 3,
            3, 2, "2017-04-24",
            'p', '0');

insert into `historia` (
		`ID_gracza`,
		`ID_duo`,

		`ID_PostacGracza`,
		`ID_PostacDuo`,


		`ID_PostacOponenta`,
		`ID_PoziomTrudnosci`,

		`ID_tryb`,
		`ID_sezon`,
        `data`,


		`Wygrana_Laning`,
		`Wygrana_Gra`)
	values (2, 1,
			16, 1,
            8, 2,
            3, 2, "2017-04-24",
            '1', '0');










 # (Workbench);
# CTRL+Z   -- Undo
# CTRL+Y   -- Redo

