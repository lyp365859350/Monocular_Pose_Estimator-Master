# Monocular_Pose_Estimator-Master
基于非共面、非对称的三维关键点的目标对象姿态估计（输入点的数量不少于4个）

本程序是将 https://github.com/uzh-rpg/rpg_monocular_pose_estimator 中基于ROS的工程，提取出来的结果

## 运行环境
ubuntu14.04/16.04、Qtcreator

工程下载后，用QT打开“poseEstimator.pro文件，修改里面的”INCLUDEPATH“和”LIBS“，将opencv和eigen改成自己的路径（LIBS路径查询：在终端输入pkg-config --libs opencv)

## 依赖
OpenCV、Eigen
