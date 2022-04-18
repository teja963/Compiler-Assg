all: 
	yacc -d exptree.y
	lex -i exptree.l
	gcc lex.yy.c y.tab.c -o a.out
	lex ltranslate.l
	gcc lex.yy.c -o ltranslate.out
	./a.out
	./ltranslate.out
	
clean:
	rm -f lex.yy.c y.tab.c y.tab.h a.out ltranslate.out B191143CS.xsm
