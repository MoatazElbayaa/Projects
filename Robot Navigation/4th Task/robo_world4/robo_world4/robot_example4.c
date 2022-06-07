/*
Copyright 2021 for (robot_example4.c) Moataz Elbayaa (moataz.elbayaa@stud.hshl.de) or (moatazelbayaa9610@gmail.com)
*/
#include <stdio.h>
#include <string.h>
#include "robot_example4.h"


static int road[200],j=0,old_map_id=-1,emrg_n=0,e=0,emrg_E=0,emrg_S=0,emrg_W=0;
// Hardcoded to solve maps for testing
int move(char *world, int map_id) {


    if (old_map_id!=map_id)
    {
        old_map_id=map_id;
        j=0;
    }
    static int mode=0;
    static int obstacle_free_space=0;
    int dir = 1,y=0; // direction in which robot move
	unsigned int size = strlen(world);	// find length of world
	//printf("Size= %d\n",size);
	int target = 0, robot = 0, width = 0,t=0;
	//char mode='L'; //robot starts in “land mode”

	for (int i = 0; i < size; i++) // find width of world
	{
		if (world[i] == '\n') {
			width = i;
			//printf("width= %d\n",width);
			break;
		}
	}
	for (int i = 0; i < size; i++) { // find robot index
		if (world[i] == 'R') {
			robot = i;
			//printf("R= %d\n",i);
			break;
		}
	}



    for (int i = 0; i < size; i++) // find target index
        {
            if (world[i] == 'T'||world[i] == 't') {
            target = i;
            t=1;
            //printf("Target = %d\n",target);
            break;
        }
        }


    if(t==0)//return road
        {

        if(--j>=0)
            {
                dir=road[j];
                if(dir==1&&world[robot-21]=='~'&&mode==0)
                {
                    dir=5;
                    mode=1;
                    ++j;
                }
                else if(dir==3&&world[robot+21]=='~'&&mode==0)
                {
                    dir=5;
                    mode=1;
                    ++j;
                }
                else if(dir==2&&world[robot+1]=='~'&&mode==0)
                {
                    dir=5;
                    mode=1;
                    ++j;
                }
                else if(dir==4&&world[robot-1]=='~'&&mode==0)
                {
                    dir=5;
                    mode=1;
                    ++j;
                }
                if(dir==1&&world[robot-21]=='O'&&mode==1)
                {
                    dir=5;
                    mode=0;
                    ++j;
                }
                else if(dir==3&&world[robot+21]=='O'&&mode==1)
                {
                    dir=5;
                    mode=0;
                    ++j;
                }
                else if(dir==2&&world[robot+1]=='O'&&mode==1)
                {
                    dir=5;
                    mode=0;
                    ++j;
                }
                else if(dir==4&&world[robot-1]=='O'&&mode==1)
                {
                    dir=5;
                    mode=0;
                    ++j;
                }
                if(j==0)
                    mode=0;
                return dir;
            }
        }


    //Emergency North
    if(emrg_n==1&&robot>e)
    {
        if(world[robot-21]=='*')
            {

                dir=6;

            }
        else
        {
            dir=1;
        }

        if((robot+1)-21==e)
        {
            emrg_E=1;
            emrg_n=0;
            e=0;
        }

        goto Line;
    }

    Emergency_East:
    if(emrg_E==1)
    {
        if(world[robot+1]=='*')
            {
                dir=7;


            }
        else
        {
            dir=2;
            emrg_E=0;
        }

        goto Line;
    }

    //Emergency South
    if(emrg_S==1&&robot<e)
    {
        if(world[robot+21]=='*')
            {
                dir=8;

            }
        else
        {
            dir=3;
        }

        if((robot-1)+21==e)
        {
            emrg_W=1;
            emrg_S=0;
            e=0;
        }

        goto Line;
    }

   Emergency_Wast:
    if(emrg_W==1)
    {
        if(world[robot-1]=='*')
            {
                dir=9;

            }
        else
        {
            dir=4;
            emrg_W=0;
        }

        goto Line;
    }



	// NORTH
	if (robot/(width+1) - target/(width+1)>0)
    {
		if(world[robot-21]=='~'&&mode==0)
        {
            dir=5;
            mode=1;
        }

        else if(world[robot-21]=='O'&&mode==1)
        {
            dir=5;
            mode=0;
        }


        else if(world[robot-21]=='#')//new
        {
            if((robot%(width+1)<target%(width+1))&&world[robot-21+1]=='O')
            {
                emrg_E=1;
                goto Emergency_East;
            }


            int e=((robot-21)/width)*(width+1)+1;
            //printf("e = %d\n",e);
            for(int i=robot-21;i>e;--i)
            {
                if(world[i]=='O'||world[i]=='*')
                {
                    if(world[robot+1]=='O')
                        dir=4; //go to Wast
                    else if(world[robot+1]=='*')
                        dir=9;
                        break;
                }
                else if(world[i]=='#'&&world[robot-1]=='#'&&world[robot+1]=='#')
                {
                    dir=3;
                    emrg_W=1;
                }

            }



        }
        else if(world[robot-21]=='*')
        {
            if(world[robot-21-21]!='#'&&world[robot-21-1]!='#'&&world[robot-21+1]!='#')
            {
                dir =6;

            }
            else
            {
                emrg_W=1;
                goto Emergency_Wast;
            }
        }



	}



	// SOUTH
	else if (target/(width+1) - robot/(width+1)>0)
	{
		if(world[robot+21]=='~'&&mode==0)
        {
            dir=5;
            mode=1;
        }

        else if(world[robot+21]=='O'&&mode==1)
        {
            dir=5;
            mode=0;
        }

        else if(world[robot+21]=='#')//new
        {
            int e=((robot+21)/width)*(width+1)+1;
            for(int i=robot+21;i<e+21;++i)
            {
                if(world[i]=='O'||world[i]=='*')
                {
                    if(world[robot+1]=='O')
                        dir=2; //go to East
                    else if(world[robot+1]=='*')
                        dir=7;
                        break;
                }
            }
        }
        else if(world[robot+21]=='*')
        {
            dir=8;
        }

        else
            dir = 3;
	}
	// EAST
	else if (robot - target < 0)
	{
		if(world[robot+1]=='~'&&mode==0)
        {
            dir=5;
            mode=1;
        }

        else if(world[robot+1]=='O'&&mode==1)
        {
            dir=5;
            mode=0;
        }

        else if(world[robot+1]=='#')//new
        {
            for(int i=robot+1;i>width+1;i-=21)
            {

                if(world[i]=='O'||world[i]=='*')
                {
                    e=i;
                    //printf("e = %d\n",e);
                    if(world[robot-21]=='O')
                        {
                            dir=1; //go to North
                            emrg_n=1;
                            break;
                        }
                    else if(world[robot-21]=='*')
                        {
                            dir=6;
                            emrg_n=1;
                            break;
                        }

                }
            }
        }
        else if(world[robot+1]=='*')
        {
            dir =7;
        }

        else
            dir = 2;
	}
	// WEST
	else if (robot - target > 0)
	{
		if(world[robot-1]=='~'&&mode==0)
        {
            dir=5;
            mode=1;
        }

        else if(world[robot-1]=='O'&&mode==1)
        {
            dir=5;
            mode=0;
        }

        else if(world[robot-1]=='#')
        {

            for(int i=robot-1;i<size;i+=21)
            {

                if(world[i]=='O'||world[i]=='*')
                {
                    e=i;
                    //printf("e = %d\n",e);
                    if(world[robot+21]=='O')
                        {
                            dir=3; //go to South
                            emrg_S=1;
                            break;
                        }
                    else if(world[robot+21]=='*')
                        {
                            dir=8;
                            emrg_S=1;
                            break;
                        }

                }
            }
        }

        else if(world[robot-1]=='*')
        {
            dir =9;
        }

        else
            dir = 4;

	}
	if(dir==1&&(world[robot+1-21]=='*'||world[robot+1-21]=='O')&&robot%(width+1)<target%(width+1))
    {
        emrg_E=1;
    }

    Line:

    if(dir>0&&dir<5)
    {
        if(dir==1)
        {
            road[j]=3;
            j++;
        }
        else if(dir==2)
        {
            road[j]=4;
            j++;
        }
        else if(dir==3)
        {
            road[j]=1;
            j++;
        }
        else //then dir=4
        {
            road[j]=2;
            j++;
        }
    }


	return dir; // REPLACE THE RETURN VALUE WITH YOUR CALCULATED RETURN VALUE


}
