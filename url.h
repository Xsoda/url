/* -*- encoding: utf-8; -*- */
/* -*- c-mode -*- */
/* File-name:    <url.h> */
/* Author:       <Xsoda> */
/* Create:       <Friday December 20 12:47:08 2013> */
/* Time-stamp:   <Friday December 20, 14:29:56 2013> */
/* Mail:         <Xsoda@Live.com> */

#ifndef __URL_H__
#define __URL_H__

/*
 * parse url like this
 *
 * schema://username:password@host:port/path?key=value#fragment
 * \____/   \______/ \______/ \__/ \__/ \__/ \_______/ \______/
 *   |         |        |       |    |    |      |         |
 * schema      |     password   |   port  |   parament  fragment
 *          username          host      path
 *
 * note:
 *   - username, password, port, path, query, fragment is optional.
 *   - scheme, host must be setting.
 *   - username and password must be paired.
 *
 */

typedef struct _url_field {
   char *href;
   char *schema;
   char *username;
   char *password;
   char *host;
   char *port;
   char *path;
   char *parament;
   char *fragment;
} url_field_t;

#ifdef __cplusplus
extern "C" {
#endif

url_field_t *url_parse(const char *str);

void url_free(url_field_t *url);

void url_field_print(url_field_t *url);

#ifdef __cplusplus
}
#endif

#endif /* !__URI_H__ */
