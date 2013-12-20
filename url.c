/* -*- encoding: utf-8; -*- */
/* -*- c-mode -*- */
/* File-name:    <url.c> */
/* Author:       <Xsoda> */
/* Create:       <Friday December 20 12:38:02 2013> */
/* Time-stamp:   <Friday December 20, 15:4:16 2013> */
/* Mail:         <Xsoda@Live.com> */

#include "url.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static char *strndup(const char *str, int n)
{
   char *dst;
   if (n < 0) n = strlen(str);
   if (n == 0) return NULL;
   if ((dst = (char *)malloc(n + 1)) == NULL)
      return NULL;
   memcpy(dst, str, n);
   dst[n] = 0;
   return dst;
}

url_field_t *url_parse (const char *str)
{
   const char *pch;
   url_field_t *url;
   if ((url = (url_field_t *)malloc(sizeof(url_field_t))) == NULL)
      return NULL;
   memset(url, 0, sizeof(url_field_t));
   if (str && str[0])
   {
      url->href = strndup(str, -1);
      pch = strchr(str, ':');   /* parse schema */
      if (pch && pch[1] == '/' && pch[2] == '/')
      {
         url->schema = strndup(str, pch - str);
         str = pch + 3;
      }
      else
         goto __fail;
      pch = strchr(str, '@');   /* parse user info */
      if (pch)
      {
         pch = strchr(str, ':');
         if (pch)
         {
            url->username = strndup(str, pch - str);
            str = pch + 1;
            pch = strchr(str, '@');
            if (pch)
            {
               url->password = strndup(str, pch - str);
               str = pch + 1;
            }
            else
               goto __fail;
         }
         else
            goto __fail;
      }
      if (str[0] == '[')        /* parse host info */
      {
         str++;
         pch = strchr(str, ']');
         if (pch)
         {
            url->host = strndup(str, pch - str);
            str = pch + 1;
            if (str[0] == ':')
            {
               str++;
               pch = strchr(str, '/');
               if (pch)
               {
                  url->port = strndup(str, pch - str);
                  str = pch + 1;
               }
               else
               {
                  url->port = strndup(str, -1);
                  str = str + strlen(str);
               }
            }
         }
         else
            goto __fail;
      }
      else
      {
         pch = strchr(str, ':');
         if (pch)
         {
            url->host = strndup(str, pch - str);
            str = pch + 1;
            pch = strchr(str, '/');
            if (pch)
            {
               url->port = strndup(str, pch - str);
               str = pch + 1;
            }
            else
            {
               url->port = strndup(str, -1);
               str = str + strlen(str);
            }
         }
         else
         {
            pch = strchr(str, '/');
            if (pch)
            {
               url->host = strndup(str, pch - str);
               str = pch + 1;
            }
            else
            {
               url->host = strndup(str, -1);
               str = str + strlen(str);
            }
         }
      }
      if (str[0])               /* parse path, parament and fragment */
      {
         pch = strchr(str, '?');
         if (pch)
         {
            url->path = strndup(str, pch - str);
            str = pch + 1;
            pch = strchr(str, '#');
            if (pch)
            {
               url->parament = strndup(str, pch - str);
               str = pch + 1;
               url->fragment = strndup(str, -1);
            }
            else
            {
               url->parament = strndup(str, -1);
               str = str + strlen(str);
            }
         }
         else
         {
            pch = strchr(str, '#');
            if (pch)
            {
               url->path = strndup(str, pch - str);
               str = pch + 1;
               url->fragment = strndup(str, -1);
               str = str + strlen(str);
            }
            else
            {
               url->path = strndup(str, -1);
               str = str + strlen(str);
            }
         }
      }
   }
   else
   {
__fail:
      url_free(url);
      return NULL;
   }
   return url;
}

void url_free(url_field_t *url)
{
   if (!url) return;
   if (url->href) free(url->href);
   if (url->schema) free(url->schema);
   if (url->username) free(url->username);
   if (url->password) free(url->password);
   if (url->host) free(url->host);
   if (url->port) free(url->port);
   if (url->path) free(url->path);
   if (url->parament) free(url->parament);
   if (url->fragment) free(url->fragment);
   free(url);
}

void url_field_print(url_field_t *url)
{
   if (!url) return;
   fprintf(stdout, "\nuri field:\n");
   fprintf(stdout, "  - href:     '%s'\n", url->href);
   fprintf(stdout, "  - schema:   '%s'\n", url->schema);
   if (url->username)
      fprintf(stdout, "  - username: '%s'\n", url->username);
   if (url->password)
      fprintf(stdout, "  - password: '%s'\n", url->password);
   fprintf(stdout, "  - host:     '%s'\n", url->host);
   if (url->port)
      fprintf(stdout, "  - port:     '%s'\n", url->port);
   if (url->path)
   fprintf(stdout, "  - path:     '%s'\n", url->path);
   if (url->parament)
      fprintf(stdout, "  - parament: '%s'\n", url->parament);
   if (url->fragment)
      fprintf(stdout, "  - fragment: '%s'\n", url->fragment);
}

int main()
{
   char *str[] = {
      "scheme://host",
      "http://[::1]:8080/index.html",
      "scheme://username:password@host",
      "scheme://host:port",
      "scheme://host:port/path?id=1&method=get#fragment",
      "scheme://host/path/to/subpath#fragment",
      "scheme://username:password@host/path?name=test#fragment",
      "scheme://username:password@host:port/path?name=test#fragment",
      NULL
   };
   for (int i = 0; str[i]; i++)
   {
      url_field_t *url = url_parse(str[i]);
      url_field_print(url);
      url_free(url);
   }
   return 0;
}
