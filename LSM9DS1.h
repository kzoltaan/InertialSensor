//  LSM9DS1.h
//
//
//  Created by Andrea Vivani on 18/7/15.
//  Copyright (c) 2015 Andrea Vivani. All rights reserved.
//
//======================================Parameters=============================================//
#define LSM9DS1_GYRO_SELF_TEST_MEASURES 10 //number of samples to be averaged when performing gyroscope self-test
#define LSM9DS1_ACCEL_SELF_TEST_MEASURES 10 //number of samples to be averaged when performing accelerometer self-test
#define LSM9DS1_MAG_SELF_TEST_MEASURES 10 //number of samples to be averaged when performing magnetometer self-test
#define LSM9DS1_DISCARDED_MEASURES	5	//number of measures to be discarded when performing automatic tasks (greater than 1, preferably even)
#define LSM9DS1_DISCARDED_MEASURES_ST 10 //number of measures to be discarded after performing self-tests (greater than 1, preferably even)
#define LSM9DS1_DISCARD_TIMEOUT		2e6 //timeout time in us between measures when discarding
//=====================================ODR Values Gyro===============================================//
#define LSM9DS1_ODR_G_14_9_CO_N		0x20
#define LSM9DS1_ODR_G_59_5_CO_16	0x40
#define LSM9DS1_ODR_G_119_CO_14		0x60
#define LSM9DS1_ODR_G_119_CO_31		0x63
#define LSM9DS1_ODR_G_238_CO_14		0x80
#define LSM9DS1_ODR_G_238_CO_29		0x81
#define LSM9DS1_ODR_G_238_CO_63		0x82
#define LSM9DS1_ODR_G_238_CO_78		0x83
#define LSM9DS1_ODR_G_476_CO_21		0xA0
#define LSM9DS1_ODR_G_476_CO_28		0xA1
#define LSM9DS1_ODR_G_476_CO_57		0xA2
#define LSM9DS1_ODR_G_476_CO_100	0xA3
#define LSM9DS1_ODR_G_952_CO_33		0xC0
#define LSM9DS1_ODR_G_952_CO_40		0xC1
#define LSM9DS1_ODR_G_952_CO_58		0xC2
#define LSM9DS1_ODR_G_952_CO_100	0xC3
//====================================Range Values Gyro==============================================//
#define LSM9DS1_RANGE_G_245			0x00
#define LSM9DS1_RANGE_G_500			0x08
#define LSM9DS1_RANGE_G_2000		0x18
//====================================ODR Values Accel===============================================//
#define LSM9DS1_ODR_A_10			0x20
#define LSM9DS1_ODR_A_50			0x40
#define LSM9DS1_ODR_A_119			0x60
#define LSM9DS1_ODR_A_238			0x80
#define LSM9DS1_ODR_A_476			0xA0
#define LSM9DS1_ODR_A_952			0xC0
//====================================Range Values Accel=============================================//
#define LSM9DS1_RANGE_A_2			0x00
#define LSM9DS1_RANGE_A_4			0x10
#define LSM9DS1_RANGE_A_8			0x18
#define LSM9DS1_RANGE_A_16			0x08
//======================================Low-Pass Accel===============================================//
#define LSM9DS1_LP_A_408			0x00
#define LSM9DS1_LP_A_211			0x01
#define LSM9DS1_LP_A_105			0x02
#define LSM9DS1_LP_A_50				0x03
//=====================================High-Pass Accel===============================================//
#define LSM9DS1_HP_A_ODR_50			0x00
#define LSM9DS1_HP_A_ODR_100		0x20
#define LSM9DS1_HP_A_ODR_9			0x40
#define LSM9DS1_HP_A_ODR_400		0x60
//=======================================ODR Values Mag==============================================//
#define LSM9DS1_ODR_M_0_625			0x00
#define LSM9DS1_ODR_M_1_25			0x04
#define LSM9DS1_ODR_M_2_5			0x08
#define LSM9DS1_ODR_M_5				0x0C
#define LSM9DS1_ODR_M_10			0x10
#define LSM9DS1_ODR_M_20			0x14
#define LSM9DS1_ODR_M_40			0x18
#define LSM9DS1_ODR_M_80			0x1C
//=====================================Range Values Mag==============================================//
#define LSM9DS1_RANGE_M_4			0x00
#define LSM9DS1_RANGE_M_8			0x20
#define LSM9DS1_RANGE_M_12			0x40
#define LSM9DS1_RANGE_M_16			0x60

#ifndef LSM9DS1_H_
#define LSM9DS1_H_
#include "InertialSensor.h"
#include <SPI.h>

