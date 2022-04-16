all: 
	yacc -d exptree.y
	lex exptree.l
	lex -o translate.yy.c ltranslate.l
	gcc lex.yy.c y.tab.c -o a.out
	gcc translate.yy.c -o l.out 
	./a.out
	./l.out
	
clean:
	rm -f lex.yy.c y.tab.c translate.yy.c y.tab.h a.out l.out B191143CS.xsm
