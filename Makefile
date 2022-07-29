tp1: control.o fonctionprincipale.o main.o
	g++ -o tp1 control.o fonctionprincipale.o main.o -I/usr/local/include/opencv -I/usr/local/include -L/usr/local/lib -lopencv_shape -lopencv_stitching -lopencv_objdetect -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_ml -lopencv_imgproc -lopencv_flann -lopencv_core
control.o: control.cpp
	g++ -Wall -g -c control.cpp -o control.o `pkg-config opencv --cflags --libs`
fonctionprincipale.o: fonctionprincipale.cpp
	g++ -Wall -g -c fonctionprincipale.cpp -o fonctionprincipale.o `pkg-config opencv --cflags --libs`
main.o: main.cpp
	g++ -Wall -g -c main.cpp -o main.o `pkg-config opencv --cflags --libs`
clean:
	rm -f *.o ctimage
