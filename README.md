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
