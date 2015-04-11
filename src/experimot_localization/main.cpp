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

#include "experimot\common\ParameterClient.h"
#include "experimot\common\ParameterHelper.h"
#include <boost/program_options.hpp>

int main(int argc, char *argv[])
{
	try {
		experimot::msgs::NodePtr nodeInfo;
		if (argv != NULL){
			experimot::msgs::Node _node;
			for (int i = 0; i < argc; i++){
				std::cout
					<< "arg " << i + 1 << " : " << std::string(argv[i]) << std::endl;
			}
			if (argc > 2){
				std::cout
					<< "Parsing command line option " << std::endl;
				namespace po = boost::program_options;
				po::options_description desc("Options");
				desc.add_options()
					("help,h", "Print help messages")
					("name,n", po::value<std::string>(), "name of the node")
					("param,p", po::value<std::string>(), "parameter server address");

				po::variables_map vm;
				try
				{
					po::store(po::parse_command_line(argc, argv, desc),
						vm); // can throw 

					/** --help option
					*/
					if (vm.count("help"))
					{
						std::cout << "Basic Command Line Parameter App" << std::endl
							<< desc << std::endl;
						return 0;
					}
					std::string name;
					std::string param;
					if (vm.count("name")){
						name = vm["name"].as<std::string>();
						std::cout << "Name of node: " << std::endl
							<< vm["name"].as<std::string>() << std::endl;
					}
					if (vm.count("param")){
						param = vm["param"].as<std::string>();
						std::cout << "Parameter server : " << std::endl
							<< vm["param"].as<std::string>() << std::endl;
					}
					po::notify(vm); // throws on error, so do after help in case 
					// there are any problems 

					if (!name.empty() && !param.empty()){
						nodeInfo = experimot::msgs::NodePtr(new experimot::msgs::Node());
						if (ParameterClient::Get(param, name, nodeInfo, 1000)){
							nodeInfo->PrintDebugString();
						}
					}
				}
				catch (po::error& e)
				{
					std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
					std::cerr << desc << std::endl;
					return 1;
				}
				catch (const std::exception &e) {
					std::cout << "Exception: " << e.what() << endl;
				}
			}
		}
		boost::asio::io_service ios;
#if RobotListener
		RobotStateListenerTest test(ios);
#else
#if MarkerTest
		MarkerDetectionTest detect(ios);
#else
		LocalizationPtr pLocalize;
		if (nodeInfo != 0){
			pLocalize = LocalizationPtr(new Localization(ios, nodeInfo));
		}
		else{
			pLocalize = LocalizationPtr(new Localization(ios));
		}
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