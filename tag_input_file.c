/**
  *
  *从tunning.metadata.txt和testing.metadata.txt中读取信息，然后制定language model的输入文件
  *输入文件中的内容为：
  *photo.id lat lon tagid1 tagid2 tagid3 ... tagidn -1
  *
  **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int _isupper(char c);

int
main()
{
	int i, tagid;
	double lat, lon;
	char ch, id[11], owner_nsid[20], location_woeid[20], fname[20], buf[10000], tag[10000];
	FILE *fp_metadata, *fp_input, *fp_tagtable;

	if((fp_metadata = fopen("tunning.metadata.txt", "r")) == NULL)
	{
		printf("openning file 'tunning.metadata.txt' failed.\n");
		return -1;
	}

	if((fp_input = fopen("tunning.tag.input.file.txt", "w")) == NULL)
	{
		printf("openning file 'tunning.tag.input.file.txt' failed.\n");
		return -1;
	}

	while(1)
	{
		if(fscanf(fp_metadata, "%s%lf%lf%s%s", id, &lat, &lon, owner_nsid, location_woeid) != EOF)
		{
			fprintf(fp_input, "%s %lf %lf ", id, lat, lon);
			fscanf(fp_metadata, "%c", &ch);
			fscanf(fp_metadata, "%c", &ch);
			i = 0;
			while(ch != '\n')
			{
				if(ch == ' ')
				{
					tag[i] = '\0';
					i = 0;
				

					if(tag[0] >= 'a' && tag[0] <= 'z')
						sprintf(fname, "%c.tag.txt", tag[0]);
					else
						sprintf(fname, "other.tag.txt");

					if((fp_tagtable = fopen(fname, "r")) == NULL)
					{
						printf("openning file '%s' failed.\n", fname);
						return -1;
					}

					while(fscanf(fp_tagtable, "%d%s", &tagid, buf) != EOF)
					{
						if(strcmp(buf, tag) == 0)
						{
							fprintf(fp_input, "%d ", tagid);
							break;
						}
					}
					fclose(fp_tagtable);
				}
				else
				{
					if(_isupper(ch))
					{
						tag[i] = (char)(ch + ('a' - 'A'));
						i++;
					}
					else
					{
						tag[i] = ch;
						i++;
					}
				}
				fscanf(fp_metadata, "%c", &ch);
			}
			fprintf(fp_input, "-1\n");
		}
		else
			break;
	}
	fclose(fp_metadata);
	fclose(fp_input);
	return 0;
}

int _isupper(char c)
{
	if(c >= 'A' && c <= 'Z')
		return 1;
	else
		return 0;
}
