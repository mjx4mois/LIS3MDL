/*-----------------------------------------------------------------------
     Creator		: Morris chiou
     Sensor		: E-COMPASS & Temperature
     File Name		: SENSOR_LIS3MDL.h
     Function		: SENSOR_LIS3MDL
     Create Date	: 2020/07/23
---------------------------------------------------------------------- */
#ifndef __LIS3MDL_HEADER__ 
#define __LIS3MDL_HEADER__  

/*Note : CS must connect to high , enable  I2C .*/
/*--------------------------------- Define SLAVE ADDRESS ------------------------------------*/
/*LIS3MDL SLAVE ADDRESS*/
	#define LIS3MDL_ADDR_PIN 	 				(0)			/*PIN9(ADDR(SA1)) connect  "0" GND or "1" Vcc*/
#if (LIS3MDL_ADDR_PIN == 1)
	#define LIS3MDL_SLAVE_ADDRESS 				(0x3C)
#elif (LIS3MDL_ADDR_PIN == 0)
	#define LIS3MDL_SLAVE_ADDRESS 				(0x38)
#endif
/*--------------------------------- Define SLAVE ADDRESS ------------------------------------*/



/* ------------- DEFINE LIS3MDL REGISTER  ------------*/
/*------------------------------------------------*/
/* default : 0x3D[00111101]*/
#define LIS3MDL_REG_WHO_AM_I								(0x0F)		/* R*/
//LIS3MDL ID -> 0x3D
/*------------------------------------------------*/
/* default : 0x10 [00010000]*/
#define LIS3MDL_REG_CTRL1									(0x20)		/* R/W*/
/*
	bit 7 [TEMP_EN]Temperature sensor enable. Default value: 0
	Temperature sensor enable. Default value: 0  (0: temperature sensor disabled; 1: temperature sensor enabled)
	---------------------------------
	bit 6~5 [OM] X and Y axes operative mode selection. Default value: 00
	OM1		 	OM0		 		Operating mode for X and Y axes
	0 			0 				Low-power mode
	0 			1 				Medium-performance mode
	1 			0 				High-performance mode
	1 			1 				Ultra-high-performance mode
	---------------------------------
	bit 4~2 [DO] Output data rate selection. Default value: 1 0 0 
	DO2	 	DO1 	DO0 		ODR [Hz]
	0 		0 		0 			0.625
	0 		0 		1 			1.25
	0 		1 		0 			2.5
	0 		1 		1 			5
	 1 		0 		0 			10
	 1 		0 		1 			20
	1 		1 		0 			40
	 1 		1 		1 			80
	---------------------------------
	bit 1 [FAST_ODR] FAST_ODR enables data rates higher than 80 Hz
	DO2 	DO1 	DO0 	FAST_ODR	 	ODR [Hz] 	OM
	X 		X      	X 			1 			1000 		LP
	X 		X      	X 			1 			560 			MP
	X 		X      	X 			1 			300 			HP
	X 		X      	X 			1 			155 			UHP
	---------------------------------
	bit 0 [ST] Self-test enable. Default value: 0 (0: self-test disabled; 1: self-test enabled)
*/
/*------------------------------------------------*/
/* default : 0x00 [00000000]*/
#define LIS3MDL_REG_CTRL2									(0x21)		/* R/W*/
/* 
	bit 7 -> must be "0"
	---------------------------------
	bit 6~5 [FS] Full-scale configuration. Default value: 00
	FS1	 FS0	 	Full-scale
	0 	   0 		¡Ó4 gauss
	0 	   1 		¡Ó8 gauss
	1 	   0 		¡Ó12 gauss
	1 	   1 		¡Ó16 gauss
	---------------------------------
	bit 4  -> must be "0"
	---------------------------------
	bit 3 [REBOOT]Reboot memory content. Default value: 0  (0: normal mode; 1: reboot memory content)
	---------------------------------
	bit 2 [SOFT_RST]Configuration registers and user register reset function. (0: Default value; 1: Reset operation)
	---------------------------------
	bit 1~0  -> must be "0"
*/
/*------------------------------------------------*/
/*default : 0x03 [00000011]*/
#define LIS3MDL_REG_CTRL3									(0x22)		/* R/W*/
/*
	bit 7~6 -> must be "0"
	---------------------------------
	bit 5 [LP] Low-power mode configuration. Default value: 0
	If this bit is ¡¥1¡¦, DO[2:0] is set to 0.625 Hz and the system performs, for each
	channel, the minimum number of averages. Once the bit is set to ¡¥0¡¦, the magnetic
	data rate is configured by the DO bits in CTRL_REG1 (20h) register.
	---------------------------------
	bit 4~3 -> must be "0"
	---------------------------------
	bit 2 [SIM] SPI serial interface mode selection. Default value: 0 (0: 4-wire interface; 1: 3-wire interface).
	---------------------------------
	bit 1~0 [MD] Operating mode selection. Default value: 11
	MD1 		MD0 	Mode
	0 		0 		Continuous-conversion mode
	0 		1 		Single-conversion mode ; Single-conversion mode has to be used with sampling frequency from 0.625 Hz to 80Hz.
	1 		0 		Power-down mode
	1 		1 		Power-down mode
*/
/*------------------------------------------------*/
/*default : 0x00 [00000000] */
#define LIS3MDL_REG_CTRL4									(0x23)		/* R/W*/
/*
	bit 7~4 -> must be "0"
	---------------------------------
	bit 3~2 [OMZ]Z-axis operative mode selection.
	OMZ1	 OMZ0		 Operating mode for Z-axis
 	0 			0 			Low-power mode
	0 			1 			Medium-performance mode
	 1 			0 			High-performance mode
	1 			1 			Ultra-high-performance mode
	---------------------------------
	bit 1 [BLE] Big/Little Endian data selection. Default value: 0 (0: data LSb at lower address; 1: data MSb at lower address)
	---------------------------------
	bit 0 -> must be "0"
*/
/*------------------------------------------------*/
/*default : 0x00 [00000000] */
#define LIS3MDL_REG_CTRL5									(0x24)		/*R/W*/
/*
	bit 7 [FAST_READ]FAST READ allows reading the high part of DATA OUT only in order to increase reading efficiency. Default value: 0
	(0: FAST_READ disabled; 1: FAST_READ enabled)
	---------------------------------
	bit 6 [BDU]Block data update for magnetic data. Default value: 0
	(0: continuous update;1: output registers not updated until MSb and LSb have been read)
	---------------------------------
	bit 5~ 0  -> must be "0"
*/
/*------------------------------------------------*/
/*default : Output */
#define LIS3MDL_REG_STATUS									(0x27)		/*R*/
/*
	bit 7 [ZYXOR]X-, Y- and Z-axis data overrun. Default value: 0		(0: no overrun has occurred;1: a new set of data has overwritten the previous set)
	---------------------------------
	bit 6 [ZOR]Z-axis data overrun. Default value: 0	(0: no overrun has occurred;1: new data for the Z-axis has overwritten the previous data)
	---------------------------------
	bit 5 [YOR]Y-axis data overrun. Default value: 0		(0: no overrun has occurred;1: new data for the Y-axis has overwritten the previous data)
	---------------------------------
	bit 4 [XOR]X-axis data overrun. Default value: 0	(0: no overrun has occurred;1: new data for the X-axis has overwritten the previous data)
	---------------------------------
	bit 3 [ZYXDA]X-, Y- and Z-axis new data available. Default value: 0	(0: a new set of data is not yet available;1: a new set of data is available)
	---------------------------------
	bit 2 [ZDA]Z-axis new data available. Default value: 0	(0: new data for the Z-axis is not yet available;1: new data for the Z-axis is available)
	---------------------------------
	bit 1 [YDA]Y-axis new data available. Default value: 0	(0: new data for the Y-axis is not yet available;1: new data for the Y-axis is available)
	---------------------------------
	bit 0 [XDA]X-axis new data available. Default value: 0	(0: new data for the X-axis is not yet available;1: new data for the X-axis is available)
*/
/*------------------------------------------------*/
/*default : Output*/
#define LIS3MDL_REG_OUT_X_L								(0x28)		/*R*/
//X-axis data output. The value of magnetic field is expressed as two¡¦s complement.*/
/*------------------------------------------------*/
/*default : Output*/
#define LIS3MDL_REG_OUT_X_H								(0x29)		/*R*/
//X-axis data output. The value of magnetic field is expressed as two¡¦s complement.*/
/*------------------------------------------------*/
/*default : Output*/
#define LIS3MDL_REG_OUT_Y_L									(0x2A)		/*R*/
//Y-axis data output. The value of magnetic field is expressed as two¡¦s complement.*/
/*------------------------------------------------*/
/*default : Output */ 
#define LIS3MDL_REG_OUT_Y_H								(0x2B)		/*R*/
//Y-axis data output. The value of magnetic field is expressed as two¡¦s complement.*/
/*------------------------------------------------*/
/*default : Output */ 
#define LIS3MDL_REG_OUT_Z_L									(0x2C)		/*R*/
//Z-axis data output. The value of magnetic field is expressed as two¡¦s complement.*/
/*------------------------------------------------*/
/*default : Output */ 
#define LIS3MDL_REG_OUT_Z_H								(0x2D)		/*R*/
/*Z-axis data output. The value of magnetic field is expressed as two¡¦s complement.*/
/*------------------------------------------------*/
/*default : Output */ 
#define LIS3MDL_REG_TEMP_OUT_L							(0x2E)		/*R	*//*temperature*/
/*Temperature sensor data. The value of temperature is expressed as two¡¦s complement.*/
/*------------------------------------------------*/
/*default : Output */ 
#define LIS3MDL_REG_TEMP_OUT_H							(0x2F)		/*R	*//*temperature*/
/*Temperature sensor data. The value of temperature is expressed as two¡¦s complement.*/
/*------------------------------------------------*/
/*default : 0xE8 [11101000] */
#define LIS3MDL_REG_INT_CFG									(0x30)		/*R/W*/
/*
	bit 7 [XIEN] Enable interrupt generation on X-axis. Default value: 1		(0: disable interrupt request; 1: enable interrupt request)
	---------------------------------
	bit 6 [YIEN] Enable interrupt generation on Y-axis. Default value: 1		(0: disable interrupt request; 1: enable interrupt request)
	---------------------------------
	bit 5 [ZIEN] Enable interrupt generation on Z-axis. Default value: 1		(0: disable interrupt request; 1: enable interrupt request)
	---------------------------------
	bit 4 set "0" This bit must be set to ¡¥0¡¦ for correct functioning of the device.
	---------------------------------
	bit 3 set "1" .
	---------------------------------
	bit 2 [IEA] Interrupt active configuration on INT. Default value: 0	(0: low; 1: high)
	---------------------------------
	bit 1 [LIR] Latch interrupt request. Default value: 0			(0: interrupt request latched; 1: interrupt request not latched)
	Once latched, the INT pin remains in the same state until INT_SRC (31h) is read.
	---------------------------------
	bit 0 [IEN] Interrupt enable on INT pin. Default value: 0		(0: disabled; 1: enabled)
	---------------------------------
*/
/*------------------------------------------------*/
/*default : 0x00 [00000000]*/
#define LIS3MDL_REG_INT_SRC									(0x31)		/*R*/
/*
	bit 7 [PTH_X] Value on X-axis exceeds the threshold on the positive side.		Default value: 0
	---------------------------------
	bit 6 [PTH_Y] Value on Y-axis exceeds the threshold on the positive side.			Default value: 0
	---------------------------------
	bit 5 [PTH_Z] Value on Z-axis exceeds the threshold on the positive side.		Default value: 0
	---------------------------------
	bit 4 [NTH_X] Value on X-axis exceeds the threshold on the negative side.		Default value: 0
	---------------------------------
	bit 3 [NTH_Y] Value on Y-axis exceeds the threshold on the negative side.		Default value: 0
	---------------------------------
	bit 2 [NTH_Z] Value on Z-axis exceeds the threshold on the negative side.		Default value: 0
	---------------------------------
	bit 1 [MROI] Internal measurement range overflow on magnetic value.			Default value: 0
	---------------------------------
	bit 0 [INT] This bit signals when an interrupt event occurs.
	If any interrput event occurs -> "1".;  no any interrupt event ouccurs -> "0".
	---------------------------------
*/
/*------------------------------------------------*/
/*default : 0x00 [00000000] */
#define LIS3MDL_REG_INT_THS_L							(0x32)		/*R/W*/
/*
	LOW byte THS value.
	Interrupt threshold. Default value: 0.
	The value is expressed in 16-bit unsigned.
	Even if the threshold is expressed in absolute value, the device detects both positive and
	negative thresholds.
*/
/*------------------------------------------------*/
//default : 0x00 [00000000] */
#define LIS3MDL_REG_INT_THS_H							(0x33)		/*R/W*/
/*
	HIGH byte THS value.
	Interrupt threshold. Default value: 0.
	The value is expressed in 16-bit unsigned.
	Even if the threshold is expressed in absolute value, the device detects both positive and
	negative thresholds.
*/
/*------------------------------------------------*/
/* ------------- DEFINE LIS3MDL REGISTER  ------------*/





