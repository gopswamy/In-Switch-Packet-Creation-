#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include "openflow/openflow.h"
#include "openflow/beba-ext.h"
#include "ofl-exp-beba.h"
#include "oflib/ofl-log.h"
#include "oflib/ofl-print.h"
#include "oflib/ofl-utils.h"
#include "oflib/ofl-structs.h"
#include "oflib/oxm-match.h"
#include "lib/hash.h"
#include "lib/ofp.h"
#include "lib/ofpbuf.h"
#include "lib/timeval.h"



struct ofl_exp_beba_instr_header {
    struct ofl_instruction_experimenter   header; /* BEBA_VENDOR_ID */
    uint32_t   instr_type;
};

struct ofl_exp_instruction_in_switch_pkt_gen {
	struct ofl_exp_beba_instr_header  header; /* OFPIT_EXP_IN_SWITCH_PKT_GEN*/
	uint32_t				          pkttmp_id;
	size_t                     	      actions_num;
	struct ofl_action_header        **actions;
};


struct pkttmp_table {
    struct datapath  *dp;
	//struct ofl_msg_multipart_reply_group_features *features;
	size_t            entries_num;
    struct hmap       entries;
};

struct pkttmp_entry {
    struct hmap_node            node;

    uint32_t                    pkttmp_id;
    struct datapath             *dp;
    struct pkttmp_table         *table;
    uint64_t                    created;
    uint8_t                     *data;     /* to check if it is good for tmp implementation */
    size_t                      data_length;
};

struct pkttmp_table *
pkttmp_table_create(struct datapath *dp);

void
pkttmp_table_destroy(struct pkttmp_table *table);
