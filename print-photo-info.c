/*
 * print-photo-info.c - Flickcurl example code to get information about a photo
 *
 * This is example code and not complete because the API Key, Shared
 * Secret and Auth Token are not configured.  The flickcurl utility
 * in utils/flickcurl.c contains code that fully uses the API.
 *
 * ID.txt is the the photo_IDs file
 *
 * This file is in the Public Domain
 *
 * Compile it like this:
 *   gcc -o print-photo-info print-photo-info.c `flickcurl-config --cflags` `flickcurl-config --libs`
 * or use
 *   make print-photo-info
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <flickcurl.h>


int main(int argc, char *argv[]) {
  flickcurl *fc;
  flickcurl_photo *photo;
  flickcurl_photo_field_type field_type;
  int i, j, loc_accu;
  char photoID[42];
  FILE *fp_ID;
  FILE *fp[17], *fp_GetIm[17];
  /*file pointers for photos with different location accuracy,fpM1 if for accuracy=-1*/
  /*FILE *fpM1, *fp1, *fp2, *fp3, *fp4, *fp5, *fp6, *fp7, *fp8, *fp9, *fp10,
   *    *fp11, *fp12, *fp13, *fp14, *fp15, *fp16;
   */

  char *fname[17] = {"info_M1.txt", "info_1.txt", "info_2.txt", "info_3.txt",
                    "info_4.txt", "info_5.txt", "info_6.txt", "info_7.txt",
                    "info_8.txt", "info_9.txt", "info_10.txt", "info_11.txt",
                    "info_12.txt", "info_13.txt", "info_14.txt", "info_15.txt",
                    "info_16.txt"};

  char *fname_GetIm[17] = {"GetIm_M1.txt", "GetIm_1.txt", "GetIm_2.txt", "GetIm_3.txt",
                    "GetIm_4.txt", "GetIm_5.txt", "GetIm_6.txt", "GetIm_7.txt",
                    "GetIm_8.txt", "GetIm_9.txt", "GetIm_10.txt", "GetIm_11.txt",
                    "GetIm_12.txt", "GetIm_13.txt", "GetIm_14.txt", "GetIm_15.txt",
                    "GetIm_16.txt"};

  char *prefix[68] = {"<photoID>", "<update_time>", "<farm>", "<isfavorite>", "<license>",
	                  "<originalformat>", "<rotation>", "<server>", "<dates_lastupdate>", "<dates_posted>",
					  "<dates_taken>", "<dates_takengranularity>", "<description>", "<editability_canaddmeta>", "<editability_cancomment>",
					  "<geoperms_iscontact>", "<geoperms_isfamily>", "<geoperms_isfriend>", "<geoperms_ispublic>", "<location_accuracy>",
					  "<location_latitude>", "<location_longitude>", "<owner_location>", "<owner_nsid>", "<owner_realname>",
					  "<owner_username>", "<photo_title>", "<visibility_isfamily>", "<visibility_isfriend>", "<visibility_ispublic>",
					  "<secret>", "<originalsecret>", "<location_neighbourhood>", "<location_locality>", "<location_neighborhood>",
					  "<location_region>", "<location_country>", "<location_placeid>", "<neighbourhood_placeid>", "<locality_placeid>",
					  "<county_placeid>", "<region_placeid>", "<country_placeid>", "<location_woeid>", "<neighbourhood_woeid>",
					  "<locality_woeid>", "<county_woeid>", "<region_woeid>", "<country_woeid>", "<usage_candownload>",
					  "<usage_canblog>", "<usage_canprint>", "<owner_iconserver>", "<owner_iconfarm>", "<original_width>",
					  "<original_height>", "<views>", "<comments>", "<favorites>", "<gallery_comment>",
					  "<url_for_s>", "<url_for_t>", "<url_for_m>", "<url_for_->", "<url_for_z>",
					  "<url_for_b>", "<url_for_o>", "<TAGs>"};

  char *suffix[68] = {"</photoID>", "</update_time>", "</farm>", "</isfavorite>", "</license>",
	                  "</originalformat>", "</rotation>", "</server>", "</dates_lastupdate>", "</dates_posted>",
					  "</dates_taken>", "</dates_takengranularity>", "</description>", "</editability_canaddmeta>", "</editability_cancomment>",
					  "</geoperms_iscontact>", "</geoperms_isfamily>", "</geoperms_isfriend>", "</geoperms_ispublic>", "</location_accuracy>",
					  "</location_latitude>", "</location_longitude>", "</owner_location>", "</owner_nsid>", "</owner_realname>",
					  "</owner_username>", "</photo_title>", "</visibility_isfamily>", "</visibility_isfriend>", "</visibility_ispublic>",
					  "</secret>", "</originalsecret>", "</location_neighbourhood>", "</location_locality>", "</location_neighborhood>",
					  "</location_region>", "</location_country>", "</location_placeid>", "</neighbourhood_placeid>", "</locality_placeid>",
					  "</county_placeid>", "</region_placeid>", "</country_placeid>", "</location_woeid>", "</neighbourhood_woeid>",
					  "</locality_woeid>", "</county_woeid>", "</region_woeid>", "</country_woeid>", "</usage_candownload>",
					  "</usage_canblog>", "</usage_canprint>", "</owner_iconserver>", "</owner_iconfarm>", "</original_width>",
					  "</original_height>", "</views>", "</comments>", "</favorites>", "</gallery_comment>",
					  "</url_for_s>", "</url_for_t>", "</url_for_m>", "</url_for_->", "</url_for_z>",
					  "</url_for_b>", "</url_for_o>", "<TAGs>"};


  fp_ID = fopen("ID.txt", "r");
  
  for(i=0; i<17; i++)
  {
   fp[i] = fopen(fname[i], "a+");
   fp_GetIm[i] = fopen(fname_GetIm[i], "a+");
  }



  for(i = 0; i < 14000000; i++)
  {
    flickcurl_init(); /* optional static initialising of resources */
    fc=flickcurl_new();

    /* Set configuration, or more likely read from a config file */
    flickcurl_set_api_key(fc, "b989a68d4f87acfc513f708e7d404ced");
    flickcurl_set_shared_secret(fc, "9c317f312857b8dc");
    flickcurl_set_auth_token(fc, "72157625359500520-36d6056561e97c07");

	fscanf(fp_ID, "%s", photoID);
    photo = flickcurl_photos_getInfo(fc, photoID); /* photo ID */

    /*
      for(field_type=0; field_type <= PHOTO_FIELD_LAST; field_type++) {
        flickcurl_field_value_type datatype=photo->fields[field_type].type;
      
        if(datatype != VALUE_TYPE_NONE)
          fprintf(stderr, "field %s (%d) with %s value: '%s' / %d\n", 
                  flickcurl_get_photo_field_label(field_type), (int)field_type,
                  flickcurl_get_field_value_type_label(datatype),
                  photo->fields[field_type].string,
                  photo->fields[field_type].integer);
    */


    /*
     *Need to choose photos satisfying:
     *1)this photo is public;
     *2)location permision is public;
     *3)can be download
     */


    /*
     *Info witten to info.txt (one line per photo,deferent items are separated by tab)
     *in order as:

     *1) photo ID;
     *2) field(1) uploade time;
     *3) field(2) farm;
     *4) field(3) isfavorite;
     *5) field(4) license;
     *6) field(5) originalformat;
     *7) field(6) rotation;
     *8) field(7) server;
     *9) field(8) dates_lastupdate;
     *10) field(9) dates_posted;
     *11) field(10) dates_taken;
     *12) field(11) dates_takengranularity;
     *13) field(12) description(string);
     *14) field(13) editability_canaddmeta;
     *15) field(14) editability_cancomment;
     *16) field(15) geoperms_iscontact;
     *17) field(16) geoperms_isfamily;
     *18) field(17) geoperms_isfriend;
     *19) field(18) geoperms_ispublic;
     *20) field(19) location_accuracy(int,-1 and 1~16);
     *21) field(20) location_latitude;
     *22) field(21) location_longitude;
     *23) field(22) owner_location;
     *24) field(23) owner_nsid;
     *25) field(24) owner_realname;
     *26) field(25) owner_username;
     *27) field(26) photo_title;
     *28) field(27) visibility_isfamily;
     *29) field(28) visibility_isfriend;
     *30) field(29) visibility_ispublic;
     *31) field(30) secret;
     *32) field(31) originalsecret;
     *33) field(32) location_neighbourhood;
     *34) field(33) location_locality;
     *35) field(34) location_neighborhood;
     *36) field(35) location_region;
     *37) field(36) location_country;
     *38) field(37) location_placeid;
     *39) field(38) neighbourhood_placeid;
     *40) field(39) locality_placeid;
     *41) field(40) county_placeid;
     *42) field(41) region_placeid;
     *43) field(42) country_placeid;
     *44) field(43) location_woeid;
     *45) field(44) neighbourhood_woeid;
     *46) field(45) locality_woeid;
     *47) field(46) county_woeid;
     *48) field(47) region_woeid;
     *49) field(48) country_woeid;
	 *50) field(49) usage_candownload;
	 *51) field(50) usage_canblog;
     *52) field(51) usage_canprint;
	 *53) field(52) owner_iconserver;
	 *54) field(53) owner_iconfarm;
	 *55) field(54) original_width;
	 *56) field(55) original_height;
	 *57) field(56) views;
	 *58) field(57) comments;
	 *59) field(58) favorites;
	 *60) field(59) gallery_comment;
     *61) url for s(75X75);
     *62) url for t(100X100);
     *63) url for m(max=240X240);
     *64) url for -(max=500X500);
     *65) url for z(max=640X640);
     *66) url for b(max=1024*1024);
     *67) url for o(origin);
     *68) TAGs ID(separated by TAB).

     */

    if(photo && photo->fields[29].integer == 1 && photo->fields[49].integer == 1)
      {
         loc_accu = photo->fields[19].integer; /* get the location accuracy */

         if(loc_accu == -1)  loc_accu=0; /* here change loc_accu for ease of writting info  */

		 /*if (photo->fields[19].integer != -1)*/ 
		 {
			 fprintf(fp[loc_accu], "%s %s %s", prefix[0], photoID, suffix[0]); /* photo ID */
			 fprintf(fp_GetIm[loc_accu], "%s	%s	%s	%s\n", photoID, photo->fields[2].string, photo->fields[7].string, photo->fields[30].string);
			 for(field_type=1; field_type <= 59; field_type++) 
			 {
				 flickcurl_field_value_type datatype=photo->fields[field_type].type;
				 
				 if(datatype == VALUE_TYPE_NONE)
                     fprintf(fp[loc_accu], " %s %s %s", prefix[field_type], "NULL", suffix[field_type]);
				 else
					 fprintf(fp[loc_accu], " %s %s %s",  prefix[field_type], photo->fields[field_type].string, suffix[field_type]);
			 }
			 /*  url info */  
			 fprintf(fp[loc_accu], " %s http://farm%s.static.flickr.com/%s/%s_%s_s.jpg %s",
				 prefix[field_type],
				 photo->fields[2].string, photo->fields[7].string, 
				 photoID, photo->fields[30].string,
				 suffix[field_type]);
			 
			 fprintf(fp[loc_accu], " %s http://farm%s.static.flickr.com/%s/%s_%s_t.jpg %s",
                 prefix[field_type+1],
				 photo->fields[2].string, photo->fields[7].string, 
                 photoID, photo->fields[30].string,
				 suffix[field_type+1]);
			 
			 fprintf(fp[loc_accu], " %s http://farm%s.static.flickr.com/%s/%s_%s_m.jpg %s",
				 prefix[field_type+2],
                 photo->fields[2].string, photo->fields[7].string, 
                 photoID, photo->fields[30].string,
				 suffix[field_type+2]);

			 fprintf(fp[loc_accu], " %s http://farm%s.static.flickr.com/%s/%s_%s.jpg %s",
				 prefix[field_type+3],
                 photo->fields[2].string, photo->fields[7].string, 
                 photoID, photo->fields[30].string,
				 suffix[field_type+3]);
			 
			 fprintf(fp[loc_accu], " %s http://farm%s.static.flickr.com/%s/%s_%s_z.jpg %s",
                 prefix[field_type+4],
				 photo->fields[2].string, photo->fields[7].string, 
                 photoID, photo->fields[30].string,
				 suffix[field_type+4]);
			 
			 fprintf(fp[loc_accu], " %s http://farm%s.static.flickr.com/%s/%s_%s_b.jpg %s",
				 prefix[field_type+5],
                 photo->fields[2].string, photo->fields[7].string, 
                 photoID, photo->fields[30].string,
				 suffix[field_type+5]);
			 
			 fprintf(fp[loc_accu], " %s http://farm%s.static.flickr.com/%s/%s_%s_o.%s %s",
				 prefix[field_type+6],
                 photo->fields[2].string, photo->fields[7].string, 
                 photoID, photo->fields[30].string, photo->fields[5].string,
				 suffix[field_type+6]);

			 fprintf(fp[loc_accu], " %s", prefix[field_type+7]);
			 
			 for(j=0; j < photo->tags_count; j++) 
			 {
				 flickcurl_tag* tag=photo->tags[j];
                 fprintf(fp[loc_accu]," %s", tag->raw);
			 }

			 if(photo->tags_count == 0) fprintf(fp[loc_accu], " %s", "NULL");

			 fprintf(fp[loc_accu], " %s", suffix[field_type+7]);
		 }
		 fprintf(fp[loc_accu], "\n");
	}
	
	if(photo)
	{
		flickcurl_free_photo(photo);
        photo=NULL;
    }
	
	flickcurl_free(fc);
    flickcurl_finish(); /* optional static free of resources */
}

for(i=0;i<17;i++)
{
	fclose(fp[i]);
	fclose(fp_GetIm[i]);
}

fclose(fp_ID);
return 0;
}