/* ------------- DEFINE LIS3MDL Parameter -------------*/
/* ----------------------------------------------*/
/* I2C Multi-Read Mask */
#define I2C_MULTI_READ					(0x80)

/* ----------------------------------------------*/
/* **register : 0x20 [LIS3MDL_REG_CTRL1]*/
/* for set XY-axis LIS3MD run mode*/
typedef enum 
{
	LIS3MDL_XY_LOW_POWER_MODE=(0x00<<5),
	LIS3MDL_XY_MIDIUM_PERFORMANCE_MODE=(0x01<<5),	
	LIS3MDL_XY_HIGH_PERFORMANCE_MODE=(0x02<<5),
	LIS3MDL_XY_ULTRA_HIGH_PERFORMANCE_MODE=(0x03<<5),
}LIS3MDL_XY_AXIS_RUN_MODE_ENUM;

/***register : 0x20 [LIS3MDL_REG_CTRL1]*/
/*for set LIS3MD mode*/
typedef enum
{
	DATA_RATE_0_625HZ=(0x00<<2),		/*0.625Hz*/
	DATA_RATE_1_25HZ=(0x01<<2),			/*1.25Hz*/
	DATA_RATE_2_5HZ=(0x02<<2),			/*2.5Hz*/
	DATA_RATE_5HZ=(0x03<<2),			/*5Hz*/
	DATA_RATE_10HZ=(0x04<<2),			/*10Hz*/
	DATA_RATE_20HZ=(0x05<<2),			/*20Hz*/
	DATA_RATE_40HZ=(0x06<<2),			/*40Hz*/
	DATA_RATE_80HZ=(0x07<<2),			/*80Hz*/
}LIS3MDL_DATA_RATE_ENUM;

