/* 
  Intra-logic block router determines if a candidate packing solution (or intermediate solution) can route.

  Author: Jason Luu
  Date: July 22, 2013
 */

/* Constructors/Destructors */
t_lb_router_data *alloc_and_load_router_data(vector<t_lb_type_rr_node> *lb_type_graph, t_type_ptr type);
void free_router_data(t_lb_router_data *router_data);
void free_intra_lb_nets(vector <t_intra_lb_net> *intra_lb_nets);

/* Routing Functions */
void add_atom_as_target(t_lb_router_data *router_data, const int iatom);
void remove_atom_from_target(t_lb_router_data *router_data, const int iatom);
void set_reset_pb_modes(t_lb_router_data *router_data, const t_pb *pb, const bool set);
bool try_intra_lb_route(t_lb_router_data *router_data);

/* Accessor Functions */
t_pb_route *alloc_and_load_pb_route(const vector <t_intra_lb_net> *intra_lb_nets, t_pb_graph_node *pb_graph_head); 
void free_pb_route(t_pb_route *free_pb_route);

