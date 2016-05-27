#include<stdio.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>

#define IC 1 /*cost to insert*/
#define RC 1 /*cost to replace*/
#define DC 1 /*cost to delete*/

char array_of_words[1000][45]; //An array is a systematic arrangement of objects, usually in rows and columns;

int minimum(int a, int b, int c) 
{
	int min;
	
	min = c;
 
    if( a < b )
    {
        if( a < c )
        {
            min = a;
        }
    }
    else
    {
        if( b < c )
        {
            min = b;
        }
    }
 
    return min;
}	        

int minimum_two(int a, int b)
{
	int min;
	
	if(a < b)
        min = a;
    else
        min = b;
 
    return min;
}

int size_of_file(char file_name[100])
{
	FILE* fd = NULL;
	char ch;
	int i,j;
	
    fd = fopen(file_name,"r");
    
    if( fd == NULL )
	{
		printf("\nError while opening the file.\n");
		return -1;
	}
 
 	i=0;
 	j=0;
	while( ( ch = fgetc(fd) ) != EOF )
	{	
		array_of_words[i][j]=ch;
		j = j + 1;
		if (ch == '\n')
		{
			j=0;
			i = i + 1;
		}
	}
	
	strcat(array_of_words[i],"\n"); //This function is used to concatenate two strings
	
 	fclose(fd);
 	
 	return i;
}

int merge(char arr[][45], int l, int m, int h) 
{
    char arr1[1000][45], arr2[1000][45];
    int n1, n2, i, j, k;
    n1 = m - l + 1;
    n2 = h - m;

    for(i = 0; i < n1; i++)
        strcpy(arr1[i], arr[l + i]); //The first argument is the string that will receive the copy, 

    for(j = 0; j < n2; j++)
        strcpy(arr2[j], arr[m + j + 1]);

    strcpy(arr1[i],"zzzzzzzzzzzzz");
    strcpy(arr2[j],"zzzzzzzzzzzzz");

    i = 0;
    j = 0;

    for(k = l; k <= h; k++)
    {
        if(strcmp(arr1[i], arr2[j]) < 0)
            strcpy(arr[k], arr1[i++]);
        else
            strcpy(arr[k], arr2[j++]); //strcmp compares lexically two strings character by character, and returns 0 if the two strings are equal,
			//a positive number if s1 is lexicographically greater than s2 , and a negative number and if s1 is lexicographically less than s2 .
    }

    return 0;
}

int merge_sort(char arr[][45],int low,int high)
{
    int mid;

    if(low < high) 
    {
        mid = (low + high) / 2;

        // Divide and Conquer
        merge_sort(arr, low, mid); 
       
        merge_sort(arr, mid + 1, high); 
       
        // Combine
        merge(arr, low, mid, high); 
    }

    return 0;
}

int binary_search(char lookup_word[45], int no_of_words) // binary search or half-interval search algorithm locates the position of an item in a sorted array.
{
	int first, last, middle;

	first = 0;
	last = no_of_words - 1;
	middle = (first+last)/2;

	while( first <= last )
	{
		if(strcmp(array_of_words[middle], lookup_word) < 0)
			first = middle + 1;    
		else if(strcmp(array_of_words[middle], lookup_word) == 0)
		{
			return 1;
			break;
		}
		else
			last = middle - 1;

		middle = (first + last)/2;
	}

	if(first > last)
		return 0;

	return 0;
}

int edit_distance_recursive(char *word1, char *word2)//edit distance is a way of quantifying how dissimilar two strings
{
    int d,e,f;
 
    /* Base cases */
 
    if(*word1==0)return strlen(word2);
    if(*word2== 0)return strlen(word1);//strlen returns the number of characters in a string char * character in the terminal cash to zero,
	//but not including it in the total. 
 
    /* Recurse */
 
    if(*word1==*word2)
         d=edit_distance_recursive(word1+1,word2+1);
    else
         d=RC+edit_distance_recursive(word1+1,word2+1); /*replace*/
    e=IC+edit_distance_recursive(word1,word2+1); /*insert*/
    f=DC+edit_distance_recursive(word1+1,word2); /*delete*/
 
    return minimum(d,e,f);
}

int edit_distance(char word1[45], char word2[45])
{
    int i, j, l1, l2, m;
    int t[45][45];
    l1 = strlen(word1);
    l2 = strlen(word2);
    //vector< vector<int> > t(l1 + 1, vector<int>(l2 + 1));
 
    for (i = 0; i <= l1; i++)
        t[i][0] = i;
    for (i = 1; i <= l2; i++)
        t[0][i] = i;
 
    for (i = 1; i <= l1; i++)
    {
        for (j = 1; j <= l2; j++)
        {
            m = minimum_two(t[i-1][j], t[i][j-1]) + 1;
            t[i][j] = minimum_two(m, t[i-1][j-1] + (word1[i-1] == word2[j-1] ? 0 : 1));
        }
    }
    return t[l1][l2];
}

int main()
{                 
	char file_name[100], word[45];
	int no_of_words, i, isfound, min_distance[1000], min_dis_ref=100, min_distance2[1000];
	
	printf("\nEnter the file name :");
	scanf("%s", &file_name);
	
	no_of_words = size_of_file(file_name) + 1;
	
	if(no_of_words == 0)
		return 0;
		
	printf("\n No. of words found in the file = %d", no_of_words);
	
	printf("\n******************Sorting the words from the dictionary-Start******************\n");
	merge_sort(array_of_words, 0, no_of_words-1);
	printf("\n******************Sorting the words from the dictionary-End******************\n");
	
	printf("\nEnter the word :");
	scanf("%s", &word);
	strcat(word,"\n");
	
	printf("\n******************Searching the words in the dictionary-Start******************\n");
	isfound = binary_search(word, no_of_words);
	
	if(isfound == 1)
		printf("\nThe word exists in the dictionary");
	else
	{
		printf("\nThe word does not exist in the dictionary");
		
		for(i=0;i<no_of_words;i++)
		{
			min_distance[i]=edit_distance_recursive(word,array_of_words[i]);
			
			if(min_distance[i] <= min_dis_ref)
				min_dis_ref = min_distance[i];
		}
		
		//printf("\n%d",min_dis_ref);	
		
		printf("\nPossible suggestions are :");	
		for(i=0;i<no_of_words;i++)
		{
			if(min_distance[i] == min_dis_ref)
				printf("\n%s",array_of_words[i]);
		}
	}
	printf("\n******************Searching the words in the dictionary-End******************\n");
	
	//for(i=0;i<no_of_words;i++)
	//printf("%s",array_of_words[i]);
	
    return 0;
}	                   
