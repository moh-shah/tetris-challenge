#include "game.h"
#include <iostream>
#include "persistent_data_manager.h"
using namespace  std;

int main(int argc, char *argv[])
{
    /*std::vector<vector<int>> vec =  {
        vector<int>{1,2},
        vector<int>{10,20},
        vector<int>{100,200}
    };

    for (const auto &item: vec){
        cout<<item[0]<<"\n";
    }

    return 0;*/


    std::cout << "Hello, World!" << std::endl;

    persistent_data_manager::init();
    //persistent_data_manager::try_save(persistent_data(5), false);
    /*std::cout<<endl<<"best score: "<< persistent_data_manager::load().best_score << endl;

    return 0;*/

	auto game_instance = game();
	game_instance.start();

	return 0;
}