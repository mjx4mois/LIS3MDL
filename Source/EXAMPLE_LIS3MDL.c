/*-----------------------------------------------------------------------
     Creator		: Morris chiou
     Sensor		: E-COMPASS & Temperature
     File Name		: EXAMPLE_LIS3MDL.c
     Function		: EXAMPLE_LIS3MDL
     Create Date	: 2020/07/23
---------------------------------------------------------------------- */

#include <mega32a.h>
#include <stdio.h>
#include <delay.h>
#include <math.h>
#include <i2c.h>
#include <alcd.h>
#include <datatype_Layer.h>
#include <swi2c_Layer.h>
#include <SENSOR_LIS3MDL.h>




void EXAMPLE_LIS3MDL(void);

/********** self test **************/
#define LIS3MDL_SELF_TEST  					(0)		/*set "1" enable self test ; "0" disable self test*/
/********** self test **************/
#define LIS3MDL_GET_RAW_DATA_ONLY		(0)		/* enable print data to UART TX only */

#define  LIS3MDL_READ_BY_STATUS 			(0)
#define  LIS3MDL_READ_BY_DRDY_PIN 		(1)


/* if set LIS3MDL_READ_BY_STATUS ->    use reg status read data*/
/* if set LIS3MDL_READ_BY_DRDY_PIN -> use DRDY pin read data*/
#define LIS3MDL_READ_DATA_WAY 			(LIS3MDL_READ_BY_STATUS)



/* set DRDY io read */
#if (LIS3MDL_READ_DATA_WAY == LIS3MDL_READ_BY_DRDY_PIN)
/* PIND.4 -> read LIS3MDL DRDY status  [INPUT pin]*/
#define LIS3MDL_DRDY_PIN						PIND.4			
#endif


LIS3MDL_AXIS GET_DATA;

