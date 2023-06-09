//#pragma once
//#include<cstdint>
//#pragma pack(1)
//typedef __packed struct{
//	uint8_t game_type : 4;
//	uint8_t game_progress : 4;
//	uint16_t stage_remain_time;
//	uint64_t SyncTimeStamp;
//}ext_game_status_t;
//typedef __packed struct{
//	uint8_t winner;
//}ext_game_result_t;
//typedef __packed struct{
//	uint16_t red_1_robot_HP;
//	uint16_t red_2_robot_HP;
//	uint16_t red_3_robot_HP;
//	uint16_t red_4_robot_HP;
//	uint16_t red_5_robot_HP;
//	uint16_t red_7_robot_HP;
//	uint16_t red_outpost_HP;
//	uint16_t red_base_HP;
//	uint16_t blue_1_robot_HP;
//	uint16_t blue_2_robot_HP;
//	uint16_t blue_3_robot_HP;
//	uint16_t blue_4_robot_HP;
//	uint16_t blue_5_robot_HP;
//	uint16_t blue_7_robot_HP;
//	uint16_t blue_outpost_HP;
//	uint16_t blue_base_HP;
//} ext_game_robot_HP_t;
//typedef __packed struct{
//	uint8_t F1_zone_status : 1;
//	uint8_t F1_zone_buff_debuff_status : 3;
//	uint8_t F2_zone_status : 1;
//	uint8_t F2_zone_buff_debuff_status : 3;
//	uint8_t F3_zone_status : 1;
//	uint8_t F3_zone_buff_debuff_status : 3;
//	uint8_t F4_zone_status : 1;
//	uint8_t F4_zone_buff_debuff_status : 3;
//	uint8_t F5_zone_status : 1;
//	uint8_t F5_zone_buff_debuff_status : 3;
//	uint8_t F6_zone_status : 1;
//	uint8_t F6_zone_buff_debuff_status : 3;
//	uint16_t red1_bullet_left;
//	uint16_t red2_bullet_left;
//	uint16_t blue1_bullet_left;
//	uint16_t blue2_bullet_left;
//	uint8_t lurk_mode;
//	uint8_t res;
//} ext_ICRA_buff_debuff_zone_and_lurk_status_t;
//typedef __packed struct{
//	uint32_t event_type;
//} ext_event_data_t;
//typedef __packed struct{
//	uint8_t supply_projectile_id;
//	uint8_t supply_robot_id;
//	uint8_t supply_projectile_step;
//	uint8_t supply_projectile_num;
//} ext_supply_projectile_action_t;
//typedef __packed struct{
//	uint8_t level;
//	uint8_t foul_robot_id;
//} ext_referee_warning_t;
//typedef __packed struct
//{
//	uint8_t dart_remaining_time;
//} ext_dart_remaining_time_t;
//typedef __packed struct
//{
//	uint8_t robot_id;
//	uint8_t robot_level;
//	uint16_t remain_HP;
//	uint16_t max_HP;
//	uint16_t shooter_id1_17mm_cooling_rate;
//	uint16_t shooter_id1_17mm_cooling_limit;
//	uint16_t shooter_id1_17mm_speed_limit;
//	uint16_t shooter_id2_17mm_cooling_rate;
//	uint16_t shooter_id2_17mm_cooling_limit;
//	uint16_t shooter_id2_17mm_speed_limit;
//	uint16_t shooter_id1_42mm_cooling_rate;
//	uint16_t shooter_id1_42mm_cooling_limit;
//	uint16_t shooter_id1_42mm_speed_limit;
//	uint16_t chassis_power_limit;
//	uint8_t mains_power_gimbal_output : 1;
//	uint8_t mains_power_chassis_output : 1;
//	uint8_t mains_power_shooter_output : 1;
//} ext_game_robot_status_t;
//typedef __packed struct
//{
//	uint16_t chassis_volt;
//	uint16_t chassis_current;
//	float chassis_power;
//	uint16_t chassis_power_buffer;
//	uint16_t shooter_id1_17mm_cooling_heat;
//	uint16_t shooter_id2_17mm_cooling_heat;
//	uint16_t shooter_id1_42mm_cooling_heat;
//} ext_power_heat_data_t;
//typedef __packed struct
//{
//	float x;
//	float y;
//	float z;
//	float yaw;
//} ext_game_robot_pos_t;
//typedef __packed struct
//{
//	uint8_t power_rune_buff;
//} ext_buff_t;
//typedef __packed struct
//{
//	uint8_t attack_time;
//} aerial_robot_energy_t;
//typedef __packed struct
//{
//	uint8_t armor_id : 4;
//	uint8_t hurt_type : 4;
//} ext_robot_hurt_t;
//typedef __packed struct
//{
//	uint8_t bullet_type;
//	uint8_t shooter_id;
//	uint8_t bullet_freq;
//	float bullet_speed;
//} ext_shoot_data_t;
//typedef __packed struct
//{
//	uint16_t bullet_remaining_num_17mm;
//	uint16_t bullet_remaining_num_42mm;
//	uint16_t coin_remaining_num;
//} ext_bullet_remaining_t;
//typedef __packed struct
//{
//	uint32_t rfid_status;
//} ext_rfid_status_t;
//typedef __packed struct
//{
//	uint8_t dart_launch_opening_status;
//	uint8_t dart_attack_target;
//	uint16_t target_change_time;
//	uint16_t operate_launch_cmd_time;
//} ext_dart_client_cmd_t;
//
//
//typedef __packed struct
//{
//	uint16_t data_cmd_id;
//	uint16_t sender_ID;
//	uint16_t receiver_ID;
//} ext_student_interactive_header_data_t;
//typedef __packed struct
//{
//	uint8_t* data;
//} robot_interactive_data_t;
//typedef __packed struct
//{
//	uint8_t operate_tpye;
//	uint8_t layer;
//} ext_client_custom_graphic_delete_t;
//
//typedef __packed struct
//{
//	uint8_t graphic_name[3];
//	uint32_t operate_tpye : 3;
//	uint32_t graphic_tpye : 3;
//	uint32_t layer : 4;
//	uint32_t color : 4;
//	uint32_t start_angle : 9;
//	uint32_t end_angle : 9;
//	uint32_t width : 10;
//	uint32_t start_x : 11;
//	uint32_t start_y : 11;
//	uint32_t radius : 10;
//	uint32_t end_x : 11;
//	uint32_t end_y : 11;
//} graphic_data_struct_t;
//typedef __packed struct
//{
//	graphic_data_struct_t grapic_data_struct;
//} ext_client_custom_graphic_single_t;
//typedef __packed struct
//{
//	graphic_data_struct_t grapic_data_struct[2];
//} ext_client_custom_graphic_double_t;
//typedef __packed struct
//{
//	graphic_data_struct_t grapic_data_struct[5];
//} ext_client_custom_graphic_five_t;
//typedef __packed struct
//{
//	graphic_data_struct_t grapic_data_struct[7];
//} ext_client_custom_graphic_seven_t;
//typedef __packed struct{
//graphic_data_struct_t grapic_data_struct;
//uint8_t data[30];
//} ext_client_custom_character_t;
//typedef __packed struct
//{
//	float target_position_x;
//	float target_position_y;
//	float target_position_z;
//	uint8_t commd_keyboard;
//	uint16_t target_robot_ID;
//} ext_robot_command_t;
//typedef __packed struct
//{
//	uint16_t target_robot_ID;
//	float target_position_x;
//	float target_position_y;
//} ext_client_map_command_t;
//#pragma once
//#include<cstdint>
//#pragma pack(1)
//typedef __packed struct{
//	uint8_t game_type : 4;
//	uint8_t game_progress : 4;
//	uint16_t stage_remain_time;
//	uint64_t SyncTimeStamp;
//}ext_game_status_t;
//typedef __packed struct{
//	uint8_t winner;
//}ext_game_result_t;
//typedef __packed struct{
//	uint16_t red_1_robot_HP;
//	uint16_t red_2_robot_HP;
//	uint16_t red_3_robot_HP;
//	uint16_t red_4_robot_HP;
//	uint16_t red_5_robot_HP;
//	uint16_t red_7_robot_HP;
//	uint16_t red_outpost_HP;
//	uint16_t red_base_HP;
//	uint16_t blue_1_robot_HP;
//	uint16_t blue_2_robot_HP;
//	uint16_t blue_3_robot_HP;
//	uint16_t blue_4_robot_HP;
//	uint16_t blue_5_robot_HP;
//	uint16_t blue_7_robot_HP;
//	uint16_t blue_outpost_HP;
//	uint16_t blue_base_HP;
//} ext_game_robot_HP_t;
//typedef __packed struct{
//	uint8_t F1_zone_status : 1;
//	uint8_t F1_zone_buff_debuff_status : 3;
//	uint8_t F2_zone_status : 1;
//	uint8_t F2_zone_buff_debuff_status : 3;
//	uint8_t F3_zone_status : 1;
//	uint8_t F3_zone_buff_debuff_status : 3;
//	uint8_t F4_zone_status : 1;
//	uint8_t F4_zone_buff_debuff_status : 3;
//	uint8_t F5_zone_status : 1;
//	uint8_t F5_zone_buff_debuff_status : 3;
//	uint8_t F6_zone_status : 1;
//	uint8_t F6_zone_buff_debuff_status : 3;
//	uint16_t red1_bullet_left;
//	uint16_t red2_bullet_left;
//	uint16_t blue1_bullet_left;
//	uint16_t blue2_bullet_left;
//	uint8_t lurk_mode;
//	uint8_t res;
//} ext_ICRA_buff_debuff_zone_and_lurk_status_t;
//typedef __packed struct{
//	uint32_t event_type;
//} ext_event_data_t;
//typedef __packed struct{
//	uint8_t supply_projectile_id;
//	uint8_t supply_robot_id;
//	uint8_t supply_projectile_step;
//	uint8_t supply_projectile_num;
//} ext_supply_projectile_action_t;
//typedef __packed struct{
//	uint8_t level;
//	uint8_t foul_robot_id;
//} ext_referee_warning_t;
//typedef __packed struct
//{
//	uint8_t dart_remaining_time;
//} ext_dart_remaining_time_t;
//typedef __packed struct
//{
//	uint8_t robot_id;
//	uint8_t robot_level;
//	uint16_t remain_HP;
//	uint16_t max_HP;
//	uint16_t shooter_id1_17mm_cooling_rate;
//	uint16_t shooter_id1_17mm_cooling_limit;
//	uint16_t shooter_id1_17mm_speed_limit;
//	uint16_t shooter_id2_17mm_cooling_rate;
//	uint16_t shooter_id2_17mm_cooling_limit;
//	uint16_t shooter_id2_17mm_speed_limit;
//	uint16_t shooter_id1_42mm_cooling_rate;
//	uint16_t shooter_id1_42mm_cooling_limit;
//	uint16_t shooter_id1_42mm_speed_limit;
//	uint16_t chassis_power_limit;
//	uint8_t mains_power_gimbal_output : 1;
//	uint8_t mains_power_chassis_output : 1;
//	uint8_t mains_power_shooter_output : 1;
//} ext_game_robot_status_t;
//typedef __packed struct
//{
//	uint16_t chassis_volt;
//	uint16_t chassis_current;
//	float chassis_power;
//	uint16_t chassis_power_buffer;
//	uint16_t shooter_id1_17mm_cooling_heat;
//	uint16_t shooter_id2_17mm_cooling_heat;
//	uint16_t shooter_id1_42mm_cooling_heat;
//} ext_power_heat_data_t;
//typedef __packed struct
//{
//	float x;
//	float y;
//	float z;
//	float yaw;
//} ext_game_robot_pos_t;
//typedef __packed struct
//{
//	uint8_t power_rune_buff;
//} ext_buff_t;
//typedef __packed struct
//{
//	uint8_t attack_time;
//} aerial_robot_energy_t;
//typedef __packed struct
//{
//	uint8_t armor_id : 4;
//	uint8_t hurt_type : 4;
//} ext_robot_hurt_t;
//typedef __packed struct
//{
//	uint8_t bullet_type;
//	uint8_t shooter_id;
//	uint8_t bullet_freq;
//	float bullet_speed;
//} ext_shoot_data_t;
//typedef __packed struct
//{
//	uint16_t bullet_remaining_num_17mm;
//	uint16_t bullet_remaining_num_42mm;
//	uint16_t coin_remaining_num;
//} ext_bullet_remaining_t;
//typedef __packed struct
//{
//	uint32_t rfid_status;
//} ext_rfid_status_t;
//typedef __packed struct
//{
//	uint8_t dart_launch_opening_status;
//	uint8_t dart_attack_target;
//	uint16_t target_change_time;
//	uint16_t operate_launch_cmd_time;
//} ext_dart_client_cmd_t;
//
//
//typedef __packed struct
//{
//	uint16_t data_cmd_id;
//	uint16_t sender_ID;
//	uint16_t receiver_ID;
//} ext_student_interactive_header_data_t;
//typedef __packed struct
//{
//	uint8_t* data;
//} robot_interactive_data_t;
//typedef __packed struct
//{
//	uint8_t operate_tpye;
//	uint8_t layer;
//} ext_client_custom_graphic_delete_t;
//
//typedef __packed struct
//{
//	uint8_t graphic_name[3];
//	uint32_t operate_tpye : 3;
//	uint32_t graphic_tpye : 3;
//	uint32_t layer : 4;
//	uint32_t color : 4;
//	uint32_t start_angle : 9;
//	uint32_t end_angle : 9;
//	uint32_t width : 10;
//	uint32_t start_x : 11;
//	uint32_t start_y : 11;
//	uint32_t radius : 10;
//	uint32_t end_x : 11;
//	uint32_t end_y : 11;
//} graphic_data_struct_t;
//typedef __packed struct
//{
//	graphic_data_struct_t grapic_data_struct;
//} ext_client_custom_graphic_single_t;
//typedef __packed struct
//{
//	graphic_data_struct_t grapic_data_struct[2];
//} ext_client_custom_graphic_double_t;
//typedef __packed struct
//{
//	graphic_data_struct_t grapic_data_struct[5];
//} ext_client_custom_graphic_five_t;
//typedef __packed struct
//{
//	graphic_data_struct_t grapic_data_struct[7];
//} ext_client_custom_graphic_seven_t;
//typedef __packed struct{
//graphic_data_struct_t grapic_data_struct;
//uint8_t data[30];
//} ext_client_custom_character_t;
//typedef __packed struct
//{
//	float target_position_x;
//	float target_position_y;
//	float target_position_z;
//	uint8_t commd_keyboard;
//	uint16_t target_robot_ID;
//} ext_robot_command_t;
//typedef __packed struct
//{
//	uint16_t target_robot_ID;
//	float target_position_x;
//	float target_position_y;
//} ext_client_map_command_t;
//#pragma once
//#include<cstdint>
//#pragma pack(1)
//typedef __packed struct {
//	uint8_t game_type : 4;
//	uint8_t game_progress : 4;
//	uint16_t stage_remain_time;
//	uint64_t SyncTimeStamp;
//}ext_game_status_t;
//typedef __packed struct {
//	uint8_t winner;
//}ext_game_result_t;
//typedef __packed struct {
//	uint16_t red_1_robot_HP;
//	uint16_t red_2_robot_HP;
//	uint16_t red_3_robot_HP;
//	uint16_t red_4_robot_HP;
//	uint16_t red_5_robot_HP;
//	uint16_t red_7_robot_HP;
//	uint16_t red_outpost_HP;
//	uint16_t red_base_HP;
//	uint16_t blue_1_robot_HP;
//	uint16_t blue_2_robot_HP;
//	uint16_t blue_3_robot_HP;
//	uint16_t blue_4_robot_HP;
//	uint16_t blue_5_robot_HP;
//	uint16_t blue_7_robot_HP;
//	uint16_t blue_outpost_HP;
//	uint16_t blue_base_HP;
//} ext_game_robot_HP_t;
//typedef __packed struct {
//	uint8_t F1_zone_status : 1;
//	uint8_t F1_zone_buff_debuff_status : 3;
//	uint8_t F2_zone_status : 1;
//	uint8_t F2_zone_buff_debuff_status : 3;
//	uint8_t F3_zone_status : 1;
//	uint8_t F3_zone_buff_debuff_status : 3;
//	uint8_t F4_zone_status : 1;
//	uint8_t F4_zone_buff_debuff_status : 3;
//	uint8_t F5_zone_status : 1;
//	uint8_t F5_zone_buff_debuff_status : 3;
//	uint8_t F6_zone_status : 1;
//	uint8_t F6_zone_buff_debuff_status : 3;
//	uint16_t red1_bullet_left;
//	uint16_t red2_bullet_left;
//	uint16_t blue1_bullet_left;
//	uint16_t blue2_bullet_left;
//	uint8_t lurk_mode;
//	uint8_t res;
//} ext_ICRA_buff_debuff_zone_and_lurk_status_t;
//typedef __packed struct {
//	uint32_t event_type;
//} ext_event_data_t;
//typedef __packed struct {
//	uint8_t supply_projectile_id;
//	uint8_t supply_robot_id;
//	uint8_t supply_projectile_step;
//	uint8_t supply_projectile_num;
//} ext_supply_projectile_action_t;
//typedef __packed struct {
//	uint8_t level;
//	uint8_t foul_robot_id;
//} ext_referee_warning_t;
//typedef __packed struct
//{
//	uint8_t dart_remaining_time;
//} ext_dart_remaining_time_t;
//typedef __packed struct
//{
//	uint8_t robot_id;
//	uint8_t robot_level;
//	uint16_t remain_HP;
//	uint16_t max_HP;
//	uint16_t shooter_id1_17mm_cooling_rate;
//	uint16_t shooter_id1_17mm_cooling_limit;
//	uint16_t shooter_id1_17mm_speed_limit;
//	uint16_t shooter_id2_17mm_cooling_rate;
//	uint16_t shooter_id2_17mm_cooling_limit;
//	uint16_t shooter_id2_17mm_speed_limit;
//	uint16_t shooter_id1_42mm_cooling_rate;
//	uint16_t shooter_id1_42mm_cooling_limit;
//	uint16_t shooter_id1_42mm_speed_limit;
//	uint16_t chassis_power_limit;
//	uint8_t mains_power_gimbal_output : 1;
//	uint8_t mains_power_chassis_output : 1;
//	uint8_t mains_power_shooter_output : 1;
//} ext_game_robot_status_t;
//typedef __packed struct
//{
//	uint16_t chassis_volt;
//	uint16_t chassis_current;
//	float chassis_power;
//	uint16_t chassis_power_buffer;
//	uint16_t shooter_id1_17mm_cooling_heat;
//	uint16_t shooter_id2_17mm_cooling_heat;
//	uint16_t shooter_id1_42mm_cooling_heat;
//} ext_power_heat_data_t;
//typedef __packed struct
//{
//	float x;
//	float y;
//	float z;
//	float yaw;
//} ext_game_robot_pos_t;
//typedef __packed struct
//{
//	uint8_t power_rune_buff;
//} ext_buff_t;
//typedef __packed struct
//{
//	uint8_t attack_time;
//} aerial_robot_energy_t;
//typedef __packed struct
//{
//	uint8_t armor_id : 4;
//	uint8_t hurt_type : 4;
//} ext_robot_hurt_t;
//typedef __packed struct
//{
//	uint8_t bullet_type;
//	uint8_t shooter_id;
//	uint8_t bullet_freq;
//	float bullet_speed;
//} ext_shoot_data_t;
//typedef __packed struct
//{
//	uint16_t bullet_remaining_num_17mm;
//	uint16_t bullet_remaining_num_42mm;
//	uint16_t coin_remaining_num;
//} ext_bullet_remaining_t;
//typedef __packed struct
//{
//	uint32_t rfid_status;
//} ext_rfid_status_t;
//typedef __packed struct
//{
//	uint8_t dart_launch_opening_status;
//	uint8_t dart_attack_target;
//	uint16_t target_change_time;
//	uint16_t operate_launch_cmd_time;
//} ext_dart_client_cmd_t;
//
//
//typedef __packed struct
//{
//	uint16_t data_cmd_id;
//	uint16_t sender_ID;
//	uint16_t receiver_ID;
//} ext_student_interactive_header_data_t;
//typedef __packed struct
//{
//	uint8_t* data;
//} robot_interactive_data_t;
//typedef __packed struct
//{
//	uint8_t operate_tpye;
//	uint8_t layer;
//} ext_client_custom_graphic_delete_t;
//
//typedef __packed struct
//{
//	uint8_t graphic_name[3];
//	uint32_t operate_tpye : 3;
//	uint32_t graphic_tpye : 3;
//	uint32_t layer : 4;
//	uint32_t color : 4;
//	uint32_t start_angle : 9;
//	uint32_t end_angle : 9;
//	uint32_t width : 10;
//	uint32_t start_x : 11;
//	uint32_t start_y : 11;
//	uint32_t radius : 10;
//	uint32_t end_x : 11;
//	uint32_t end_y : 11;
//} graphic_data_struct_t;
//typedef __packed struct
//{
//	graphic_data_struct_t grapic_data_struct;
//} ext_client_custom_graphic_single_t;
//typedef __packed struct
//{
//	graphic_data_struct_t grapic_data_struct[2];
//} ext_client_custom_graphic_double_t;
//typedef __packed struct
//{
//	graphic_data_struct_t grapic_data_struct[5];
//} ext_client_custom_graphic_five_t;
//typedef __packed struct
//{
//	graphic_data_struct_t grapic_data_struct[7];
//} ext_client_custom_graphic_seven_t;
//typedef __packed struct {
//	graphic_data_struct_t grapic_data_struct;
//	uint8_t data[30];
//} ext_client_custom_character_t;
//typedef __packed struct
//{
//	float target_position_x;
//	float target_position_y;
//	float target_position_z;
//	uint8_t commd_keyboard;
//	uint16_t target_robot_ID;
//} ext_robot_command_t;
//typedef __packed struct
//{
//	uint16_t target_robot_ID;
//	float target_position_x;
//	float target_position_y;
//} ext_client_map_command_t;
#pragma once
#include<cstdint>
#pragma pack(1)
typedef  struct {
	uint8_t game_type : 4;
	uint8_t game_progress : 4;
	uint16_t stage_remain_time;
	uint64_t SyncTimeStamp;
}ext_game_status_t;
typedef  struct {
	uint8_t winner;
}ext_game_result_t;
typedef  struct {
	uint16_t red_1_robot_HP;
	uint16_t red_2_robot_HP;
	uint16_t red_3_robot_HP;
	uint16_t red_4_robot_HP;
	uint16_t red_5_robot_HP;
	uint16_t red_7_robot_HP;
	uint16_t red_outpost_HP;
	uint16_t red_base_HP;
	uint16_t blue_1_robot_HP;
	uint16_t blue_2_robot_HP;
	uint16_t blue_3_robot_HP;
	uint16_t blue_4_robot_HP;
	uint16_t blue_5_robot_HP;
	uint16_t blue_7_robot_HP;
	uint16_t blue_outpost_HP;
	uint16_t blue_base_HP;
} ext_game_robot_HP_t;
typedef  struct {
	uint8_t F1_zone_status : 1;
	uint8_t F1_zone_buff_debuff_status : 3;
	uint8_t F2_zone_status : 1;
	uint8_t F2_zone_buff_debuff_status : 3;
	uint8_t F3_zone_status : 1;
	uint8_t F3_zone_buff_debuff_status : 3;
	uint8_t F4_zone_status : 1;
	uint8_t F4_zone_buff_debuff_status : 3;
	uint8_t F5_zone_status : 1;
	uint8_t F5_zone_buff_debuff_status : 3;
	uint8_t F6_zone_status : 1;
	uint8_t F6_zone_buff_debuff_status : 3;
	uint16_t red1_bullet_left;
	uint16_t red2_bullet_left;
	uint16_t blue1_bullet_left;
	uint16_t blue2_bullet_left;
	uint8_t lurk_mode;
	uint8_t res;
} ext_ICRA_buff_debuff_zone_and_lurk_status_t;
typedef  struct {
	uint32_t event_type;
} ext_event_data_t;
typedef  struct {
	uint8_t supply_projectile_id;
	uint8_t supply_robot_id;
	uint8_t supply_projectile_step;
	uint8_t supply_projectile_num;
} ext_supply_projectile_action_t;
typedef  struct {
	uint8_t level;
	uint8_t foul_robot_id;
} ext_referee_warning_t;
typedef  struct
{
	uint8_t dart_remaining_time;
} ext_dart_remaining_time_t;
typedef  struct
{
	uint8_t robot_id;
	uint8_t robot_level;
	uint16_t remain_HP;
	uint16_t max_HP;
	uint16_t shooter_id1_17mm_cooling_rate;
	uint16_t shooter_id1_17mm_cooling_limit;
	uint16_t shooter_id1_17mm_speed_limit;
	uint16_t shooter_id2_17mm_cooling_rate;
	uint16_t shooter_id2_17mm_cooling_limit;
	uint16_t shooter_id2_17mm_speed_limit;
	uint16_t shooter_id1_42mm_cooling_rate;
	uint16_t shooter_id1_42mm_cooling_limit;
	uint16_t shooter_id1_42mm_speed_limit;
	uint16_t chassis_power_limit;
	uint8_t mains_power_gimbal_output : 1;
	uint8_t mains_power_chassis_output : 1;
	uint8_t mains_power_shooter_output : 1;
} ext_game_robot_status_t;
typedef  struct
{
	uint16_t chassis_volt;
	uint16_t chassis_current;
	float chassis_power;
	uint16_t chassis_power_buffer;
	uint16_t shooter_id1_17mm_cooling_heat;
	uint16_t shooter_id2_17mm_cooling_heat;
	uint16_t shooter_id1_42mm_cooling_heat;
} ext_power_heat_data_t;
typedef  struct
{
	float x;
	float y;
	float z;
	float yaw;
} ext_game_robot_pos_t;
typedef  struct
{
	uint8_t power_rune_buff;
} ext_buff_t;
typedef  struct
{
	uint8_t attack_time;
} aerial_robot_energy_t;
typedef  struct
{
	uint8_t armor_id : 4;
	uint8_t hurt_type : 4;
} ext_robot_hurt_t;
typedef  struct
{
	uint8_t bullet_type;
	uint8_t shooter_id;
	uint8_t bullet_freq;
	float bullet_speed;
} ext_shoot_data_t;
typedef  struct
{
	uint16_t bullet_remaining_num_17mm;
	uint16_t bullet_remaining_num_42mm;
	uint16_t coin_remaining_num;
} ext_bullet_remaining_t;
typedef  struct
{
	uint32_t rfid_status;
} ext_rfid_status_t;
typedef  struct
{
	uint8_t dart_launch_opening_status;
	uint8_t dart_attack_target;
	uint16_t target_change_time;
	uint16_t operate_launch_cmd_time;
} ext_dart_client_cmd_t;


