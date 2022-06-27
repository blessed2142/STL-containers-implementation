#include <iostream>
#include <fstream>

// int main(int argc, char **argv)
int main(void)
{
	// (void)argc;
	// (void)argv;


	std::ifstream inf("vec_output.txt");
	std::ifstream inf1("vec_output_std.txt");
 
	if (!inf)
	{
		std::cerr << "Uh oh, *_filename_* could not be opened for reading!" << std::endl;
		return(1);
	}
	if (!inf1)
	{
		std::cerr << "Uh oh, *_filename_* could not be opened for reading!" << std::endl;
		return(1);
	}

	while (inf)
	{
		std::string strInput;
		std::string strInput1;
		std::getline(inf, strInput);
		std::getline(inf1, strInput1);
		if (!(strInput1 == strInput))
		{
			std::cout << std::endl;
			std::cout << "!!!__If pair or value_compare differ its ok__!!!" << std::endl << std::endl;
			std::cout << "not_equal" << std::endl;
			std::cout << strInput << std::endl;
			std::cout << strInput1 << std::endl;
		}
	}

	return (0);
}