PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

OBJS = EVP_HMAC_SHA256.o test.o

ifeq ($(BUILD_MODE),debug)
	CFLAGS += -g
else ifeq ($(BUILD_MODE),run)
	CFLAGS += -O2
else ifeq ($(BUILD_MODE),linuxtools)
	CFLAGS += -g -pg -fprofile-arcs -ftest-coverage
	LDFLAGS += -pg -fprofile-arcs -ftest-coverage
	EXTRA_CLEAN += EVP_HMAC_SHA256.gcda EVP_HMAC_SHA256.gcno $(PROJECT_ROOT)gmon.out
	EXTRA_CMDS = rm -rf EVP_HMAC_SHA256.gcda
else
    $(error Build mode $(BUILD_MODE) not supported by this Makefile)
endif

LIBS = -lcrypto -lssl

all:	EVP_HMAC_SHA256

EVP_HMAC_SHA256:	$(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)
	$(EXTRA_CMDS)

%.o:	$(PROJECT_ROOT)%.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

%.o:	$(PROJECT_ROOT)%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

clean:
	rm -fr EVP_HMAC_SHA256 $(OBJS) $(EXTRA_CLEAN)
