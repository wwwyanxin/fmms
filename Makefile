#为.cpp文件指定搜索目录
vpath %.cpp src
#为.h文件指定搜索目录
vpath %.h include

CC = g++
CFLAGS = -std=c++11 -g
LIB = -lhiredis -ljsoncpp -lmysqlcppconn -lglog -lgflags -pthread
OUT_PATH = /var/www/fmms/cgi-bin/

hello_world.cgi: hello_world.cpp
	$(CC) $(CFLAGS) $(LIB) $^ -o $(OUT_PATH)$@
	
clean:
		rm -f $(OUT_PATH)*.cgi
	    rm -f build/*.o
