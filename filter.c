/**
 * get only one picuter's metadata if there are many pictures taken at the same place and with same tags
 *
 **/

/**
 *产生两个中间文件
 *temp1和temp2文件中的内容格式为
 *photo.id lat lon
 *owner.nsid location.woeid tags
 *temp2中没有由同一用户上传摄于同一地点具有相同tags的多张照片
 *
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main()
{
	int i,j, repeated = 0;
	char curstr[10000], fname[50], line1[10000], line2[100000], line1_[10000], line2_[100000];
	FILE *fp_origin, *fp_temp1, *fp_temp2;


	for(i = 1; i <= 21; i++)
	{
		printf("milestone:\n...roud 1, i = %d\n\n", i);
		sprintf(fname, "metadata%d.txt", i);
		if((fp_origin = fopen(fname, "r")) == 0)
		{
			printf("openning file '%s' failed.1\n", fname);
			getchar();
			return -1;
		}

		sprintf(fname, "metadata%d.temp1.txt", i);
		if((fp_temp1 = fopen(fname, "w")) == 0)
		{
			printf("openning file '%s' failed.2\n", fname);
			getchar();
			return -1;
		}

		sprintf(fname, "metadata%d.temp2.txt", i);
		if((fp_temp2 = fopen(fname, "w")) == 0)
		{
			printf("openning file '%s' failed.3\n", fname);
			getchar();
			return -1;
		}
		fclose(fp_temp2);  //just to create file metadata*.temp2.txt

		while(fscanf(fp_origin, "%s", curstr) != EOF)
		{
			if(strcmp(curstr, "<photoID>") == 0)
			{
				fscanf(fp_origin, "%s", curstr);
				fprintf(fp_temp1, "%s ", curstr);
			}

			if(strcmp(curstr, "<location_latitude>") == 0)
			{
				fscanf(fp_origin, "%s", curstr);
				fprintf(fp_temp1, "%s ", curstr);
			}

			if(strcmp(curstr, "<location_longitude>") == 0)
			{
				fscanf(fp_origin, "%s", curstr);
				fprintf(fp_temp1, "%s\n", curstr);
			}

			if(strcmp(curstr, "<owner_nsid>") == 0)
			{
				fscanf(fp_origin, "%s", curstr);
				fprintf(fp_temp1, "%s ", curstr);
			}

			if(strcmp(curstr, "<location_woeid>") == 0)
			{
				fscanf(fp_origin, "%s", curstr);
				fprintf(fp_temp1, "%s ", curstr);
			}

			if(strcmp(curstr, "<TAGs>") == 0)
			{
				while(1)
				{
					fscanf(fp_origin, "%s", curstr);
					if(strcmp(curstr, "</TAGs>") == 0)
					{
						fprintf(fp_temp1, "\n");
						break;
					}
					else
						fprintf(fp_temp1, "%s ", curstr);
				}
			}
		}

		fclose(fp_origin);
		fclose(fp_temp1);
	}

	for(i = 1; i <= 21; i++)
	{
		printf("milestone:\n...roud 2, i = %d\n\n", i);
		sprintf(fname, "metadata%d.temp1.txt", i);
		if((fp_temp1 = fopen(fname, "r")) == 0)
		{
			printf("openning file '%s' failed.4\n", fname);
			getchar();
			return -1;
		}

		while(1)
		{
			if((fgets(line1, 10000, fp_temp1) != 0) && (fgets(line2, 100000, fp_temp1) != 0))
			{
				repeated = 0;
				sprintf(fname, "metadata%d.temp2.txt", i);
				if((fp_temp2 = fopen(fname, "r")) == 0)
				{
					printf("openning file '%s' failed.5\n", fname);
					getchar();
					return -1;
				}

				while(1)
				{
					if((fgets(line1_, 10000, fp_temp2) != 0) && (fgets(line2_, 100000, fp_temp2) != 0))
					{
						//printf("line1 = %s\nline2 = %s\nline1_ = %s\nline2_ = %s\n", line1, line2, line1_, line2_);
						if(strcmp(line2, line2_) == 0)
						{
							repeated = 1;
							break;
						}
					}
					else
						break;
				}
				fclose(fp_temp2);

				if(repeated == 0)
				{
					if((fp_temp2 = fopen(fname, "a+")) == 0)
					{
						printf("oenning file '%s' failed.6\n", fname);
						getchar();
						return -1;
					}
					fprintf(fp_temp2, "%s%s", line1, line2);
					fclose(fp_temp2);
				}
			}
			else
				break;
		}

		fclose(fp_temp1);
	}
	return 0;
}
