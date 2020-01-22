# 2019_MOSH_B1_XUANTANG_HUIJIE_ZHE
This project aims to develop a dangerous gas detecting system, whose buzzer will alarm as soon as the gas index is higher than the warning line. The system includes programming the software based on Arduino, sending the data of gas sensor to TTN platform via LoRa, using Node-Red to display our data on a graphical interface and finally designing the PCB board by Kicad. 
 
 Documents in attachment
- Arduino Software files 
- Kicad files 
- Node-Red dashboard

## Arduino
Components:
- An Arduino uno board
- A Lora chip RN2483A
- A Grove Gas Sensor
- A buzzer
![avatar](https://github.com/MOSH-Insa-Toulouse/2019_MOSH_B1_XUANTANG_HUIJIE_ZHE/blob/master/pic/arduino.jpg "Figure 1: Arduino")

With Arduino, we achieve to make a detecting system that when the gas index is higher than our standard, the buzzer will alarm. The code is in the folder.
After the soldering of the LoRa chip RN2483A, we succeed in communicating with the TTN platform, here is the screenshot of TTN:

![avatar](https://github.com/MOSH-Insa-Toulouse/2019_MOSH_B1_XUANTANG_HUIJIE_ZHE/blob/master/pic/ttn.PNG "Figure 2: ttn data")

![avatar](https://github.com/MOSH-Insa-Toulouse/2019_MOSH_B1_XUANTANG_HUIJIE_ZHE/blob/master/pic/ttn_data_payload.PNG "Figure 3: ttn data payload")

Energy Consumption
To reduce the energy consumption, we decide to decrease the frequency of transmitting by sending data only when the gas index is higher than a seuil, otherwise, the LoRa system is in sleep mode. The energy consumption befor is 1.5W, and now the energy consumption reduced to 1.1W.

Node-Red
Finally, we did a dashboard by Node-Red, retrieving the data from TTN platform.
![avatar](https://github.com/MOSH-Insa-Toulouse/2019_MOSH_B1_XUANTANG_HUIJIE_ZHE/blob/master/pic/node-red.JPG "Figure 4: flow of node-red")


## kicad

In order to establish the best circuit between the LoRa module and the gas sensor introduced in the MOSH section above, we have drawn the following circuit diagram, which includes our components: a LoRa Module (RN2483) as transceiver, a Gas sensor, an amplifier (LTC1050) and two connector.

![avatar](https://github.com/MOSH-Insa-Toulouse/2019_MOSH_B1_XUANTANG_HUIJIE_ZHE/blob/master/pic/circuit_diagram.jpg "Figure 5: Diagram of the shield's electrical circuit")

After the electrical diagram is completed, the different components must be packaged and integrated on a board. This is a complicated process, we have to consider the placement of components and the problem of circuit connection. The principle is to make the connection as simple as possible, without interleaving, and to ensure the safety of the circuit based on the correct circuit connection. Our results are as follows:

![avatar](https://github.com/MOSH-Insa-Toulouse/2019_MOSH_B1_XUANTANG_HUIJIE_ZHE/blob/master/pic/PCB.jpg "Figure 6: Printed circuit board 1")

We used two layers of circuits, the lower layer was connected to ground, the voltage was zero, and the upper layer was a circuit connected to other components.
![avatar](https://github.com/MOSH-Insa-Toulouse/2019_MOSH_B1_XUANTANG_HUIJIE_ZHE/blob/master/pic/PCB_2.jpg "Figure 7: Printed circuit board 2")

Here is the final 3d model of our results:
![avatar](https://github.com/MOSH-Insa-Toulouse/2019_MOSH_B1_XUANTANG_HUIJIE_ZHE/blob/master/pic/3D.jpg "Figure 8: 3D Model")


## Part LTSpice

The stage is composed of several filters and an operational amplifier. We used LTSpice to simulate the analog circuit.
![avatar](https://github.com/MOSH-Insa-Toulouse/2019_MOSH_B1_XUANTANG_HUIJIE_ZHE/blob/master/pic/ltspice.JPG "Figure 9: Ltspice")

#### Question 1: check the operation in nominal conditions
Normally, the circuit amplify with a gain equals 100.
#### Question 2:  is the impact of the LTC1050C amplifier offset acceptable ?
The offset of input is 0.5mv, with our gain of 100, the offset of output 50mv which make 1 digit error in the 12 bits ADC.
#### Question 3:  is the impact of the amplifier input current acceptable ?
With the data sheet of ltc1050, we got the input noise current is 1.8fA/sqrt(HZ). So with a signal of 1KHz, we have an erreur 5.6E-14 << 1E-9 

#### Question 4:  what is the cutoff frequency of each low-pass filter stage?
stage 1: 15.9Hz
stage 2: 1.59Hz
stage 3: 1.59KHz
#### Question 5 : What is the global attenuation of a 50 Hz current noise ?
The global attenuation equals 40 dB of 50Hz current noise.

#### Question 6 : What is the global attenuation of a current noise occurring at the aliasing limit frequency (in the case of Arduino Uno ADC) ?
For a 16MHz Arduino, the ADC clock is set to 16MHz/128=125KHz. Each conversion takes 13 ADC clocks so 125KHz/13 = 9615Hz. At this frequency, we have an attenuation of 115 dB.