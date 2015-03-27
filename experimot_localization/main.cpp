
#include "Localization.h"

int main(int argc, char *argv[])
{
	try {
		boost::asio::io_service ios;
		Localization localize(ios);
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