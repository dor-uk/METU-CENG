#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 5

typedef struct QueryNode
{
    char *query;
    struct QueryNode *prev;
    struct QueryNode *next;
} QueryNode;

typedef struct CountNode
{
    int count;
    struct CountNode *prev;
    struct CountNode *next;
    QueryNode *querylist;
} CountNode;


typedef struct Element
{
    char* str;
    int freq;
} Element;

Element Table[10];
int table_sz;

CountNode *first;

int compare(char *str1,char *str2)
{
    int i=0;
    for(i=0;1;i++)
    {
        if(str1[i]==0 && str2[i]==0)
        {
            return 2;
        }

        if(str1[i]==0)
        {
            return 0;
        }

        if(str2[i]==0)
        {
            return 1;
        }

        if(str1[i]<str2[i])
        {
            return 0;
        }

        if(str1[i]>str2[i])
        {
            return 1;
        }
    }
}

QueryNode *add_query_node(char *str, QueryNode *fr)
{
    if(fr==NULL)
    {
        QueryNode *nw=(QueryNode*)malloc(sizeof(QueryNode));

        nw->next=NULL;
        nw->prev=NULL;
        nw->query=str;

        return nw;
    }

    if(compare(str,fr->query)==0)
    {
        QueryNode *nw=(QueryNode*)malloc(sizeof(QueryNode));

        fr->prev=nw;

        nw->next=fr;
        nw->prev=NULL;
        nw->query=str;

        return nw;
    }

    QueryNode *curr=fr;

    while(curr->next!=NULL && compare(str,curr->next->query)==1)
    {
        curr=curr->next;
    }

    QueryNode *nw=(QueryNode*)malloc(sizeof(QueryNode));

    nw->next=curr->next;
    nw->prev=curr;

    if(curr->next!=NULL)
    {
        curr->next->prev=nw;
    }

    curr->next=nw;

    nw->query=str;

    return NULL;
}

void add_query(char *str,int freq)
{
    if(first==NULL)
    {
        CountNode *nw=(CountNode*)malloc(sizeof(CountNode));
        nw->count=freq;
        nw->next=NULL;
        nw->prev=NULL;
        nw->querylist=NULL;

        QueryNode *res=add_query_node(str,nw->querylist);

        if(res!=NULL)
        {
            nw->querylist=res;
        }

        first=nw;

        return;
    }

    if(freq<first->count)
    {
        CountNode *nw=(CountNode*)malloc(sizeof(CountNode));

        first->prev=nw;

        nw->count=freq;
        nw->next=first;
        nw->prev=NULL;
        nw->querylist=NULL;

        QueryNode *res=add_query_node(str,nw->querylist);

        if(res!=NULL)
        {
            nw->querylist=res;
        }

        first=nw;

        return;
    }

    CountNode *curr=first;

    while(curr->next!=NULL && curr->next->count<=freq)
    {
        curr=curr->next;
    }

    if(curr->count==freq)
    {
        QueryNode *res=add_query_node(str,curr->querylist);

        if(res!=NULL)
        {
            curr->querylist=res;
        }

        return;
    }

    CountNode *nw=(CountNode*)malloc(sizeof(CountNode));
    nw->next=curr->next;
    nw->prev=curr;

    if(curr->next!=NULL)
    {
        curr->next->prev=nw;
    }

    curr->next=nw;

    nw->count=freq;
    nw->querylist=NULL;

    QueryNode *res=add_query_node(str,nw->querylist);

    if(res!=NULL)
    {
        nw->querylist=res;
    }

    return;
}

QueryNode *delete_query_node(char *str,QueryNode *fr)
{
    QueryNode *curr=fr;

    while(compare(curr->query,str)!=2)
    {
        curr=curr->next;
    }

    if(curr->prev!=NULL)
    {
        curr->prev->next=curr->next;
    }

    if(curr->next!=NULL)
    {
        curr->next->prev=curr->prev;
    }

    QueryNode *ret; 

    if(curr==fr)
    {
        ret=curr->next;
    }

    else
    {
        ret=fr;
    }

    free(curr);

    return ret;
}

void delete_query(char *str,int freq)
{
    CountNode *curr=first;

    while(curr->count!=freq)
    {
        curr=curr->next;
    }

    QueryNode *res=delete_query_node(str,curr->querylist);

    curr->querylist=res;

    if(res==NULL)
    {
        if(curr->prev!=NULL)
        {
            curr->prev->next=curr->next;
        }

        if(curr->next!=NULL)
        {
            curr->next->prev=curr->prev;
        }

        if(curr==first)
        {
            first=curr->next;
        }

        free(curr);
    }

    return;
}

int main()
{
    int count=0;

    scanf("%d",&count);

    int i=0;

    for(i=0;i<count;i++)
    {
        char *str=(char*)malloc(sizeof(char)*6);



        int freq;

        scanf(" %s %d",str,&freq);

        Table[table_sz].str=str;
        Table[table_sz].freq=freq;

        table_sz++;

        add_query(str,freq);
    }

    scanf(" %d",&count);

    for(i=0;i<count;i++)
    {
        char *str=(char*)malloc(sizeof(char)*6);

        scanf(" %s",str);

        int j;

        int location=-1;

        for(j=0;j<table_sz;j++)
        {
            if(compare(Table[j].str,str)==2)
            {
                location=j;

                break;
            }
        }

        if(location!=-1)
        {
            delete_query(Table[location].str,Table[location].freq);

            Table[location].freq++;

            add_query(Table[location].str,Table[location].freq);
        }

        else
        {
            if(table_sz<MAX_SIZE)
            {
                Table[table_sz].freq=1;
                Table[table_sz].str=str;

                add_query(str,1);

                table_sz++;
            }

            else
            {
                char *delete=first->querylist->query;

                for(j=0;j<table_sz;j++)
                {
                    if(compare(Table[j].str,delete)==2)
                    {
                        location=j;

                        break;
                    }
                }

                delete_query(Table[location].str,Table[location].freq);

                Table[location].str=str;
                Table[location].freq=1;

                add_query(Table[location].str,Table[location].freq);
            }
        }
    }

    CountNode *curr=first;

    while(curr!=NULL)
    {
        printf("%d ",curr->count);
        
        QueryNode *curr2=curr->querylist;

        while(curr2!=NULL)
        {
            printf("%s ",curr2->query);

            curr2=curr2->next;
        }

        printf("\n");

        curr=curr->next;
    }

    
    return 0;
}
