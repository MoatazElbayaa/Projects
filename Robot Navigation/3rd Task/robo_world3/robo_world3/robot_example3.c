//Copyright 2021 for (robot_example3.c) file Moataz Elbayaa (moataz.elbayaa@stud.hshl.de) or (moatazelbayaa9610@gmail.com)

#include <stdio.h>
#include <string.h>
#include "robot_example3.h"

// IMPLEMENT THIS FUNCTION
// ALLOWED RETURN VALUES:
// 1: North, 2: East, 3: South, 4: West, 5: Toggle watern/land mode
//int c = 0;

int move(char *world)
{
    /*c = c+1;
    if(c > 3) {
        return 3;
    } else {
        return 1;
    }*/

    static int mode=0;
    static int obstacle_free_space=0;
    int dir = 1; // direction in which robot move
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
            if (world[i] == 'T') {
            target = i;
            t=1;
            //printf("T= %d\n",target);
            break;
        }
        }
    if(t==0&&obstacle_free_space!=0)
    {
        target = obstacle_free_space;
        obstacle_free_space=0;
        t=1;
    }

    if(t==0)
        {
            for (int i = 0; i < size; i++)// find X index
        {
            if (world[i] == 'X')
            {
			target = i;
			t=0;
			//printf("X= %d\n",target);
			break;
            }
        }
        }



	int y=0;
	for (int i = 0; i < size; i++) { // find robot open vertical gab
		if (world[i]=='#'&&world[i+1]=='O'&&world[i+2]=='#')
		{
			y=i+1;
			//printf("y= %d\n",y);
			break;
		}
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
        else if(world[robot-21]=='#')
        {
            if(world[robot-1]!='#')
                dir=4; //go to West
        }
        else if(world[robot-21]=='*')
        {
            printf("obstacle= %d\n",robot-21);
            obstacle_free_space=robot-21;
            world[robot-21]='O';
            dir=1;
            if(mode==1)
                {
                    mode=0;
                    dir=5;
                }

        }




        else if(robot-21-y<18&&robot-21-y!=0)
            dir = 4;


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
        else if(world[robot+21]=='#')
        {
            if(world[robot+1]!='#')
                dir=2; //go to East
        }
        else if(world[robot+21]=='*')
        {
            printf("obstacle= %d\n",robot+21);
            obstacle_free_space=robot+21;
            world[robot+21]='O';
            dir=3;
            if(mode==1)
                {
                    mode=0;
                    dir=5;
                }

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
        else if(world[robot+1]=='#')
        {
            if(world[robot-21]!='#')
                dir=1; //go to north
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
            if(world[robot+21]!='#')
                dir=3; //go to south
        }

        else
            dir = 4;

	}

	return dir; // REPLACE THE RETURN VALUE WITH YOUR CALCULATED RETURN VALUE
}
