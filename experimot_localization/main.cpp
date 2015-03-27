#define MarkerTest 1

#if MarkerTest
#include "MarkerDetectionTest.h"
#else
#include "Localization.h"
#endif

int main(int argc, char *argv[])
{
	try {
		boost::asio::io_service ios;
#if MarkerTest
		MarkerDetectionTest detect(ios);
#else
		Localization localize(ios);
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