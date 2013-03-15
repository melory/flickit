/**
  *
  *ºÏ²¢for_getting_IM*.txt Îªfor_getting_IM.txt
  *
  **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int
main()
{
	int i;
	char fname[100], ch;
	FILE *fp1, *fp2;

	if((fp2 = fopen("modeling_key_distri.txt", "w")) == 0)
	{
		printf("openning file 'modeling_key_distri.txt' failed.\n");
		return -1;
	}

	for(i = 1; i <= 4; i++)
	{
		sprintf(fname, "modeling_key_distri_%d.txt", i);
		if((fp1 = fopen(fname, "r")) == 0)
		{
			printf("openning file '%s' failed.\n", fname);
			return -1;
		}

		while(fscanf(fp1, "%c", &ch) != EOF)
		{
			fprintf(fp2, "%c", ch);
		}
	}

	return 0;
}
