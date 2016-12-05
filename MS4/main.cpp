#include <iostream>
#include <string>
#include "Profile.h"
#include "Araig_Sensors.h"

int main(int argc, char** argv) 
	
	{
		if (argc != 4) {
			std::cerr << argv[0] << ": incorrect number of arguments\n";
			std::cerr << "Usage: " << argv[0] << " file_name\n";
			return 1;
		}		
		
		try
		{
			ARAIG_Sensors taskslib(argv[1],argv[2]);
			Profile a(argv[3], cout, taskslib);
			a.run();
			
		}
		
		catch (std::string a) {
			cout << a << endl;
		}
		catch (const std::exception&)
		{

		}
		catch (std::runtime_error) 
		{

		}
		
		std::cout << "\nPress any key to continue ... ";
		std::cin.get();
		return 1;
	}
//}