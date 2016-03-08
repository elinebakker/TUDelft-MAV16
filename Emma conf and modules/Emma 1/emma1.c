/*
 * Copyright (C) Matthias Baert
 *
 * This file is part of paparazzi
 *
 * paparazzi is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * paparazzi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with paparazzi; see the file COPYING.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
/**
 * @file "modules/emma1/emma1.c"
 * @author Matthias Baert
 * This is a first module for Emma
 */

#include "modules/emma1/emma1.h"
//#include "modules/orange_avoider/orange_avoider.h"
//#include "modules/computer_vision/colorfilter.h"
#include "firmwares/rotorcraft/navigation.h"
#include "state.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int count = 1;

void emma_init() {
	// initialize variables

}
void emmafunction() {

	// no idea
	//printf("it's working!!!!!");
}

uint8_t emma69(uint8_t waypoint) {
	float wp1_x = -2.;
	float wp1_y = -2.;
	float wp2_x = 2.;
	float wp2_y = 2.;
	float wp3_x = -2.;
	float wp3_y = 2.;
	float dist_threshold = 0.1;
	double wps[6] = {wp1_x, wp1_y, wp2_x, wp2_y, wp3_x, wp3_y};
	int i = 0;

	struct *pos = stateGetPositionEnu_i(); // Get your current position EnuCoor_i
	
	printf("Current pos \n");
        printf("posX= %f \n", pos->x);
        printf("posY= %f \n", pos->y);
       
	float wpX = waypoint_get_x(waypoint);
	float wpY = waypoint_get_y(waypoint);
        
	printf("Current wp \n");
        printf("wpX: %f \n", wpX);
        printf("wpY: %f \n", wpY);
	
	float dist_curr = (POS_BFP_OF_REAL(wpX) - pos->x)*(POS_BFP_OF_REAL(wpX) - pos->x) + (POS_BFP_OF_REAL(wpY) - pos->y)*(POS_BFP_OF_REAL(wpY) - pos->y);

	printf("Dist to current wp \n");	
        printf("dist_curr: %f \n", dist_curr);        

        float dist1 = (wpX - wp1_x)*(wpX - wp1_x) + (wpY - wp1_y)*(wpY - wp1_y); // Dist between current wp and navigation wps
	float dist2 = (wpX - wp2_x)*(wpX - wp2_x) + (wpY - wp2_y)*(wpY - wp2_y);
	float dist3 = (wpX - wp3_x)*(wpX - wp3_x) + (wpY - wp3_y)*(wpY - wp3_y);
	
	
	if (dist1 < dist2 && dist1 < dist3){i=1;} 
	else if (dist2 < dist1 && dist2 < dist3){i=2;}
	else {i=3;}

	if (dist_curr < dist_threshold*dist_threshold){
		i = i + 1;
		if (i> 3){i=1;}
	}

	// Set the waypoint to the calculated position
        printf("Set waypoint to \n");
	printf("wpsX: %f \n",wps[(i-1)*2]);
	printf("wpsY: %f \n",wps[(i-1)*2+1]);
	waypoint_set_xy_i(waypoint, wps[(i-1)*2], wps[(i-1)*2+1]);
        
	if (count < 2) {count = 2;}
	else {count = 1;}
        printf("Count: %d \n", count);

	return FALSE;

}


