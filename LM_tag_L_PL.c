/**
  *
  *language model(textual tags only) for large granularity
  *计算出baseline里面的每个cell的概率，每章图片存一体个文件，以id命名
  *
  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define lamda 0.1    //set lamda
#define CELLNUM 1533 //cell id: 0~1533
#define TAGNUM 53318 //tag id:1~53318

#define N 50
#define S 24
#define E -66
#define W -125
#define W_E 59

void** malloc2d(int w, int h, int size);

int
main()
{
	int i, j, k, tagid, tagnum, freq, cellid_actual, tag_cell, tag_globe = 0, a_tag_total, **frequency, tag_seq[1000], PL[CELLNUM];
	char name[30], id[11];
	double lat, lon, PTL;
	FILE *fp_input, *fp_freq, *fp_PTL, *fp_PL;

	frequency = (int **)malloc2d(TAGNUM + 1, CELLNUM + 1, sizeof(int));

	for(i = 0; i < CELLNUM; i++)
		for(j = 0; j < TAGNUM; j++)
			frequency[i][j] = 0;
	
	for(i = 0; i < CELLNUM; i++)
	{
		sprintf(name, "cell%d.txt", i);
		if((fp_freq = fopen(name, "r")) == NULL)
		{
			printf("openning file '%s' failed.\n", name);
			getchar();
			return -1;
		}

		while(fscanf(fp_freq, "%d%d", &tagid, &freq) != EOF)
			frequency[i][tagid] = freq;

		fclose(fp_freq);
	}

	for(i = 0; i < CELLNUM; i++)
		for(j = 0; j < TAGNUM; j++)
		{
			tag_globe = tag_globe + frequency[i][j];
			//printf("tag_globe=%d freq[%d][%d]=%d\n", tag_globe, i, j, frequency[i][j]);
			//getchar();
		}

	if((fp_PL = fopen("tag_each_cell.txt", "r")) == NULL)
	{
		printf("openning file 'tag_each_cell.txt' failed.\n");
		return -1;
	}

	while(fscanf(fp_PL, "%d%d", &j, &k) != EOF)
		PL[j] = k + 1;

	if((fp_input = fopen("tunning.tag.input.file.txt", "r")) == NULL)
	{
		printf("openning file 'tunning.tag.input.file.txt' failed.\n");
		return -1;
	}

	while(fscanf(fp_input, "%s%lf%lf", id, &lat, &lon) != EOF)
	{
		cellid_actual = floor(lat - S) * W_E + floor(lon - W);
		tagnum = 0;
printf("%s\n", id);
		while(1)
		{
			fscanf(fp_input, "%d", &tagid);
			if(tagid == -1)
				break;
			tag_seq[tagnum] = tagid;
			tagnum++;
		}

		//一张图片写一个文件
		sprintf(name, "%s_L_PTL.txt", id);
		if((fp_PTL = fopen(name, "w")) == NULL)
		{
			printf("openning file '%s' failed.\n", name);
			return -1;
		}

		fprintf(fp_PTL, "%d\n", cellid_actual);

		for(i = 0; i < CELLNUM; i++)
		{
			PTL = 0;
			tag_cell = 0;

			for(j = 1; j < TAGNUM; j++)
				tag_cell = tag_cell + frequency[i][j];

			for(j = 0; j < tagnum; j++)
			{
				a_tag_total = 0;
				for(k = 0; k < CELLNUM; k++)
					a_tag_total = a_tag_total + frequency[k][tag_seq[j]];


				if(a_tag_total == 0)
				{
					printf("tag % d's a_tag_total = 0\n", tag_seq[j]);
					printf("photoid = %s\n", id);
				}
				if(tag_cell == 0)
				{
					if(a_tag_total == 0)
						PTL = PTL + log((lamda / (1 + lamda)) * (1.0 / tag_globe));
					else
						PTL = PTL + log((lamda / (1 + lamda)) * ((double)a_tag_total / tag_globe));
				}
				else
				{
					if((frequency[i][tag_seq[j]] == 0) && (a_tag_total == 0))
						PTL = PTL + log((1 / (1 + lamda)) * (1.0 / tag_cell) + (lamda / (1 + lamda)) * (1.0 / tag_globe));
					else
						PTL = PTL + log((1 / (1 + lamda)) * ((double)frequency[i][tag_seq[j]] / tag_cell) + (lamda / (1 + lamda)) * ((double)a_tag_total / tag_globe));
				}
				//printf("frequency[%d][%d] = %d, tag_cell = %d,a_tag_total = %d, tag_globe = %d\n", i, tag_seq[j], frequency[i][tag_seq[j]], tag_cell, a_tag_total, tag_globe);
				//printf("PTL = %lf\n", PTL);
				//getchar();
			}
			//写入文件，这个图片这个cell里面的ptl
			PTL = (PTL + log((double)PL[i])) / tagnum;
			fprintf(fp_PTL, "%d %lf\n", i, PTL);
		}
		fclose(fp_PTL);
	}
	fclose(fp_input);
	fclose(fp_PL);
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
