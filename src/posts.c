#define LIMIT 5

PGresult *getPosts(PGconn *conn, char *query, char *formatted_query, int limit, int offset);

/* TODO remove hardcore */
char *formatted_query = "SELECT * FROM posts LIMIT %d OFFSET %d";
char query[1000];


PGconn *connect()
{
    return PQconnectdb("dbname=cblog user=cblog password=123123");
}

void disconnect(PGconn *conn)
{
    PQfinish(conn);
}

PGresult *getPosts(PGconn *conn, char *query, char *formatted_query, int limit, int offset)
{
    PGresult *res;

    sprintf(query, formatted_query, limit, offset);
    res = PQexec(conn, query);
    return res;
}
