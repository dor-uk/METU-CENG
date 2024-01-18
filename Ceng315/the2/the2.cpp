#include <cstdio>
#include <string>
using std::string;




int maxstring_length(std::string* arr, int size)
{
    int maxlength = 0;
    
    for(int i = 0;i < size; i++)
    {
        int len = arr[i].length();
        
        if(len > maxlength)
        {
            maxlength = len;
        }
    }
    return maxlength;
}

int char_to_int(std::string s, int digit)
{
    int size = s.length();
    
    return (digit >= size) ? 0 : (s[digit] - 64);
}

void countSort(std::string* arr, int size, bool ascending, int key, int& iterations){

    std::string outputt[size];
    int alphabet = 27;
    
    int count[alphabet];
    int convert;
    
    for(int i=0; i<alphabet; i++)
    {
        count[i] = 0;
    }

    for(int j=0; j<size; j++)
    {
        convert = char_to_int(arr[j], key);
        count[convert]++;
        
        iterations++;
    }
    
    if(ascending)
    {
        for(int i=1; i<alphabet; i++)
        {
            count[i] += count[i-1];
            
            iterations++;
        }
        
        for(int j=size-1; j>=0; j--)
        {
            convert = char_to_int(arr[j], key);
            count[convert]--;
            outputt[count[convert]] = arr[j];
            
            iterations++;
        }
        
    }
    
    else
    {
        for (int i = alphabet - 1; i > 0; i--) {
            count[i - 1] += count[i];

            iterations++;
        }

        for (int j = size-1; j >= 0; j--) {
            convert = char_to_int(arr[j], key);
            count[convert]--;
            outputt[count[convert]] = arr[j];

            iterations++;
        }
    }
    
    
    for(int j=0; j<size; j++)
    {
        arr[j] = outputt[j];
        
        iterations++;
    }
    
}

int radix_string_sort(std::string* arr, int size){
    
    int max = maxstring_length(arr,size);
    bool ascending = 0;
    int iterations = 0;
    
    for (int dummy = max; dummy > 0; dummy--)
    { 
        countSort(arr, size, ascending, dummy - 1, iterations);
    }
    
    
    return iterations;    
    
}

int main()
{
    std::string data[] = {"BETELGEUSE", "VEGA", "SEGINUS", "SEGIN", "ANTARES", "ALDERAMIN", "ALDEBERAN"};
    puts("before sorting:");
    for (size_t i = 0; i < sizeof(data) / sizeof(data[0]); i++) {
        printf("    %s ", data[i].c_str());
        
    }
    printf("\n");
    int res = radix_string_sort(data, (int)(sizeof(data) / sizeof(data[0])));
    puts("after sorting:");
    for (size_t i = 0; i < sizeof(data) / sizeof(data[0]); i++) {
        printf("    %s ", data[i].c_str());
    }
    printf("%d", res);
    return 0;

    
}