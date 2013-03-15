/**
  *
  *计算各种检验结果值
  *输入文件为PTL文件，同时还需要tunning.id.txt(testing.id.txt)文件做为输入
  *需要适当改动fp_id所指向的文件，来分别验证testing images的准确率和tunning images的准确率
  **/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define W_E 59

int is_hittedAT1(int cellid_actual, int cellid, int WE);
int is_hittedAT2(int cellid_actual, int cellid, int WE);
int is_hittedAT3(int cellid_actual, int cellid, int WE);

int
main()
{
	int i, cellid_actual, cellid, cellid_cur, rank, hits = 0, hitsAT1 = 0, hitsAT2 = 0, hitsAT3 = 0, photonum = 0;
	char id[11], name[30];
	double ptl, cur_max, ptl_actual, acc, accAT1, accAT2, accAT3, mrr = 0.0;
	FILE *fp_PTL, *fp_id;

	printf("make sure that W_E is rightly setted.");
	//getchar();

	if((fp_id = fopen("tunning.id.txt", "r")) == NULL)
	{
		printf("openning file 'tunning.id.txt' faided.\n");
		getchar();
		return -1;
	}

	while(fscanf(fp_id, "%s", id) != EOF)
	{
		sprintf(name, "%s_L_PTL.txt", id);

		if((fp_PTL = fopen(name, "r")) == NULL)
		{
			printf("openning file '%s' failed.\n", name);
			continue;
		}

		photonum ++;

		if(fscanf(fp_PTL, "%d", &cellid_actual) == EOF)
		{
			printf("something bad in file '%s'\n", name);
			getchar();
			return -1;
		}

		while(fscanf(fp_PTL, "%d%lf", &cellid, &ptl) != EOF)
		{
			if(cellid == cellid_actual)
			{
				ptl_actual = ptl;
				break;
			}
		}

		fclose(fp_PTL);
		
		if((fp_PTL = fopen(name, "r")) == NULL)
		{
			printf("openning file '%s' failed.\n", name);
			getchar();
			return -1;
		}
		fscanf(fp_PTL, "%d", &cellid_actual);
		cur_max = -1.7E308;
		rank = 1;
		while(fscanf(fp_PTL, "%d%lf", &cellid, &ptl) != EOF)
		{
			if(ptl > cur_max)
			{
				cur_max = ptl;
				cellid_cur = cellid;
			}

			if(ptl > ptl_actual)
				rank ++;
		}

		fclose(fp_PTL);
		if(cellid_cur == cellid_actual)
			hits ++;
		if(is_hittedAT1(cellid_actual, cellid_cur, W_E))
			hitsAT1 ++;
		if(is_hittedAT2(cellid_actual, cellid_cur, W_E))
			hitsAT2 ++;
		if(is_hittedAT3(cellid_actual, cellid_cur, W_E))
			hitsAT3 ++;
		mrr = mrr + (1.0 / rank);
	}
	fclose(fp_id);
	mrr = mrr / photonum;
	
	printf("total:%d\nhits:%d\nhitsAT1:%d\nhitsAT2:%d\nhitsAT3:%d\nacc:%lf\naccAT1:%lf\naccAT2:%lf\naccAT3:%lf\nmrr:%lf\n", photonum, hits, hitsAT1, hitsAT2, hitsAT3, ((double)hits / photonum), ((double)hitsAT1 / photonum), ((double)hitsAT2 / photonum), ((double)hitsAT3 / photonum), mrr);
	getchar();
	return 0;
}



int
is_hittedAT1(int cellid_actual, int cellid, int WE)
{
	if(((cellid >= cellid_actual - 1) && (cellid <= cellid_actual + 1)) || 
		((cellid >= cellid_actual - 1 - W_E) && (cellid <= cellid_actual + 1 - W_E)) ||
		((cellid >= cellid_actual - 1 + W_E) && (cellid <= cellid_actual + 1 + W_E)))
		return 1;
	else
		return 0;
}


int
is_hittedAT2(int cellid_actual, int cellid, int WE)
{
	if(((cellid >= cellid_actual - 2) && (cellid <= cellid_actual + 2)) || 
		((cellid >= cellid_actual - 2 - W_E) && (cellid <= cellid_actual + 2 - W_E)) ||
		((cellid >= cellid_actual - 2 + W_E) && (cellid <= cellid_actual + 2 + W_E)))
		return 1;
	else
		return 0;
}


int
is_hittedAT3(int cellid_actual, int cellid, int WE)
{
	if(((cellid >= cellid_actual - 3) && (cellid <= cellid_actual + 3)) || 
		((cellid >= cellid_actual - 3 - W_E) && (cellid <= cellid_actual + 3 - W_E)) ||
		((cellid >= cellid_actual - 3 + W_E) && (cellid <= cellid_actual + 3 + W_E)))
		return 1;
	else
		return 0;
}
