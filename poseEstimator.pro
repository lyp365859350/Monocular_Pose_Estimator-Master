TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /usr/local/include \
                /usr/local/include/opencv \
                /usr/local/include/opencv2 \
                /usr/include/eigen3\

LIBS += -L/usr/local/lib -lopencv_calib3d -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_ocl -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab -lrt -lpthread -lm -ldl

SOURCES += \
    monocular_pose_estimator_lib/visualization.cpp \
    monocular_pose_estimator_lib/pose_estimator.cpp \
    monocular_pose_estimator_lib/p3p.cpp \
    monocular_pose_estimator_lib/led_detector.cpp \
    monocular_pose_estimator_lib/combinations.cpp \
    main.cpp

HEADERS += \
    monocular_pose_estimator_lib/visualization.h \
    monocular_pose_estimator_lib/pose_estimator.h \
    monocular_pose_estimator_lib/p3p.h \
    monocular_pose_estimator_lib/led_detector.h \
    monocular_pose_estimator_lib/datatypes.h \
    monocular_pose_estimator_lib/combinations.h \
