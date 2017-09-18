PROGRAM = interactive_deduction
CC = g++
CFLAGS = -pedantic -ansi -std=c++0x
LEX = flex  
YACC = bison
YFLAGS = -d -v

$(PROGRAM): interactive_deduction.tab.o lex.yy.o formula.o naturaldeduction.o
	$(CC) $(CFLAGS) -o $@ $^
interactive_deduction.tab.o: interactive_deduction.tab.cpp
	$(CC) $(CFLAGS) -c -o $@ $<
lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) -c -o $@ $<
interactive_deduction.tab.cpp interactive_deduction.tab.hpp : interactive_deduction.ypp
	$(YACC) $(YFLAGS) $<
lex.yy.c: interactive_deduction.l interactive_deduction.tab.hpp
	$(LEX) $<
formula.o: formula.cpp formula.hpp
	$(CC) $(CFLAGS) -c -o $@ $<
naturaldeduction.o: naturaldeduction.cpp naturaldeduction.hpp
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	-rm -f *~ $(PROGRAM) *.c *.tab.hpp *.o *.tab.cpp interactive_deduction.output