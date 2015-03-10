#ifndef CURLBKPS_HPP_INCLUDED
#define CURLBKPS_HPP_INCLUDED

#include "mainStructs.hpp"
#include <curl/curl.h>
#include <iostream>

size_t write_data(char *buffer, size_t size, size_t nitems, void *outstream);
int progress_callback(void *clientp,   curl_off_t dltotal,   curl_off_t dlnow,   curl_off_t ultotal,   curl_off_t ulnow);



#endif // CURLBKPS_HPP_INCLUDED
