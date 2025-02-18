#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// max lines greather then that of the file
#define MAX_LINES 211
// line char array must be defined to be of length greater then the longest line
#define MAX_LENGTH 211

int main(void) {
  char userfilename[100];
  char filename[] = "statscan_diabetes.csv";


  // user enters input for file name
  printf("Please enter the filename you would like to read: ");
  scanf("%s", filename);

  FILE *input_file = fopen(filename, "r"), *output_file;

  
  if (input_file == NULL)
    printf("Cannot open file %s \n", filename);

    
  // file is opened for reading
  printf("file %s succesfully opened\n", filename);
  printf("\n");
  printf("please wait a moment for file to be read..\n");
  

  // arrays for storing csv file information
  int infoYear[MAX_LINES];
  char infoLocation[MAX_LINES][MAX_LENGTH];
  char infoAgeGroup[MAX_LINES][MAX_LENGTH];
  char infoSex[MAX_LINES][MAX_LENGTH];
  double infoValue[MAX_LINES];
  int numLines = 0;

  // start counting vars with impossible values
  int canadaStart = -1, quebecStart = -1, ontarioStart = -1, albertaStart = -1,
      bcStart = -1, canadaEnd = -1, quebecEnd = -1, ontarioEnd = -1,
      albertaEnd = -1, bcEnd = -1;

  // buffer array to keep information temporarily
  char bufferLine[MAX_LENGTH];
  int i = 0;

  // skip header line
  fgets(bufferLine, sizeof(bufferLine), input_file);

  // parse each line of the file
  while (fgets(bufferLine, sizeof(bufferLine), input_file) != NULL && i < MAX_LINES) {

    // token var created, field var tracks columns
    char *token;
    int field_count = 0;

    // token creates comma delimeter
    token = strtok(bufferLine, ",");

    // extracting only relavant columns into code
    while (token != NULL && field_count < 14) {
      if (field_count == 0) {
        sscanf(token, "\"%d\"", &infoYear[i]);
      } else if (field_count == 1) {
        sscanf(token, "\"%[^\"]\"", infoLocation[i]);

        // counts and collects information relating to Canada
        if (strcmp(infoLocation[i], "Canada (excluding territories)") == 0) {
          if (canadaStart == -1) {
            canadaStart = i;
          }
          canadaEnd = i;
          // counts and collects information relating to Quebec
        } else if (strcmp(infoLocation[i], "Quebec") == 0) {
          if (quebecStart == -1) {
            quebecStart = i;
          }
          quebecEnd = i;

          // counts and collects information relating to Ontario
        } else if (strcmp(infoLocation[i], "Ontario") == 0) {
          if (ontarioStart == -1) {
            ontarioStart = i;
          }
          ontarioEnd = i;

          // counts and collects information relating to Alberta
        } else if (strcmp(infoLocation[i], "Alberta") == 0) {
          if (albertaStart == -1) {
            albertaStart = i;
          }
          albertaEnd = i;
      
          // counts and collects information relating to BC
        } else if (strcmp(infoLocation[i], "British Columbia") == 0) {
          if (bcStart == -1) {
            bcStart = i;
          }
          bcEnd = i;
        }

        // collects information relating to age group
      } else if (field_count == 3) {
        sscanf(token, "\"%[^\"]\"", infoAgeGroup[i]);
        // collects information relating to sex
      } else if (field_count == 4) {
        sscanf(token, "\"%[^\"]\"", infoSex[i]);
        // collects information relating to values
      } else if (field_count == 13) {
        sscanf(token, "\"%lf\"", &infoValue[i]);
      }

      // token creates the comma as a delimeter getting rid of it
      token = strtok(NULL, ",");

      // moves to next colTBD or row?
      field_count++;
    }

    // moves to next rowTBD or col?
    i++;
  }

  numLines = i;

  printf("...the file has been read succesfully!\n");
  printf("\n");
  printf(" Calculations:\n ");
  printf("-------------\n\n");

  //------------------------Question 1a-----------------------------------------------------
  printf("\033[0;34m");
  printf("Question 1a) \n");
  printf("\033[0m");

  //double and count vars are intialized
  double sum1 = 0;
  int count1 = 0;

  //for loop traverses through location arr looking for quebec values and sums them
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "Quebec")) {
      sum1 = sum1 + infoValue[i];
      count1++;
    }
  }

  //Quebec values are averaged using count and sum vars and then printed
  double avg1 = sum1 / count1;
  printf("\n Average for Quebec is %.2lf", avg1);


  //double and count vars are intialized
  double sum2 = 0;
  int count2 = 0;

  //for loop traverses through location arr looking for Ontario values and sums them
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "Ontario")) {
      sum2 = sum2 + infoValue[i];
      count2++;
    }
  }

  //Ontario values are averaged using count and sum vars and then printed
  double avg2 = sum2 / count2;
  printf("\n Average for Ontario is %.2lf", avg2);


  //double and count vars are initialized
  double sum3 = 0;
  int count3 = 0;

  //for loop traverses through location arr looking for Alberta values and sums them
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "Alberta")) {
      sum3 = sum3 + infoValue[i];
      count3++;
    }
  }

  //Alberta values are averaged using count and sum vars and then printed
  double avg3 = sum3 / count3;
  printf("\n Average for Alberta is %.2lf", avg3);

  //double and count vars are initialized
  double sum4 = 0;
  int count4 = 0;

  //for loop traverses through location arr looking for BC values and sums them
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "British Columbia")) {
      sum4 = sum4 + infoValue[i];
      count4++;
    }
  }

  //BC values are averaged using count and sum vars and then printed
  double avg4 = sum4 / count4;
  printf("\n Average for British Columbia is %.2lf", avg4);

  //-----------------------------------Question 1b--------------------------------------------
  //color coding header blue
  printf("\n");
  printf("\033[0;34m");
  printf("\n Question 1b) \n");
  printf("\033[0m");

  //initializing sum and increment values
  double sum5 = 0;
  int count5 = 0;

  //for loop traverses through location arr and sums all values and increments count var
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "Canada (excluding territories)")) {
      sum5 = sum5 + infoValue[i];
      count5++;
    }
  }

  //avg var is initialized and printed 
  double avg5 = sum5 / count5;
  printf("\n Average for Canada (excluding territories) is %.2lf", avg5);

  

  //----------------------------------Question 1c----------------------------------------------
  
  //color coding header blue
  printf("\033[0;34m");
  printf("\n\nQuestion 1c) ");
  printf("\033[0m");

  //sum and count var are initialized
  double sum6 = 0;
  int count6 = 0;
  //for loop traverses through location array for Quebec values. If statement inside searches for 2015 values, summing and counting incrementation
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "Quebec")) {
      if (infoYear[i] == 2015) {
        sum6 = sum6 + infoValue[i];
        count6++;
      }
    }
  }

  //2015 specfic Quebec values are stored in avg var and then printed
  double avg6 = sum6 / count6;
  printf("\n \n 2015 Quebec Diabetes Average: %.2lf", avg6);

  
  //sum and count var are initialized  
  double sum7 = 0;
  int count7 = 0;

  //for loop traverses through location array for Quebec values. If statement inside searches for 2016 values, summing and counting incrementation
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "Quebec")) {
      if (infoYear[i] == 2016) {
        sum7 = sum7 + infoValue[i];
        count7++;
      }
    }
  }

  //2016 specfic Quebec values are stored in avg var and then printed
  double avg7 = sum7 / count7;
  printf("\n 2016 Quebec Diabetes Average: %.2lf", avg7);


  //sum and count var are initialized
  double sum8 = 0;
  int count8 = 0;

  //for loop traverses through location array for Quebec values. If statement inside searches for 2017 values, summing and counting incrementation
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "Quebec")) {
      if (infoYear[i] == 2017) {
        sum8 = sum8 + infoValue[i];
        count8++;
      }
    }
  }

  //2017 specfic Quebec values are stored in avg var and then printed
  double avg8 = sum8 / count8;
  printf("\n 2017 Quebec Diabetes Average: %.2lf", avg8);

  //sum and count var are initialized
  double sum181 = 0;
  int count181 = 0;

  //for loop traverses through location array for Quebec values. If statement inside searches for 2018 values, summing and counting incrementation
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "Quebec")) {
      if (infoYear[i] == 2018) {
        sum181 = sum181 + infoValue[i];
        count181++;
      }
    }
  }

  //2018 specfic Quebec values are stored in avg var and then printed
  double avg181 = sum181 / count181;
  printf("\n 2018 Quebec Diabetes Average: %.2lf", avg181);


  //sum and count var are initialized
  double sum9 = 0;
  int count9 = 0;

  //for loop traverses through location array for Quebec values. If statement inside searches for 2019 values, summing and counting incrementation
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "Quebec")) {
      if (infoYear[i] == 2019) {
        sum9 = sum9 + infoValue[i];
        count9++;
      }
    }
  }

  //2019 specfic Quebec values are stored in avg var and then printed
  double avg9 = sum9 / count9;
  printf("\n 2019 Quebec Diabetes Average: %.2lf", avg9);

  //sum and count var are initialized
  double sum10 = 0;
  int count10 = 0;

  //for loop traverses through location array for Quebec values. If statement inside searches for 2020 values, summing and counting incrementation
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "Quebec")) {
      if (infoYear[i] == 2020) {
        sum10 = sum10 + infoValue[i];
        count10++;
      }
    }
  }

  //2021 specfic Quebec values are stored in avg var and then printed
  double avg10 = sum10 / count10;
  printf("\n 2020 Quebec Diabetes Average: %.2lf", avg10);


  //sum and count var are initialized
  double sum11 = 0;
  int count11 = 0;
  
  //for loop traverses through location array for Quebec values. If statement inside searches for 2021 values, summing and counting incrementation
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "Quebec")) {
      if (infoYear[i] == 2021) {
        sum11 = sum11 + infoValue[i];
        count11++;
      }
    }
  }

  //2021 specfic Quebec values are stored in avg var and then printed
  double avg11 = sum11 / count11;
  printf("\n 2021 Quebec Diabetes Average: %.2lf \n\n", avg11);


  //the same format is done for Ontario, Alberta, BC and Canada
  double sum12 = 0;
  int count12 = 0;
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "Ontario")) {
      if (infoYear[i] == 2015) {
        sum12 = sum12 + infoValue[i];
        count12++;
      }
    }
  }
  double avg12 = sum12 / count12;

  printf("2015 Ontario Diabetes Average: %.2lf", avg12);

  double sum13 = 0;
  int count13 = 0;
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "Ontario")) {
      if (infoYear[i] == 2016) {
        sum13 = sum13 + infoValue[i];
        count13++;
      }
    }
  }
  double avg13 = sum13 / count13;
  printf("\n 2016 Ontario Diabetes Average: %.2lf", avg13);

  double sum14 = 0;
  int count14 = 0;
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "Ontario")) {
      if (infoYear[i] == 2017) {
        sum14 = sum14 + infoValue[i];
        count14++;
      }
    }
  }
  double avg14 = sum14 / count14;
  printf("\n 2017 Ontario Diabetes Average: %.2lf", avg14);

  double sum182 = 0;
  int count182 = 0;
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "Ontario")) {
      if (infoYear[i] == 2018) {
        sum182 = sum182 + infoValue[i];
        count182++;
      }
    }
  }
  double avg182 = sum182 / count182;
  printf("\n 2018 Ontario Diabetes Average: %.2lf", avg8);

  double sum15 = 0;
  int count15 = 0;
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "Ontario")) {
      if (infoYear[i] == 2019) {
        sum15 = sum15 + infoValue[i];
        count15++;
      }
    }
  }
  double avg15 = sum15 / count15;
  printf("\n 2019 Ontario Diabetes Average: %.2lf", avg15);

  double sum16 = 0;
  int count16 = 0;
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "Ontario")) {
      if (infoYear[i] == 2020) {
        sum16 = sum16 + infoValue[i];
        count16++;
      }
    }
  }
  double avg16 = sum16 / count16;
  printf("\n 2020 Ontario Diabetes Average: %.2lf", avg16);

  double sum17 = 0;
  int count17 = 0;
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "Ontario")) {
      if (infoYear[i] == 2021) {
        sum17 = sum17 + infoValue[i];
        count17++;
      }
    }
  }
  double avg17 = sum17 / count17;
  printf("\n 2021 Ontario Diabetes Average: %.2lf", avg17);

  double sum18 = 0;
  int count18 = 0;
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "Alberta")) {
      if (infoYear[i] == 2015) {
        sum18 = sum18 + infoValue[i];
        count18++;
      }
    }
  }
  double avg18 = sum18 / count18;
  printf("\n \n Average for Alberta for 2015  is %.2lf", avg18);

  double sum19 = 0;
  int count19 = 0;
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "Alberta")) {
      if (infoYear[i] == 2016) {
        sum19 = sum19 + infoValue[i];
        count19++;
      }
    }
  }
  double avg19 = sum19 / count19;
  printf("\n Average for Alberta for 2016  is %.2lf", avg19);

  double sum20 = 0;
  int count20 = 0;
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "Alberta")) {
      if (infoYear[i] == 2017) {
        sum20 = sum20 + infoValue[i];
        count20++;
      }
    }
  }
  double avg20 = sum20 / count20;
  printf("\n Average for Alberta for 2017  is %.2lf", avg20);

  double sum183 = 0;
  int count183 = 0;
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "Alberta")) {
      if (infoYear[i] == 2018) {
        sum183 = sum183 + infoValue[i];
        count183++;
      }
    }
  }
  double avg183 = sum183 / count183;
  printf("\n Average for Alberta for 2018  is %.2lf", avg183);
  
  double sum21 = 0;
  int count21 = 0;
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "Alberta")) {
      if (infoYear[i] == 2019) {
        sum21 = sum21 + infoValue[i];
        count21++;
      }
    }
  }
  double avg21 = sum21 / count21;
  printf("\n Average for Alberta for 2019  is %.2lf", avg21);

  double sum22 = 0;
  int count22 = 0;
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "Alberta")) {
      if (infoYear[i] == 2020) {
        sum22 = sum22 + infoValue[i];
        count22++;
      }
    }
  }
  double avg22 = sum22 / count22;
  printf("\n Average for Alberta for 2020  is %.2lf", avg22);

  double sum23 = 0;
  int count23 = 0;
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "Alberta")) {
      if (infoYear[i] == 2021) {
        sum23 = sum23 + infoValue[i];
        count23++;
      }
    }
  }
  double avg23 = sum23 / count23;
  printf("\n Average for Alberta for 2021  is %.2lf", avg23);

  double sum24 = 0;
  int count24 = 0;
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "British Columbia")) {
      if (infoYear[i] == 2015) {
        sum24 = sum24 + infoValue[i];
        count24++;
      }
    }
  }
  double avg24 = sum24 / count24;
  printf("\n \n Average for British Columbia for 2015  is %.2lf", avg24);

  double sum25 = 0;
  int count25 = 0;
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "British Columbia")) {
      if (infoYear[i] == 2016) {
        sum25 = sum25 + infoValue[i];
        count25++;
      }
    }
  }
  double avg25 = sum25 / count25;
  printf("\n Average for British Columbia for 2016  is %.2lf", avg25);

  double sum26 = 0;
  int count26 = 0;
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "British Columbia")) {
      if (infoYear[i] == 2017) {
        sum26 = sum26 + infoValue[i];
        count26++;
      }
    }
  }
  double avg26 = sum26 / count26;
  printf("\n Average for British Columbia for 2017  is %.2lf", avg26);

  
  double sum184 = 0;
  int count184 = 0;
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "British Columbia")) {
      if (infoYear[i] == 2018) {
        sum184 = sum184 + infoValue[i];
        count184++;
      }
    }
  }
  double avg184 = sum184 / count184;
  printf("\n Average for British Columbia for 2018  is %.2lf", avg184);

  double sum27 = 0;
  int count27 = 0;
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "British Columbia")) {
      if (infoYear[i] == 2019) {
        sum27 = sum27 + infoValue[i];
        count27++;
      }
    }
  }
  double avg27 = sum27 / count27;
  printf("\n Average for British Columbia for 2019  is %.2lf", avg27);

  double sum28 = 0;
  int count28 = 0;
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "British Columbia")) {
      if (infoYear[i] == 2020) {
        sum28 = sum28 + infoValue[i];
        count28++;
      }
    }
  }
  double avg28 = sum28 / count28;
  printf("\n Average for British Columbia for 2020  is %.2lf", avg28);

  double sum29 = 0;
  int count29 = 0;
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "British Columbia")) {
      if (infoYear[i] == 2021) {
        sum29 = sum29 + infoValue[i];
        count29++;
      }
    }
  }
  double avg29 = sum29 / count29;
  printf("\n Average for British Columbia for 2021  is %.2lf", avg29);

  double sum30 = 0;
  int count30 = 0;
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "Canada (excluding territories)")) {
      if (infoYear[i] == 2015) {
        sum30 = sum30 + infoValue[i];
        count30++;
      }
    }
  }
  double avg30 = sum30 / count30;
  printf("\n \n Average for Canada (excluding territories) for 2015  is %.2lf",
         avg30);

  double sum31 = 0;
  int count31 = 0;
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "Canada (excluding territories)")) {
      if (infoYear[i] == 2016) {
        sum31 = sum31 + infoValue[i];
        count31++;
      }
    }
  }
  double avg31 = sum31 / count31;
  printf("\n Average for Canada (excluding territories) for 2016  is %.2lf",
         avg31);

  double sum32 = 0;
  int count32 = 0;
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "Canada (excluding territories)")) {
      if (infoYear[i] == 2017) {
        sum32 = sum32 + infoValue[i];
        count32++;
      }
    }
  }
  double avg32 = sum32 / count32;
  printf("\n Average for Canada (excluding territories) for 2017  is %.2lf",
         avg32);

  double sum185 = 0;
  int count185 = 0;
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "Canada (excluding territories)")) {
      if (infoYear[i] == 2018) {
        sum185 = sum185 + infoValue[i];
        count185++;
      }
    }
  }
  double avg185 = sum185 / count185;
  printf("\n Average for Canada (excluding territories) for 2018  is %.2lf", avg185);

  double sum33 = 0;
  int count33 = 0;
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "Canada (excluding territories)")) {
      if (infoYear[i] == 2019) {
        sum33 = sum33 + infoValue[i];
        count33++;
      }
    }
  }
  double avg33 = sum33 / count33;
  printf("\n Average for Canada (excluding territories) for 2019  is %.2lf",
         avg33);

  double sum34 = 0;
  int count34 = 0;
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "Canada (excluding territories)")) {
      if (infoYear[i] == 2020) {
        sum34 = sum34 + infoValue[i];
        count34++;
      }
    }
  }
  double avg34 = sum34 / count34;
  printf("\n Average for Canada (excluding territories) for 2020  is %.2lf",
         avg34);

  double sum35 = 0;
  int count35 = 0;
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "Canada (excluding territories)")) {
      if (infoYear[i] == 2021) {
        sum35 = sum35 + infoValue[i];
        count35++;
      }
    }
  }
  double avg35 = sum35 / count35;
  printf("\n Average for Canada (excluding territories) for 2021  is %.2lf \n",
          avg35);
  double avgqueb;
  printf("\n");

  //----------------------------------question 1d---------------------------------------------

  //chanigng color for header
  printf("\033[0;34m");
  printf("\n\nQuestion 1d).");
  printf("\033[0m");
  printf("\n");

  //counting and sum vars initiated
  double count = 0;
  double sum = 0;

  //for loop calls ontario start and end vars to count and regulate values. for checks age for desired age group, and then sums the values from value array corresponding to age list with sum and count vars.
  for (int j = ontarioStart; j <= ontarioEnd; j++) {
    if (strcmp(infoAgeGroup[j], "35 to 49 years") == 0) {
      if (infoValue[j] != 0) {
        sum += infoValue[j];
        count++;
      }
    }
  }

  //output vars use sum and count vars to create average and print it
  double output =  sum / count;
  printf("  Diabetes average for Ontario (35-49 years): %.2lf\n",output);


  //same concept done to every province for each age group, 35-49, 50-64, 65+

  
  count = 0;
  sum = 0;
  for (int j = ontarioStart; j <= ontarioEnd; j++) {
    if (strcmp(infoAgeGroup[j], "50 to 64 years") == 0) {
      if (infoValue[j] != 0) {
        sum += infoValue[j];
        count++;
      }
    }
  }
  output = 0;
  output = sum / count;
  printf("  Diabetes average for Ontario (50-64 years): %.2lf\n", output);

  count = 0;
  sum = 0;
  for (int j = ontarioStart; j <= ontarioEnd; j++) {
    if (strcmp(infoAgeGroup[j], "65 years and over") == 0) {
      if (infoValue[j] != 0) {
        sum += infoValue[j];
        count++;
      }
    }
  }
  output = 0;
  output = sum / count;
  printf("  Diabetes average for Ontario (65+ years): %.2lf\n", output);

  printf("\n");

  count = 0;
  sum = 0;
  for (int j = canadaStart; j <= canadaEnd; j++) {
    if (strcmp(infoAgeGroup[j], "35 to 49 years") == 0) {
      if (infoValue[j] != 0) {
        sum += infoValue[j];
        count++;
      }
    }
  }
  output = 0;
  output = sum / count;
  printf("  Diabetes average for Canada (35-49 years): %.2lf\n", output);

  count = 0;
  sum = 0;
  for (int j = canadaStart; j <= canadaEnd; j++) {
    if (strcmp(infoAgeGroup[j], "50 to 64 years") == 0) {
      if (infoValue[j] != 0) {
        sum += infoValue[j];
        count++;
      }
    }
  }
  output = 0;
  output = sum / count;
  printf("  Diabetes average for Canada (50-64 years): %.2lf\n", output);

  count = 0;
  sum = 0;
  for (int j = canadaStart; j <= canadaEnd; j++) {
    if (strcmp(infoAgeGroup[j], "65 years and over") == 0) {
      if (infoValue[j] != 0) {
        sum += infoValue[j];
        count++;
      }
    }
  }

  output = 0;
  output = sum / count;
  printf("  Diabetes average for Canada (65+ years): %.2lf\n", output);

  printf("\n");

  count = 0;
  sum = 0;
  for (int j = quebecStart; j <= quebecEnd; j++) {
    if (strcmp(infoAgeGroup[j], "35 to 49 years") == 0) {
      if (infoValue[j] != 0) {
        sum += infoValue[j];
        count++;
      }
    }
  }

  output = 0;
  output = sum / count;
  printf("  Diabetes average for Quebec (35-49 years): %.2lf\n", output);

  count = 0;
  sum = 0;
  for (int j = quebecStart; j <= quebecEnd; j++) {
    if (strcmp(infoAgeGroup[j], "50 to 64 years") == 0) {
      if (infoValue[j] != 0) {
        sum += infoValue[j];
        count++;
      }
    }
  }

  output = 0;
  output = sum / count;
  printf("  Diabetes average for Quebec (50-64 years): %.2lf\n", output);

  count = 0;
  sum = 0;
  for (int j = quebecStart; j <= quebecEnd; j++) {
    if (strcmp(infoAgeGroup[j], "65 years and over") == 0) {
      if (infoValue[j] != 0) {
        sum += infoValue[j];
        count++;
      }
    }
  }

  output = 0;
  output = sum / count;
  printf("  Diabetes average for Quebec (65+ years): %.2lf\n", output);

  printf("\n");

  count = 0;
  sum = 0;
  for (int j = albertaStart; j <= albertaEnd; j++) {
    if (strcmp(infoAgeGroup[j], "35 to 49 years") == 0) {
      if (infoValue[j] != 0) {
        sum += infoValue[j];
        count++;
      }
    }
  }

  output = 0;
  output = sum / count;
  printf("  Diabetes average for Alberta (35-49 years): %.2lf\n", output);

  count = 0;
  sum = 0;
  for (int j = albertaStart; j <= albertaEnd; j++) {
    if (strcmp(infoAgeGroup[j], "50 to 64 years") == 0) {
      if (infoValue[j] != 0) {
        sum += infoValue[j];
        count++;
      }
    }
  }

  output = 0;
  output = sum / count;
  printf("  Diabetes average for Alberta (50-64 years): %.2lf\n", output);

  count = 0;
  sum = 0;
  for (int j = albertaStart; j <= albertaEnd; j++) {
    if (strcmp(infoAgeGroup[j], "65 years and over") == 0) {
      if (infoValue[j] != 0) {
        sum += infoValue[j];
        count++;
      }
    }
  }
  output = sum / count;
  printf("  Diabetes average for Alberta (65+ years): %.2lf\n", output = 0);

  printf("\n");

  count = 0;
  sum = 0;
  for (int j = bcStart; j <= bcEnd; j++) {
    if (strcmp(infoAgeGroup[j], "35 to 49 years") == 0) {
      if (infoValue[j] != 0) {
        sum += infoValue[j];
        count++;
      }
    }
  }

  output = 0;
  output = sum / count;
  printf("  Diabetes average for British Columbia (35-49 years): %.2lf\n", output);

  count = 0;
  sum = 0;
  for (int j = bcStart; j <= bcEnd; j++) {
    if (strcmp(infoAgeGroup[j], "50 to 64 years") == 0) {
      if (infoValue[j] != 0) {
        sum += infoValue[j];
        count++;
      }
    }
  }

  output = 0;
  output = sum / count;
  printf("  Diabetes average for British Columbia (50-64 years): %.2lf\n", output);

  count = 0;
  sum = 0;
  for (int j = bcStart; j <= bcEnd; j++) {
    if (strcmp(infoAgeGroup[j], "65 years and over") == 0) {
      if (infoValue[j] != 0) {
        sum += infoValue[j];
        count++;
      }
    }
  }
  output = sum / count;
  printf("  Diabetes average for British Columbia (65+ years): %.2lf\n", output);

  //-------------------------------------Question 2------------------------------------------

  //prints header blue 
  printf("\033[0;34m");
  printf("\nQuestion 2).\n");
  printf("\033[0m");

  //print statements help remind user of relavent but already calculated information 
  printf("\n The percent average for Quebec for all infoYears and age is %.2lf\n",
         avg1);


  printf(
      "\n The percent average for Ontario for all infoYears and age is %.2lf\n",
      avg2);

  
  printf( "\n The percent average for Alberta for all infoYears and age is %.2lf\n",avg3);

  
  printf("\n The percent average for British Columbia for all infoYears and "
         "age is %.2lf\n",
         avg4);

  //if statements compare average values of all provinces to reach conclusion
  if (avg4 < avg3 && avg4 < avg2 && avg4 < avg1)
    printf("\nThe province which has the lowest percentage of diabetes (all "
           "infoYears and age groups together) is British Columbia\n");

  if (avg3 < avg4 && avg3 < avg2 && avg3 < avg1)
    printf("\nThe province which has the lowest percentage of diabetes (all "
           "infoYears and age groups together) is Alberta\n");

  if (avg2 < avg3 && avg2 < avg4 && avg2 < avg1)
    printf("\nThe province which has the lowest percentage of diabetes (all "
           "infoYears and age groups together) is Ontario\n");

  if (avg1 < avg3 && avg1 < avg2 && avg1 < avg4)
    printf("\nThe province which has the lowest percentage of diabetes (all "
           "infoYears and age groups together) is Quebec\n");

  if (avg4 > avg3 && avg4 > avg2 && avg4 > avg1)
    printf("\nThe province which has the Highest percentage of diabetes (all "
           "infoYears and age groups together) is British Columbia\n");

  if (avg3 > avg4 && avg3 > avg2 && avg3 > avg1)
    printf("\nThe province which has the Highest percentage of diabetes (all "
           "infoYears and age groups together) is Alberta\n");

  if (avg2 > avg3 && avg2 > avg4 && avg2 > avg3)
    printf("\nThe province which has the Highest percentage of diabetes (all "
           "infoYears and age groups together) is Ontario\n");

  if (avg3 > avg3 && avg3 > avg2 && avg3 > avg4)
    printf("\nThe province which has the Highest percentage of diabetes (all "
           "infoYears and age groups together) is Quebec\n");

    //-----------------------------------question 3--------------------------------------------


  //changed header color to blue 
  printf("\033[0;34m");
  printf("\nQuestion 3).\n");
  printf("\033[0m");


  //print statement reminds user of relavent but already calculated information
  printf("\n The percent average for Canada (excluding territories) for all infoYears and age is %.2lf\n", avg5);
  
  double A,B;

