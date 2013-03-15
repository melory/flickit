/**
  *
  *将所有建模（包括聚类的）的keypoints按距离分配到现在得到的centers去
  *name.txt的内容是所有建模照片的编号
  *输出文件的内容为 photo.id lat lon center.id1 center.id2   ...   center.idn -1
  *以-1作为结束标志
  *
  **/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

double dist(double KP1[128], double KP2[128]);

int 
main()
{
	FILE *fp_center, *fp_metadata, *fp_assignment, *fp_key;
	int i, j, key[128];
	double temp[128], _dist[1000], center[1000][128], lat, lon, curmin, line2[10000], field1, field2, field3, field4;
	char ch, name[30], id[11];

	if((fp_center = fopen("cluster.txt", "r")) == NULL)
	{
		printf("openning file 'cluster.txt' failed.\n");
		return -1;
	}

	for(i = 0; i < 1000; i++)
		for(j = 0; j < 128; j++)
			fscanf(fp_center, "%lf", &(center[i][j]));

	fclose(fp_center);

	if((fp_assignment = fopen("modeling_key_distri.txt", "w")) == NULL) 
	{
		printf("openning file 'modeling_key_distri.txt' failed.\n");
		return -1;
	}

	if((fp_metadata = fopen("modeling.metadata.all.txt", "r")) == NULL)
	{
		printf("openningfile 'modeling.metadata.all.txt'failed.\n");
		return -1;
	}

	while(fscanf(fp_metadata, "%s%lf%lf", id, &lat, &lon) != EOF)
	{
		fscanf(fp_metadata, "%c", &ch);
		fgets(line2, 100000, fp_metadata);
		id[10] = '\0';
		sprintf(name, "%s.key", id);
		if((fp_key = fopen(name, "r")) == NULL)
		{
			printf("openning file '%s' failed.\n", name);
			continue;
		}
		fprintf(fp_assignment, "%s %lf %lf ", id, lat, lon);

		while(1)
		{
			if(fscanf(fp_key, "%lf%lf%lf%lf", &field1, &field2, &field3, &field4) == EOF)
				goto ENDofFILE;
			for(i = 0; i < 128; i++)
			{
				if(fscanf(fp_key, "%d", &(key[i])) == EOF)
					goto ENDofFILE;
				temp[i] = (double)key[i];
			}

			for(i = 0; i < 1000; i++)
			{
				_dist[i] = dist(temp, center[i]);
			}

			curmin = 1.79E+308;
			for(i = 0; i < 1000; i++)
			{
				if(curmin > _dist[i])
				{
					j = i;
					curmin = _dist[i];
				}
			}
			fprintf(fp_assignment, "%d ", j);
		}

ENDofFILE:
		fprintf(fp_assignment, "-1\n");
		fclose(fp_key);
	}
	fclose(fp_metadata);
	fclose(fp_assignment);

	return -1;
}


double dist(double KP1[128], double KP2[128])
{
	int i;
	double result;
	for(i = 0; i < 128; i ++)
	{
		result += (KP1[i] - KP2[i]) * (KP1[i] - KP2[i]);
	}
	result = sqrt(result);
	return result;
}
