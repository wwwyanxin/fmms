#为.cpp文件指定搜索目录
vpath %.cpp src
#为.h文件指定搜索目录
vpath %.h include

CC = g++
RELEASE = -o3  #开启o3优化
DEBUG = -o0 -g  #调试模式 不开启优化
CFLAGS = -std=c++11 -pthread $(DEBUG)
LIB = -lhiredis -ljsoncpp -lmysqlcppconn -lglog -lgflags 
OUT_PATH = /var/www/fmms/cgi-bin/

hello_world.cgi: hello_world.cpp util.cpp WebServer.cpp Handler.cpp DBConn.cpp
	$(CC) $(CFLAGS) $(LIB) $^ -o $(OUT_PATH)$@
	
clean:
		rm -f $(OUT_PATH)*.cgi
	    rm -f build/*.o
