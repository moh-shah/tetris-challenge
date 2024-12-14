#pragma once

struct persistent_data//can be inherited
{
public:
	int best_score;
	
	// This method lets cereal know which data members to serialize
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(best_score); // serialize things by passing them to the archive
	}
};

class persistent_data_manager
{
public:
	static void init();
	static persistent_data load();
	static void try_save(persistent_data data, bool force);
};
