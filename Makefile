CUR_DIR = $(shell pwd)

#为.cpp文件指定搜索目录
vpath %.cpp src
#为.h文件指定搜索目录
vpath %.h include
#为.o文件制定搜索目录
vpath %.o build

CC = g++
RELEASE = -o3  #开启o3优化
DEBUG = -o0 -g  #调试模式 不开启优化
CFLAGS = -std=c++11 -pthread $(DEBUG) $(LIB)
OUT_PATH = /var/www/fmms/cgi-bin/
COMPILE_PATH = build/

#patsubst是patten substitude的缩写，匹配替代的意思。这句是在SRC中找到所有.cpp 结尾的文件，然后把所有的.cpp换成.o。
OBJECTS = $(patsubst %.cpp,$(COMPILE_PATH)%.o,$(SOURCES)) 

LIB = -lhiredis -ljsoncpp -lmysqlcppconn -lglog -lgflags 

SOURCES = hello_world.cpp util.cpp WebServer.cpp Handler.cpp DBConn.cpp DAO.cpp

TARGET = hello_world.cgi


all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $(OUT_PATH)$@

$(OBJECTS): $(COMPILE_PATH)%.o:%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
		rm -f $(OUT_PATH)*.cgi
	    rm -f $(COMPILE_PATH)*.o