/***register : 0x20 [LIS3MDL_REG_CTRL1]*/
#define LIS3MDL_ENA_TEMPERATURE			(0x80)		/*enable Temperature IP.*/
#define LIS3MDL_HIGH_SPEED					(0x02)		/*bit1 ; if =1 set high speed ; ** watch sepc  detail*/
#define LIS3MDL_SELF_TEST					(0x01)		/*bit0 ; if =1 enable Self-test enable ; default : 0*/
/* ----------------------------------------------*/
/* ----------------------------------------------*/
/***register : 0x21 [LIS3MDL_REG_CTRL2]*/
/*for set LIS3MD Full-scale configuration*/
typedef enum
{
	LIS3MDL_4_GAUSS=(0x00<<5),		/*¡Ó4 gauss*/
	LIS3MDL_8_GAUSS=(0x01<<5),		/*¡Ó8 gauss*/
	LIS3MDL_12_GAUSS=(0x02<<5),		/*¡Ó12 gauss*/	
	LIS3MDL_16_GAUSS=(0x03<<5),		/*¡Ó16 gauss*/	
}LIS3MDL_FULL_SCALE_ENUM;

#define LIS3MDL_REG_CTRL2_MASK			(0x6C)		/*SET bit7, 4 , 1 , 0 as " 0 "*/
/* ----------------------------------------------*/
/* ----------------------------------------------*/
/***register : 0x22 [LIS3MDL_REG_CTRL3]*/
/*for set LIS3MD run mode*/
typedef enum 
{
	LIS3MDL_CONT_CONVER_MODE=(0x00<<0),		/*Continuous-conversion mode*/
	LIS3MDL_SINGLE_CONVER_MODE=(0x01<<0),		/*Single-conversion mode ->  used with sampling frequency from 0.625 Hz to 80Hz.*/
	LIS3MDL_POWER_DOWN_MODE_0=(0x02<<0),		/*Power-down mode*/
	LIS3MDL_POWER_DOWN_MODE_1=(0x03<<0),		/*Power-down mode*/
}LIS3MDL_SYSTEM_MODE;

