/*
================================================
ABElectronics UK ADC-DAC Pi
Version 1.1 Updated 21/04/2020
================================================
*/

#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <cstring>
#include <stdexcept>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include "ABE_ADCDACPi.h"

#define adcdevice "/dev/spidev0.0"
#define dacdevice "/dev/spidev0.1"

using namespace ABElectronics_CPP_Libraries;



ADCDACPi::ADCDACPi(){
	mode = SPI_MODE_0; // SPI_MODE_0
	adcspeed = 1100000; // SPI ADC bus speed 1.1MHz
	dacspeed = 20000000; // SPI DAC bus speed 20MHz

	adctx[0] = 0x01; // transmit buffer for the ADC
	adctx[1] = 0x80;
	adctx[2] = 0x00;

	adcrefvoltage = 3.3; // reference voltage for the ADC chip.
	dacgain = 1; // gain setting for the DAC chip.
	dacvoltage = 2.048; // maximum voltage for the DAC output
}

int ADCDACPi::open_adc() {
	/**
	* Open the ADC SPI bus channel
	* This needs to be called before using the ADC
	*/

	// Open SPI device
	if ((adc = open(adcdevice, O_RDWR)) < 0)
		return (0);

	if (ioctl(adc, SPI_IOC_WR_MAX_SPEED_HZ, &adcspeed) == -1)
		return (0);
	// Set SPI mode
	if (ioctl(adc, SPI_IOC_WR_MODE, &mode) == -1)
		return (0);

	return (1);
}

void ADCDACPi::close_adc() {
	/**
	* Close the ADC SPI bus channel
	*/
	close(adc);
}

int ADCDACPi::open_dac() {
	/**
	* Open the DAC SPI bus channel
	* This needs to be called before using the DAC
	*/

	// Open SPI device
	if ((dac = open(dacdevice, O_RDWR)) < 0)
		return (0);

	if (ioctl(dac, SPI_IOC_WR_MAX_SPEED_HZ, &dacspeed) == -1)
		return (0);
	// Set SPI mode
	if (ioctl(dac, SPI_IOC_WR_MODE, &mode) == -1)
		return (0);

	return (1);
}

void ADCDACPi::close_dac() {
	/**
	* Close the DAC SPI bus channel
	*/
	close(dac);
}

double ADCDACPi::read_adc_voltage(uint8_t channel, uint8_t mode) {
	/**
	* Read the voltage from the ADC
	* @param channel - 1 or 2
	* @param mode - 0 = Single Ended or 1 = Differential
	* When in differential mode setting channel to 1 will make IN1 = IN+ and IN2 = IN-
	* When in differential mode setting channel to 2 will make IN1 = IN- and IN2 = IN+
	* @returns between 0V and the reference voltage
	*/

	uint16_t rawval = read_adc_raw(channel, mode);
	return ((adcrefvoltage / 4096) * (double) rawval);
}

uint16_t ADCDACPi::read_adc_raw(uint8_t channel, uint8_t mode) {
	/**
	* Read the raw value from the ADC
	* @param channel -  1 to 8
	* @param mode -  0 = Single Ended or 1 = Differential
	* When in differential mode setting channel to 1 will make IN1 = IN+ and IN2 = IN-
	* When in differential mode setting channel to 2 will make IN1 = IN- and IN2 = IN+
	* @returns 12 bit value between 0 and 4096
	*/

	if (channel == 1) {
		if (mode == 0) {
			adctx[1] = 0x80;
		} else if (mode == 1) {
			adctx[1] = 0x00;
		} else {
			return (0);
		}
	} else if (channel == 2) {
		if (mode == 0) {
			adctx[1] = 0xC0;
		} else if (mode == 1) {
			adctx[1] = 0x40;
		} else {
			return (0);
		}
	} else {
		return (0);
	}

	struct spi_ioc_transfer spi;
	memset(&spi,0,sizeof(spi));

	spi.tx_buf = (uint32_t)adctx;
	spi.rx_buf = (uint32_t)adcrx;
	spi.len = 3;
	spi.speed_hz = adcspeed;
	spi.delay_usecs = 0;
	spi.bits_per_word = 8;


	if (ioctl(adc, SPI_IOC_MESSAGE(1), &spi) == -1)
		return (0);

	return (((adcrx[1] & 0x0F) << 8) + (adcrx[2]));

}

void ADCDACPi::set_adc_refvoltage(double ref) {
	/**
	* Set the reference voltage for the adc
	* @param ref - Set this value to be the same as the voltage measured on the 3.3V GPIO pin
	*/
	adcrefvoltage = ref;
}

void ADCDACPi::set_dac_voltage(double voltage, uint8_t channel) {
	/**
	* Set the DAC voltage
	* @param voltage - between 0 and 2.048 when gain is set to 1,  0 and 3.3 when gain is set to 2
	* @param channel - 1 or 2
	*/
	if (channel < 1 && channel > 2) {
		throw std::out_of_range("set_dac_voltage channel out of range: 1 or 2");
	}

	if ((voltage >= 0.0) && (voltage < dacvoltage)) {
		uint16_t rawval = ((voltage / 2.048) * 4096) / dacgain;
		set_dac_raw(rawval, channel);
	} else {
		throw std::out_of_range("set_dac_voltage voltage out of range");
	}
}

void ADCDACPi::set_dac_raw(uint16_t raw, uint8_t channel) {
	/**
	* Set the raw value from the selected channel on the DAC
	* @param raw - between 0 and 4095
	* @param channel - 1 or 2
	*/

	uint8_t dactx[2];

	dactx[1] = (raw & 0xff);
	dactx[0] = (((raw >> 8) & 0xff) | (channel - 1) << 7 | 0x1 << 5 | 1 << 4);

	if (dacgain == 2) {
		uint16_t x = dactx[0];
        dactx[0] = (x &= ~(1 << 5));
    }

	struct spi_ioc_transfer tr;
    memset(&tr,0,sizeof(tr));

	tr.tx_buf = (uint32_t)&dactx;
	tr.rx_buf = (uint32_t)NULL;
	tr.len = 2;
	tr.speed_hz = dacspeed;
	tr.delay_usecs = 0;
	tr.bits_per_word = 8;
	tr.cs_change = 0;

	// Write data
	if (ioctl(dac, SPI_IOC_MESSAGE(1), &tr) == -1) throw std::runtime_error("error setting dac raw value");;
	return;

}

void ADCDACPi::set_dac_gain(uint8_t gain) {
	/**
	* Set the DAC gain
	* @param gain - 1 or 2 - The output voltage will be between 0 and 2.048V when gain is set to 1,  0 and 3.3V when gain is set to 2
	*/
	if (gain == 1) {
		dacgain = 1;
		dacvoltage = 2.048;
	}
	if (gain == 2) {
		dacgain = 2;
		dacvoltage = 3.3;
	}

}
