#include "histogram.hpp"
#include <iostream>

int main()
{
	vector<pair<string,int>> counter;
	histogram_add(counter, "yolo");
	histogram_add(counter, "yolo");
	histogram_add(counter, "yolo");
	histogram_add(counter, "hi");
	histogram_add(counter, "hi");
	histogram_add(counter, "eureka");
	histogram_add(counter, "eureka");
	histogram_add(counter, "eureka");
	histogram_add(counter, "eureka");
	cout << histogram_get_count(counter, "yolo") << " " << histogram_get_count(counter, "hi") << " " << histogram_get_count(counter, "eureka") << " " << counter.size() << endl;
}
