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

struct pkttmp_table *
pkttmp_table_create(struct datapath *dp) {
    struct pkttmp_table *table;
    //size_t i;

    OFL_LOG_DBG(LOG_MODULE, "Creating PKTTMP TABLE.");

    table = xmalloc(sizeof(struct pkttmp_table));
    table->dp = dp;

    table->entries_num = 0;
    hmap_init(&table->entries);

    return table;
}

void
pkttmp_table_destroy(struct pkttmp_table *table) {
    struct pkttmp_entry *entry, *next;

    HMAP_FOR_EACH_SAFE(entry, next, struct pkttmp_entry, node, &table->entries) {
        pkttmp_entry_destroy(entry);
    }

    free(table);
}

struct pkttmp_entry *
pkttmp_entry_create(struct datapath *dp, struct pkttmp_table *table, struct ofl_exp_add_pkttmp *mod) {
    struct pkttmp_entry *e;
    //size_t i;
    uint64_t now_ms;
    now_ms = time_msec();

    e = xmalloc(sizeof(struct pkttmp_entry));
    e->created = now_ms;
    e->dp = dp;
    e->table = table;
    e->pkttmp_id = mod->pkttmp_id;
    e->data = NULL;
    e->data_length = mod->data_length;
    if (e->data_length > 0) {
        e->data = xmalloc(e->data_length);
        memcpy(e->data, mod->data, e->data_length);
    }
    //e->data = mod->data_length > 0 ? (uint8_t *)memcpy(malloc(mod->data_length), mod->data, mod->data_length) : NULL;


    OFL_LOG_DBG(LOG_MODULE, "Creating PKTTMP entry with following values id %u, data_len %zu.",e->pkttmp_id, e->data_length);

    return e;
}

void
pkttmp_entry_destroy(struct pkttmp_entry *entry) {
    free(entry->data);
    free(entry);
}
