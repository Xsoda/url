..
   -*- encoding: utf-8; -*-
   -*- rst-mode -*-
   File-name:    <README.rst>
   Author:       <Xsoda>
   Create:       <Wednesday December 25 10:11:22 2013>
   Time-stamp:   <Wednesday December 25, 10:16:46 2013>

URL parse
============

mini URL parse code.

url struct define:

.. code::

   /*
    * parse url like this
    *
    * schema://username:password@host:port/path?key=value#fragment
    * \____/   \______/ \______/ \__/ \__/ \__/ \_______/ \______/
    *   |         |        |       |    |    |      |         |
    * schema      |     password   |   port  |    query    fragment
    *          username          host      path
    *
    * note:
    *   - username, password, port, path, query, fragment is optional.
    *   - scheme, host must be setting.
    *   - username and password must be paired.
    *
    */

   typedef struct _url_field
   {
      host_type_t host_type;
      char *href;
      char *schema;
      char *username;
      char *password;
      char *host;
      char *port;
      char *path;
      char *query;
      char *fragment;
   } url_field_t;

parse function define:

.. code::

   url_field_t *url_parse(const char *str);
   void url_free(url_field_t *url);
   void url_field_print(url_field_t *url);

Usage:

.. code::

   int main()
   {
      char *str[] = {
         "scheme://0.0.0.0",
         "http://username:password@[::1]:8080/index.html",
         "scheme://username:password@www.google.com",
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