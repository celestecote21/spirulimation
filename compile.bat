mingw32-gcc.exe -Wall -g -Iinclude -c E:\programation\C\spiruline\sources\main.c -o obj\Debug\sources\main.o -w
mingw32-gcc.exe -Wall -g -Iinclude -c E:\programation\C\spiruline\sources\jeu.c -o obj\Debug\sources\jeu.o -w
mingw32-gcc.exe -Wall -g -Iinclude -c E:\programation\C\spiruline\sources\editeur.c -o obj\Debug\sources\editeur.o -w
mingw32-gcc.exe -Wall -g -Iinclude -c E:\programation\C\spiruline\sources\logique.c -o obj\Debug\sources\logique.o -w
mingw32-gcc.exe -Wall -g -Iinclude -c E:\programation\C\spiruline\sources\vente.c -o obj\Debug\sources\vente.o -w
mingw32-gcc.exe -Llib -o spiruline.exe obj\Debug\sources\main.o obj\Debug\sources\jeu.o obj\Debug\sources\logique.o obj\Debug\sources\vente.o obj\Debug\sources\editeur.o -lmingw32 -lSDLmain -lSDL lib\SDL_image.lib lib\SDL_TTF.lib
