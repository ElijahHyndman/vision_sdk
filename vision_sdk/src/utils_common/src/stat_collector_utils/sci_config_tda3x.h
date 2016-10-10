/*
 * SCI_CONFIG_TDA3x_H
 *
 * Statistic Collector Instrumentation Library
 * - Statistic Collector module specific definitions
 * - Device specific configurations
 *
 * Copyright (C) 20131 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

#ifndef SCI_CONFIG_TDA3x_H

#define SCI_CONFIG_TDA3x_H
#define SC_VER 116
#include "sc_reg.h"
#define SC_INTERFACE_VERSION 1.0

#define SC_LAT1_BASE 0x45002000
#define SC_LAT1_NUM_CNTRS 4
#define SC_LAT1_NUM_PROBES 6

#define SC_LAT2_BASE 0x45004000
#define SC_LAT2_NUM_CNTRS 4
#define SC_LAT2_NUM_PROBES 8

#define SC_LAT3_BASE 0x45003000
#define SC_LAT3_NUM_CNTRS 4
#define SC_LAT3_NUM_PROBES 7

#define SC_LAT4_BASE 0x45005000
#define SC_LAT4_NUM_CNTRS 4
#define SC_LAT4_NUM_PROBES 8
#define SC_MAP_MAX         4
#define SC_MAX_SLAVE          33
#define SC_MAX_MASTER         25
#define SC_MSTR_PROBE         25
#define SC_SDRAM_PROBE        0
#define SC_SDRAM_PROBE        0

/* Statistic Collector counter element definition*/
typedef struct sc_cnt_elements {
    int32_t num_filters;
    uint32_t cnt_offset;
}sc_cnt_elements_t;

/* lat1 Statistic Collector counter register configurations */
typedef struct sc_lat_1_counters {
        struct sc_lat_cnt_filter1 cnt[4];
    }sc_lat_1_counters_t;


/* lat1 Statistic Collector register configuration */
struct sc_lat_1_reg_map {
sc_lat_regs regs;
struct sc_lat_1_counters counters;
};

/* lat2 Statistic Collector counter register configurations */
struct sc_lat_2_counters {
        struct sc_lat_cnt_filter1 cnt[4];
    };


/* lat2 Statistic Collector register configuration */
struct sc_lat_2_reg_map {
sc_lat_regs regs;
struct sc_lat_2_counters counters;
};

/* lat3 Statistic Collector counter register configurations */
struct sc_lat_3_counters {
        struct sc_lat_cnt_filter1 cnt[4];
    };


/* lat3 Statistic Collector register configuration */
struct sc_lat_3_reg_map {
sc_lat_regs regs;
struct sc_lat_3_counters counters;
};

/* lat4 Statistic Collector counter register configurations */
struct sc_lat_4_counters {
        struct sc_lat_cnt_filter1 cnt[4];
    };


/* lat4 Statistic Collector register configuration */
struct sc_lat_4_reg_map {
sc_lat_regs regs;
struct sc_lat_4_counters counters;
};

/* Statistic Collector probe element definition */
typedef struct sc_probe_element {
    uint32_t probe_id;
    int32_t req_port_num;
    int32_t rsp_port_num;
}sc_probe_element_t;

enum sc_probe_valid {
    SCI_INVALID_PROBE,
     SCI_VALID_PROBE
};


/* Statistic Collector element definition */
enum sc_module_type {SDRAM, MSTR};
typedef struct sc_element_map {
        enum sc_module_type mod_type;
        uint32_t base_addr;
        int32_t mod_size;                   /* In bytes */
        int32_t num_counters;
        struct sc_cnt_elements * cnt_map;
        int32_t num_probes;
        struct sc_probe_element * probe_map;
        enum sc_probe_valid * sc_no_filter_valid_probe_map; /* First probe restricted counter*/
        uint32_t cnt_overflow_load; /*Counter saturation value */
        uint32_t cnt_overflow_lat; /*Latency counter saturation value */
}sc_element_map_t;

/* Statistic Collector element maps */
extern const sc_element_map_t sc_lat_1_map;
extern const sc_element_map_t sc_lat_2_map;
extern const sc_element_map_t sc_lat_3_map;
extern const sc_element_map_t sc_lat_4_map;

extern const sc_element_map_t * sc_map[SC_MAP_MAX];

 /* Statistic Collector names are in sc_map order */
extern const char * sci_unit_name_table[SC_MAP_MAX];


/* Statistic Collector probe name tables */

extern const char * sci_mstr_probe_name_table[SC_MSTR_PROBE];

extern const char * sci_sdram_probe_name_table[SC_SDRAM_PROBE]; /* not Implemented */

/* Statistic Collector master address table */
extern enum sci_master_addr sci_master_addr_table[SC_MAX_MASTER];
/* Statistic Collector master name table.
        In sci_master_addr_table order.
       */
extern const char * sci_master_name_table[SC_MAX_MASTER];
/* Statistic Collector slave address table */
extern enum sci_slave_addr sci_slave_addr_table[SC_MAX_SLAVE];
/* Statistic Collector slave name table.
       In sci_slave_addr_table order.
       */
extern const char * sci_slave_name_table[SC_MAX_SLAVE];
#endif

