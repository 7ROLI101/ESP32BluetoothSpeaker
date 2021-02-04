# ESP32BluetoothSpeaker  
This is a project that I wanted to do for a long time coming. I recently created a Class A audio amplifier for my Kenwood LSK-02S speaker that I had at home, and I was thinking about creating a PCB for it. However, I felt like making a Bluetooth speaker instead, since I was in need of one and I felt that it would have been a great chance to learn about the Bluetooth stack. I decided to use the ESP32 as the microcontroller I would use to accomplish this, since Bluetooth and WiFi are both integrated onto the ESP32.    

    Looking through the EspressIF's (the creators of the ESP32) github, I found example code showing exactly how you can use the Bluetooth API to create a simple Bluetooth speaker with bare minimum capabilities, which was exactly what I was looking for (a simple Bluetooth speaker setup). However, I was looking through the code and found the documentation (the comments explaining what the code does) lackluster, to say the least. It was really hard for me to go through the documentation, especially since this was my first time using the Bluetooth stack, and using concepts like callback functions.  
    
    Currently, I am using the ESP-IDF'S Bluetooth API and the code given by the EspressIF example I found on their Github (called a2dp_sink) to create my application. The EspressIF example gives options for enabling things like outputting to the internal DAC (8 bit) vs outputting with I2S(options of 8 bit, 16 bit, 32 bit).  
     
     Instead of giving options to the user using the sdkconfig file (which can be edited directly or by using the command line, changing directory to the current project and then running idf.py menuconfig), I am going to be writing the code to suit my application purposes (in my case, I would be using I2S with an exernal I2S decoder and an amplifier to produce the sound). 
