
/**
  *
  *将所有的tag编号，按照首字母放在不同的文件中
  *输入文件是tags.txt
  **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char * all_lower_letter(char *str);
int _isupper(char c);
int _isdigit(char c);

int 
main()
{
	FILE *fp, *fp_fname_temp[27], *fp_fname[27];
	char *fname_temp[27] = {"a.tag.temp.txt", "b.tag.temp.txt", "c.tag.temp.txt", "d.tag.temp.txt", "e.tag.temp.txt", "f.tag.temp.txt", "g.tag.temp.txt", "h.tag.temp.txt", 
	"i.tag.temp.txt", "j.tag.temp.txt", "k.tag.temp.txt", "l.tag.temp.txt", "m.tag.temp.txt", "n.tag.temp.txt", "o.tag.temp.txt", "p.tag.temp.txt", "q.tag.temp.txt", 
	"r.tag.temp.txt", "s.tag.temp.txt", "t.tag.temp.txt", "u.tag.temp.txt", "v.tag.temp.txt", "w.tag.temp.txt", "x.tag.temp.txt", "y.tag.temp.txt", "z.tag.temp.txt", "other.tag.temp.txt"};

	char *fname[27] = {"a.tag.txt", "b.tag.txt", "c.tag.txt", "d.tag.txt", "e.tag.txt", "f.tag.txt", "g.tag.txt", "h.tag.txt", 
	"i.tag.txt", "j.tag.txt", "k.tag.txt", "l.tag.txt", "m.tag.txt", "n.tag.txt", "o.tag.txt", "p.tag.txt", "q.tag.txt", 
	"r.tag.txt", "s.tag.txt", "t.tag.txt", "u.tag.txt", "v.tag.txt", "w.tag.txt", "x.tag.txt", "y.tag.txt", "z.tag.txt", "other.tag.txt"};

	int i, j, k, curID[27];
	char buf[10000];

	for(i = 0; i < 27; i++)
	{
		curID[i] = 0;
		if((fp_fname_temp[i] = fopen(fname_temp[i], "w")) == NULL)
		{
			printf("openning file '%s' failed.\n", fname_temp[i]);
			return -1;
		}
	}

	if((fp = fopen("tags.txt", "r")) == NULL)
	{
		printf("openning file 'tags.txt' failed.\n");
		return -1;
	}


	while(fscanf(fp, "%s", buf) != EOF)
	{
		if(buf[0] >= 'a' && buf[0] <= 'z')
		{
			fprintf(fp_fname_temp[(int)((buf[0]) - 'a')], "%d	%s\n", (curID[(int)((buf[0]) - 'a')] + 1), buf);
			curID[(int)((buf[0]) - 'a')] = curID[(int)((buf[0]) - 'a')] + 1;
		}
		else
		{
			fprintf(fp_fname_temp[26], "%d	%s\n", (curID[26] + 1), buf);
			curID[26] = curID[26] + 1;
		}
	}

	fclose(fp);
	for(i = 0; i < 27; i ++)
	{
		fclose(fp_fname_temp[i]);
	}

	k = 0;
	for(i = 0; i < 27; i++)
	{
		if((fp_fname_temp[i] = fopen(fname_temp[i], "r")) == NULL)
		{
			printf("openning file '%s' failed.\n", fname_temp[i]);
			return -1;
		}

		if((fp_fname[i] = fopen(fname[i], "w")) == NULL)
		{
			printf("openning file '%s'failed.\n", fname[i]);
			return -1;
		}

		while(fscanf(fp_fname_temp[i], "%d%s", &j, buf) != EOF)
		{
			fprintf(fp_fname[i], "%d	%s\n", (j + k), buf);
		}

		fclose(fp_fname[i]);
		fclose(fp_fname_temp[i]);
		k = k + j;
	}

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

