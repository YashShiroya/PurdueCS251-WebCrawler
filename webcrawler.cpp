
#include "webcrawler.h"

// Add your implementation here

WebCrawler::WebCrawler(int maxUrls, int nInitialURLs,  const char ** initialURLs)
{
  // Allocate space for _urlArray
  // insert the initialURls
  // Update _maxUrls, _headURL and _tailURL
  
  _urlArray = new URaLRecord[maxUrls + nInitialURLs];
}

int main() {
	return 0;
}
