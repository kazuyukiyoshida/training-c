EXEC = sample_convert
OBJS = sample_convert.o
LDLIBS := -lopencv_core -lopencv_highgui -lopencv_imgproc -lm

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

romfs:
	$(ROMFSINST) /usr/bin/$(EXEC)

clean:
