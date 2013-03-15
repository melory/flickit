
/**
  *
  *从所有照片的for_getting_IM.txt文件中提取没有重复（就是由同一用户上传摄于同一地点具有完全相同tags的照片只保留一张）的for_getting_IM.txt
  *
  *输入文件有clustering.id.txt+modeling.id.txt和for_getting_IM.txt
  **/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int
main()
{
	int i;
	char line1[10000], line2[100000], id[11], ID[11], FARM[5], SERVER[10], SECRECT[20];
	FILE *fp1, *fp2, *fp3;
	

	if((fp2 = fopen("for_getting_IM_filetered.txt", "w")) == NULL)
	{
		printf("openning file 'for_getting_IM_filetered.txt' failed.\n");
		getchar();
		return -1;
	}

	if((fp3 = fopen("metadata.temp2.txt", "r")) == NULL)
	{
		printf("openning file 'metadata.temp2.txt' failed.\n");
		getchar();
		return -1;
	}

	while(1)
	{
		if((fgets(line1, 10000, fp3) != 0) && (fgets(line2, 100000, fp3) != 0))
		{
			for(i = 0; i < 10; i++)
				id[i] = line1[i];
			id[10] = '\0';

			if((fp1 = fopen("for_getting_IM.txt", "r")) == NULL)
			{
				printf("openning file 'for_getting_IM.txt' failed.\n");
				getchar();
				return -1;
			}

			while(fscanf(fp1, "%s%s%s%s", ID, FARM, SERVER, SECRECT) != EOF)
			{
				if(strcmp(id, ID) == 0)
				{
					fprintf(fp2, "%s %s %s %s\n", ID, FARM, SERVER, SECRECT);
					break;
				}
			}
		fclose(fp1);
		}
		else
			break;
	}
	fclose(fp2);
	fclose(fp3);

	return 0;
}