
#include "webcrawler.h"


// Add your implementation here

WebCrawler::WebCrawler(int maxUrls, int nInitialURLs,  const char ** initialURLs)
{
  // Allocate space for _urlArray
  // insert the initialURls
  // Update _maxUrls, _headURL and _tailURL
  
  _urlArray = new URLRecord[maxUrls]; //nInitialURLs later
  char ** init = initialURLs;
  
  for(int i = 0; i < nInitialURLs; i++) {
  	_urlArray[i]._url = *init;
  	*init++;
  }
  
  
}

int main() {
	return 0;
}
