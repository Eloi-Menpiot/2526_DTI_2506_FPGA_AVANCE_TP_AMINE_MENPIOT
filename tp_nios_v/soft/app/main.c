#include <stdio.h>
#include <unistd.h> // for usleep

#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "altera_avalon_i2c.h"



//chenillard
/*
int main (void)
{
	u_int chenillard;
	useconds_t usec = 100000;
	while(1){
		chenillard = 0x1;
		for(int i = 0; i<10; i++){
			IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, chenillard);
			chenillard = chenillard << 1;
			usleep(usec);
		}
	}
}
*/

int main()
{
	uint8_t rxbuffer[6];
	int16_t x, y, z;
	uint8_t txbuffer1[1];
	uint8_t txbuffer[2];
	ALT_AVALON_I2C_DEV_t * i2c_dev = alt_avalon_i2c_open("/dev/i2c_0");
	uint8_t accelerometer_en = 0x0;
	uint8_t id = 0x0;

	alt_avalon_i2c_master_target_set(i2c_dev, 0x1D);

	printf("Hello World!\n");
	printf("Heh\n");
	txbuffer1[0] = 0x00;
	alt_avalon_i2c_master_tx_rx(i2c_dev, txbuffer1, 1, rxbuffer, 1, ALT_AVALON_I2C_NO_INTERRUPTS);
	id = rxbuffer[0];
	
	printf("WAAAAAAAAAOO!\n");
	printf("id : %d\n\n",id);

	
	txbuffer[0] = 0x2D;
	txbuffer[1] = 0x1;
	while(accelerometer_en==0x0){
		alt_avalon_i2c_master_tx(i2c_dev, txbuffer, 2, ALT_AVALON_I2C_NO_INTERRUPTS);
		alt_avalon_i2c_master_tx_rx(i2c_dev, txbuffer, 1, rxbuffer, 1, ALT_AVALON_I2C_NO_INTERRUPTS);
		accelerometer_en = rxbuffer[0];
	}

	txbuffer[0] = 0x32;
	while(1){
		alt_avalon_i2c_master_tx_rx(i2c_dev, txbuffer, 1, rxbuffer, 6, ALT_AVALON_I2C_NO_INTERRUPTS);
		x = (rxbuffer[1] << 8) + rxbuffer[0];
		y = (rxbuffer[3] << 8) + rxbuffer[2];
		z = (rxbuffer[5] << 8) + rxbuffer[4];

		printf("x = %d \ny = %d \nz = %d \n\n",(int) x,(int) y,(int) z);
	}
}
