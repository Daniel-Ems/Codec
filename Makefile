CPPFLAGS+= -Wall -Wextra -Wpedantic -Wextra -Wpedantic -Wwrite-strings 
CPPFLAGS+= -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline

CFLAGS+=-std=c11
CFLAGS+=-g
LDLIBS += -lm



BINARY = decode
OBJECT = decode.o structs.o pay_functions.o

$(BINARY):$(OBJECT)
.PHONY: clean debug profile

$(BINARY): 

debug: CLFAGS+=-g
debug: $(BINARY)

profile: CFLAGS+=-pg
profile: LDFLAGS+=-pg
profile: $(BINARY)


clean:
	$(RM) $(BINARY) $(OBJECT)







