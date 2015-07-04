
#include "webcrawler.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "openhttp.h"
#include "SimpleHTMLParser.h"

// Add your implementation here

void onAnchorFound(char * url);

void WebCrawler::onAnchorFound(char * url) {

	char * m = strdup(url);
	char * domain = strdup(_urlArray[_headURL]._url);
	char * urlcat = (char*) malloc(sizeof(char) * (strlen(url) + strlen(domain) + 100));
	
	urlcat = "";
	
	if(m[0] == 'h' && m[1] == 't' && m[2] == 't' && m[3] == 'p') {
	
		if(findArray(url)) return;
		
		_urlArray[_tailURL]._url = strdup(url);
		_tailURL++;
	
	}
	
	else {

		strcat(urlcat,domain);
	
		if(domain[strlen(domain) - 1] == '/') {
			strcat(urlcat,"/");
		}
	
		strcat(urlcat,m);
		
		
		if(findArray(url)) return;
		
		_urlArray[_tailURL]._url = strdup(url);
		_tailURL++;
	
	}
		
}

bool WebCrawler::findArray(char * url) {
	for(int i = 0; i <= _tailURL; i++) {
		char * givenURL = strdup(url);
		char * AtIndex = strdup(_urlArray[i]._url);
		int n1; int n2;
		if(strcmp(fetchHTML(givenURL, &n1), fetchHTML(AtIndex, &n2)) == 0) {
			return false;
		}
	}
	return true;
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



void WebCrawler::crawl() {

	int n;
	
  while (_headURL < _tailURL) {
    
    //Fetch the next URL in _headURL
	
	char * buffer = fetchHTML(_urlArray[_headURL]._url, &n);
	
	if (buffer==NULL) {
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


int main() {
	
	char * url;
	//url = argv[1];
	
	return 0;
}