#define LIS3MDL_REG_CTRL3_MASK			(0x27)		/*SET bit7, 6 , 4 , 3  as " 0 "*/
#define LIS3MDL_LOW_POWER_MODE			(0x20)		/*enable Low Power mode*/
/* ----------------------------------------------*/
/* ----------------------------------------------*/
/***register : 0x23 [LIS3MDL_REG_CTRL4]*/
/*for set Z-axis LIS3MD run mode*/
typedef enum 
{
	LIS3MDL_Z_LOW_POWER_MODE=(0x00<<2),
	LIS3MDL_Z_MIDIUM_PERFORMANCE_MODE=(0x01<<2),	
	LIS3MDL_Z_HIGH_PERFORMANCE_MODE=(0x02<<2),
	LIS3MDL_Z_ULTRA_HIGH_PERFORMANCE_MODE=(0x03<<2),
}LIS3MDL_Z_AXIS_RUN_MODE;

#define LIS3MDL_REG_CTRL4_MASK			(0x0E)		/* SET bit7, 6 , 5 , 4 , 1  as " 0 "*/
#define LIS3MDL_DATA_DATA_ENDIAN			(0<<1)		/* if set 1 MSB at lower address ; set 0 LSB as lower address ; default 0*/

/* ----------------------------------------------*/
/* ----------------------------------------------*/
/* **register : 0x24 [LIS3MDL_REG_CTRL5]*/
/* for set LIS3MD data type*/
#define LIS3MDL_REG_CTRL5_MASK			(0xC0)
#define LIS3MDL_SET_BLK_READ	 			(0x01<<6)		/* if 1 -> output registers not updated until MSb and LSb have been read*/
#define LIS3MDL_SET_FAST_READ				(0x01<<7)		/* if 1 -> set FAST READ ; default 0*/

