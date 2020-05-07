CC=g++

override CFLAGS+=-DIL_STD -c -Wall -g --std=c++11 -D_GLIBCXX_USE_CXX11_ABI=0 -I/opt/ibm/ILOG/CPLEX_Studio1261/concert/include -I/opt/ibm/ILOG/CPLEX_Studio1261/cplex/include

override CFLAGSL+=/usr/lib/x86_64-linux-gnu/libpthread-2.31.so /opt/ibm/ILOG/CPLEX_Studio1261/concert/lib/x86-64_linux/static_pic/libconcert.a /opt/ibm/ILOG/CPLEX_Studio1261/cplex/lib/x86-64_linux/static_pic/libcplex.a /opt/ibm/ILOG/CPLEX_Studio1261/cplex/lib/x86-64_linux/static_pic/libilocplex.a /usr/lib/x86_64-linux-gnu/libm.so.6 /opt/ibm/ILOG/CPLEX_Studio1261/cplex/lib/x86-64_linux/static_pic/libilocplex.a /opt/ibm/ILOG/CPLEX_Studio1261/cplex/lib/x86-64_linux/static_pic/libcplex.a /opt/ibm/ILOG/CPLEX_Studio1261/concert/lib/x86-64_linux/static_pic/libconcert.a /usr/lib/x86_64-linux-gnu/libm.so.6 /usr/lib/x86_64-linux-gnu/libpthread-2.31.so

override LDFLAGS+=-DIL_STD -L/opt/ibm/ILOG/CPLEX_Studio1261/cplex/lib/x86-64_linux/static_pic/ -L/opt/ibm/ILOG/CPLEX_Studio1261/concert/lib/x86-64_linux/static_pic/ /usr/lib/x86_64-linux-gnu/libpthread-2.31.so /opt/ibm/ILOG/CPLEX_Studio1261/concert/lib/x86-64_linux/static_pic/libconcert.a /opt/ibm/ILOG/CPLEX_Studio1261/cplex/lib/x86-64_linux/static_pic/libcplex.a /opt/ibm/ILOG/CPLEX_Studio1261/cplex/lib/x86-64_linux/static_pic/libilocplex.a /usr/lib/x86_64-linux-gnu/libm.so.6 /opt/ibm/ILOG/CPLEX_Studio1261/cplex/lib/x86-64_linux/static_pic/libilocplex.a /opt/ibm/ILOG/CPLEX_Studio1261/cplex/lib/x86-64_linux/static_pic/libcplex.a /opt/ibm/ILOG/CPLEX_Studio1261/concert/lib/x86-64_linux/static_pic/libconcert.a /usr/lib/x86_64-linux-gnu/libm.so.6 /usr/lib/x86_64-linux-gnu/libpthread-2.31.so

SOURCES=                          \
    mainTest.cpp                      \
    Genetic2_old.cpp       \
    ILS.cpp			  \
    Individual.cpp                \
    Instance.cpp                  \
    Solver.cpp               

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=BLVL2_OLD_TEST
all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(CFLAGSL)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ $(CFLAGSL)

.PHONY: clean
clean:
	$(RM) $(OBJECTS) $(EXECUTABLE)
