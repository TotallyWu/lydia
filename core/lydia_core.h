#ifndef _LYDIA_CORE_H_
#define _LYDIA_CORE_H_

#ifdef _c_plus_plus
    extern "C"{
#endif
#include <stdint.h>


/***********************************************
 *  lydia metadata define
 * ********************************************/
    typedef enum{
        LYDIA_METADATA_SRC_CARD,
        LYDIA_METADATA_SRC_ENTRY_POINT,
        LYDIA_METADATA_SRC_CARD,
        LYDIA_METADATA_SRC_CARD,
    }lydia_metadata_src_t;
    
    typedef enum{

    }lydia_metadata_fmt_t;

    typedef enum{

    }lydia_metadata_tpl_t;

    typedef enum{

    }lydia_metadata_len_attr_t;

    typedef enum{

    }lydia_metadata_updater_t;

    typedef struct _lydia_metadata_attr_t
    {
        char *name;
        char *desc;
        lydia_metadata_src_t scr;
        lydia_metadata_fmt_t fmt;
        lydia_metadata_tpl_t tpl;
        lydia_metadata_len_attr_t len_attr;
        lydia_metadata_updater_t daupter;
    }lydia_metadata_attr_t;

    typedef struct _lydia_metadata_t{
        uint32_t tag;
        lydia_metadata_attr_t attr;
        uint16_t l;
        uint8_t *v;
    }lydia_metadata_t;

    typedef struct _lydia_metadata_list_t{
        lydia_metadata_t *data;
        uint16_t size;
        struct repo{
            uint8_t *buf;
            uint16_t len;
        }repo;
    }lydia_metadata_list_t;

/***********************************************
 *  lydia application selection define
 * ********************************************/
    #define MAX_AID_LEN         16
    #define VERSION_LEN         2
    typedef struct _lyadia_as_aid_t{
        uint8_t version[VERSION_LEN];
        uint8_t id[MAX_AID_LEN];
        uint8_t len;
    }lyadia_as_aid_t;

    #define MAX_DOL_LEN         128
    #define TAC_SIZE            5

    typedef struct _lydia_as_app_config_t{
        union mark
        {
            uint8_t asRaw;
            struct subdivs
            {
                uint8_t partial_match:1;
                uint8_t force_confirm:1;
                uint8_t random_trans_sel:1;
                uint8_t is_ddol_exist:1;
                uint8_t is_default_tac_exist:1;
                uint8_t is_online_tac_exist:1;
                uint8_t is_denial_tac_exist:1;
                uint8_t is_online_pin_sprt:1;
                uint8_t is_velocity_sprt:1;
            }asBits;
        }mark;

        uint8_t priority;
        uint8_t default_ddol[MAX_DOL_LEN];
        uint8_t default_tdol[MAX_DOL_LEN];
        uint8_t tartget_percentage;
        uint32_t threshold;
        uint8_t default_tac[TAC_SIZE];
        uint8_t online_tac[TAC_SIZE];
        uint8_t denial_tac[TAC_SIZE];
        uint32_t floor_limit;
        uint32_t ec_trans_limit;
        uint32_t cl_offline_limit;
        uint32_t cl_trans_limit;
        uint32_t cvm_limit;
    }lydia_as_app_config_t;

    typedef struct _lydia_as_app_t{
        lyadia_as_aid_t aid;
        lydia_as_app_config_t config;
    }lydia_as_app_t;

    typedef struct _lydia_as_app_list_t{
        lydia_as_app_t *apps;
        uint8_t size;
    }lydia_as_app_list_t;

/*************************************************************
 *  lydia certificates for offline data authentication
 * **********************************************************/
    typedef enum _lydia_ca_hash_schm_t{
        LYDIA_CA_HASH_SCHEM_SHA1,
    }lydia_ca_hash_schm_t;
    
    typedef enum _lydia_ca_sign_schm_t{
        LYDIA_CA_SIGN_SCHEM_RSA,
        LYDIA_CA_SIGN_SCHEM_SM,
    }lydia_ca_sign_schm_t;

    typedef struct _lydia_ca_schm_t{
        lydia_ca_hash_schm_t hash_schm;
        lydia_ca_sign_schm_t sign_schm;
    }lydia_ca_schm_t;

    #define RID_LEN         (5)
    #define INDATE_LEN      (4)
    #define MODULE_LEN      (248)
    #define EXPONENT_LEN      (3)

    #define SM_ID_LEN       (80)
    #define SM_POINT_SIZE      (32)

    typedef struct _lydia_ca_cert_t{
        uint8_t magic;
        uint8_t rid[RID_LEN];
        uint8_t index;
        uint8_t indate[INDATE_LEN];
        lydia_ca_schm_t schm;
        union 
        {
            struct raw{
                uint8_t *value;
                uint16_t len;
            }asRaw;

            struct rsa
            {
                uint8_t module[MODULE_LEN];
                uint16_t module_size;
                uint8_t exponent[EXPONENT_LEN];
            }asRsa;

            struct sm
            {
                uint8_t id[SM_ID_LEN];
                uint8_t id_len;
                uint16_t entl;
                uint8_t x[SM_POINT_SIZE];
                uint8_t y[SM_POINT_SIZE];
            }asSm;
        }pk;
    }lydia_ca_cert_t;

    typedef struct _lydia_ca_cert_list_t{
        lydia_ca_cert_t *certs;
        int8_t size;
    }lydia_ca_cert_list_t;

/*************************************************************
 *  lydia context
 * **********************************************************/
    typedef struct _lydia_context_t{
        lydia_metadata_list_t *metadata_list;
        lydia_as_app_list_t   *app_list;
        lydia_ca_cert_list_t  *ca_cert_list;
    }lydia_context_t;
#ifdef _c_plus_plus
    }
#endif
#endif