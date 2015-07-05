
#include "webcrawler.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "openhttp.h"
#include "SimpleHTMLParser.h"

// Add your implementation here

void WebCrawler::onAnchorFound(char * url) {

	char * m = strdup(url);
	char * domain = strdup(_urlArray[_headURL]._url);
	char * urlcat = (char*) malloc(sizeof(char) * (strlen(url) + strlen(domain) + 100));
	char * urlcase = (char*) malloc(sizeof(char) * (strlen(url) + strlen(domain) + 100));
	
	strcpy(urlcat, "");
	strcpy(urlcase, "");
	
	if(_tailURL < _maxURLs) {
		
		if(m[0] == 'h' && m[1] == 't' && m[2] == 't' && m[3] == 'p') { //HTTPS ______________________________________
		
			if(m[4] == 's') return;
			if(findArray(url)) return;
						
			else strcat(urlcase,m);
			
			_urlArray[_tailURL]._url = strdup(urlcase);
			_urlArray[_tailURL]._description = strdup("default");
			_tailURL++;
		
		}
	
		else {
			
			if(url[0] == '/' && url[1] == '/') return;
			
			if(strlen(m) <= 1) return;
						
			strcat(urlcat,domain);

			
			if(url[0] == '/' && domain[strlen(domain) - 1] == '/') {
					char * s = strdup(url);
					*s++;
					strcat(urlcat,s);
			}
			
			if((url[0] == '/' && domain[strlen(domain) - 1] != '/') || (url[0] != '/' && domain[strlen(domain) - 1] == '/')) {
				strcat(urlcat,m);
			}
			
			if(url[0] != '/' && domain[strlen(domain) - 1] != '/') {
				strcat(urlcat,"/");
				strcat(urlcat,m);
			}
	
		
			if(findArray(urlcat)) return;
		
			_urlArray[_tailURL]._url = strdup(urlcat);
			_urlArray[_tailURL]._description = strdup("default");
			_tailURL++;
	
		}
	}
	return;
		
}


void
WebCrawler::onContentFound(char * url) {
	return;
}

bool WebCrawler::findArray(char * url) {		
	int n1, n2;
	for(int i = 0; i < _tailURL; i++) {
		char * givenURL = strdup(url);
		char * AtIndex = strdup(_urlArray[i]._url);
		if(strcmp(givenURL, AtIndex) == 0) {
			return true;
		}
	}
	return false;
}


WebCrawler::WebCrawler(int maxURLs, int nInitialURLs,  const char ** initialURLs)
{
  // Allocate space for _urlArray
  // insert the initialURls
  // Update _maxUrls, _headURL and _tailURL
  
  _urlArray = new URLRecord[maxURLs]; //nInitialURLs later
  _maxURLs = maxURLs;
  _headURL = 0;
  _tailURL = nInitialURLs;
  const char ** init = initialURLs;
  
    
  for(int i = 0; i < nInitialURLs; i++) {
  	_urlArray[i]._url = strdup(*init);
  	_urlArray[i]._description = strdup("default");
  	*init++;
  }
 
  
}

int WebCrawler::getTail() { return _tailURL;}

void WebCrawler::setTail(int tail) {_tailURL = tail;}

void WebCrawler::printArray() {
	printf("URL Array:\n");
	for(int i = 0; i < getTail(); i++) {
		printf("%d URL: %s\n%d DISC:%s\n", i + 1, _urlArray[i]._url, i + 1, _urlArray[i]._description);
	}
}

void WebCrawler::crawl() {

	int n;
	
  while (_headURL < _tailURL) {
    
    //Fetch the next URL in _headURL
	
	char * buffer = fetchHTML(_urlArray[_headURL]._url, &n);
	
	if (buffer == NULL) {
		  fprintf(stderr, "*** Cannot open URL\n");	  
	}
	else 	parse(buffer, n);
	
	_headURL++;


    //Increment _headURL

//_____________________---//    If the document is not text/html
     

          //continue;

    /*Get the first 100 characters (at most) of the document without tags. Add this 
       description to theURL record for this URL.



    Find all the hyperlinks of this document and add them to the
      _urlArray and _urlToUrlRecord if they are not already in the
      _urlToUrlRecord. Only insert up to _maxURL entries.

    For each word in the document without tags, add the index of this URL to
      a URLRecordList in the _wordToURLRecordList table if the URL is not already there.*/
  }//while
}


int main(int argc, const char ** argv) { 

	  const char ** urlSet = argv;
		urlSet += 1;
		int maxURLs = 10;
		
		printf("urlSet %s\n", *urlSet);
		
		WebCrawler * wCrawler = new WebCrawler(maxURLs, argc - 1, urlSet);
		
		//wCrawler->setTail(argc - 1);
		wCrawler->crawl();
		printf("tail %d", wCrawler->getTail());
		wCrawler->printArray();
		
	return 0;
}