printf("\n|    Above Average National Average |       Below Average National Average |");
printf("\n-----------------------------------------------------------------------------");

  //if statement compares averages of different provinces, and prints which are above and below national average 
if (avg5 < avg4){
  A = avg4;
  printf("\n British Columbia                    |");
}
  
if (avg5 < avg3){
  A = avg3;
  printf("\n|    Alberta                        |");
}
if (avg5 < avg2){
  A = avg2;
  printf("\n    Ontario                        ");
}
if (avg5 < avg1){
  A = avg1;
  printf("\n   Quebec                        ");
}
if (avg5 > avg4){
  B = avg4;
  printf("\n                                          British Columbia   ");
}
  
if (avg5 > avg3){
  B = avg3;
  printf("\n                                             Alberta        ");
}
if (avg5 > avg1){
  B = avg1;
  printf("\n                                             Quebec\n        ");
}if (avg5 > avg2){
  B = avg2;
  printf("\n                                             Ontario        ");
}



//-----------------------------question 4-----------------------------------------------------

  printf("\033[0;34m");
  printf("\nQuestion 4\n");
  printf("\033[0m");

  
  float quebec[] = {avg6, avg7, avg8, avg9, avg10, avg11};
  float ontario[] = {avg12, avg13, avg14, avg15, avg16, avg17};
  float alberta[] = {avg18, avg19, avg20, avg21, avg22, avg23};
  float bc[] = {avg25, avg26, avg27, avg28, avg29, avg30};

  // initialize all variable
  int max_year;
  float max = 0.0; // starts at lowest value since we need the max
  char *max_province;

  for (int i = 0; i < 6; i++) { // loops array
    if (quebec[i] > max) { // will identify a new max for every value in array
      max = quebec[i];
      max_year = i + 2016; // Will tell us the year at which the max was found
      max_province = "Quebec";
    }
    if (ontario[i] > max) {
      max = ontario[i];
      max_year = i + 2016;
      max_province = "Ontario";
    }
    if (alberta[i] > max) {
      max = alberta[i];
      max_year = i + 2016;
      max_province = "Alberta";
    }
    if (bc[i] > max) {
      max = bc[i];
      max_year = i + 2016; // Will tell us the year at which the max was found
      max_province = "British Columbia";
    }
  }

  printf("\nThe highest percentage of diebetes is %f%%, in the year %d by %s.\n",
         max, max_year, max_province);

  int min_year;
  float min = 100.0; // set value of 100 since we are looing for the min
  char *min_province;

  for (int i = 0; i < 6; i++) { // loops array
    if (quebec[i] < min) { // will identify a new min for every value in array
      min = quebec[i];     // use the smallest
      min_year = i + 2017; // Will tell us the year at which the min was found
      min_province = "Quebec";
    }
    if (ontario[i] < min) {
      min = ontario[i];
      min_year = i + 2017; // Will tell us the year at which the min was found
      min_province = "Ontario";
    }
    if (alberta[i] < min) {
      min = alberta[i];
      min_year = i + 2017;
      min_province = "Alberta";
    }
    if (bc[i] < min) {
      min = bc[i];
      min_year = i + 2017; // Will tell us the year at which the min was found
      min_province = "British Columbia";
    }
  }

  printf("\nThe lowest percentage of diabetes is %f%%, in the year %d by %s.\n",
         min, min_year, min_province);

  // Code for the gnuplot starts from here
  FILE *out;
