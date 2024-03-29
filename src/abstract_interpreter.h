//User Input Based
#include <iostream>
#include <map>

#include "interval.h"

#include "goto-programs/goto_program.h"
#include "goto-programs/goto_model.h"
#include "analyses/natural_loops.h"


class abstract_interpreter
{
	private:

		std::map<irep_idt, interval*> interval_map;
		int threshold = -1 ;

		interval handle_rhs(exprt& expression, goto_modelt& goto_model);
		void set_rhs(exprt &rhs_expr, interval* &rhs , goto_modelt &goto_model);
		void set_lhs(symbol_exprt &lhs_sym, interval* &lhs, goto_modelt &goto_model);
		bool check_if_loop(natural_loops_mutablet &loops, goto_programt::targett &target);
		bool check_condition(exprt &expr, goto_modelt &goto_model, namespacet &ns, bool update);
		void join_values(std::map<irep_idt, interval*> &interval_map_before_loop);
		void check_for_convergence(std::map<irep_idt, interval*> &interval_map_prev_iteration, bool &converged);
		void copy_map(std::map<irep_idt, interval*> &copy);
		void widening (natural_loops_mutablet::natural_loopt &current_loop, natural_loops_mutablet &all_loops,
										  goto_modelt &goto_model, namespacet &ns);
		void remove_not(exprt &expr, namespacet &ns);

		bool check_assert(exprt &expr, goto_modelt &goto_model, namespacet &ns);

		bool check_if_equal(interval* first , interval* second);
		void iterate_over_if(goto_programt::targett &it, goto_modelt &goto_model, 
						   goto_programt::targett &target_if, goto_programt::targett &target_end, bool &else_present, natural_loops_mutablet &loops, namespacet &ns) ;
		void check_if_else_present(goto_programt::targett &it, goto_programt::targett &target_end, goto_programt::targett &target_if, bool &else_present) ;
		void iterate_over_else(goto_programt::targett &it, goto_modelt &goto_model, 
						   goto_programt::targett &target_end, natural_loops_mutablet &loops, namespacet &ns) ;
		void restore_map(std::map<irep_idt, interval*> &copy) ;

	public:
		void run_interpreter(goto_modelt &goto_model);
		void print_all();
		void handle_declaration(goto_programt::instructiont &instruction, goto_modelt &goto_model);
		void handle_assignments(goto_programt::instructiont &instruction, goto_modelt &goto_model);	
		void handle_assignments_widen(goto_programt::instructiont &instruction, goto_modelt &goto_model, std::map<irep_idt, interval*> &interval_map_prev);	
		void handle_goto(goto_programt::instructiont &instruction, goto_modelt &goto_model, 
						goto_programt::targett &it, bool &target_changed, natural_loops_mutablet &loops, namespacet &ns);	
		void handle_loops(natural_loops_mutablet::natural_loopt &current_loop ,  natural_loops_mutablet &all_loops, goto_modelt &goto_model, namespacet &ns);
		void handle_assertions(goto_programt::instructiont &instruction ,
												goto_modelt &goto_model,
												namespacet &ns) ;
};

