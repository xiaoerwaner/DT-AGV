# DT-AGV

若没有AGV实体的实验运行顺序
先使用命令保证AGV与UE4可以互相通信
roslaunch rosbridge_server rosbridge_tcp.launch bson_only_mode:=True
1、打开环境
roslaunch turtlebot3_gazebo turtlebot3_stage_1.launch 
2、打开rviz导航,进行行走
roslaunch turtlebot3_slam turtlebot3_slam.launch slam_methods:=gmapping
3、打开车行走的键盘launch
roslaunch turtlebot3_teleop turtlebot3_teleop_key.launch 
4、保存刚得到的地图文件
rosrun map_server map_saver -f ~/map
5、保留gazebo，关闭rviz，打开刚刚得到的地图
roslaunch turtlebot3_navigation turtlebot3_navigation.launch map_file:=$HOME/map.yaml
6、启动rosbridge
roslaunch rosbridge_server rosbridge_tcp.launch bson_only_mode:=True
7、启动节点
rosrun turtlebot3_navigation tf_translation
rosrun turtlebot3_navigation listen_navigation
