/*-----------------------------------------------------------------------
     Creator		: Morris chiou
     Sensor		: E-COMPASS & Temperature
     File Name		: SENSOR_LIS3MDL.c
     Function		: SENSOR_LIS3MDL
     Create Date	: 2020/07/23
---------------------------------------------------------------------- */

#include <stdio.h>
#include <math.h>
#include <delay.h>
#include <stdlib.h>
#include <datatype_Layer.h>
#include <swi2c_Layer.h>
#include <SENSOR_LIS3MDL.h>


LIS3MDL_AXIS	LIS3MDL_AXIS_DATA;


/********************************************** SYSTEM **************************************************/
/*------------------------------------------------------------------------------------------------------*/
/*initial LIS3MDL*/
CHAR8S LIS3MDL_SET_INITIAL(void)
{

	CHAR8S status = 0;

		/*step 0 : software reset*/
		status = LIS3MDL_SET_SWRESET();
		if(status!=0)
		{
			return -1;		/* fail*/
		}

		/*setp 1: let LIS3MDL into power_down mode */
		status = LIS3MDL_SET_SYSTEM_MODE_POWER_DOWN();
		if(status!=0)
		{
			return -2;		/* fail*/
		}

		/*step 2 : set X ,Y ,Z axis  mode &  data rate*/
		status = LIS3MDL_SET_MODE_SPEED(); 
		if(status!=0)
		{
			return -3;		/*  fail*/
		}

		/*step 3 : set Scale */
		status = LIS3MDL_SET_SCALE(); 
		if(status!=0)
		{
			return -4;		/* fail*/
		}

		/*step 5 :  set the [BDU] Block data update  Enable*/
		status = LIS3MDL_LIS3MDL_SET_READ_DATA_TYPE(); 
		if(status!=0)
		{
			return -5;		/* fail*/
		}

		/*step 6 :  set interrput config*/
		status = LIS3MDL_SET_INT_CONFIG(); 
		if(status!=0)
		{
			return -6;		/* fail*/
		}

		/*step 7 :  set Interrupt threshold*/
		status = LIS3MDL_SET_INT_THD_VALUE(4000); 	/*set 4000 for Interrupt threshold*/
		if(status!=0)
		{
			return -7;		/*fail*/
		}

		/*step 8 :  let LIS3MDL into Single-conversion mode */
		status = LIS3MDL_SET_SYSTEM_RUN_MODE(); 
		if(status!=0)
		{
			return -8;		/*fail*/
		}
		
}
/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/* get LIS3MDL id */
/* must be ID = 0x3D */
CHAR8S LIS3MDL_GET_ID(CHAR8U *id)
{
	CHAR8U read_data ;
	CHAR8S status = 0;

		status = i2c_read_1_byte_data(LIS3MDL_SLAVE_ADDRESS,LIS3MDL_REG_WHO_AM_I,&read_data);
		if(status !=1) 
		{
			return -1;		/* read fail*/
		}

		*id = read_data;	/*read success*/
		return 0;
}
/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/* LIS3MDL SOFTWARE reset */
/* use define LIS3MDL_SET_RESET	set reset */
CHAR8S LIS3MDL_SET_SWRESET(void)
{
	CHAR8U read_data ;
	CHAR8S status = 0;

		/*set reset to LIS3MDL */
		status = i2c_write_1_byte_data(LIS3MDL_SLAVE_ADDRESS,LIS3MDL_REG_CTRL2,LIS3MDL_SET_RESET);
		if(status !=1)
		{
			return -1; /*write fail fail*/
		}
		else
		{
			return 0;
		}
}
/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/*
	LIS3MDL set mode & data rate & enable temperature
	use define LIS3MDL_SET_X_Y_RUN_MODE		set mode & data rate
	use define LIS3MDL_SET_Z_RUN_MODE		set mode & data rate
*/
CHAR8S LIS3MDL_SET_MODE_SPEED(void)
{
	CHAR8S status = 0;

		/*set X,Y axis mode & set the data rate */
		status = i2c_write_1_byte_data(LIS3MDL_SLAVE_ADDRESS,LIS3MDL_REG_CTRL1,LIS3MDL_SET_X_Y_RUN_MODE);
		if(status !=1) 
		{
			return -1; /* write fail fail*/
		}

		/*set Z axis mode*/
		status = i2c_write_1_byte_data(LIS3MDL_SLAVE_ADDRESS,LIS3MDL_REG_CTRL4,LIS3MDL_SET_Z_RUN_MODE);
		if(status !=1) 
		{
			return -1; /* write fail fail*/
		}
		return 0 ; /*set ok!!	*/
}
/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/* LIS3MDL set scale*/
/* use define LIS3MDL_SET_SCALE	set mode & data rate*/
CHAR8S LIS3MDL_SET_SCALE(void)
{
	CHAR8S status = 0;
		
		/* set Scale mode	;  +- 8 guess*/
		status = i2c_write_1_byte_data(LIS3MDL_SLAVE_ADDRESS,LIS3MDL_REG_CTRL2,LIS3MDL_SET_SCALE_MODE);
		if(status !=1) 
		{
			return -1; /* write fail fail*/
		}
		else
		{
			return 0; /* set ok!!*/		
		}
}
/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/*
	LIS3MDL set system mode
	use define LIS3MDL_SET_SYSTEM_MODE	set system mode
	LIS3MDL set system mode -> Single-conversion mode ; do one measurement & done -> turn Power down mode [Idle mode]
*/
CHAR8S LIS3MDL_SET_SYSTEM_RUN_MODE(void)
{
	CHAR8S status = 0;
		
		/*set Single-conversion mode ->  used with sampling frequency from 0.625 Hz to 80Hz.*/
		status = i2c_write_1_byte_data(LIS3MDL_SLAVE_ADDRESS,LIS3MDL_REG_CTRL3,LIS3MDL_SET_SYSTEM_MODE);
		if(status !=1)
		{
			return -1; /* write fail fail*/
		}
		else
		{
			return 0 ; /* set ok!!*/
		}
}			
/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/* LIS3MDL set system mode -> power down mode [Idle mode]*/
CHAR8S LIS3MDL_SET_SYSTEM_MODE_POWER_DOWN(void)
{
	CHAR8S status = 0;
		
		/*set Power down mode -> Idle mode*/
		status = i2c_write_1_byte_data(LIS3MDL_SLAVE_ADDRESS,LIS3MDL_REG_CTRL3,LIS3MDL_SET_SYSTEM_POWER_DOWN);
		if(status !=1) 
		{
			return -1;	/* write fail fail*/
		}
		else
		{
			return 0 ;	/*set ok!!*/
		}
}
/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/* LIS3MDL set the [BDU] Block data update  Enable*/
/* use define LIS3MDL_SET_READ_DATA_TYPE set read data type*/
CHAR8S LIS3MDL_LIS3MDL_SET_READ_DATA_TYPE(void)
{
	CHAR8S status = 0;
		
		/*set the [BDU] Block data update  Enable*/
		status = i2c_write_1_byte_data(LIS3MDL_SLAVE_ADDRESS,LIS3MDL_REG_CTRL5,LIS3MDL_SET_READ_DATA_TYPE);
		if(status !=1)
		{
			return -1;	/*write fail fail*/
		}
		else
		{
			return 0 ;	/*set ok!!	*/
		}
}
/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/*
	get LIS3MDL  status
	use define LIS3MDL_REG_STATUS	get status
	if data_status return   0x01 -> XYZ data ready
	if data_status return   0xF0 -> XYZ data not ready
*/
CHAR8S LIS3MDL_GET_STATUS(CHAR8U *data_status)
{
	CHAR8S status = 0;
	CHAR8U temp_read_data=0;
		
		/*read XYZ data ready status*/
		status = i2c_read_1_byte_data(LIS3MDL_SLAVE_ADDRESS,LIS3MDL_REG_STATUS,&temp_read_data);
		if(status !=1) 
		{
			return -1;	/* read fail*/
		}

		if(temp_read_data & 0x88) /*the data ready ! -> read data!!*/
		{
			*data_status = 0x01;
			return 0;			/*the data  X Y Z data ok!!.*/
		}
		else 
		{
			*data_status = 0xF0;
			return 0;			/*the data  X Y Z data not  ready!*/
		}

}
/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/*
	****** use Register status LIS3MDL_REG_STATUS [0x27] to get data
	LIS3MDL get X Y Z axis data  & Temperautre data
	if data status not ready -> return -4
*/
CHAR8S LIS3MDL_GET_XYZ_AXIS_DATA_USE_STATUS(INT16S *data)
{
	CHAR8S status_function = 0;
	CHAR8U data_ready=0;
	CHAR8U read_stat_retry=0;
	CHAR8U xyz_data[6] = {0};
	CHAR8U temp_data[2]= {0};
			
		/*re try 4 times*/
		for(read_stat_retry=0;read_stat_retry<8;read_stat_retry++)
		{

			status_function = LIS3MDL_GET_STATUS(&data_ready);
			if(status_function!=0)
			{
				return -4; 		/*read stats fail*/    
			}	
			
			if(data_ready == 0x01) 
			{
				break;	        /*data ready to read .*/
			}
			else 
			{
				delay_ms(10);
			}
		}

		if(data_ready == 0x01)	/* read data */
		{
			/* READ 3 axis data (X,Y,Z) */
			status_function = i2c_read_n_byte_data(LIS3MDL_SLAVE_ADDRESS,LIS3MDL_REG_OUT_X_L |I2C_MULTI_READ ,6,&xyz_data[0]);
			if(status_function !=1) 
			{
				return -1;	/*read fail*/
			}	

			/* READ TEMPERATURE */
			status_function = i2c_read_n_byte_data(LIS3MDL_SLAVE_ADDRESS,LIS3MDL_REG_TEMP_OUT_L|I2C_MULTI_READ,2,&temp_data[0]);
			if(status_function !=1) 
			{
				return -1;	/*read fail*/
			}	


			{
		
				/*X axis 16bit data */
				data[0]= ((INT16U)(xyz_data[1]<<8) + (INT16U)(xyz_data[0]) );	/*get data & turn 2'S complement*/

				/* calculate X-axis 2'S complement*/
				if(data[0] & 0x8000) /* positive */
				{
					data[0]=data[0];
				}
				else	/* negative , turn 2'S complement*/
				{
					data[0]=~data[0] +1;
					data[0]=-data[0];
				}
		
				/*Y axis 16bit data */
				data[1]=( (INT16U)(xyz_data[3]<<8) + (INT16U)(xyz_data[2]) );	/*get data & turn 2'S complement*/
				
				/* calculate Y-axis 2'S complement*/	
				if(data[1] & 0x8000) /* positive */
				{
					data[1]=data[1];
				}
				else	/* negative , turn 2'S complement*/
				{
					data[1]=~data[1] +1;
					data[1]=-data[1];
				}
		
				/*Z axis 16bit data */
				data[2]=( (INT16U)(xyz_data[5]<<8) + (INT16U)(xyz_data[4]) );	/*get data & turn 2'S complement*/

				/* calculate Z-axis 2'S complement*/		
				if(data[2] & 0x8000) /* positive */
				{
					data[2]=data[2];
				}
				else	/* negative , turn 2'S complement*/
				{
					data[2]=~data[2] +1;
					data[2]=-data[2];
				}					
				
				/*Temperature 16bit data */
				data[3]=( (INT16U)(temp_data[1]<<8) + (INT16U)(temp_data[0]) );	/*get data & turn 2'S complement*/

				/* calculate temperature 2'S complement*/	
				if(data[3] & 0x8000) /* positive */
				{
					data[3]=data[3];
				}
				else	/* negative , turn 2'S complement*/
				{
					data[3]=~data[3] +1;
					data[3]=-data[3];
				}
				
			}

			
			return 0; 	/*data read ok!!*/
				
		}
	       else if(data_ready == 0xF0) 	/* the data not ready*/
		{
			data[0]=0;
			data[1]=0;
			data[2]=0;
			data[3]=0;
				
			return -4;			/* data not ready !!*/
	       }


}
/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/*
	****** use output pin DRDY pin [pin 8] to get data
	****** detail use  see EXAMPLE_LIS3MDL
	LIS3MDL get X Y Z axis data  & Temperautre data
	if data status not ready -> return -4
*/
CHAR8S LIS3MDL_GET_XYZ_AXIS_DATA_USE_DRDY_PIN(INT16U *data)
{
	CHAR8S status = 0;
	CHAR8U data_ready=0;
	CHAR8U read_stat_retry=0;
	CHAR8U xyz_temp_data[8] = {0};
			
		status = i2c_read_n_byte_data(LIS3MDL_SLAVE_ADDRESS,LIS3MDL_REG_OUT_X_L,8,&xyz_temp_data[0]);
		if(status !=1) 
		{
			return -1; /*read fail*/
		}		

		/* X axis 16bit data */
		data[0]= (INT16U)(xyz_temp_data[1]<<8) + (INT16U)(xyz_temp_data[0]);
		/* Y axis 16bit data */
		data[1]= (INT16U)(xyz_temp_data[3]<<8) + (INT16U)(xyz_temp_data[2]);
		/* Z axis 16bit data */
		data[2]= (INT16U)(xyz_temp_data[5]<<8) + (INT16U)(xyz_temp_data[4]);
		/* Temperature 16bit data */
		data[3]= (INT16U)(xyz_temp_data[7]<<8) + (INT16U)(xyz_temp_data[6]);

		return 0;	/*data read ok!!*/			

}
/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/* LIS3MDL set interrput pin & config*/
/* use define LIS3MDL_SET_INT_CFG set interrput config*/
CHAR8S LIS3MDL_SET_INT_CONFIG(void)
{
	CHAR8S status = 0;
		
		/* set the INTERRPUT CONFIG */
		status = i2c_write_1_byte_data(LIS3MDL_SLAVE_ADDRESS,LIS3MDL_REG_INT_CFG,LIS3MDL_SET_INT_CFG);
		if(status !=1) 
		{
			return -1; /* write fail fail*/
		}
		else
		{
			return 0 ; /* set ok!!*/
		}
}
/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/*
	LIS3MDL set Interrupt threshold
	set the Interrupt threshold //The value is expressed in 16-bit unsigned.
	use LIS3MDL_REG_INT_THS_L[0x32]   ->  LOW byte THS value.
	LIS3MDL_REG_INT_THS_H[0x33]   ->  HIGH byte THS value.
*/
CHAR8S LIS3MDL_SET_INT_THD_VALUE(INT16U thd_data)
{
	CHAR8S status = 0;
	CHAR8U write_data[1]={0};

		write_data[0] =(CHAR8U)(thd_data & 0xFF );	 /*low byte*/
		write_data[0] =(CHAR8U)(thd_data >> 8) ; 	/*high byte*/		
						
		/*set the Interrupt threshold*/
		status = i2c_write_n_byte_data(LIS3MDL_SLAVE_ADDRESS,LIS3MDL_REG_INT_THS_L,1,&write_data[0]);
		if(status !=1) 
		{
			return -1; /*write fail fail*/
		}
		else
		{
			return 0 ; /*set ok!!*/	
		}
}
/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/* LIS3MDL get interrput status*/
/* the status flag -> set the  LIS3MDL_REG_INT_SRC[0x31] */
CHAR8S LIS3MDL_GET_INT_STATUS(CHAR8U *int_status)
{
	CHAR8S status = 0;
	CHAR8U temp_read_data=0;
		
		/* get the interrput status*/
		status = i2c_read_1_byte_data(LIS3MDL_SLAVE_ADDRESS,LIS3MDL_REG_INT_SRC,&temp_read_data);
		if(status !=1) 
		{
			return -1;	/*read fail*/
		}

		*int_status = temp_read_data;

		return 0;	/*read ok!!*/
}
/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/*
	------------------------------------------------
	step1:
		REG20 -> 0x1C
		REG21 -> 0x40
		delay_ms(20)
		REG22 -> 0x00  turn on sensor
	------------------------------------------------
	setp2:
		delay_ms(20)

		read  5 times		
		check data ready & read data
		
		end
		
		average 5 time data 
		a.OUTX_NOST   [NOST : NO SELF TEST]
		b.OUTY_NOST
		c.OUTZ_NOST
	------------------------------------------------
	step3:
             REG20 -> 0x1D    enable self test
             delay_ms(60)    
	------------------------------------------------    		
	step4:
		
		read  5 times		
		check data ready & read data
		
		end
		
		average 5 time data 
		a.OUTX_ST	[ST : SELF TEST]
		b.OUTY_ST
		c.OUTZ_ST
	------------------------------------------------
	step5: 
		compare the 
	
		a.OUTX_NOST   [NOST : NO SELF TEST]
		b.OUTY_NOST
		c.OUTZ_NOST

		with	
		a.OUTX_ST	[ST : SELF TEST]
		b.OUTY_ST
		c.OUTZ_ST

		**note :  Self-test limits (FS = 12 gauss)
		Axis		ST min [gauss]	ST max [gauss]
		X-axis		1.0				3.0
		Y-axis		1.0				3.0
		Z-axis		0.1				1.0
	
		-> 
		1.	|min(OUTX_ST)| <  |OUTX_ST -OUTX_NOST | < |max(OUTX_ST)|
		2.    	|min(OUTY_ST)| <  |OUTY_ST -OUTY_NOST | < |max(OUTY_ST)| 
		3.    	|min(OUTZ_ST)| <  |OUTZ_ST -OUTY_NOST | < |max(OUTZ_ST)|

		if (1 && 2 && 3) -> pass , then IC is good .
		else  -> fail , the IC is bad .
	------------------------------------------------
	step6:
		REG20 -> 0x1C	disable self test
		REG22 -> 0x03     power down mode
	------------------------------------------------	
*/
CHAR8S LIS3MDL_SET_GET_SELF_TEST(void)
{

	CHAR8S status = 0;
	CHAR8U cnt = 0;
	INT16U  read_nost_data[5][4]={0};
	FLOAT average_nost_data[3]={0};

	INT16U  read_st_data[5][4]={0};
	FLOAT average_st_data[3]={0};

	FLOAT x_axis_diff=0,y_axis_diff=0,z_axis_diff=0;
				
		/*----------------------------- STEP1 -------------------------------*/
		status = i2c_write_1_byte_data(LIS3MDL_SLAVE_ADDRESS,LIS3MDL_REG_CTRL1,0x1C);
		if(status !=1) 
		{
			return -1; /* write fail fail*/
		}

		status = i2c_write_1_byte_data(LIS3MDL_SLAVE_ADDRESS,LIS3MDL_REG_CTRL2,0x40);
		if(status !=1)
		{
			return -1; /* write fail fail*/
		}

		delay_ms(30);
		
		status = i2c_write_1_byte_data(LIS3MDL_SLAVE_ADDRESS,LIS3MDL_REG_CTRL3,0x00);
		if(status !=1)
		{
			return -1; /*write fail fail*/	
		}
		/*----------------------------- STEP1 -------------------------------*/


		/*----------------------------- STEP2 -------------------------------*/
		delay_ms(30);

		for(cnt=0;cnt<=5;cnt++)
		{
			status = LIS3MDL_GET_XYZ_AXIS_DATA_USE_STATUS(&read_nost_data[cnt][0]);
			if(status !=1) 
			{
				return -1; /*READ fail*/		
			}
		}
		
		average_nost_data[0]=0;
		average_nost_data[0]=0;
		average_nost_data[0]=0;
		
		for(cnt=0;cnt<=5;cnt++)
		{
			average_nost_data[0]+=read_nost_data[cnt][0];		/*X-axis data*/	
			average_nost_data[1]+=read_nost_data[cnt][1];		/*Y-axis data*/	
			average_nost_data[2]+=read_nost_data[cnt][2];		/*Z-axis data*/	
		}	

		/*average 5 times*/	
		average_nost_data[0]=(FLOAT)(average_nost_data[0]/5);
		average_nost_data[1]=(FLOAT)(average_nost_data[1]/5);
		average_nost_data[2]=(FLOAT)(average_nost_data[2]/5);
		
		/*----------------------------- STEP2 -------------------------------*/


		/*----------------------------- STEP3 -------------------------------*/
		status = i2c_write_1_byte_data(LIS3MDL_SLAVE_ADDRESS,LIS3MDL_REG_CTRL1,0x1D);		/*ENABLE SELF TEST*/
		if(status !=1) 
		{
			return -1; /* write fail fail	*/
		}
		/*----------------------------- STEP3 -------------------------------*/


		/*----------------------------- STEP4 -------------------------------*/
		delay_ms(1);
		
		for(cnt=0;cnt<=5;cnt++)
		{
			status = LIS3MDL_GET_XYZ_AXIS_DATA_USE_STATUS(&read_st_data[cnt][0]);
			if(status !=1) return -1; // READ fail*/		
		}

		average_st_data[0]=0;
		average_st_data[0]=0;
		average_st_data[0]=0;
		
		for(cnt=0;cnt<=5;cnt++)
		{
			average_st_data[0]+=read_st_data[cnt][0];		/*X-axis data*/	 
			average_st_data[1]+=read_st_data[cnt][1];		/*Y-axis data*/	
			average_st_data[2]+=read_st_data[cnt][2];		/*Z-axis data*/	
		}	

		/*average 5 times*/
		average_st_data[0]=(FLOAT)(average_st_data[0]/5);
		average_st_data[1]=(FLOAT)(average_st_data[1]/5);
		average_st_data[2]=(FLOAT)(average_st_data[2]/5);
		/*----------------------------- STEP4 -------------------------------*/



		/*----------------------------- STEP5 -------------------------------*/

		x_axis_diff=abs(average_st_data[0] - average_nost_data[0]);
		y_axis_diff=abs(average_st_data[1] - average_nost_data[1]);
		z_axis_diff=abs(average_st_data[2] - average_nost_data[2]);
		
              printf("x_axis_diff = %f \r\n",x_axis_diff);
		printf("y_axis_diff = %f \r\n",y_axis_diff);
		printf("z_axis_diff = %f \r\n",z_axis_diff);

		/*
		**note :  Self-test limits (FS = 12 gauss)
		Axis		ST min [gauss]	ST max [gauss]
		X-axis		1.0				3.0
		Y-axis		1.0				3.0
		Z-axis		0.1				1.0
		*/
		
		if( (x_axis_diff<=3.0) && (x_axis_diff>=1.0) && (y_axis_diff<=3.0) && (y_axis_diff>=1.0) && (z_axis_diff<=1.0) && (x_axis_diff>=0.1) )
		{
			/*pass*/
			printf("IC PASS !!\r\n");
		}
		else
		{
			/*fail*/
			printf("IC FAIL !!\r\n");
		}
		/*----------------------------- STEP5 -------------------------------*/


		/*----------------------------- STEP6 -------------------------------*/
		status = i2c_write_1_byte_data(LIS3MDL_SLAVE_ADDRESS,LIS3MDL_REG_CTRL1,0x1C);		/*disable self test*/
		if(status !=1) 
		{
			return -1; /*write fail fail*/
		}

		status = i2c_write_1_byte_data(LIS3MDL_SLAVE_ADDRESS,LIS3MDL_REG_CTRL3,0x03);		/*POWER DOWN MODE*/
		if(status !=1)
		{
			return -1; /*write fail fail*/
		}

		delay_ms(30);
		
		/*----------------------------- STEP6 -------------------------------*/


		return 0 ; /*self test finish!!*/


}
/*------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------*/
/* simple calculate */
/* calculate the LIS3MDL azimuth*/
/* return degree */
/* the coordinates is 

			y
			^
			|     /
                   	|    /
			|   /  
                   	|  /		
			| /     degree
                   	|/  
			------------> x

     and point to South
*/
FLOAT LIS3MDL_GET_AZIMUTH(LIS3MDL_AXIS data)
{
	FLOAT x_data,y_data,result_data,cal;
	
		/* calculate the azimuth */
		result_data =atan2((FLOAT)data.Y_AXIS,(FLOAT)data.X_AXIS)*180.0/3.14159 +180.0;			
		return result_data;
}
/*--------------------------------------------------------------------------------------------------*/
/********************************************** SYSTEM **************************************************/