/* ----------------------------------------------*/
/* ----------------------------------------------*/
/* **register : 0x30 [LIS3MDL_REG_INT_CFG]*/
/* for set LIS3MD Interrupt config*/
#define LIS3MDL_XINT_EN						(0x80)
#define LIS3MDL_YINT_EN						(0x40)
#define LIS3MDL_ZINT_EN						(0x20)
#define LIS3MDL_INT_ACTIVE					(0x04)		/*BIT3 set "1" active high ; "0" active low*/
#define LIS3MDL_INT_LATCH					(0X02)		/*BIT2 set "1" not latched ; "0" latched ; if latched , release INT pin ->read  Reg:0x31*/
#define LIS3MDL_INT_EN						(0x00)		/*BIT1 set "1" enable INT pin function */

#define LIS3MDL_REG_INT_CFG_MASK			(0xEF)
/* ----------------------------------------------*/
/* ------------- DEFINE LIS3MDL Parameter -------------*/

/* ------------- DEFINE LIS3MDL Variable -------------*/
typedef struct LIS3MDL_AXIS_S
{
	INT16S	X_AXIS;
	INT16S	Y_AXIS;
	INT16S	Z_AXIS;
	INT16S	TEMPERARUTE;

}LIS3MDL_AXIS;


/* ------------- DEFINE LIS3MDL Variable -------------*/





