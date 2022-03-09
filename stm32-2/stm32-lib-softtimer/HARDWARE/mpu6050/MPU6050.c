#include "MPU6050.h"
#include "math.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"

float Pose[3];//×ËÌ¬
short Gyro[3];//ÍÓÂÝÒÇ
short Accel[3];//¼ÓËÙ¶È

static signed char gyro_orientation[9] = {-1, 0, 0,
                                           0,-1, 0,
                                           0, 0, 1};													 																			 
																				 
unsigned short inv_row_2_scale(const signed char *row)
{
    unsigned short b;

    if (row[0] > 0)
        b = 0;
    else if (row[0] < 0)
        b = 4;
    else if (row[1] > 0)
        b = 1;
    else if (row[1] < 0)
        b = 5;
    else if (row[2] > 0)
        b = 2;
    else if (row[2] < 0)
        b = 6;
    else
        b = 7;      // error
    return b;
}

static  unsigned short inv_orientation_matrix_to_scalar(
    const signed char *mtx)
{
    unsigned short scalar;

    /*
       XYZ  010_001_000 Identity Matrix
       XZY  001_010_000
       YXZ  010_000_001
       YZX  000_010_001
       ZXY  001_000_010
       ZYX  000_001_010
     */

    scalar = inv_row_2_scale(mtx);
    scalar |= inv_row_2_scale(mtx + 3) << 3;
    scalar |= inv_row_2_scale(mtx + 6) << 6;


    return scalar;
}

static void run_self_test(void)
{
    int result;
//    char test_packet[4] = {0};
    long gyro[3], accel[3];

    result = mpu_run_self_test(gyro, accel);
    if (result == 0x7) {
        /* Test passed. We can trust the gyro data here, so let's push it down
         * to the DMP.
         */
        float sens;
        unsigned short accel_sens;
        mpu_get_gyro_sens(&sens);
        gyro[0] = (long)(gyro[0] * sens);
        gyro[1] = (long)(gyro[1] * sens);
        gyro[2] = (long)(gyro[2] * sens);
        dmp_set_gyro_bias(gyro);
        mpu_get_accel_sens(&accel_sens);
        accel[0] *= accel_sens;
        accel[1] *= accel_sens;
        accel[2] *= accel_sens;
        dmp_set_accel_bias(accel);
	//	PrintChar("setting bias succesfully ......\n");
    }
	else
	{
	//	PrintChar("bias has not been modified ......\n");
	}
}




void MPU6050_initialize(void) //³õÊ¼»¯
{
	int result;
	
	i2cInit();//IIC×ÜÏßµÄ³õÊ¼»¯
	result = mpu_init();
  if(!result)
  {
	  	//mpu_set_sensor
	mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL);
	//mpu_configure_fifo
	mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL);
    //mpu_set_sample_rate
    mpu_set_sample_rate(DEFAULT_MPU_HZ);
    //dmp_load_motion_driver_firmvare
	dmp_load_motion_driver_firmware();
	//dmp_set_orientation
	dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_orientation));
	//dmp_enable_feature
	dmp_enable_feature(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_TAP |
	        DMP_FEATURE_ANDROID_ORIENT | DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO |
	        DMP_FEATURE_GYRO_CAL);
	//dmp_set_fifo_rate
	dmp_set_fifo_rate(DEFAULT_MPU_HZ);
	run_self_test();
    mpu_set_dmp_state(1);
  }
}

float Pitch,Roll,Yaw;
void MPU6050_Pose(float *pose ,short *gyro,short *accel)
{
	#define q30  1073741824.00f
	float q0=1.00f,q1=0.00f,q2=0.00f,q3=0.00f;
//	float Pitch,Roll,Yaw;
	unsigned long sensor_timestamp;
	short sensors;
	unsigned char more;
	long quat[4];
	dmp_read_fifo(gyro, accel, quat, &sensor_timestamp, &sensors,&more);	
	
	if (sensors & INV_WXYZ_QUAT )//×ËÌ¬Á¿
	 {
			// PrintChar("in Calculating quaternion steps.....\n");
			q0=quat[0] / q30;
			q1=quat[1] / q30;
			q2=quat[2] / q30;
			q3=quat[3] / q30;
			Pitch  = asin(-2 * q1 * q3 + 2 * q0* q2)* 57.30f; // pitch
			Roll = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* 57.30f; // roll
			Yaw = 	atan2(2*(q1*q2 + q0*q3),q0*q0+q1*q1-q2*q2-q3*q3) * 57.30f;
		//	Yaw+=gyro[3]*0.002f;
			pose[0] = Pitch;//¸©Ñö ÈÆYÖá
			pose[1] = Roll;//ºá¹ö ÈÆXÖá
			pose[2] = Yaw;//º½Ïò ÈÆZÖá
		 
			

		//	UART1_ReportIMU((int)(Yaw*10),(int)(Pitch*10),(int)(Roll*10),1,1,1,100);
	 }
	
}

