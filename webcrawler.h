
// CS251 Definitions for web-crawler

#include "HashTableTemplate.h"
#include "openhttp.h"
#include "SimpleHTMLParser.h"

#define url_file "url.txt"
#define word_file "word.txt"

// Stores a URL and the first 100 words


struct URLRecord {
  char * _url;          // URL of the document.
  char * _title;
  char * _keywords;
  char * _description;  // First 100 words of the document without tags
};

// Used to implement a list of URL indexes of the url array.
// There is one list of URLs for each word 
struct URLRecordList {
  int _urlRecordIndex;     // Index into the URL Array
  URLRecordList * _next;   // Pointer to the next URL Record in the list
};

class WebCrawler : public SimpleHTMLParser {
  // The url array stores all the URLs that have been scanned
  int _maxURLs;            // Max size of the URL array
  URLRecord * _urlArray;   // Array of URLs 
  int _headURL;            // Points to the next URL to scan by the web crawler
  int _tailURL;            // Next position unused in the urlArray

  HashTableTemplate<int> * _urlToUrlRecord;         //  maps a URL to its index in the URLArray 
  
  //HashTableTemplateIterator<Data> * _iterator;
  
  HashTableTemplate<URLRecordList *> *_wordToURLRecordList; // maps a word to a list of URLs

 public:
  // Create a web crawler object with the initial urls
  WebCrawler(int maxUrls, int nurlRoots, const char ** urlRoots);
  
  // crawl the web
  void crawl();
  
  //Helper Method Find
  bool findArray(char * url);
  int getTail();
  void setTail(int tail);
  void printArray();
  void setNull(char * str);
  void InsertNextWord(URLRecord *_array);
  char * removeNextLn(char * description);
  //Pareser Sublcassing
  void onAnchorFound(char * url);
  void urlText(char * file_name);
  void onContentFound(char b);
  void setDescDefault();
  
  
  //bool parse(char * buffer, int n);

  //bool match(char **b, const char *m);
  // Write array of URLs and descriptions to file
  void writeURLFile(const char * urlFileName);

  // Write list of words with their urls to file
  void writeWordFile(const char *wordFileName);

  // Add any other objects you may need
};


