CC=gcc
COMMON= -Wall -Wextra -Wfloat-equal -pedantic -std=c90 -Werror
SDLCFLAGS=`sdl2-config --cflags`
SDLLIBS=`sdl2-config --libs`
DEBUG= -g3
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
PRODUCTION= $(COMMON) -O3
LDLIBS = -lm


testrealloc_s : test/testrealloc.c Realloc/realloc.h Realloc/realloc.c General/general.h General/general.c
	$(CC) test/testrealloc.c Realloc/realloc.c General/general.c -o testrealloc_s  $(SANITIZE) $(LDLIBS)

testrealloc_v : test/testrealloc.c Realloc/realloc.h Realloc/realloc.c General/general.h General/general.c
	$(CC) test/testrealloc.c Realloc/realloc.c General/general.c -o testrealloc_v  $(VALGRIND) $(LDLIBS)


testparser_s : test/testparser.c Parser/parser.h Parser/parser.c Realloc/realloc.h Realloc/realloc.c General/general.h General/general.c
	$(CC) test/testparser.c Parser/parser.c Realloc/realloc.c General/general.c -o testparser_s  $(SANITIZE) $(LDLIBS)

testparser_v : test/testparser.c Parser/parser.h Parser/parser.c Realloc/realloc.h Realloc/realloc.c General/general.h General/general.c
	$(CC) test/testparser.c Parser/parser.c Realloc/realloc.c General/general.c -o testparser_v  $(VALGRIND) $(LDLIBS)


teststack_s: test/teststack.c Interp/Stack/stack.h Interp/Stack/linked.c General/general.h General/general.c
	$(CC) test/teststack.c Interp/Stack/linked.c General/general.c -o teststack_s  $(SANITIZE) $(LDLIBS)

teststack_v: test/teststack.c Interp/Stack/stack.h Interp/Stack/linked.c General/general.h General/general.c
	$(CC) test/teststack.c Interp/Stack/linked.c General/general.c -o teststack_v  $(VALGRIND) $(LDLIBS)


testpoint: test/testpoint.c Interp/SDL/neillsdl2.h Interp/SDL/neillsdl2.c Interp/Point/point.h Interp/Point/point.c General/general.h General/general.c
	$(CC) test/testpoint.c Interp/SDL/neillsdl2.c Interp/Point/point.c General/general.c -o testpoint  $(SDLCFLAGS) $(SDLLIBS) $(LDLIBS)

testinterp: test/testinterp.c Interp/pars-interp.h Interp/pars-interp.c Interp/interp.h Interp/interp.c Interp/SDL/neillsdl2.h Interp/SDL/neillsdl2.c Interp/Point/point.h Interp/Point/point.c Interp/Stack/stack.h Interp/Stack/linked.c Interp/Varpool/varpool.h Interp/Varpool/varpool.c Realloc/realloc.h Realloc/realloc.c General/general.h General/general.c
	$(CC) test/testinterp.c Interp/pars-interp.c Interp/interp.c Interp/Stack/linked.c Interp/Varpool/varpool.c Interp/SDL/neillsdl2.c Interp/Point/point.c Realloc/realloc.c General/general.c -o testinterp $(SDLCFLAGS) $(SDLLIBS) $(LDLIBS)


clean:
	rm -fr testrealloc_s testrealloc_v testparser_s testparser_v teststack_s teststack_v testpoint testinterp

realloc: testrealloc_s testrealloc_v
	./testrealloc_s DATA/basic.ttl
	./testrealloc_s DATA/loop.ttl
	./testrealloc_s DATA/nested.ttl
	./testrealloc_s DATA/usevar.ttl
	valgrind ./testrealloc_v DATA/basic.ttl
	valgrind ./testrealloc_v DATA/loop.ttl
	valgrind ./testrealloc_v DATA/nested.ttl
	valgrind ./testrealloc_v DATA/usevar.ttl

parse: testparser_s testparser_v


stack: teststack_s teststack_v
	./teststack_s DATA/stack_testsample
	valgrind ./teststack_v DATA/stack_testsample

point: testpoint
	./testpoint

interp: testinterp


test: parse interp
	./testparser_s DATA/basic.ttl
	./testparser_s DATA/loop.ttl
	./testparser_s DATA/nested.ttl
	./testparser_s DATA/usevar.ttl
	./testinterp DATA/basic.ttl
	./testinterp DATA/loop.ttl
	./testinterp DATA/nested.ttl
	./testinterp DATA/usevar.ttl
	valgrind ./testparser_v DATA/basic.ttl
	valgrind ./testparser_v DATA/loop.ttl
	valgrind ./testparser_v DATA/nested.ttl
	valgrind ./testparser_v DATA/usevar.ttl
