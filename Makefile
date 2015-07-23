
all: gethttp webcrawler git-commit

gethttp: gethttp.cpp openhttp.cpp SimpleHTMLParser.cpp
	g++ -o gethttp -g gethttp.cpp openhttp.cpp SimpleHTMLParser.cpp

webcrawler: webcrawler.cpp openhttp.cpp SimpleHTMLParser.cpp HashTableTemplate.h
	g++ -o webcrawler -g webcrawler.cpp openhttp.cpp SimpleHTMLParser.cpp HashTableTemplate.h

git-commit:
	git add Makefile *.h *.cpp  >> .local.git.out || echo
	git commit -a -m "Commit web-crawler" >> .local.git.out || echo

clean:
	rm -f *.o gethttp core
	rm -f *.o webcrawler core