class LSM9DS1: public InertialSensor{
	public:
		LSM9DS1 (uint8_t CS_pin_XG, uint8_t CS_pin_M);	//constructor
		LSM9DS1 (uint8_t CS_pin_XG, uint8_t CS_pin_M, uint8_t DRDY_pin_G, uint8_t DRDY_pin_A, uint8_t DRDY_pin_M);	//constructor with Data ready pin
		virtual void init(); //initializes pins and variables
		float gx,gy,gz;	//gyroscope output data
		float ax,ay,az;	//accelerometer output data
		float mx,my,mz;	//magnetometer output data
		float temperature; //temperature value
		//==================Gyroscope==================//
		uint8_t config_accel_gyro(uint8_t gyro_range, uint8_t gyro_odr, uint8_t LPF2_enable_gyro, uint8_t HP_enable_gyro, uint8_t HP_freq_gyro, uint8_t accel_range, uint8_t accel_odr, uint8_t LPF_enable_accel, uint8_t LPF_freq_accel, uint8_t HP_enable_accel, uint8_t HP_freq_accel); //configure the gyroscope and the accelerometer
		virtual void turn_on_gyro(); //turn on the gyroscope
		virtual void turn_off_gyro(); //turn off the gyroscope
		virtual void sleep_gyro(); //put the gyroscope to sleep
		virtual inline uint8_t read_gyro(uint32_t timeout){return read_gyro_STATUS(timeout);}; //default read method from gyroscope, timeout in us
		uint8_t read_raw_gyro(); //read data from gyroscope registers
		uint8_t read_gyro_DRDY(uint32_t timeout); //read data from gyroscope if DRDY is high, timeout in us
		uint8_t read_gyro_STATUS(uint32_t timeout); //read data from gyroscope if available (reads the status register). timeout in us
		virtual uint8_t check_gyro_biases(float bx, float by, float bz); //check if gyro biases are within reasonable limits, according to datasheet
		void HP_reset_gyro(); //resets the High-Pass filter
		uint8_t self_test_gyro(); //self-test
		uint8_t status_gyro(); //returns the value of the status register
		virtual uint8_t discard_measures_gyro(uint8_t number_of_measures, uint32_t timeout); //discards the first n measures after being called, timeout in us
		//===============Accelerometer================//
		virtual void turn_on_accel(); //turn on the accelerometer
		virtual void turn_off_accel(); //turn off the accelerometer
		virtual inline uint8_t read_accel(uint32_t timeout){return read_accel_STATUS(timeout);}; //default read method for accelerometer, timeout in us
		uint8_t read_raw_accel(); //read data from accelerometer registers
		uint8_t read_accel_DRDY(uint32_t timeout); //read data from accelerometer if DRDY is high, timeout in us
		uint8_t read_accel_STATUS(uint32_t timeout); //read data from gyroscope if available (reads the status register), timeout in us
		virtual uint8_t check_accel_biases(float bx, float by, float bz); //check if accel biases are within reasonable limits, according to datasheet
		void HP_reset_accel(); //resets the High-Pass filter
		uint8_t self_test_accel(); //self-test
		uint8_t status_accel(); //returns the value of the status register
		virtual uint8_t discard_measures_accel(uint8_t number_of_measures, uint32_t timeout); //discards the first n measures after being called. timeout in us
		//===============Magnetometer=================//
		uint8_t config_mag(uint8_t range_conf, uint8_t odr_conf); //configure the magnetometer
		virtual void turn_on_mag(); //turn on the magnetometer
		virtual void turn_off_mag(); //turn off the magnetometer
		virtual inline uint8_t read_mag(uint32_t timeout){return read_mag_STATUS(timeout);}; //default read method for magnetometer, timeout in us
		uint8_t read_raw_mag(); //read data from magnetometer registers
		uint8_t read_mag_DRDY(uint32_t timeout); //read data from magnetometer if DRDY is high, timeout in us
		uint8_t read_mag_STATUS(uint32_t timeout); //read data from gyroscope if available (reads the status register), timeout in us
		uint8_t self_test_mag(); //self-test
		uint8_t status_mag(); //returns the value of the status register
		virtual uint8_t discard_measures_mag(uint8_t number_of_measures, uint32_t timeout); //discards the first n measures after being called, timeout in us
		//================Temperature=================//
		virtual void turn_on_thermo(){return turn_on_mag();}; //turn on the thermometer
		virtual void turn_off_thermo(){return;}; //turn off the thermometer
		virtual inline uint8_t read_thermo(uint32_t timeout){return read_raw_thermo();}; //default read method for thermometer 
		uint8_t read_raw_thermo(); //read data from thermometer registers
		uint8_t read_thermo_DRDY(uint32_t timeout); //read temperature when DRDY is high (same INT2 and ODR as magnetometer), timeout in us
		uint8_t read_thermo_STATUS(uint32_t timeout); //read data from thermometer if available (reads the status register), timeout in us
		virtual uint8_t discard_measures_thermo(uint8_t number_of_measures, uint32_t timeout); //discards the first n measures after being called, timeout in us
	private:
		float _sc_fact_g, _sc_fact_a, _sc_fact_m;		//scale factors
		uint8_t _chipSelectPin_XG, _chipSelectPin_M, _DRDY_pin_G, _DRDY_pin_A, _DRDY_pin_M;	//ChipSelectPin and Data Ready pin
		uint8_t _CTRL1_val_XG, _CTRL6_val_XL, _CTRL3_val_M; //values of the register used when powering up and down the sensor
		uint8_t readRegister(uint8_t chipSelectPin, uint8_t thisRegister);
		void readMultipleRegisters_M(uint8_t chipSelectPin, uint8_t* buffer, uint8_t number_of_registers, uint8_t startRegister);
		void readMultipleRegisters(uint8_t chipSelectPin, uint8_t* buffer, uint8_t number_of_registers, uint8_t startRegister);
		void writeRegister(uint8_t chipSelectPin, uint8_t thisRegister, const uint8_t thisValue);
		uint8_t ch_st (const double val1, const double val2, const double lim1, const double lim2);
};
#endif