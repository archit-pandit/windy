set files=src\glad.c src\main.c
set libs=C:\_root\hobbies\coding\projects\windy\lib\SDL3.lib C:\_root\hobbies\coding\projects\windy\lib\freetype.lib

CL /Zi /I C:\_root\hobbies\coding\projects\windy\include %files% /link %libs% /OUT:mygame.exe
