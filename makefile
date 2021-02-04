all: build

hooks.dll: hooks.c hooks.def
	gcc -c hooks.c -o hooks.o
	gcc -shared -o hooks.dll hooks.o hooks.def '-Wl,--enable-stdcall-fixup'

build/logs.o: logs.c
	 gcc -c -o $@ $<

build/utils.o: utils.c
	 gcc -c -o $@ $<

build/handlers.o: handlers.c
	 gcc -c -o $@ $<

build/emulator.o: emulator.c
	 gcc -c -o $@ $<

build/sounds.o: sounds.c
	 gcc -c -o $@ $<

build/global.o: global.c
	 gcc -c -o $@ $<

build: main.c\
	build/logs.o\
	build/handlers.o\
	build/emulator.o\
	build/sounds.o\
	build/global.o\
	build/utils.o	
		gcc -o run\
			build/logs.o\
			build/handlers.o\
			build/emulator.o\
			build/sounds.o\
			build/global.o\
			build/utils.o\
			main.c\
			-lwinmm -lshlwapi

rebuild: clear build

clear:
	rm build
	mkdir build
