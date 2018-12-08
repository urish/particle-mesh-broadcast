# particle-mesh-broadcast

Example of how to broadcast messages received from the local WiFi over the local mesh network of Particle devices (using UDP).

## How does it work?

This example consists of two parts:

* `mesh_sender` - Sets up a simple UDP server running on port 8888 of your Argon device. It then forwards any incoming packet into the mesh network, broadcasting it to the multicast address `ff03::1:1001` on UDP port 31313
* `mesh_listener` - Runs on your end devices, and listens for UDP packets on port 31313 of the above multicast address. It prints the contents of any incoming packet to the Serial console

## Running the example

You will need one Argon and one (or more) Xenon devices.

Flash `mesh_sender` to your Argon device, and `mesh_listener` to your Xenon device(s).

Then, connect one of your Xenon devices to the PC via USB, and monitor its serial port using the [Particle CLI](https://docs.particle.io/tutorials/developer-tools/cli/):

    particle monitor --follow

Make sure your Argon device is connected to WiFi, find its IP address and then use the following command to send a UDP packet to your Argon:

    particle udp send 192.168.1.106 8888 "It works!"

Replace `192.168.1.106` above with the actual IP address of your Argon device.

You should see the following message appearing on your Xenon monitoring console:

    Got packet: It works!

Congratulations! You have successfully broadcasted a message over your mesh network.

## License

Copyright (C) 2018, Uri Shaked. Released under the LGPL license. 

Parts of this example are based on code found in the [particle-iot](https://github.com/particle-iot/firmware/blob/cdf25a93f9b6283a0907e2fa5afe259d56dd6594/wiring/inc/spark_wiring_mesh.h) firwmare.
