#pragma once
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<vector>
class SELF_CHECK
{
public:
	void* check_data = nullptr;
	void* pre_check_data = nullptr;
	uint32_t check_length = 0;
	SELF_CHECK(uint32_t length, void* pdata, void* pthis);
	~SELF_CHECK();
	// 
	//static std::vector<SELF_CHECK*> node_list;
	static void run_detect(const std::vector<SELF_CHECK*>& node_list);

private:
	enum STATUS
	{
		 ERROR,FINE,BEGIN,RUNNING,END,INITIAL
	};
protected:
	STATUS m_status = INITIAL;
};
extern std::vector<SELF_CHECK*> node_list;
extern int i;


