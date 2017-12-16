game : character.c game_rank.c game_signal.c aiomain.c game_help.c game_menu.c game_start.c game_mode.c game_map.c
	gcc -o game game_rank.c character.c aiomain.c game_help.c game_menu.c game_signal.c game_mode.c game_map.c -lcurses -lrt

