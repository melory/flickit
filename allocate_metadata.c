/**
  *
  *提取出聚类的部分，建模的部分，调整的部分，调整的部分
  *
  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main()
{
	int i, count = 0, len;
	char fname[50], line1[10000], line2[100000];
	FILE *fp, *fp_modeling, *fp_testing, *fp_tunning, *fp_clustering;


	if((fp_modeling = fopen("modeling.id.txt", "a+")) == 0)
	{
		printf("openning file 'modeling.id.txt' failed.1\n");
		getchar();
		return -1;
	}

	if((fp_testing = fopen("testing.id.txt", "a+")) == 0)
	{
		printf("openning file 'testing.id.txt' failed.2\n");
		getchar();
		return -1;
	}

	if((fp_tunning = fopen("tunning.id.txt", "a+")) == 0)
	{
		printf("openning file 'tunning.id.txt' failed.3\n");
		getchar();
		return -1;
	}

	if((fp_clustering = fopen("clustering.id.txt", "a+")) == 0)
	{
		printf("openning file 'clustering.id.txt' failed.4\n");
		getchar();
		return -1;
	}

	for(i = 1; i <= 21; i++)
	{
		sprintf(fname, "metadata%d.temp2.txt", i);
		if((fp = fopen(fname, "r")) == 0)
		{
			printf("openning file '%s' failed.\n", fname);
			getchar();
			return -1;
		}

		while(1)
		{
			if((fgets(line1,10000, fp) != 0) && (fgets(line2, 100000, fp) != 0))
			{
				len = strlen(line2);
				count++;

				if((count % 20 == 7) && ((line2[len - 3] != 'L') || (line2[len - 4] != 'L') || (line2[len - 5] != 'U') || (line2[len - 6] != 'N')))
					fprintf(fp_testing, "%s%s", line1, line2);
				else if((count % 20 == 14) && ((line2[len - 3] != 'L') || (line2[len - 4] != 'L') || (line2[len - 5] != 'U') || (line2[len - 6] != 'N')))
					fprintf(fp_tunning, "%s%s", line1, line2);
				else if((count % 20 == 1) || (count % 20 == 5) || (count % 20 == 9) || (count % 20 == 17))
					fprintf(fp_clustering, "%s%s", line1, line2);
				else
					fprintf(fp_modeling, "%s%s", line1, line2);
			}
			else
				break;
		}
		fclose(fp);
	}
	fclose(fp_clustering);
	fclose(fp_testing);
	fclose(fp_tunning);
	fclose(fp_modeling);
}