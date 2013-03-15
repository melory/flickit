/**
  *
  *统计在最大粒度的情况下，每个cell里面的所有tag的频数
  *
  **/

/**
  *    0    1    2    3    4   5   ...(cellid)
  * -----------------------------------------
  * |    |    |    |    |    |    |    |    |
  * 0    1    2    3    4    5    6  ...
  **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define W -125
#define E -66
#define N 50
#define S 24
#define W_E 59
#define N_S 26


int
main()
{
	int i, num[W_E * N_S], cellid, tags_in_thispic, len;
	char photo_id[20], line2[100000], ch;
	double lat, lon;
	FILE *fp_temp2, *fp_tag_fre;

	for(i = 0; i < W_E * N_S; i++)
		num[i] = 0;

	if((fp_temp2 = fopen("metadata.temp2.txt","r")) == NULL)
	{
		printf("openning file 'metadata.temp2.txt' failed.\n");
		return -1;
	}
	
	while(1)
	{
		if((fscanf(fp_temp2, "%s%lf%lf%c", photo_id, &lat, &lon, &ch) != EOF) && (fgets(line2, 100000, fp_temp2) != EOF))
		{
			cellid = floor(lat - S) * W_E + floor(lon - W);
			tags_in_thispic = 0;
			len = strlen(line2);
			for(i = 0; i< len; i++)
			{
				if(line2[i] == ' ')
					tags_in_thispic++;
			}
			num[cellid] = num[cellid] + tags_in_thispic - 2;
		}
		else
			break;
	}

	fclose(fp_temp2);

	if((fp_tag_fre = fopen("tagnum_in_each_cell_L.txt", "w")) == NULL)
	{
		printf("openning file 'tagnum_in_each_cell_L.txt' failed.\n");
		return -1;
	}

	for(i = 0; i < W_E * N_S; i++)
		fprintf(fp_tag_fre, "%d %d\n", i, num[i]);
	fclose(fp_temp2);
	return 0;
}