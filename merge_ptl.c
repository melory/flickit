#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define CELLNUM 1533

int
main()
{
	int i, cellid, actual_tag, actual_key;
	char path1[1000], path2[1000], path[30], id[20];
	double ptl, ptl_tag[CELLNUM + 1], ptl_key[CELLNUM + 1];
	FILE *fp_id, *fp_tag, *fp_key, *fp;

	for(i = 0; i < CELLNUM + 1; i++)
	{
		ptl_tag[i] = 0.0;
		ptl_key[i] = 0.0;
	}

	if((fp_id = fopen("tunning.id.txt", "r")) ==NULL)
	{
		printf("openning file 'tunning.id.txt' failed.\n");
		return -1;
	}

	while(fscanf(fp_id, "%s", id) != EOF)
	{
		sprintf(path1, "tunning_tag_NO_PL\\%s_L_PTL.txt", id);
		sprintf(path2, "KEY_NO_PL\\%s_L_PTL.txt", id);
		sprintf(path, "%s_L_PTL.txt", id);
		if(((fp_tag = fopen(path1, "r")) != NULL) && ((fp_key = fopen(path2, "r")) != NULL))
		{
			if((fp = fopen(path, "w")) == NULL)
			{
				printf("openning file '%s' failed.\n", path);
				return -1;
			}

			fscanf(fp_tag, "%d", &actual_tag);
			while(fscanf(fp_tag, "%d%lf", &cellid, &ptl) != EOF)
			{
				ptl_tag[cellid] = ptl;
			}
			fclose(fp_tag);

			fscanf(fp_key, "%d", &actual_key);
			while(fscanf(fp_key, "%d%lf", &cellid, &ptl) != EOF)
			{
				ptl_key[cellid] = ptl;
			}
			fclose(fp_key);

			if(actual_tag != actual_key)
			{
				printf("ACTUALs are different.\n");
				break;
			}

			fprintf(fp, "%d\n", actual_tag);
			for(i = 0; i < CELLNUM + 1; i++)
			{
				fprintf(fp, "%d %lf\n", i, ptl_tag[i] + ptl_tag[i]);
			}

			fclose(fp);
		}
	}
	fclose(fp_id);
	return 0;

}