
/**
  *
  *从temp2文件中统计所有不同的tags，并写在tags.txt文件中。
  *
  **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


char * all_lower_letter(char *str);
int _isupper(char c);
int _isdigit(char c);

int
main()
{
	int i, len, k;
	FILE *fp, *fp_tags, *fp_temp;
	char line1[10000], line2[100000], buf[1000], tag[1000];

	if((fp = fopen("metadata.temp2.txt", "r")) == NULL)
	{
		printf("open file 'metadata.temp2.txt' err!\n");
		return -1;
	}

	if((fp_temp = fopen("temp.txt", "w")) == 0)
	{
		printf("openning file 'temp.txt' failed.\n");
		return -1;
	}

	//如果是要增加则需要把这个if去掉，以免冲掉以前的tags
	if((fp_tags = fopen("tags.txt", "w")) == 0)
	{
		printf("openning file 'tags.txt' failed.\n");
		return -1;
	}
	fclose(fp_tags); //just to create the file 'tags.txt'

	while(1)
	{
		if((fgets(line1, 10000, fp) !=0) && (fgets(line2, 100000, fp) != 0))
		{
			len = strlen(line2);

			for(i =  0, k = 0; i < len; i++)
			{
				if(k == 2)
					break;
				if(line2[i] == ' ')
					k ++;
			}
			for( ; i < len; i++)
				fprintf(fp_temp, "%c", line2[i]);
		}
		else
			break;
	}

	fclose(fp_temp);


	if((fp_temp = fopen("temp.txt", "r")) == 0)
	{
		printf("openning file 'temp.txt' failed.\n");
		return -1;
	}

	while(fscanf(fp_temp, "%s", buf) != EOF)
	{
		strcpy(tag, all_lower_letter(buf));

		if((fp_tags = fopen("tags.txt", "r")) == NULL)
		{
			printf("openning file 'tags.txt' failed.\n");
			return -1;
		}

		while(1)
		{
			if(fscanf(fp_tags, "%s", buf) == EOF)
			{
				fclose(fp_tags);
				fp_tags = fopen("tags.txt", "a+");
				fprintf(fp_tags, "%s\n", tag);
				fclose(fp_tags);
				break;
			}
			if(strcmp(buf, tag) == 0)
			{
				fclose(fp_tags);
				break;
			}
		}
	}

	fclose(fp_temp);

	return 0;
}


char *
all_lower_letter(char *str)
{
	int i, len;
	char buf[1000];

	len = strlen(str);
	for(i = 0; i < len; i ++)
	{
		if(_isupper(str[i]))
			buf[i] = (char)(str[i] + 32);
		else
			buf[i] = str[i];
	}
	buf[len] = '\0';

	return buf;
}

int
_isupper(char c)
{
	if(c >= 'A' && c <= 'Z')
		return 1;
	else
		return 0;
}

int
_isdigit(char c)
{
	if(c >= '0' && c <= '9')
		return 1;
	else
		return 0;
}