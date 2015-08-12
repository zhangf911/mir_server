.PHONY : clean

######## Sword Library Makefile########
Project = Library
Version	= 0.0.1
Target = $(Project).$(Version).a
TargetLib = lib$(Project).a
Home = ../../../
LibDir = $(Home)libs/MyLibrary/lib

$(shell mkdir -p ${LibDir})

######## Compile Set #######

CC = g++

AR = ar -rc

MV = mv

CFLAGES = -std=c++11 -g -Wall -I /home/zhangf/workspace/boost_1_55_0/ -I $(Home)libs/MySQL/include -I $(Home)libs/MySQLConnectorC++/include -static
# -DBOOST_SYSTEM_NO_DEPRECATED
# 动态库连接 LDFLAGS = -fPIC -shared

LFLAGES = -L. -L/home/zhangf/workspace/boost_1_55_0/stage/lib

CPPSrc = $(wildcard *.cpp)
CSrc = $(wildcard *.c)
CPPOBJ = $(CPPSrc:.cpp=.o)
COBJ = $(CSrc:.c=.o)

######## Target ########

%.o : %.cpp
	$(CC) -c $(CFLAGES) $< -o $@
	echo $<

%.o : %.c
	$(CC) -c $(CFLAGES) $< -o $@
	echo $<

$(TargetLib) : $(CPPOBJ) $(COBJ)
	$(AR) $(TargetLib) $(CPPOBJ) $(COBJ)
	$(MV) $(TargetLib) $(LibDir)


clean : 
	rm -f *.o
	rm -f $(TargetLib)
