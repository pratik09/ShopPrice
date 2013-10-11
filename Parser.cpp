#include<iostream>
#include<fstream>
#include<sstream>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdio.h>
#include<curl/curl.h>
 
using namespace std;

void parseDocument(string, ofstream&);
string getHTMLSource(string);

int main ()
{
   ifstream ifs;
   ofstream ofs;
   string pathToReadFile = "/cise/homes/pjain/ShopPrice/crawledData/linkdb/links";
   
   string pathToWriteFile = "/cise/homes/pjain/ShopPrice/results/";
   mkdir(pathToWriteFile.c_str(), S_IRWXU);

   ifs.open(pathToReadFile.c_str(), std::fstream::in);
   ofs.open((pathToWriteFile + "productDetails").c_str(), std::fstream::out | std::fstream::app);
  
   char line[256];
   int count = 0;
   while(ifs.good() && count < 2)
    {
       ifs.getline(line, 256);
       string lineS = line;
       istringstream ss(lineS);
       string token;
       bool fromUrlToken = false;
       bool httpUrlToken = false;
       
       while( (ss >> token) )
         {
           if( (token.size() > 7) && (token.substr(0, 7)=="http://") )
             {
                parseDocument(token, ofs);
                count = count + 1;  
             }
           else if(token == "fromUrl:")
             {
                if(ss >> token)
                  {
                     parseDocument(token, ofs);
                     count = count + 1;
                  }    
                 else
                  {
                     fromUrlToken = true;
                  }      
             }
         }
    }

    ofs.close();
    return 0;
}


void parseDocument(string url, ofstream &ofs)
{
    url = url + "\n";
    ofs.write(url.c_str(), url.size());
    cout<<url<<endl;    
   
    string page =  getHTMLSource(url);
    
    cout<<endl<<endl<<page<<endl<<endl;\
}

string getHTMLSource(string url)
{

  CURL *curl;
  CURLcode res;
 
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "url");
    /* example.com is redirected, so we tell libcurl to follow redirection */ 
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
 
    /* Perform the request, res will get the return code */ 
    res = curl_easy_perform(curl);
    /* Check for errors */ 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    CString str(curl_easy_strerror(res));
    /* always cleanup */
    curl_easy_cleanup(curl);

    return str;
}
