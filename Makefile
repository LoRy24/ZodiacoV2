MAIN_FILE = main.cpp

build-run:
	g++ -o ./out/program.exe ./src/${MAIN_FILE} -I./include -L./libs -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
	cls
	./out/program.exe