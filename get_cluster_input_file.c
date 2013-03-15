
/**
  *
  *将clustering的那些由sift *.pgm的key中的keypoints提取出来放在clustering_key.txt中，并把实际参与clustering的photo_id写在clustering_id.txt
  *
  **/

int
main()
{
	int i, desc[128];
	char line1[10000], line2[100000],fname[14];
	float temp;
	FILE *fp_id1, *fp_key1, *fp_key2, *fp_id2;

	if((fp_id1 = fopen("clustering.id.txt", "r")) == NULL)
	{
		printf("openning file 'clustering.id.txt' failed.\n");
		return -1;
	}

	if((fp_key2 = fopen("clustering_key.txt", "w")) == NULL)
	{
		printf("openning file 'clustering.id.txt' failed.\n");
		return -1;
	}

	if((fp_id2 = fopen("clustering_id.txt", "w")) == NULL)
	{
		printf("opennnig file 'clustering_id.txt' failed.\n");
		return -1;
	}

	while(1)
	{
		if((fgets(line1, 10000, fp_id1) != NULL) && (fgets(line2, 100000, fp_id1) != NULL))
		{
			for(i = 0; i <10; i++)
				fname[i] = line1[i];
			fname[10] = '.';
			fname[11] = 'k';
			fname[12] = 'e';
			fname[13] = 'y';
			fname[14] = '\0';

			//printf("%s\n", fname);

			if((fp_key1 = fopen(fname, "r")) == NULL)
			{
				printf("openning file %s failed.\n", fname);
				continue;
			}

			while(1)
			{
				for(i = 0; i < 4; i++)
					if(fscanf(fp_key1, "%lf", &temp) == EOF)
						goto END;

				for(i = 0; i <128; i++)
					if(fscanf(fp_key1, "%d", &(desc[i])) == EOF)
						goto END;

				//printf("line1 = %s\ndesc=", line1);
				//for(i = 0; i < 128; i++) printf(" %d", desc[i]); printf("\n");
				//getchar();

				for(i = 0; i < 128; i++)
					fprintf(fp_key2, "%d ", desc[i]);
				fprintf(fp_key2, "\n");
			}
END:
			fclose(fp_key1);

			for(i = 0; i < 10; i++)
			{
				fprintf(fp_id2, "%c", line1[i]);
			}
			fprintf(fp_id2, "\n");
		}
		else
			break;
	}

	fclose(fp_id1);
	fclose(fp_key2);
	fclose(fp_id2);

	return 0;
}