typedef  struct
{
	uint16_t data_cmd_id;
	uint16_t sender_ID;
	uint16_t receiver_ID;
} ext_student_interactive_header_data_t;
typedef  struct
{
	uint8_t* data;
} robot_interactive_data_t;
typedef  struct
{
	uint8_t operate_tpye;
	uint8_t layer;
} ext_client_custom_graphic_delete_t;

typedef  struct
{
	uint8_t graphic_name[3];
	uint32_t operate_tpye : 3;
	uint32_t graphic_tpye : 3;
	uint32_t layer : 4;
	uint32_t color : 4;
	uint32_t start_angle : 9;
	uint32_t end_angle : 9;
	uint32_t width : 10;
	uint32_t start_x : 11;
	uint32_t start_y : 11;
	uint32_t radius : 10;
	uint32_t end_x : 11;
	uint32_t end_y : 11;
} graphic_data_struct_t;
typedef  struct
{
	graphic_data_struct_t grapic_data_struct;
} ext_client_custom_graphic_single_t;
typedef  struct
{
	graphic_data_struct_t grapic_data_struct[2];
} ext_client_custom_graphic_double_t;
typedef  struct
{
	graphic_data_struct_t grapic_data_struct[5];
} ext_client_custom_graphic_five_t;
typedef  struct
{
	graphic_data_struct_t grapic_data_struct[7];
} ext_client_custom_graphic_seven_t;
typedef  struct {
	graphic_data_struct_t grapic_data_struct;
	uint8_t data[30];
} ext_client_custom_character_t;
typedef  struct
{
	float target_position_x;
	float target_position_y;
	float target_position_z;
	uint8_t commd_keyboard;
	uint16_t target_robot_ID;
} ext_robot_command_t;
typedef  struct
{
	uint16_t target_robot_ID;
	float target_position_x;
	float target_position_y;
} ext_client_map_command_t;
