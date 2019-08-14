#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include"mylist.h"

typedef struct wordnode{
	char word[28];//单词
	int wordcount;//单词的出现次数
    int location;//单词出现位置
}WordNode;

int k = 0;
List *wordlist[26];
//输出单词链表
void display(void *word)
{
	WordNode *words = (WordNode *)word;
//	FILE *out;
//	out = fopen("test.txt","a+");
//	if(out == NULL)
//		printf("打开失败\n");
//	freopen("test.txt","a",stdout);
    printf("单词：%-20s个数：%-5d\n",words->word,words->wordcount);
//	freopen("dev/tty","a",stdout);
//	fclose(out);
}
//按单词查找
int find_word(void *word_a,void *word_b)
{
	WordNode *wordnode_a = (WordNode *)word_a;
	WordNode *wordnode_b = (WordNode *)word_b;
	return (strcmp(wordnode_a->word,wordnode_b->word) == 0);
}
//划分单词
void divide_word(char word[])
{
	int i = 0;
	while(word[i] != '\0')
	{
		if(word[i] >= 'A' && word[i] <= 'Z') //大写转小写
			word[i] = word[i]+32;
		i++;
	}
}
int is_word(char word[])
{
	int i = 0;
	while(word[i] != '\0')
	{
		if((word[i] >= 'A' && word[i] <= 'Z')||(word[i] >= 'a' && word[i] <= 'z'))
			i++;
		else
			return 0;
	}
	return 1;
}
//按单词数量比较
int compare_wordcount(void *word_a,void *word_b)
{	
	WordNode *wordnode_a = (WordNode *)word_a;
	WordNode *wordnode_b = (WordNode *)word_b;
	return wordnode_a->wordcount < wordnode_b->wordcount;
}
//按单词比较
int compare_word(void *word_a,void *word_b)
{	
	WordNode *wordnode_a = (WordNode *)word_a;
	WordNode *wordnode_b = (WordNode *)word_b;
	return (strcmp(wordnode_a->word,wordnode_b->word) < 0);
}
//按位置比较
int compare_location(void *word_a,void *word_b)
{
    WordNode *wordnode_a =(WordNode *)word_a;
    WordNode *wordnode_b = (WordNode *)word_b;
    return wordnode_a->location <wordnode_b->location;
}
//判断是否为普通文件
int isfile(char *filename)
{
	struct stat st;
	memset(&st,0,sizeof(struct stat));
	stat(filename,&st);
	if(S_ISREG(st.st_mode))
		return 1;
	return 0;
}
//获取传入的文件
int getfilename(int argc,char *argv[],char *file[])
{
	int i = 0;
	int fileindex = 0;
	for(i = 1; i < argc; i++)
	{
		if(isfile(argv[i]))
		{
			file[fileindex] = argv[i];
			fileindex++;
		}
	}
	return 0;
}
//获取文件的个数
int getfilecount(int argc,char *argv[])
{
	int count = 0;
	int i = 1;
	for(i = 1; i < argc; i++)
	{
		if(isfile(argv[i]))
			count++;
	}
	return count;
}

//读取文件，插入节点
List *createwordlist(char *filename,int flag)
{
    FILE *in;
	List *h;
    for(int i = 0 ;i < 26; i++)
        wordlist[i] = CreateList();
   
	in = fopen(filename,"r");
	if(in == NULL)
		printf("打开失败\n");
	char buff[1024];
    int index = 0;
    int word_location = 0;
    WordNode *words = NULL;
	while(fscanf(in,"%s",buff) != EOF)
	{
    	if(flag == 1)
			divide_word(buff);
		char *buff_word;
       	char *seq = ",.!-:;?\"\'()@~#^&*+1234567890\\<>/=[]$%{}";
       	buff_word=strtok(buff,seq);
      	while(buff_word != NULL)
       	{
			if(is_word(buff_word))
			{
         		if(buff_word[0]>='A'&&buff_word[0]<='Z')
            		index = buff_word[0] - 'A';
           		if(buff_word[0]>='a'&&buff_word[0]<='z')
                	index = buff_word[0] - 'a';
				Node *p = ListFind(wordlist[index],buff_word,find_word);//查找结点
				if(p == NULL)//不存在插入
				{
                	words = (WordNode *)malloc(sizeof(WordNode));
			    	if(words == NULL)
				    	printf("创建失败\n");
		    		words->wordcount = 1;
                	words->location = (word_location++);
			    	strcpy(words->word, buff_word);
					ListInsertTail(wordlist[index],words);
				}
				else//存在单词次数加1
				{
					WordNode *exist_word = (WordNode *)p->data;
					(exist_word->wordcount)++;
				}
            	words = NULL;
			}
            buff_word=strtok(NULL,seq);
		}
	}
  	for(int i = 0; i<26;i++)
	{
		if(wordlist[i]->first != NULL || wordlist[i]->last != NULL)
		{
			wordlist[k] = wordlist[i];
			k++;
		}
		else
		{
			free(wordlist[i]);
		}
	}
	for(int i=0;i<k-1;i++)
    {
       	wordlist[i+1]->first->prev = wordlist[i]->last;
        wordlist[i]->last->next = wordlist[i+1]->first;
		wordlist[i]->last = wordlist[i+1]->last;
        wordlist[0]->count +=wordlist[i+1]->count;	
    }
    wordlist[0]->last = wordlist[k-1]->last;
    wordlist[0]->last->next = NULL;
    printf("总共有%d个单词\n",wordlist[0]->count);
    fclose(in);
	h= wordlist[0];
    return h;
}

int main(int argc,char *argv[])
{
	int filecount = 0;
	int casesup = 0;
    int reverse = 0;
	int opt = 0;
	int (*cmp)(void *,void *) = NULL;
	filecount = getfilecount(argc,argv);
    printf("%d\n",filecount);
	char *filename[filecount];
	char *writefilename[filecount];
	getfilename(argc,argv,filename);
	int i = 0;

    while((opt = getopt(argc,argv,"d::c::l::spw:")) != -1)
	{   
		switch(opt)
		{
			case 'd':
				cmp = compare_word;
				break;
			case 'c':
				cmp = compare_wordcount;
				break;
			case 'l':
				cmp = compare_location;
				break;
			case 's':
				casesup = 1;
                break;
			case 'p':
				reverse = 1;
				break;
            case 'w':
			//	strcpy(writefilename,optarg);
                for(int i = 0;i<filecount;i++)
                {
                	strcpy(writefilename[i],argv[i+optind]);
                   	printf("%s\n",writefilename[i]);
                   //	freopen(writefilename[i],"w",stdout);
                }
				break;
			default:
				break;
		}
	}
	for(i = 0; i < filecount; i++)
	{
		List *h1 = NULL;
		printf("%s:\n",filename[i]);
	    h1 = createwordlist(filename[i],casesup);
	//	freopen(writefilename[i],"w",stdout);
		if(cmp)
		{
			ListSort(h1,cmp);
  		//	if(reverse == 0)
        //	{
        //	   	ListOutput(h1,display);
       	//	}
        	if(reverse == 1)
        	{
         //   	ListInvertOutput(h1,display);
				ListReverse(h1);

        	}
		}
		ListOutput(h1,display);
	//	freopen("dev/tty","w",stdout);
        ListFree(wordlist[0]);
        for(int j=1;j<=k-1;j++)
    		free(wordlist[j]);
		k = 0;
    }
	return 0;

}

