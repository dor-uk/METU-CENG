#include <stdio.h>

int main()
{
    int wall_length, army_count;
    int wall[100000];
    int h = 0;
    int i = 0;
    int k;
    
    scanf("%d %d", &wall_length, &army_count);
    
    wall_length += 1;
    for(h = 0;h < wall_length;h++)
    {
        wall[h] = 1;
    }
    
    
    
    while(i < army_count)
    {
        int width, height, time, position, speed, att_time, num_att;
        int j, movement, interval, control;
        
        scanf("%d %d %d %d %d %d %d", &width, &height, &time, &position, &speed, &att_time, &num_att);

        
        movement = (att_time)*(speed);
        interval = position + width;
        
        for(j = 0;j < num_att;j++)
        {
            
            control = position;
            if (interval < wall_length && interval > -1 && position < wall_length && position > -1)
            {
                for(control;control < interval;control++)
                {
                    if (wall[control] < height)
                    {
                        wall[control] = height;
                        
                    }
                }
                
            }
            else if (position < wall_length && position > -1)
            {
                if (interval < 0)
                {
                    for(control;control > -1;control--)
                    {                        
                       if (wall[control] < height)
                        {
                            wall[control] = height;
                        }
                    }
                }
                else
                {
                    for(control;control < wall_length+1;control++)
                    {
                        if (wall[control] < height)
                        {
                            wall[control] = height;
                        }
                    }
                }
            }
            else if (interval < wall_length && interval > -1)
            {
                if (position < 0)
                {
                    for(interval-=1;interval > -1;interval--)
                    {
                        if (wall[interval] < height)
                        {
                            wall[interval] = height;
                        }
                    }
                }
                else
                {
                    for(interval;interval < wall_length+1;interval++)
                    {
                        if (wall[interval] < height)
                        {
                            wall[interval] = height;
                        }
                    }
                }
            }
            else
            {
                if (position < 0 && interval > wall_length)
                {
                    int whole;
                    for(whole = 0;whole < wall_length;whole++)
                    {
                        if (wall[whole] < height)
                        {
                            wall[whole] = height;
                        }
                    }
                }
            }
            
            position += movement;
            interval += movement;
            
        }
        i += 1;
    }

    
    for(k = 0;k < wall_length-1;k++)
    {
        int output;
        output = wall[k];
        printf("%d ", output);
    }
    printf("%d\n", wall[k]);




}
