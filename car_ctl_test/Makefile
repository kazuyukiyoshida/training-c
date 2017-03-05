EXEC = car_ctl_test
OBJS = car_ctl_test.o
LDLIBS =

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

romfs:
	$(ROMFSINST) /usr/bin/$(EXEC)

clean:
