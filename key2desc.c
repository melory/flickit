/**
  *
  *将.key文件中的descriptor写到.desc文件里面去。
  *
  **/

#include <stdio.h>
#include <stdlib.h>

int
main()
{
	int i, term;
	char id[11], name[20];
	double temp1, temp2, temp3, temp4;
	FILE *fp_key, *fp_desc, *fp_id;

	if((fp_id = fopen("tunning.id.txt", "r")) == NULL)
	{
		printf("openning file 'tunning.id.txt' failed.\n");
		return -1;
	}

	while(fscanf(fp_id, "%s", id) != EOF)
	{
		sprintf(name, "%s.key", id);
		if((fp_key = fopen(name, "r")) == NULL)
		{
			printf("openning file '%s' failed.\n", name);
			continue;
		}

		sprintf(name, "%s.desc", id);
		if((fp_desc = fopen(name, "w")) == NULL)
		{
			printf("openning file '%s' failed.\n", name);
			return -1;
		}

		while(fscanf(fp_key, "%lf%lf%lf%lf", &temp1, &temp2, &temp3, &temp4) != EOF)
		{
			for(i = 0; i < 128; i++)
			{
				if(fscanf(fp_key, "%d", &term) != EOF)
					fprintf(fp_desc, "%d ", term);
			}
			fprintf(fp_desc, "\n");
		}

		fclose(fp_key);
		fclose(fp_desc);
	}

	fclose(fp_id);
	return 0;
}