/*********************************************************************************************************/
/*SET CONFIG Parameter*/
/*
	**Function LIS3MDL_SET_MODE_SPEED use
	can use  LIS3MDL_HIGH_SPEED	;	LIS3MDL_SELF_TEST   
	enum     LIS3MDL_XY_AXIS_RUN_MODE_ENUM	;	LIS3MDL_DATA_RATE_ENUM
*/
#define LIS3MDL_SET_X_Y_RUN_MODE				(0x00 |LIS3MDL_XY_HIGH_PERFORMANCE_MODE |DATA_RATE_10HZ | LIS3MDL_ENA_TEMPERATURE)


/*
	**Function   use  LIS3MDL_SET_SWRESET
	must use LIS3MDL_REG_CTRL2_MASK
*/
#define LIS3MDL_SET_RESET						(0x00 & LIS3MDL_REG_CTRL2_MASK | 0x04)		/*	enable sw reset */


/*
	**Function   use  LIS3MDL_SET_SCALE
	must use LIS3MDL_REG_CTRL2_MASK
*/
#define LIS3MDL_SET_SCALE_MODE				(0x00 & LIS3MDL_REG_CTRL2_MASK |LIS3MDL_8_GAUSS)		/* set Scale*/


/*
	**Function LIS3MDL_SET_SYSTEM_RUN_MODE use
	can use  LIS3MDL_REG_CTRL3_MASK	;	 LIS3MDL_LOW_POWER_MODE   
	enum     LIS3MDL_SYSTEM_MODE_ENUM
*/
#define LIS3MDL_SET_SYSTEM_MODE				(0x00 & LIS3MDL_REG_CTRL3_MASK |LIS3MDL_SINGLE_CONVER_MODE)


/*
	**Function LIS3MDL_SET_SYSTEM_MODE_POWER_DOWN use
	enum     LIS3MDL_SYSTEM_MODE_ENUM
*/
#define LIS3MDL_SET_SYSTEM_POWER_DOWN	(0x00 & LIS3MDL_REG_CTRL3_MASK |LIS3MDL_POWER_DOWN_MODE_1)


/*
	**Function LIS3MDL_SET_MODE_SPEED use
	can use  LIS3MDL_REG_CTRL4_MASK	;	 LIS3MDL_DATA_DATA_ENDIAN   
	enum     LIS3MDL_Z_AXIS_RUN_MODE_ENUM
*/
#define LIS3MDL_SET_Z_RUN_MODE				(0x00 & LIS3MDL_REG_CTRL4_MASK |LIS3MDL_Z_HIGH_PERFORMANCE_MODE)


/*
	**Function LIS3MDL_SET_READ_DATA_TYPE use
	can use  LIS3MDL_REG_CTRL5_MASK	;  LIS3MDL_SET_BLK_READ ; LIS3MDL_SET_FAST_READ
*/
#define LIS3MDL_SET_READ_DATA_TYPE			(0x00 & LIS3MDL_REG_CTRL5_MASK |LIS3MDL_SET_BLK_READ)


/*
	**Function LIS3MDL_SET_INT_CONFIG use
	can use  LIS3MDL_REG_INT_CFG_MASK
	LIS3MDL_XINT_EN ; LIS3MDL_YINT_EN ; LIS3MDL_ZINT_EN ;
	LIS3MDL_INT_ACTIVE ; LIS3MDL_INT_LATCH ; LIS3MDL_INT_EN
*/
#define LIS3MDL_SET_INT_CFG						(0x00 & LIS3MDL_REG_INT_CFG_MASK|LIS3MDL_XINT_EN|LIS3MDL_YINT_EN|LIS3MDL_ZINT_EN |LIS3MDL_INT_EN)
/*********************************************************************************************************/



