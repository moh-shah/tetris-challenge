#include "persistent_data_manager.h"
#include "cereal/archives/binary.hpp"
#include <fstream>

void persistent_data_manager::init()
{
    std::cout << "initializing persistent data manager\n";

    std::ifstream file("save_data.bin", std::ios::binary);

	if (!file)
    {
        std::cout << "no save file... creating one\n";
        constexpr auto d = persistent_data(0);
        try_save(d, true);
    }
}

persistent_data persistent_data_manager::load()
{
    // Open the file containing serialized data
    std::ifstream file("save_data.bin", std::ios::binary);

    // Deserialize the data
    cereal::BinaryInputArchive iarchive(file);
    persistent_data pd;
    iarchive(pd);
    return pd;
}

//not a good method... comparision should be different from save
void persistent_data_manager::try_save(persistent_data data, bool force)
{
	if (!force)
	{
	    auto last_saved_data = load();
	    std::cout << "current best score: " << last_saved_data.best_score << " requested score to be saved: " << data.best_score;

	    if (last_saved_data.best_score > data.best_score)
	    {
	        return;
	    }
    }

    // Open the file for writing serialized data
    std::ofstream file("save_data.bin", std::ios::binary);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open try_save file for writing.");
    }

    // Serialize the data
    cereal::BinaryOutputArchive oarchive(file);
    oarchive(data);
}