void EXAMPLE_LIS3MDL(void)
{

	CHAR8S status = 0;
	INT16S data[4]={0};
	CHAR8U get_id = 0;
	CHAR8U lcd_char_data[3][4]={0}; 
	CHAR8U	lcd_char_angle_data[5]={0};
	FLOAT degree;
	FLOAT temperature_degree;
	
#if (LIS3MDL_SELF_TEST == 1)
		/* ********* self test **************/
		status = LIS3MDL_SET_GET_SELF_TEST();
		if(status !=0) 
		{
			printf("LIS3MDL SELF TEST  ok!!\r\n");
		}
		else 
		{	printf("LIS3MDL SELF TEST  fail!!\r\n");	
			while(1);
		}
		/* ********* self test **************/
#endif		

/* set PORTD.4 as Input Pin	*/
#if (LIS3MDL_READ_DATA_WAY == LIS3MDL_READ_BY_DRDY_PIN)
		DDRD = DDRD & (~(1<<4)) ;
#endif

		i2c_stop_hang();
		i2c_stop_hang();

		status = LIS3MDL_GET_ID(&get_id);
		if(status !=0) 
		{
			printf("LIS3MDL get id fail\r\n");	
		}
		else 
		{
			printf("LIS3MDL id = 0x%x \r\n",get_id);
		}

		i2c_stop_hang();
		
		status = LIS3MDL_SET_INITIAL();
		if(status !=0) 
		{
			printf("LIS3MDL initial fail\r\n");	
		}
		else
		{
			printf("LIS3MDL initial success\r\n");
		}

#if (LIS3MDL_READ_DATA_WAY == LIS3MDL_READ_BY_STATUS)


		#if (LIS3MDL_GET_RAW_DATA_ONLY==1)
		while(1)
		{
			i2c_stop_hang();
			i2c_stop_hang();
        
			//let LIS3MDL into Single-conversion mode 
			status = LIS3MDL_SET_SYSTEM_RUN_MODE(); 

			status = LIS3MDL_GET_XYZ_AXIS_DATA_USE_STATUS(&data[0]);
			
			#if 0
			/*print x,y,z */
			printf("%d %d %d\r\n",data[0],data[1],data[2]);
			#endif


			#if 1
			/*print x,y only */
			printf("%d %d \r\n",data[0],data[1]);
			#endif
			delay_ms(50); /* tiny delay */		
		}  


		#endif





		while(1)
		{
		
			i2c_stop_hang();
			i2c_stop_hang();
        
			//let LIS3MDL into Single-conversion mode 
			status = LIS3MDL_SET_SYSTEM_RUN_MODE(); 
			if(status!=0)
			{
				printf("set Single-conversion mode fail  \r\n");	    
			}

			status = LIS3MDL_GET_XYZ_AXIS_DATA_USE_STATUS(&data[0]);
			if(status !=0) 
			{
				printf("get LIS3MDL data fail\r\n");  
			}
                
			printf("X -axis data = 0x%05X ,%d\r\n",data[0],data[0]);
			printf("Y -axis data = 0x%05X ,%d\r\n",data[1],data[1]);		
			printf("Z -axis data = 0x%05X ,%d\r\n",data[2],data[2]);
			printf("temperature data = 0x%05x ,%d\r\n",(INT16U)data[3],(INT16U)data[3]);

			/*temperature calculate format : (float)(lsb / 8.0f ) + ( 25.0f ) */
			temperature_degree = ((FLOAT)data[3]/8.0) + 25.0;
			printf("temperature degree = %f C\r\n",temperature_degree);
			

				/* X-AXIS*/   
	                     lcd_char_data[0][0]=(INT32U)(data[0]/1000)%10;
	                     lcd_char_data[0][1]=(INT32U)(data[0]/100)%10;   
	                     lcd_char_data[0][2]=(INT32U)(data[0]/10)%10;  
	                     lcd_char_data[0][3]=(INT32U)(data[0])%10;   
	                     
	                     /* Y-AXIS*/   
	                     lcd_char_data[1][0]=(INT32U)(data[1]/1000)%10;
	                     lcd_char_data[1][1]=(INT32U)(data[1]/100)%10;   
	                     lcd_char_data[1][2]=(INT32U)(data[1]/10)%10;  
	                     lcd_char_data[1][3]=(INT32U)(data[1])%10;         
	                     
	                     
	                     /* Z-AXIS*/   
	                     lcd_char_data[2][0]=(INT32U)(data[2]/1000)%10;
	                     lcd_char_data[2][1]=(INT32U)(data[2]/100)%10;   
	                     lcd_char_data[2][2]=(INT32U)(data[2]/10)%10;  
	                     lcd_char_data[2][3]=(INT32U)(data[2])%10;         

            			/* SHOW X axis DATA */                    
	            		lcd_gotoxy(0,0);
	            		lcd_putsf("X axis:");     
	            		if(data[0]<0)
	            		{
	            			lcd_putchar(45);		/* LCD show "-"  mean negative */
				}                             
	           		else
				{
					lcd_putchar(32);		/* LCD show " "  mean positive */
				}   
					
				/* show X axis data on LCD */
				lcd_putchar(48+lcd_char_data[0][0]);
				lcd_putchar(48+lcd_char_data[0][1]);
				lcd_putchar(48+lcd_char_data[0][2]);
				lcd_putchar(48+lcd_char_data[0][3]);


				/* SHOW Y axis DATA */    
				lcd_gotoxy(0,1);
				lcd_putsf("Y axis:"); 
	             		if(data[1]<0)
	           		{
	           			lcd_putchar(45);		/* LCD show "-"  mean negative */
				}                             
	            		else
				{
					lcd_putchar(32);		/* LCD show " "  mean positive */
				}   


				/* show Y axis data on LCD */
	                 	lcd_putchar(48+lcd_char_data[1][0]);
	                	lcd_putchar(48+lcd_char_data[1][1]);
	                 	lcd_putchar(48+lcd_char_data[1][2]);
	                 	lcd_putchar(48+lcd_char_data[1][3]);
	                    
	  
				/* SHOW Z axis DATA */    
	            		lcd_gotoxy(0,2);
	            		lcd_putsf("Z axis:"); 
	           		if(data[2]<0)
	            		{
	            			lcd_putchar(45);
				}                             
	            		else
				{
					lcd_putchar(32);
				}

									   
				/* show Y axis data on LCD */
	                 	lcd_putchar(48+lcd_char_data[2][0]);
	                 	lcd_putchar(48+lcd_char_data[2][1]);
	                 	lcd_putchar(48+lcd_char_data[2][2]);
	                 	lcd_putchar(48+lcd_char_data[2][3]);



			/* calculate the azimuth*/
			{		
			
				GET_DATA.X_AXIS=data[0];	/* x_axis data */
				GET_DATA.Y_AXIS=data[1];	/* y_axis data */
				GET_DATA.Z_AXIS=data[2];	/* z_axis data */

				/* simple calculate */
				/* GET the degree */
				degree=LIS3MDL_GET_AZIMUTH(GET_DATA);

				if((degree < 22.5) || (degree > 337.5 ))
				{
					printf("\r\nSouth\r\n");
				}
				else if((degree > 22.5) && (degree < 67.5 ))
				{
					printf("\r\nSouth-West\r\n");
				}
				else if((degree > 67.5) && (degree < 112.5 ))
				{
					printf("\r\nWest\r\n");
				}
				else if((degree > 112.5) && (degree < 157.5 ))
				{
					printf("\r\nNorth-West\r\n");
				}
				else if((degree > 157.5) && (degree< 202.5 ))
				{
					printf("\r\nNorth\r\n");
				}
				else if((degree > 202.5) && (degree < 247.5 ))
				{
					printf("\r\nNorthEast\r\n");
				}
				else if((degree > 247.5) && (degree < 292.5 ))
				{
					printf("\r\nEast\r\n");
				}
				else if((degree > 292.5) && (degree < 337.5 ))
				{
					printf("\r\nSouthEast\r\n");
				}
				
				/* SHOW Angle DATA */    
				lcd_gotoxy(0,3);
				lcd_putsf("Ang:"); 
							
				/* calculate azimuth DATA */   
				lcd_char_angle_data[0]=(INT32U)((INT32U)degree/1000)%10;
				lcd_char_angle_data[1]=(INT32U)((INT32U)degree/100)%10;   
				lcd_char_angle_data[2]=(INT32U)((INT32U)degree/10)%10;  
				lcd_char_angle_data[3]=(INT32U)((INT32U)degree)%10;         
				lcd_char_angle_data[4]=(INT32U)(degree*10)%10;      

								   
				/* SHOW azimuth DATA */  
				lcd_putchar(48+lcd_char_angle_data[0]);
				lcd_putchar(48+lcd_char_angle_data[1]);			 		
				lcd_putchar(48+lcd_char_angle_data[2]);		
				lcd_putchar(48+lcd_char_angle_data[3]);
				lcd_putchar(46);    /* print "."  */ 	
				lcd_putchar(48+lcd_char_angle_data[4]);						 
			}

				
			delay_ms(50);	/* tiny delay */ 		


			
			
		}
		
#elif (LIS3MDL_READ_DATA_WAY == LIS3MDL_READ_BY_DRDY_PIN)

		while(1)
		{
			if(LIS3MDL_DRDY_PIN==0);
			else
			{
				status = LIS3MDL_GET_XYZ_AXIS_DATA_USE_DRDY_PIN(&data[0]);
				if(status !=0)
				{
					printf("get LIS3MDL data fail\r\n");
				}	
				
				printf("X -axis data = %d \r\n",data[0]);
				printf("Y -axis data = %d \r\n",data[1]);		
				printf("Z -axis data = %d \r\n",data[2]);
				printf("temperature data = %d \r\n",data[3]);	
						
				delay_ms(5);
			}
		}
#endif

}