out = fopen ("Q5.data", "w");
    fprintf(out, "year  Quebec  Ontario  Alberta  British-Columbia Canada(excluding territories)\n");

    fprintf(out, "2015  %.2lf   %.2lf     0%.2lf      0%.2lf            %.2lf\n", avg6, avg12, avg18, avg24, avg30);

    fprintf(out, "2016  0%.2lf   %.2lf     0%.2lf      0%.2lf            %.2lf\n", avg7, avg13, avg19, avg25, avg31);

  fprintf(out, "2017  0%.2lf   %.2lf     %.2lf      0%.2lf            %.2lf\n", avg8, avg14, avg20, avg26, avg32);

  fprintf(out, "2018  %.2lf   %.2lf     %.2lf      0%.2lf            %.2lf\n", avg181, avg182, avg183, avg184,avg185);

  fprintf(out, "2019  %.2lf   %.2lf     %.2lf      0%.2lf            %.2lf\n", avg9, avg15, avg21, avg27, avg33);
  
  fprintf(out, "2020  0%.2lf   %.2lf     %.2lf      0%.2lf            %.2lf\n", avg10, avg16, avg22, avg28, avg34);

  fprintf(out, "2021  %.2lf   %.2lf     0%.2lf      0%.2lf            %.2lf", avg11, avg17, avg23, avg29, avg35);


  //calculations for q6 from below
    double sum36 = 0;
  int count36 = 0;
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "Canada (excluding territories)")) {
      if (!strcmp(infoAgeGroup[i], "35 to 49 years")) {
        sum36 = sum36 + infoValue[i];
        count36++;
      }
    }
  }
  double avg36 = sum36/ count36;
  
  
  double sum37 = 0;
  int count37 = 0;
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "Canada (excluding territories)")) {
      if (!strcmp(infoAgeGroup[i], "50 to 64 years")) {
        sum37 = sum37 + infoValue[i];
        count37++;
      }
    }
  }
  double avg37 = sum37/ count37;
 

  double sum38 = 0;
  int count38 = 0;
  for (int i = 0; i < 211; i++) {
    if (!strcmp(infoLocation[i], "Canada (excluding territories)")) {
      if (!strcmp(infoAgeGroup[i], "65 years and over")) {
        sum38 = sum38 + infoValue[i];
        count38++;
      }
    }
  }
  double avg38 = sum38/ count38;
 

  FILE *temp;

  temp = fopen ("Q6.data", "w");
  fprintf(temp, " 0 35-49                %.2lf\n", avg36);
  fprintf(temp, " 1 50-64                %.2lf\n", avg37);
  fprintf(temp, " 2 65+                  %.2lf\n", avg38);
     // 0, 1 and 2 here to make the script work in gnu plot
  
}