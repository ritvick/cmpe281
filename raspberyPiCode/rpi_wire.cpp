#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <curl/curl.h>
#include <iostream.h>

#define temp_sensor  "/sys/bus/w1/devices/10-000800c47560/w1_slave"

int main(int argc, char ** argv)
{
	int fd =0,n=0,i=0;
	CURL *curl;
	CURLcode res;
	
	// Open the Port. We want read/write, no "controlling tty" status, and open it no matter what state DCD is in
	fd = open(temp_sensor, O_RDONLY);
	if (fd == -1)
	{
		perror("open_port: Unable to open /sys/bus/w1/devices/10-000800c47560/w1_slave - ");
		return(-1);
	}

	// Read up to 255 characters from the port if they are there
	char buf[256];
	char *pch ;
	char newbuf[128];
	unsigned int temperature =0;
	n = read(fd, (void*)buf, 255);
	if (n < 0)
	{
		perror("Read failed - ");
		return -1;
	}
	else if (n == 0)
	{
		printf("No data on port\n");
	}
	else
	{
		buf[n] = '\0';
	}

	pch = strstr (buf,"t=");
	bzero(newbuf,0);
	memcpy(newbuf,pch,10);
	printf("%s\n",&newbuf[2]);
	//temperature = atoi(&newbuf[2]);
	//printf("%d\n",temperature);
 
	/* In windows, this will init the winsock stuff */ 
	curl_global_init(CURL_GLOBAL_ALL);

	/* get a curl handle */ 
	curl = curl_easy_init();
	if(curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");
	    /* example.com is redirected, so we tell libcurl to follow redirection */ 
	    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	 
	    /* Perform the request, res will get the return code */ 
	    res = curl_easy_perform(curl);
	    /* Check for errors */ 
	    if(res != CURLE_OK)
	      fprintf(stderr, "curl_easy_perform() failed: %s\n",
	              curl_easy_strerror(res));
	 	else {
	 		cout<<"Curl Succesfull";
	 	}
	    /* always cleanup */ 
	    curl_easy_cleanup(curl);
	    
	}
	
	
  
	close(fd);
	return 0;
}
