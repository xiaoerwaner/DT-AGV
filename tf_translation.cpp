#include"ros/ros.h"
#include"tf/transform_broadcaster.h"
#include"turtlesim/Pose.h"
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Point.h>
#include <actionlib/client/simple_action_client.h>
#include <tf2/LinearMath/Quaternion.h>
ros::Subscriber subscriber;
tf::Transform transform;

//update lastest location
void subscriberCallback(const geometry_msgs::PoseStamped msg)
{
	
	tf::Quaternion q(msg.pose.orientation.x,-msg.pose.orientation.y,-msg.pose.orientation.z,msg.pose.orientation.w);//创建四元数，设置旋转矩阵
	transform.setOrigin(tf::Vector3(msg.pose.position.x/300,msg.pose.position.y/300,-msg.pose.position.z/300));
	//printf(" x():=%f\n",msg.pose.position.x/300);
	//printf(" y():=%f\n",msg.pose.position.y/300);
	transform.setRotation(q);

	
	
}


int main(int argc,char **argv)
{
ros::init(argc,argv,"my_broadcaster");
//init position
transform.setOrigin(tf::Vector3(0,0,0));
tf::Quaternion q;//创建四元数，设置旋转矩阵
q.setRPY(0,0,0);//设置x,y,z的旋转关系
transform.setRotation(q);

ros::NodeHandle n;

subscriber = n.subscribe("/UE_move_base", 1, subscriberCallback);

ros::Rate rate(30.0);
while(ros::ok())
{
	static tf::TransformBroadcaster br;
	br.sendTransform(tf::StampedTransform(transform,ros::Time::now(),"odom","now_location"));
	ros::spinOnce();
	rate.sleep();
}



ros::spin();
return 0;
}
