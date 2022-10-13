#include"ros/ros.h"
#include"tf/transform_listener.h"
#include"geometry_msgs/Twist.h"
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Point.h>
int main(int argc,char **argv)
{
ros::init(argc,argv,"my_listener");
ros::NodeHandle n;



ros::Publisher turtle_vel=n.advertise<geometry_msgs::Twist>("/cmd_vel",10);//用于给第二只海归发送运动指令

tf::TransformListener listenter;
ros::Rate rate(10);
while(ros::ok())
{
tf::StampedTransform transform;   
try
{
listenter.waitForTransform("base_footprint","now_location",ros::Time(0),ros::Duration(3.0));

//等待变换，查看是否存在这两个坐标系，存在的话就继续执行下面的语句，ros::Time(0)表示查询最新实时数据，ros::Duration(3.0)为等待时间3s后就会提示错误
listenter.lookupTransform("base_footprint","now_location",ros::Time(0),transform);
//查询变换
//以上两句完成tf查询两个坐标系之间的位置关系
}
catch(tf::TransformException &ex)
{
ROS_ERROR("%s",ex.what());
ros::Duration(1.0).sleep();
continue;
}
geometry_msgs::Twist vel_msg;
vel_msg.angular.z=0.5*atan2(transform.getOrigin().y(),transform.getOrigin().x());//计算角速度，
	//printf(" x():=%f\n",transform.getOrigin().x());
	//printf(" y():=%f\n",transform.getOrigin().y());
vel_msg.linear.x=sqrt(pow(transform.getOrigin().x(),2)+pow(transform.getOrigin().y(),2))/6;//计算线速度，即欧氏距离/时间(2s)=速度
turtle_vel.publish(vel_msg);
rate.sleep();
}
return 0;
}
