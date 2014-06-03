#include <fcgi_stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>

#define LIMIT 5

void print_header(void);
void print_footer(void);

int main(int argc, char *argv[])
{
    int page = 1;
    int limit = LIMIT;
    int offset = 0;
    /* TODO remove hardcore */
    char *formatted_query = "SELECT * FROM posts LIMIT %d OFFSET %d";
    char query[1000];
    
    PGconn     *conn;
    PGresult   *res; 
    int         i;
 
    conn = PQconnectdb("dbname=cblog user=cblog password=123123");
 
    if (PQstatus(conn) == CONNECTION_BAD)
    {
        fprintf(stderr, "Connection to database failed.\n");
        fprintf(stderr, "%s", PQerrorMessage(conn));
        exit(1);
    }
    
    while(FCGI_Accept() >= 0) {
        page = atoi(getenv("PAGE_NUMBER"));
        offset = (page - 1) * 5;

        sprintf(query, formatted_query, limit, offset);
        res = PQexec(conn, query);

        if (PQresultStatus(res) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "SELECT query failed.\n");
            PQclear(res);
            PQfinish(conn);
            exit(1);
        }
     
        print_header();

        for (i = 0; i < PQntuples(res); i++) {
            printf("<div class=\"page-header\"><h2>");
            printf("%s\n</h2>", PQgetvalue(res, i, PQfnumber(res, "title")));
            printf("<span class=\"badge\">Added at %s\n</span>", PQgetvalue(res, i, PQfnumber(res, "add_time")));
            printf("</div>");
            
            printf("<p>");
            printf("%s\n", PQgetvalue(res, i, PQfnumber(res, "content")));
            printf("</p>");
        }

        print_footer();

        PQclear(res);
   }
   PQfinish(conn);

   return 0;
}

void print_header(void)
{
    printf(
        "Content-Type: text/html\n\n"
        "<!doctype html>"
        "<html>"
        "<head>"
        "<meta charset=\"utf-8\">"
        "<title>"
        "List of posts"
        "</title>"
        "<link rel=\"stylesheet\" href=\"/static/css/bootstrap.min.css\">"
        "<link rel=\"stylesheet\" href=\"/static/css/bootstrap-theme.min.css\">"
        "<script src=\"/static/js/jquery-2.1.1.min.js\"></script>"
        "<script src=\"/static/js/bootstrap.min.js\"></script>"
        "</head>"
        "<body>"
        "<div class=\"navbar navbar-default\">"
            "<div class=\"container\">"
                "<div class=\"navbar-header\">"
                    "<a class=\"navbar-brand\" href=\"/\">CBlog</a>"
                "</div>"
                "<div class=\"navbar-collapse collapse\">"
                    "<ul class=\"nav navbar-nav\">"
                        "<li class=\"active\">"
                        "<a href=\"/\">Home</a>"
                        "</li>"
                        "<li>"
                        "<a href=\"/static/about.html\">About</a>"
                        "</li>"
                        "<li>"
                        "<a href=\"#contact\">Contact</a>"
                        "</li>"
                    "</ul>"
                "</div>"
            "</div>"
        "</div>"
        "<div class=\"container\" role=\"main\">"
        );
}

void print_footer(void)
{
    printf(
        "</div>"
        "</body>"
        "</html>"
    );
}
