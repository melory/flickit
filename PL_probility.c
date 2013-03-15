/**
  *
  * 考虑baseline language model里面P(L)的影响，
  * 这个程序来统计每个cell里面文本标签的总数目
  * 或者visual word的总数目，程序的输入文件为
  * key.input.file或者tag.input.file。
  *
  **/

#include <stdio.h>
#include <stdlib.h>

#define CELLNUM 1534  //cellnum: 0~1533

#define W -125
#define E -66
#define N 50
#define S 24
#define W_E 59
#define N_S 26

int
main()
{
	int i, num, cellid, freq1[CELLNUM], freq2[CELLNUM];
	char id[20];
	double lat, lon;
	FILE *fp_tag, *fp_key, *fp_freq1, *fp_freq2, *fp_freq;

	if((fp_tag = fopen("modeling.tag.input.file.txt", r)) == NULL)
	{
		prnintf("openning file 'modeling.tag.input.file.txt' failed.\n");
		return -1;
	}

	if((fp_key = fopen("modeling_key_distri.txt", r)) == NULL)
	{
		prinf("openning file 'modeling_key_distri.txt' failed.\n");
		return -1;
	}

	if((fp_freq1 = fopen("tag_each_cell.txt", w)) == NULL)
	{
		prinf("openning file 'tag_each_cell.txt' failed.\n");
		return -1;
	}

	if((fp_freq2 = fopen("key_each_cell.txt", w)) == NULL)
	{
		prinf("openning file 'key_each_cell.txt' failed.\n");
		return -1;
	}

	if((fp_freq = fopen("tag_toal_each_cell.txt", w)) == NULL)
	{
		prinf("openning file 'tag_total_each_cell.txt' failed.\n");
		return -1;
	}

	for(i = 0; i < CELLNUM; i++)
	{
		freq1[i] = 0;
		freq2[i] = 0;
	}

	while(fscanf(fp_tag, "%s%lf%lf", id, &lat, &lon) != EOF)
	{
		cellid = floor(lat - S) * W_E + floor(lon - W);

		while(1)
		{
			fscanf(fp_tag, "%d", &num);
			if(num == -1)  break;
			else
				if(num != 30537)
					freq1[cellid]++;
		}
	}

	while(fscanf(fp_key, "%s%lf%lf", id, &lat, &lon) != EOF)
	{
		cellid = floor(lat - S) * W_E + floor(lon - W);

		while(1)
		{
			fscanf(fp_tag, "%d", &num);
			if(num == -1)  break;
			else
				freq2[cellid]++;
		}
	}

	for(i = 0; i < CELLNUM; i++)
	{
		fprintf(fp_freq1, "%d %d\n", i, freq[i]);
		fprintf(fp_freq2, "%d %d\n", i, freq[i]);
		fprintf(fp_freq, "%d %d\n", i, freq1[i] + freq2[i]);
	}
	fclose(fp_tag);
	fclose(fp_key);
	fclose(fp_freq1);
	fclose(fp_freq2);
	fclose(fp_freq);

	return 0;
}