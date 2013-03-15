/**
  *
  *从clustering.metadata.txt这样的文件里面读取照片的id
  *
  **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main()
{
	int i;
	char line1[10000], line2[100000];

	FILE *fp_metadata, *fp_id;

	if((fp_metadata = fopen("modeling.metadata.all.txt", "r")) == NULL)
	{
		printf("openning file 'modeling.metadata.all.txt' failed.\n");
		return -1;
	}

	if((fp_id = fopen("modeling.id.txt", "w")) == NULL)
	{
		printf("openning file 'modeling.id.txt' failed.\n");
		return -1;
	}
	
	while(1)
	{
		if((fgets(line1, 10000, fp_metadata) != NULL) && (fgets(line2, 100000, fp_metadata) != NULL))
		{
			for(i = 0; i < 10; i++)
				fprintf(fp_id, "%c", line1[i]);
			frpintf(fp_id"\n");
		}
		else
			break;
	}

	fclose(fp_metadata);
	fclose(fp_id);

	return 0;
}