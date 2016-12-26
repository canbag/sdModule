# SD Logging module


##About
This Arduino Library is developed for ecospace projects which need to logging their data. This library is logging datas with a custom controlls like;

 - Creates new directory (aka logging group) each running
 - Creates log files with a fixed file size

##Usage


First of all, you have to copy library files to your Documents/Arduino/libraries directory and add to your project file this line for including library.

    #include <sdModule.h>



After including,

    #define SD_CS_PIN  10
    sdModule logging = sdModule(SD_CS_PIN);

This lines have to be before setup block. It have to be inside of setup block.

For initialization, append this line to inside of setup block

    logging.init();

And it is ready to logging, for logging use this method

    logging.add("MERHABA, THIS IS A LOG LINE");


#Configration

Set maximum log file size

    logging.setFileSizeLimit(5);

Set file size checking limit

    logging.setTourLimit(100);


Set error pin, this pin will using for sending error signal a component such as buzzer

    logging.setErrorPin(5);  



#Methods

For defination of log group, you can add information rows. It will be in group directory and its name will be "groupInfo.txt". First parameters of addInfo method is keyword of information; second parameters is value of information.

    logging.addInfo("TEAM","ECOSPACE");
