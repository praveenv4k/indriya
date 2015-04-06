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