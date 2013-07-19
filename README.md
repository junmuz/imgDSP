
1)	Compile the sample project opencvtest.c or mo.c by the following command. Make sure PATH contains the cross compilation tool chain

	arm-none-linux-gnueabi-g++ -o imgDSP imgDSP.c -I /usr/local/include/opencv -L /usr/local/lib /usr/local/lib/libhighgui.a /usr/local/lib/libcvaux.a /usr/local/lib/libcv.a  /usr/local/lib/libcxcore.a /opt/arm_davinci/arm-none-linux-gnueabi/lib/libz.a /opt/arm_davinci/arm-none-linux-gnueabi/lib/libjpeg.a /opt/arm_davinci/arm-none-linux-gnueabi/lib/libpng.a /opt/arm_davinci/arm-none-linux-gnueabi/libc/usr/lib/libpthread.a /opt/arm_davinci/arm-none-linux-gnueabi/libc/usr/lib/librt.a
