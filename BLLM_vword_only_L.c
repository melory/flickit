/**
  *
  * BaseLine Language Model for visual words only with the Largest grain size case.
  *
  * 程序会输出testing的2K张照片和tunning的2K张照片在每个cell里面的p(T|L)值
  * 输出文件名为photoid_L_PTL.txt
  * 输出文件的内容为：
  *   cellidActual
  *   cellid0  The.Ptl.In.Cell0
  *   cellid1  The.Ptl.In.Cell1
  *   cellid2  The.Ptl.In.Cell2
  *   ...
  *   cellidn  The.Ptl.In.Celln
  *
  **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define lamda 0.1    //set lamda

#define CELLNUM 1534  //cell num: 0~1533
#define CENTERNUM 1000  //tag num: 0~999 

#define W -125
#define E -66
#define N 50
#define S 24
#define W_E 59
#define N_S 26

void** malloc2d(int w, int h, int size);


int
main()
{
	int i, j, k, cellid, cellidActual, centerid, vwordNum, **freq, vword_cell, vword_globe, a_vword_total, vword_seq[100000];
	char id[11], name[40];
	double lat, lon, PTL;
	FILE *fp_modeling, *fp_tunning, *fp_testing, *fp_PTL;

	freq = (int **)malloc2d(CENTERNUM, CELLNUM, sizeof(int));

	for(i = 0; i < CELLNUM; i++)
		for(j = 0; j < CENTERNUM; j++)
			freq[i][j] = 0;

	if((fp_modeling = fopen("modeling_key_distri.txt", "r")) == NULL)
	{
		printf("openning file 'modeling_key_distri.txt' failed.\n");
		return -1;
	}

	if((fp_testing = fopen("testing_key_distri.txt", "r")) == NULL)
	{
		printf("openning file 'testing_key_distri.txt' failed.\n");
		return -1;
	}

	if((fp_tunning = fopen("tunning_key_distri.txt", "r")) == NULL)
	{
		printf("openning file 'testing_key_distri.txt' failed.\n");
		return -1;
	}

	while(fscanf(fp_modeling, "%s%lf%lf", id, &lat, &lon) != EOF)
	{
		cellid = floor(lat - S) * W_E + floor(lon - W);
		while(1)
		{
			fscanf(fp_modeling, "%d", &centerid);
			if(centerid == -1)
				break;
			freq[cellid][centerid]++;
		}
	}

	vword_globe = 0;
	for(i = 0; i < CELLNUM; i++)
		for(j = 0; j < CENTERNUM; j++)
			vword_globe = vword_globe + freq[i][j];


	//for tunning images
	while(fscanf(fp_tunning, "%s%lf%lf", id, &lat, &lon) != EOF)
	{
		cellidActual = floor(lat - S) * W_E + floor(lon - W);
		vwordNum = 0;
		
		while(1)
		{
			fscanf(fp_tunning, "%d", &centerid);
			if(centerid == -1)
				break;
			vword_seq[vwordNum] = centerid;
			vwordNum++;
		}

		sprintf(name, "%s_L_PTL.txt", id);
		if((fp_PTL = fopen(name, "w")) == NULL)
		{
			printf("openning file '%s' failed.\n", name);
			return -1;
		}
		fprintf(fp_PTL, "%d\n", cellidActual);

		for(i = 0; i < CELLNUM; i++)
		{
			PTL = 0;
			vword_cell = 0;

			for(j = 0; j < CENTERNUM; j++)
				vword_cell = vword_cell + freq[i][j];

			for(j = 0; j < vwordNum; j++)
			{
				a_vword_total = 0;
				for(k = 0; k < CELLNUM; k++)
					a_vword_total = a_vword_total + freq[k][vword_seq[j]];


				if(a_vword_total == 0)
				{
					printf("tag % d's a_vword_total = 0\n", vword_seq[j]);
					printf("photoid = %s\n", id);
					//getchar();
				}
				if(vword_cell == 0)
				{
					if(a_vword_total == 0)
						PTL = PTL + log((lamda / (1 + lamda)) * (1.0 / vword_globe));
					else
						PTL = PTL + log((lamda / (1 + lamda)) * ((double)a_vword_total / vword_globe));
				}
				else
				{
					if((freq[i][vword_seq[j]] == 0) && (a_vword_total == 0))
						PTL = PTL + log((1 / (1 + lamda)) * (1.0 / vword_cell) + (lamda / (1 + lamda)) * (1.0 / vword_globe));
					else
						PTL = PTL + log((1 / (1 + lamda)) * ((double)freq[i][vword_seq[j]] / vword_cell) + (lamda / (1 + lamda)) * ((double)a_vword_total / vword_globe));
				}
				//printf("frequency[%d][%d] = %d, tag_cell = %d,a_tag_total = %d, tag_globe = %d\n", i, tag_seq[tagnum - 1], frequency[i][tag_seq[tagnum - 1]], tag_cell, a_tag_total, tag_globe);
				//printf("PTL = %lf\n", PTL);
				//getchar();
			}
			//写入文件，这个图片这个cell里面的ptl
			PTL = PTL / vwordNum;
			fprintf(fp_PTL, "%d %lf\n", i, PTL);
		}
		fclose(fp_PTL);
	}



	//for testing images
	while(fscanf(fp_testing, "%s%lf%lf", id, &lat, &lon) != EOF)
	{
		cellidActual = floor(lat - S) * W_E + floor(lon - W);
		vwordNum = 0;
		
		while(1)
		{
			fscanf(fp_testing, "%d", &centerid);
			if(centerid == -1)
				break;
			vword_seq[vwordNum] = centerid;
			vwordNum++;
		}

		sprintf(name, "%s_L_PTL.txt", id);
		if((fp_PTL = fopen(name, "w")) == NULL)
		{
			printf("openning file '%s' failed.\n", name);
			return -1;
		}
		fprintf(fp_PTL, "%d\n", cellidActual);

		for(i = 0; i < CELLNUM; i++)
		{
			PTL = 0;
			vword_cell = 0;

			for(j = 0; j < CENTERNUM; j++)
				vword_cell = vword_cell + freq[i][j];

			for(j = 0; j < vwordNum; j++)
			{
				a_vword_total = 0;
				for(k = 0; k < CELLNUM; k++)
					a_vword_total = a_vword_total + freq[k][vword_seq[j]];


				if(a_vword_total == 0)
				{
					printf("tag % d's a_vword_total = 0\n", vword_seq[j]);
					printf("photoid = %s\n", id);
					//getchar();
				}
				if(vword_cell == 0)
				{
					if(a_vword_total == 0)
						PTL = PTL + log((lamda / (1 + lamda)) * (1.0 / vword_globe));
					else
						PTL = PTL + log((lamda / (1 + lamda)) * ((double)a_vword_total / vword_globe));
				}
				else
				{
					if((freq[i][vword_seq[j]] == 0) && (a_vword_total == 0))
						PTL = PTL + log((1 / (1 + lamda)) * (1.0 / vword_cell) + (lamda / (1 + lamda)) * (1.0 / vword_globe));
					else
						PTL = PTL + log((1 / (1 + lamda)) * ((double)freq[i][vword_seq[j]] / vword_cell) + (lamda / (1 + lamda)) * ((double)a_vword_total / vword_globe));
				}
				//printf("frequency[%d][%d] = %d, tag_cell = %d,a_tag_total = %d, tag_globe = %d\n", i, tag_seq[tagnum - 1], frequency[i][tag_seq[tagnum - 1]], tag_cell, a_tag_total, tag_globe);
				//printf("PTL = %lf\n", PTL);
				//getchar();
			}
			//写入文件，这个图片这个cell里面的ptl
			PTL = PTL / vwordNum;
			fprintf(fp_PTL, "%d %lf\n", i, PTL);
		}
		fclose(fp_PTL);
	}


	fclose(fp_modeling);
	fclose(fp_testing);
	fclose(fp_tunning);
	free(freq);

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
