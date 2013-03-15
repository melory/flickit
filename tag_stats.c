/**
  *
  *统计各个cell里面每个textual tag出现的频数
  *每个cell一个文件，文件以cell的编号命名
  *输入文件不是metadata.temp2.txt，是clustering.metadata.txt + modeling.metadata.txt
  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define CELLNUM 1533  //cell num: 0~1533
#define TAGNUM 53318  //tag num: 1~53317 

#define W -125
#define E -66
#define N 50
#define S 24
#define W_E 59
#define N_S 26

void** malloc2d(int w, int h, int size);
int _isupper(char c);

int
main()
{
	int i, j, cellid, tagid, **frequency;
	char ch, id[11], owner_nsid[20], location_woeid[15], tag[10000], fname[20], buf[10000];
	double lat, lon;
	FILE *fp, *fp1;

	printf("运行程序之前请保证CELLNUM和TAGNUM已经正确设置.按任意键继续进行.\n");
	getchar();
	printf("continued.\n");
	
	frequency = (int **)malloc2d(TAGNUM + 1, CELLNUM + 1, sizeof(int));
	for(i = 0; i <= CELLNUM; i++)
		for(j = 0; j <= TAGNUM; j++)
			frequency[i][j] = 0;

	if((fp = fopen("clustering.id.txt", "r")) == NULL)
	{
		printf("openning file 'clustering.id.txt' failed.\n");
		return -1;
	}

	while(fscanf(fp, "%s%lf%lf%s%s", id, &lat, &lon, owner_nsid, location_woeid) != EOF)
	{
		cellid = floor(lat - S) * W_E + floor(lon - W);
		fscanf(fp, "%c", &ch);
		fscanf(fp, "%c", &ch);
		printf("id=%s,ch1 = %c\n", id, ch);
		//getchar();
		i = 0;
		while(ch != '\n')
		{
			//printf("ch = %c\n", ch);
			if(ch == ' ')
			{
				//printf("blank\n");
				tag[i] = '\0';
				i = 0;

				if(tag[0] >= 'a' && tag[0] <= 'z')
					sprintf(fname, "%c.tag.txt", tag[0]);
				else
					sprintf(fname, "other.tag.txt");

				printf("fname = %s\n", fname);
				if((fp1 = fopen(fname, "r")) == NULL)
				{
					printf("openning file '%s' failed.\n", fname);
					return -1;
				}

				while(fscanf(fp1, "%d%s", &tagid, buf) != EOF)
				{
					printf("tagid = %d buf = %s tag = %s\n", tagid, buf, tag);
					getchar();
					if(strcmp(buf, tag) == 0)
					{
						frequency[cellid][tagid]++;
						break;
					}
				}
				fclose(fp1);
			}
			else
			{
				if(_isupper(ch))
				{
					tag[i] = (char)(ch + ('a' - 'A'));
					//printf("tag[%d] = %c\n", i, tag[i]);
					i++;
				}
				else
				{
					tag[i] = ch;
					//printf("tag[%d] = %c\n", i, tag[i]);
					i++;
				}
			}

			fscanf(fp, "%c", &ch);
		}
	}
	fclose(fp);

	for(i = 0; i <CELLNUM; i++)
	{
		sprintf(fname, "cell%d.txt", i);
		if((fp = fopen(fname, "w")) == NULL)
		{
			printf("openning file '%s' failed.\n", fname);
			return -1;
		}

		for(j = 1; j < TAGNUM; j++)
			fprintf(fp, "%d	%d\n", j, frequency[i][j]);
		fclose(fp);
	}

	free(frequency);
	return 0;
}


void** malloc2d(int w, int h, int size)
{
  int j;
  int rowSize = w * size;
  int indexSize = h * sizeof(void *);
  void **a = (void **) malloc(indexSize + h * rowSize);
  char *dataStart = (char *) a + indexSize;
  for(j = 0; j < h; j++)
    a[j] = dataStart + j * rowSize;
  return a;
}

int _isupper(char c)
{
	if(c >= 'A' && c <= 'Z')
		return 1;
	else
		return 0;
}
