#include "SELF_CHECK.h"
//std::vector<SELF_CHECK*> SELF_CHECK::node_list;
std::vector<SELF_CHECK*> node_list(12);
int i = 0;
void* test1 =(void*)&node_list;
SELF_CHECK::SELF_CHECK(uint32_t length,void* pdata,void* pthis)
{
    node_list[i] = (SELF_CHECK*)pthis;
    i++;
    //node_list.push_back((SELF_CHECK*)pthis);
    this->check_data = pdata;
    this->check_length = length;
    this->m_status = INITIAL;
    this->pre_check_data = malloc(sizeof(uint8_t) * length);
    memset(pre_check_data, 0, sizeof(uint8_t) * length);
}
SELF_CHECK::~SELF_CHECK()
{
    free(pre_check_data);
}
void SELF_CHECK::run_detect(const std::vector<SELF_CHECK*>& node_list)
{
    for (auto i : node_list)
    {
        if (i->check_data)
        {
            uint8_t pd = 0;
            for (int j = 0; j < i->check_length; i++)
            {
                if (((uint8_t*)i->check_data)[j] ^ ((uint8_t*)i->pre_check_data)[j])
                {
                    i->m_status = FINE;
                    ++pd ;
                    break;
                }
            }
            if (!pd)i->m_status = ERROR;
        }
    }
}

