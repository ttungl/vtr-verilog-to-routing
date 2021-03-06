#ifndef BUILD_SWITCHBLOCKS_H
#define BUILD_SWITCHBLOCKS_H

#include <unordered_map>
#include <vector>
#include "physical_types.h"
#include "vpr_types.h"


/************ Classes, structs, typedefs ************/

/* Holds the coordinates of a switch block source connection. Used to index into a 
   map which specifies which destination wire segments this source wire should		//TODO: what data structure does this index to?
   connect to */
class Switchblock_Lookup{
public:
	int x_coord;		/* x coordinate of switchblock connection */	//TODO: redundant comment?? add range
	int y_coord;		/* y coordinate of switchblock connection */
	e_side from_side;	/* source side of switchblock connection */
	e_side to_side;		/* destination side of switchblock connection */
	int from_wire;		/* index of the source wire segment within the corresponding channel segment (0..W-1) */

	/* Empty constructor initializes everything to 0 */
	Switchblock_Lookup(){
		x_coord = y_coord = from_wire = -1;		//TODO: use set function
	}

	/* Constructor for initializing member variables */
	Switchblock_Lookup(int set_x, int set_y, e_side set_from, e_side set_to, int set_wire){
		this->set_coords(set_x, set_y, set_from, set_to, set_wire);		//TODO: use set function
	}

	/* Function for setting the segment coordinates */
	void set_coords(int set_x, int set_y, e_side set_from, e_side set_to, int set_wire){
		x_coord = set_x;
		y_coord = set_y;
		from_side = set_from;
		to_side = set_to;
		from_wire = set_wire;
	}

	/* Overload == operator which is used by std::unordered_map */
	bool operator == (const Switchblock_Lookup &obj) const{
		bool result;
		if (x_coord == obj.x_coord && y_coord == obj.y_coord
		  && from_side == obj.from_side && to_side == obj.to_side
		  && from_wire == obj.from_wire){
			result = true;
		} else {
			result = false;
		}
		return result;
	}
};

struct s_hash_Switchblock_Lookup{
	size_t operator()(const Switchblock_Lookup &obj) const{
		size_t result;
		result = ((((std::hash<int>()(obj.x_coord) ^ std::hash<int>()(obj.y_coord) << 10) ^
		       std::hash<int>()((int)obj.from_side) << 20) ^ 
		       std::hash<int>()((int)obj.to_side) << 30) ^ 
		       std::hash<int>()(obj.from_wire) << 40);
		return result;
	}
};

/* contains the index of the destination wire segment within a channel
   and the index of the switch used to connect to it */
typedef struct s_to_wire_inf{
	short to_wire;
	short switch_ind;	
} t_to_wire_inf;

/* Switchblock connections are made as [x][y][from_side][to_side][from_wire_ind].
   The Switchblock_Lookup class specifies these dimensions.
   Furthermore, a source_wire at a given 5-d coordinate may connect to multiple destination wires so the value
   of the map is a vector of destination wires.
   A matrix specifying connections for all switchblocks in an FPGA would be sparse and possibly very large
   so we use an unordered map to take advantage of the sparsity. */
typedef std::unordered_map< Switchblock_Lookup, std::vector< t_to_wire_inf >, s_hash_Switchblock_Lookup > t_sb_connection_map;



/************ Functions ************/

/* allocate and build switch block permutation map */
t_sb_connection_map * alloc_and_load_switchblock_permutations( t_chan_details * chan_details_x, 
				t_chan_details * chan_details_y, int nx, int ny, 
				std::vector<t_switchblock_inf> switchblocks, 
				s_chan_width *nodes_per_chan, enum e_directionality directionality);

/* deallocates switch block connections sparse array */
void free_switchblock_permutations(t_sb_connection_map *sb_conns);

#endif
