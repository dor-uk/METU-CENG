#include <stdio.h>
#include <stdlib.h>


char* input;
char* curr;
char** tf_table;
int trip;
char* var;
int char_counter, counter = 0;

char read(char* tf_row)
{
    char left, right, operation;
    char temp, res;
    int i;
    /*printf("%c",*curr);*/
    
    if(*curr == '(')
    {
        curr++;
        left = read(tf_row);
        operation = *(curr++);
        right = read(tf_row);
        curr++;
        
        /*printf("%c",*curr);*/
        /*printf("%c %c %c\n", left, right, operation);*/
        /*printf("%c\n", operation);*/
        switch (operation)
        {
            case '&':
                /*printf("& run");*/
                if((left == 'T') && (right == 'T'))
                {
                    return 'T';
                }
                else 
                {
                    return 'F';
                }
                break;
            case '|':
                /*printf("| run");*/
                if((left == 'F') && (right == 'F'))
                {
                    return 'F';
                }
                else 
                {
                    return 'T';
                }
                break;
                
            case '>':
                /*printf("> run");*/
                if(left == right)
                {
                    return 'T';
                }
                else if((left == 'T') && (left != right))
                {
                    return 'F';
                }
                else 
                {
                    return 'T';
                }
                break;
            case '=': 
                /*printf("= run\n");*/
                if(left == right)
                {
                    return 'T';
                }
                else 
                {
                    return 'F';
                }
                break;
            
        }
        
    }
    
    else
    {
        sscanf(curr, "%c", &temp);
        
        if(*curr == '-')
        {
            
            curr++;
            if(*curr == '(')
            {
                res = read(tf_row);
                if(res == 'T')
                {
                    return 'F';
                }
                else
                {
                    return 'T';
                }
            }
            else
            {
                if(islower(*curr))
                {
                    for(i = 0; i < char_counter;i++)
                    {
                
                        if(*curr == var[i])
                        {
                            left = tf_row[i];
                            /*printf("%c %c %d\n",temp, left, counter);*/
                            break;
                        }
                    }
                    while (islower(*curr))
                    {
                        curr++;
                        /*printf("%c\n",*curr);*/
                    }
                    if(left == 'T')
                    {
                        return 'F';
                    }
                    else
                    {
                        return 'T';
                    }
                    
                }
                else
                {
                    res = read(tf_row);
                    if(res == 'T')
                    {
                        return 'F';
                    }
                    else
                    {
                        return 'T';
                    }
                }
                
            }
        }
        else
        {
            
            for(i = 0; i < char_counter;i++)
            {
                
                if(temp == var[i])
                {
                    left = tf_row[i];
                    /*printf("%c %c %d\n",temp, left, counter);*/
                    break;
                }
            }
            while (islower(*curr))
            {
                curr++;
                /*printf("%c\n",*curr);*/
            }
        
            return left;
            
        }
         
        
    }
    
}

char eval(char* input, char* tf_row)
{
    curr = input;
    return read(tf_row);
}

void sorter(char* var, int char_counter)
{
    char temp;
    int i;
    for(i = 0;i < char_counter-1; i++)
    {
        temp = var[i+1];
        if(var[i] > var[i+1])
        {
            var[i+1] = var[i];
            var[i] = temp;
        }
    }
}

int power2(int n)
{
    int i, base = 1;
    for(i = 0;i < n;i++)
    {
        base *= 2;
    }
    return base;
}

void changer(char* c, int i)
{
    if(c[i] == 'T')
    {
        c[i] = 'F';
    }
    else
    {
        c[i] = 'T';
    }
}

char** combination(int char_counter)
{
    
    char* tf_list;
    char* basic;
    int power, i = 0, j = 0, table_c = 0, control;
    tf_table = (char**)malloc(sizeof(char*));
    basic = (char*)malloc(sizeof(char)*char_counter);
    for(i= 0;i < char_counter;i++)
    {
        basic[i] = 'T';
    }
    
    power = power2(char_counter);
    
    for(i = 0;i < power;i++)
    {
        j = 0;
        tf_list = (char*)malloc(sizeof(char)*char_counter);
        
        for(j = 0;j < char_counter;j++)
        {
            control = power2(char_counter - 1 - j);
            
            if(i != 0)
            {
                if(i%control == 0)
                {
                    changer(basic,j);
                
                }
            }
            
            tf_list[j] = basic[j];
            
        }
        
        tf_table[table_c] = tf_list;
        table_c++;
        tf_table = (char**)realloc(tf_table,sizeof(char*)*(table_c + 1));
        j = 0;
        
    }
    return tf_table;
    
}

int main() 
{
    int i = 0, l_count = 0, r_count = 0, var_count = 0, checker = 0, j, k = 2;
    char a;
    char* result;
    
    input = (char*)malloc(sizeof(char));
    var  = (char*)malloc(sizeof(char));
    char_counter = 0;
    
    while(1)
    {
        a = getchar();
        if(a == EOF)
        {
            break;
        }
        
        else
        {
            if(!isspace(a))
            {
                input[i] = a;
                i++;
                input = (char*)realloc(input,sizeof(char)*(i+1));
            }
        }
        
        
    }
    input[i] = '\0';
    
    
    for(i = 0; input[i] != '\0';i++)
    {
        if(input[i] >= 'a' && input[i] <= 'z')
        {
            if(var_count == 0)
            {
                var[var_count] = input[i];
                var_count++;
                var = (char*)realloc(var,sizeof(char)*(var_count+1));
                char_counter++;
            }
            else
            {
                for(j = 0;j < var_count;j++)
                {
                    if(input[i] == var[j])
                    {
                        checker++;
                    }
                }
                if(checker == 0)
                {
                    var[var_count] = input[i];
                    var_count++;
                    var = (char*)realloc(var,sizeof(char)*(var_count+1));
                    char_counter++;
                }
            }
        }
        checker = 0;
    }
    
    
    var[var_count] = '\0';
    sorter(var, char_counter);
    
    
    for(i = 0;i <= char_counter-1;i++)
    {
        printf("%c ", var[i]);
    }
    printf("R\n");
    
    for(i = 0;i < char_counter-1;i++)
    {
        k *= 2;
    }
    tf_table = combination(char_counter);
    
    result = (char*)malloc(sizeof(char)*k);
    
    for(i = 0; i < k; i++)
    {
        trip = i;
        result[i] = eval(input, tf_table[i]);
    }
    
    for(i = 0; i<k; i++)
    {
        for(j = 0; j < char_counter;j++)
        {
            printf("%c ", tf_table[i][j]);
        }
        printf("%c\n", result[i]);
    }
    
    
    return 0;
}

