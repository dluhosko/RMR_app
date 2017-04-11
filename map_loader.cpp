#include "map_loader.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

map_loader::map_loader()
{
}

 void map_loader::load_map(char *filename,TMapArea &mapss)
 {

 //    mapss.wall.numofpoints


     FILE *fp=fopen(filename,"r");
     if (fp==NULL)
     {

         printf("zly file\n");
         return ;
     }

     //tu nacitame obvodovu stenu
     char myLine[550];
     fgets(myLine,550,fp);
     printf("%s\n",myLine);
     char *myCopy=(char*)calloc(strlen(myLine)+2,sizeof(char));
     memcpy(myCopy,myLine,sizeof(char)*strlen(myLine));
     char *freeMyCopy;
     freeMyCopy=myCopy;
     myCopy=strtok(myCopy,"[]");
     mapss.wall.numofpoints=(atoi(myCopy));
      printf("num of points %i\n",mapss.wall.numofpoints);
      mapss.wall.points=(TMapPoint*)calloc(mapss.wall.numofpoints,sizeof(TMapPoint));
      for(int i=0;i<mapss.wall.numofpoints*2;i++)
      {
          myCopy=strtok(NULL,"[,");

          mapss.wall.points[i/2].suradnice[i%2]=atof(myCopy);

      }
      free(freeMyCopy);
      for(int i=0;i<mapss.wall.numofpoints;i++)
      {
           printf("suradnica steny %i %f %f\n",i, mapss.wall.points[i].suradnice[0],mapss.wall.points[i].suradnice[1]);
      }
      //tu nacitame jednotlive prekazky
       mapss.numofObjects=0;
        mapss.obstacle=NULL;
      while( fgets(myLine,550,fp))
      {
          printf("%s\n",myLine);
          myCopy=(char*)calloc(strlen(myLine)+2,sizeof(char));
          memcpy(myCopy,myLine,sizeof(char)*strlen(myLine));

          freeMyCopy=myCopy;
          myCopy=strtok(myCopy,"[]");
          if((atoi(myCopy))==0)
              break;
          mapss.numofObjects++;
          mapss.obstacle=(TMapObject*)realloc( mapss.obstacle,sizeof(TMapObject)*mapss.numofObjects);
          mapss.obstacle[mapss.numofObjects-1].numofpoints=(atoi(myCopy));
           printf("num of points %i\n", mapss.obstacle[mapss.numofObjects-1].numofpoints);
            mapss.obstacle[mapss.numofObjects-1].points=(TMapPoint*)calloc( mapss.obstacle[mapss.numofObjects-1].numofpoints,sizeof(TMapPoint));
           for(int i=0;i< mapss.obstacle[mapss.numofObjects-1].numofpoints*2;i++)
           {
               myCopy=strtok(NULL,"[,");

                mapss.obstacle[mapss.numofObjects-1].points[i/2].suradnice[i%2]=atof(myCopy);

           }
           free(freeMyCopy);
           for(int i=0;i< mapss.obstacle[mapss.numofObjects-1].numofpoints;i++)
           {
                printf("suradnica prekazok %i %f %f\n",i,  mapss.obstacle[mapss.numofObjects-1].points[i].suradnice[0], mapss.obstacle[mapss.numofObjects-1].points[i].suradnice[1]);
           }


      }
   //  free(freeMyCopy);

 }
