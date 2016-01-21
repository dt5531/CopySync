EXENAME = CopySync_client

OBJS = main.o clipboard.o config.o daemon.o
CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wfatal-errors -Werror -Wchar-subscripts -Wparentheses -Wreturn-type -Wmissing-braces -Wundef -Wshadow
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi

all: $(EXENAME)

$(EXENAME): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $@

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $< -o $*.o

clean:
	rm -f *.o $(EXENAME)
