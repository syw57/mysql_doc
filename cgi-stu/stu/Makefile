CC=gcc
AFLAGS=-Wall -g
LDFLAGS= -lmysqlclient
OBJS= add.cgi del.cgi mod.cgi sel.cgi selc.cgi addsc.cgi addstu.cgi slccl.cgi dlecla.cgi  modcla.cgi delsc.cgi modsc.cgi addtea.cgi deltea.cgi modtea.cgi seltea.cgi addschool.cgi delschool.cgi modschool.cgi selschool.cgi addtc.cgi deltc.cgi seltc.cgi 

all:$(OBJS)

$(OBJS):%.cgi:%.c
	$(CC) $(AFLAGS) $< cgic.c -o $@ $(LDFLAGS)

.PHONY:clean
clean:
	rm ./*.cgi
install:
	cp *.cgi /usr/lib/cgi-bin/sx
	cp head.html footer.html /usr/lib/cgi-bin/sx/
