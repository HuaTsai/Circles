#include <cmath>
#include <rclcpp/rclcpp.hpp>
#include <visualization_msgs/msg/marker_array.hpp>

class Circles : public rclcpp::Node {
 public:
  Circles() : Node("circles") {
    rclcpp::QoS qos(rclcpp::KeepLast(1));
    qos.transient_local();
    pub_ = this->create_publisher<visualization_msgs::msg::MarkerArray>(
        "circles", qos);
    visualization_msgs::msg::MarkerArray markers;
    int points = 100;
    for (int i = 1; i < 10; i++) {
      visualization_msgs::msg::Marker marker;
      marker.header.frame_id = "map";
      marker.header.stamp = this->now();
      marker.id = i;
      marker.type = visualization_msgs::msg::Marker::LINE_STRIP;
      marker.action = visualization_msgs::msg::Marker::ADD;
      marker.pose.orientation.w = 1;
      marker.scale.x = 0.01;
      marker.color.a = 1.0;
      marker.color.r = 160 / 255.;
      marker.color.g = 160 / 255.;
      marker.color.b = 164 / 255.;
      for (int j = 0; j < points + 1; j++) {
        geometry_msgs::msg::Point p;
        p.x = i * cos(2 * M_PI * j / points);
        p.y = i * sin(2 * M_PI * j / points);
        p.z = 0;
        marker.points.push_back(p);
      }
      markers.markers.push_back(marker);
    }
    pub_->publish(markers);
  }

 private:
  rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr pub_;
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Circles>());
  rclcpp::shutdown();
}
