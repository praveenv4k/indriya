#define MarkerTest 0
#define RobotListener 0
#if MarkerTest
#include "MarkerDetectionTest.h"
#else
#if RobotListener
#include "RobotStateListenerTest.h"
#else
#include "Localization.h"
#endif
#endif


int main(int argc, char *argv[])
{
	try {
		if (argv != NULL){
			experimot::msgs::Node _node;
			//_node.ParseFromString()
			std::cout
				<< "args size : " << argc << std::endl;
			std::cout
				<< "First arg : " << std::string(argv[0]) << std::endl;
			if (argc == 2){
				std::cout
					<< "Second arg : " << std::string(argv[1]) << std::endl;
				/*_node.ParseFromString(std::string(argv[1]));
				_node.PrintDebugString();*/
			}
		}
		boost::asio::io_service ios;
#if RobotListener
		RobotStateListenerTest test(ios);
#else
#if MarkerTest
		MarkerDetectionTest detect(ios);
#else
		Localization localize(ios);
#endif
#endif
		ios.run();
		return 0;
	}
	catch (const std::exception &e) {
		std::cout << "Exception: " << e.what() << endl;
	}
	catch (...) {
		std::cout << "Exception: unknown" << std::endl;
	}
}