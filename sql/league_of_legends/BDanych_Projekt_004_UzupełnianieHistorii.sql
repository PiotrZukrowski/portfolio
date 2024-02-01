


# Piotr Żukrowski
# 221718
# Matematyka Stosowana
# 21.06.2017
# - Projekt;
#  -- Baza Danych przechowująca historię meczy w grze "League of Legends" ;

# - Uzupełnianie historii;





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










# Uzupełnianie historii:
# Jeżeli jest "none" to uzupełniać NULL'em ...

DELETE FROM historia;
  # 				NickGracza, NickDuo, PostacGracza, PostacDuo, PostacOponenta, PoziomTrudnosci, tryb, sezon, data, WygranaLaning, WygranaGra ;
call admin_NEW_history ( "NoNammer", "none", "Swain", "none", "Riven", "High Experienced", "Normal Draft", "Mid S7", "2017-04-24", 'p', '0' );   # Duplikat -- stąd DELETE;
call admin_NEW_history ( "NoNammer", "none", "Vel'Koz", "none", "Annie", "(High)", "Normal Draft", "Mid S7", "2017-04-24", '1', '0' );   # Duplikat -- stąd DELETE;
call admin_NEW_history ( "NoNammer", "none", "Vel'Koz", "none", "Twisted Fate", "none", "Normal Draft", "Mid S7", "2017-04-25", '1', '0' );   # Duplikat -- stąd DELETE;

call admin_NEW_history ( "NoNammer", "none", "Vel'Koz", "none", "Anivia", "none", "Normal Draft", "Mid S7", "2017-04-25", '1', '1' );
call admin_NEW_history ( "NoNammer", "none", "Pantheon", "none", "Yasuo", "(High)", "Ranked Solo/Duo", "Mid S7", "2017-04-25", '1', '1' );
call admin_NEW_history ( "NoNammer", "none", "Renekton", "none", "Gangplank", "Low Experienced", "Ranked Solo/Duo", "Mid S7", "2017-04-25", '1', '1' );
call admin_NEW_history ( "NoNammer", "none", "Vel'Koz", "none", "Brand", "none", "Normal Draft", "Mid S7", "2017-04-26", 'p', '0' );
call admin_NEW_history ( "NoNammer", "none", "Vel'Koz", "none", "Kog'Maw", "(High)", "Normal Draft", "Mid S7", "2017-04-27", '1', '1' );
call admin_NEW_history ( "NoNammer", "none", "Vel'Koz", "none", "Diana", "none", "Ranked Solo/Duo", "Mid S7", "2017-04-28", 'p', '0' );
call admin_NEW_history ( "NoNammer", "none", "Vel'Koz", "none", "Brand", "Medium Experienced", "Ranked Solo/Duo", "Mid S7", "2017-04-29", '1', '1' );
call admin_NEW_history ( "NoNammer", "none", "Vel'Koz", "none", "Morgana", "High Experienced", "Ranked Solo/Duo", "Mid S7", "2017-04-30", '1', '0' );   # 11
call admin_NEW_history ( "NoNammer", "none", "Lux", "none", "Ekko", "High Experienced", "Normal Draft", "Mid S7", "2017-04-30", '1', '1' );
call admin_NEW_history ( "NoNammer", "none", "Vel'Koz", "none", "Taliyah", "(High)", "Ranked Solo/Duo", "Mid S7", "2017-05-02", '1', '1' );
call admin_NEW_history ( "NoNammer", "none", "Pantheon", "none", "Yasuo", "(High)", "Ranked Solo/Duo", "Mid S7", "2017-05-03", '1', '1' );
call admin_NEW_history ( "NoNammer", "none", "Pantheon", "none", "Yasuo", "none", "Ranked Solo/Duo", "Mid S7", "2017-05-04", '1', '0' );   # 15



# call admin_NEW_history ( "NoNammer", "none", "Renekton", "none", "GankPlank", "Low Experienced", "Ranked Solo/Duo", "Mid S7", "2017-04-25", '1', '1' );
	# Podanie nieistniejącej postaci  -- nieprzeszło= ok!

# -> Tak długo jak kożystamy z procedury, wyniki dane są spójne. Nadal możemy ręcznie wpisywać "NULL'e" ;










 # (Workbench);
# CTRL+Z   -- Undo
# CTRL+Y   -- Redo

