#include "webcrawler.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "openhttp.h"
#include "SimpleHTMLParser.h"

// Add your implementation here
char * _buffer = (char*) malloc(5000);
char * buffer_start = _buffer;

char * buffer_k = (char*) malloc(500);
char * buffer_k_p = buffer_k;

char * buffer_m = (char*) malloc(500);
char * buffer_m_p = buffer_m;

char * description = (char*) malloc(10000);
char * desc = description;

int check = 0;

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
  strcpy(buffer_k, "");
  strcpy(buffer_m, "");
  
  _urlToUrlRecord = new HashTableTemplate<int>();
    
  for(int i = 0; i < nInitialURLs; i++) {
  	_urlArray[i]._url = strdup(*init);
  	_urlArray[i]._description = strdup("default");
  	*init++;
  }
 
  
}


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
			//Adding to URLtoURLRecord
			
			//printf("Absolute: Above insert\n");
			_urlToUrlRecord->insertItem(urlcase, _tailURL);
			//printf("Absolute: Below insert\n");
			//Adding to _urlArray
			_urlArray[_tailURL]._url = strdup(urlcase);
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
			
			//Adding to URLtoURLRecord
			//printf("Relative: Above insert\n");
			_urlToUrlRecord->insertItem(urlcat, _tailURL);
			//printf("Relative: Below insert\n");
			
			//Adding to _urlArray	
			_urlArray[_tailURL]._url = strdup(urlcat);
			_tailURL++;
	
		}
	}
	return;
		
}



void
WebCrawler::onContentFound(char character) {
	
	char c = character;
	
	*_buffer = c;								//___________description = _buffer, desc = buffer_start
	_buffer++;
	*_buffer = '\0';
	strcpy(buffer_m,"");
	strcpy(buffer_k,"");
	
	if(character == '[') {
	buffer_start[strlen(buffer_start) - 3] = '\0';
		strcpy(buffer_m,"\n");
		strcat(buffer_m,"Description:");
		strcat(buffer_m,buffer_start);
		strcat(buffer_m,"\n");
		
		_buffer = buffer_start;
	}
	if(character == ']') {
	buffer_start[strlen(buffer_start) - 3] = '\0';
		strcpy(buffer_k,"\n");
		strcat(buffer_k,"Keywords:");
		strcat(buffer_k,buffer_start);
		strcat(buffer_k,"\n");

		_buffer = buffer_start;
	}
	if(character == '_') {
		memset (buffer_start,'\0',strlen(buffer_start));
		memset (_buffer,'\0',strlen(_buffer));
		_buffer = buffer_start;
	}
	
	if(buffer_m == NULL || strlen(buffer_m) == 0) {
		strcpy(buffer_m,"");
	}
	
	if(buffer_k == NULL || strlen(buffer_k) == 0) {
		strcpy(buffer_k,"");
	}
	
	
	strcat(description, buffer_m);
	
	strcat(description, buffer_k);
	
	_urlArray[_headURL]._description = strdup(description);
	description = desc;	
	return;	
		
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


void WebCrawler::printArray() {
	printf("URL Array:\n");
	for(int i = 0; i < getTail(); i++) {
		printf("%d._____\nURL: %s\nDISC:%s\n", i + 1, _urlArray[i]._url, _urlArray[i]._description);
	}
}



void WebCrawler::setNull(char * str) {
	int len = strlen(str);
	char * s = str;
	for(int i = 0; i < len; i++) {
		*s = '\0';
		s++;
	}
}


int WebCrawler::getTail() { return _tailURL;}

void WebCrawler::setTail(int tail) {_tailURL = tail;}

char * WebCrawler::removeNextLn(char * description) {
	char * d = description;
	char * desc_cpy = (char*) malloc(strlen(description) + 10);
	strcpy(desc_cpy, "a");
	char * desc_cpy_start = desc_cpy;
	//printf("desc_cpy_start %s\n", desc_cpy_start);
	while(*d) {
		if(*d != '\n') {
			*desc_cpy = *d;
			desc_cpy++;
		}
		d++;	
	}
	desc_cpy = '\0';
	//printf("desc_cpy_start %s\n", desc_cpy_start);
	return desc_cpy_start;
}

void WebCrawler::urlText(char * file_name) {
	FILE * f = fopen(file_name, "w");
	int i = 0;
	if(f != NULL) {
		while(i < _tailURL) {
		
			if((_urlArray[i]._description) == NULL) fprintf(f,"%d %s\n%s\n\n",i + 1 ,_urlArray[i]._url , "<TITLE IS NULL>");
				
			else fprintf(f,"%d %s\n%s\n\n",i + 1,_urlArray[i]._url , removeNextLn(_urlArray[i]._description));
			
			i++;
			
		}
		fclose(f);
	}	
	else return;
}


int main(int argc, const char ** argv) { 
	
	  const char ** urlSet = argv;
		urlSet += 1;
		int maxURLs = 10;
		
		printf("urlSet %s\n", *urlSet);
		
		WebCrawler * wCrawler = new WebCrawler(maxURLs, argc - 1, urlSet);
		int i = 0;
		
		//wCrawler->setTail(argc - 1);
		wCrawler->crawl();
		printf("tail %d\n", wCrawler->getTail());
		wCrawler->urlText(url_file);
		wCrawler->printArray();
		
	return 0;
}
