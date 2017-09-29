/*
 * Copyright (c) 2017 FH Dortmund and others
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Description:
 *    Minimal Hono Instance Data Sending Program
 *
 * Contributors:
 *    M.Ozcelikors 29.09.2017
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "hono_interaction.h"


#define H_HOST "localhost"
#define H_PORT ((int)8080)
#define H_TENANT "DEFAULT_TENANT"

int main()
{
	FILE* fileptr;
	char buf[20];
	int core_num = 0;
	double roverUtilCpu[4];

	// Try to register devices
	printf("Registering devices ...");
	registerDeviceToHonoInstance(H_HOST, H_PORT, H_TENANT, "roverUtilCpu1");
	registerDeviceToHonoInstance(H_HOST, H_PORT, H_TENANT, "roverUtilCpu2");
	registerDeviceToHonoInstance(H_HOST, H_PORT, H_TENANT, "roverUtilCpu3");
	registerDeviceToHonoInstance(H_HOST, H_PORT, H_TENANT, "roverUtilCpu4");


	while (1)
	{
		core_num = 0;
		// Read from file
		fileptr = fopen ("/home/pi/hono_poller/log/core_usage_rpi.inc", "r");
		if (!fileptr)
		{
			printf("Unable to read from file !\n");
			abort(); //Dump the core
		}
		else
		{
			printf ("Getting the data from sources ...\n");
			// Get the data
			fgets(buf, 20, fileptr);
			printf("buf=%s\n",buf);
			// Parse the read file to get core usage information, Splitting operation with tokens
			char *token = strtok(buf, ",");

			while (token != NULL && core_num<=4)
			{
				sscanf(token, "%lf", &roverUtilCpu[core_num]);
				token = strtok(NULL, ",");
				printf ("token=%s\n",token);
				core_num++;
			}

			printf ("Sending the data to Hono instance ...\n");

			//Send messages to hono instance
			sendTelemetryDataToHonoInstance(H_HOST, H_PORT, H_TENANT, "roverUtilCpu1", "value", roverUtilCpu[0]);
			sendTelemetryDataToHonoInstance(H_HOST, H_PORT, H_TENANT, "roverUtilCpu2", "value", roverUtilCpu[1]);
			sendTelemetryDataToHonoInstance(H_HOST, H_PORT, H_TENANT, "roverUtilCpu3", "value", roverUtilCpu[2]);
			sendTelemetryDataToHonoInstance(H_HOST, H_PORT, H_TENANT, "roverUtilCpu4", "value", roverUtilCpu[3]);
		}

		sleep(1);

	}
	return 1;
}


