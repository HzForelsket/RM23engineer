#pragma once
#include "UART.h"
#include "UI.h"
#include "CRC_CHECK.h"
#include <cstdlib>
class JUDGEMENT:public UI
{
	UART* m_uart = nullptr;
	void JUDGEMENT_IRQHandler();
public:
	JUDGEMENT();
	void init_UI();
	void upDateUI();
	virtual void add_graph(GRAPH* graph);
	virtual void delete_graph(GRAPH* graph);
	enum class ROBOT_ID
	{
		RED_HERO = 1, RED_ENGINEER, RED_INFANTRY_ONE, RED_INFANTRY_TWO, RED_INFANTRY_THREE,
		RED_UAV, RED_SENTRY, RED_RADAR = 9,
		BLUE_HERO = 101, BLUE_ENGINEER, BLUE_INFANTRY_ONE, BLUE_INFANTRY_TWO, BLUE_INFANTRY_THREE,
		BLUE_UAV, BLUE_SENTRY, BLUE_RADAR = 109,
	};
	enum class CLIENT_ID
	{
		RED_HERO = 0x101, RED_ENGINEER, RED_INFANTRY_ONE, RED_INFANTRY_TWO, RED_INFANTRY_THREE,
		RED_UAV,
		BLUE_HERO = 0x165, BLUE_ENGINEER, BLUE_INFANTRY_ONE, BLUE_INFANTRY_TWO, BLUE_INFANTRY_THREE,
		BLUE_UAV,
	};
	enum class CAMP
	{
		RED,BLUE
	};
	ext_game_status_t							game_status_t;
	ext_game_result_t							game_result_t;
	ext_game_robot_HP_t							game_robot_HP_t;
	ext_ICRA_buff_debuff_zone_and_lurk_status_t ICRA_buff_debuff_zone_and_lurk_status_t;
	ext_event_data_t							event_data_t;							    
	ext_supply_projectile_action_t				supply_projectile_action_t;				    
	ext_referee_warning_t						referee_warning_t;						    
	ext_dart_remaining_time_t					dart_remaining_time_t;					    
	ext_game_robot_status_t						game_robot_status_t;					    
	ext_power_heat_data_t						power_heat_data_t;						    
	ext_game_robot_pos_t						game_robot_pos_t;						    
	ext_buff_t									buff_t;									    
	aerial_robot_energy_t						m_aerial_robot_energy_t;
	ext_shoot_data_t							shoot_data_t;				
	ext_robot_hurt_t							robot_hurt_t;
	ext_bullet_remaining_t						bullet_remaining_t;						    
	ext_rfid_status_t							rfid_status_t;							    
	ext_dart_client_cmd_t						dart_client_cmd_t;						    										    
	ext_student_interactive_header_data_t		student_interactive_header_data_t;		    
	robot_interactive_data_t					m_robot_interactive_data_t;					    
	ext_client_custom_graphic_delete_t			client_custom_graphic_delete_t;			    
	//graphic_data_struct_t						m_graphic_data_struct_t;						    
	ext_client_custom_graphic_single_t			client_custom_graphic_single_t;			    
	ext_client_custom_graphic_double_t			client_custom_graphic_double_t;			    
	ext_client_custom_graphic_five_t			client_custom_graphic_five_t;			    
	ext_client_custom_graphic_seven_t			client_custom_graphic_seven_t;			    
	ext_client_custom_character_t				client_custom_character_t;				    
	ext_robot_command_t							robot_command_t;						    
	ext_client_map_command_t					client_map_command_t;						    
	void init(UART* uart);
};



