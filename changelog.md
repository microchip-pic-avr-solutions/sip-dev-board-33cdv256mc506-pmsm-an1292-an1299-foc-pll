# sip-dev-board-33cdv256mc506-pmsm-an1292-an1299-foc-pll v1.0.0
### Release Highlights
This is the first version of code for sensorless field oriented control of PMSM using PLL estimator and Single-Shunt Current Reconstruction Algorithm on the hardware platform dsPIC33CDV256MC506 Motor Control Development Board[(EV97M58A)](https://www.microchip.com/en-us/development-tool/ev97m58a).

The code is set up for running Hurst075 Motor(DMB0224C10002 - [AC300020](https://www.microchip.com/en-us/development-tool/AC300020))
The motor is tested under no load conditions. To achieve optimal performance under loaded conditions, the control parameters in the firmware may need additional tuning.


### Features Added\Updated

- Supports Dual-Shunt(phase shunts) and Single-Shunt(bus shunt) current measurement schemes
- Assigned functions of push buttons and potentiometer in the firmware:
	1. Push Button #1(SW1) starts and stops motor. 
	2. Potentiometer (POT1) controls the speed of the motor
	2. Push Button #2(SW2) moves the motor speed range to the field weakening(above base speed) range
- DC Bus current protection using dsPIC® features such as PWM PCI, comparator and DAC
- The application configures and uses peripherals like PWM, ADC, OP-AMP, CMP, DAC and UART