/********************************************* SYSTEM *************************************************/
/*------------------------------------------------------------------------------------------------------*/
/* initial LIS3MDL*/
CHAR8S LIS3MDL_SET_INITIAL(void);
/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/* get LIS3MDL id */
/* must be ID = 0x3D*/
CHAR8S LIS3MDL_GET_ID(CHAR8U *id);
/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/* LIS3MDL SOFTWARE reset */
/* use define LIS3MDL_SET_RESET set reset*/
CHAR8S LIS3MDL_SET_SWRESET(void);
/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/* LIS3MDL set mode & data rate & enable temperature*/
/* use define LIS3MDL_SET_X_Y_RUN_MODE set mode & data rate*/
/* use define LIS3MDL_SET_Z_RUN_MODE set mode & data rate*/
CHAR8S LIS3MDL_SET_MODE_SPEED(void);
/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/* LIS3MDL set scale*/
/* use define LIS3MDL_SET_SCALE set mode & data rate*/
CHAR8S LIS3MDL_SET_SCALE(void);
/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/* LIS3MDL set system mode*/
/* use define LIS3MDL_SET_SYSTEM_MODE set system mode*/
/* LIS3MDL set system mode -> Single-conversion mode ; do one measurement & done -> turn Power down mode [Idle mode]*/
CHAR8S LIS3MDL_SET_SYSTEM_RUN_MODE(void);
/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/*LIS3MDL set system mode -> power down mode [Idle mode]*/
CHAR8S LIS3MDL_SET_SYSTEM_MODE_POWER_DOWN(void);
/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/* LIS3MDL set the [BDU] Block data update  Enable*/
/* use define LIS3MDL_SET_READ_DATA_TYPE	set  read data type*/
CHAR8S LIS3MDL_LIS3MDL_SET_READ_DATA_TYPE(void);
/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/*
	get LIS3MDL status
	use define LIS3MDL_REG_STATUS get status
	if data_status return   0x01 -> XYZ data ready
	if data_status return   0xF0 -> XYZ data not ready
*/
CHAR8S LIS3MDL_GET_STATUS(CHAR8U *data_status);
/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/*
	****** use Register status LIS3MDL_REG_STATUS [0x27] to get data
	LIS3MDL get X Y Z axis data  & Temperautre data
	if data status not ready -> return -4
*/
CHAR8S LIS3MDL_GET_XYZ_AXIS_DATA_USE_STATUS(INT16S *data);
/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/*
	****** use output pin DRDY pin [pin 8] to get data
	****** detail use  see EXAMPLE_LIS3MDL
	LIS3MDL get X Y Z axis data  & Temperautre data
	if data status not ready -> return -4
*/
CHAR8S LIS3MDL_GET_XYZ_AXIS_DATA_USE_DRDY_PIN(INT16U *data);
/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/* LIS3MDL set interrput pin & config*/
/* use define LIS3MDL_SET_INT_CFG set interrput config*/
CHAR8S LIS3MDL_SET_INT_CONFIG(void);
/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/*
	LIS3MDL set Interrupt threshold
	set the Interrupt threshold //The value is expressed in 16-bit unsigned.
	use LIS3MDL_REG_INT_THS_L[0x32]   ->  LOW byte THS value.
	LIS3MDL_REG_INT_THS_H[0x33]   ->  HIGH byte THS value.
*/	
CHAR8S LIS3MDL_SET_INT_THD_VALUE(INT16U thd_data);
/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/* LIS3MDL get interrput status*/
/* the status flag -> set the  LIS3MDL_REG_INT_SRC[0x31] */
CHAR8S LIS3MDL_GET_INT_STATUS(CHAR8U *int_status);
/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/* LIS3MDL self test -> to test IC is good or bad!*/
CHAR8S LIS3MDL_SET_GET_SELF_TEST(void);
/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
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
FLOAT LIS3MDL_GET_AZIMUTH(LIS3MDL_AXIS data);
/*------------------------------------------------------------------------------------------------------*/
/********************************************* SYSTEM **************************************************/

#endif 		/*#ifndef __LIS3MDL_HEADER__ */
