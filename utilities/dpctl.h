/* Copyright (c) 2011, TrafficLab, Ericsson Research, Hungary
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of the Ericsson Research nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * Author: Zoltán Lajos Kis <zoltan.lajos.kis@ericsson.com>
 */

#ifndef DPCTL_H
#define DPCTL_H 1

#include "openflow/openflow.h"

struct names8 {
    uint8_t   code;
    char     *name;
};

struct names16 {
    uint16_t   code;
    char      *name;
};

struct names32 {
    uint32_t   code;
    char      *name;
};



static struct names32 port_names[] = {
        {OFPP_IN_PORT,    "in_port"},
        {OFPP_TABLE,      "table"},
        {OFPP_NORMAL,     "normal"},
        {OFPP_FLOOD,      "flood"},
        {OFPP_ALL,        "all"},
        {OFPP_CONTROLLER, "ctrl"},
        {OFPP_LOCAL,      "local"},
        {OFPP_ANY,        "any"}
};

static struct names32 queue_names[] = {
        {OFPQ_ALL, "all"}
};

static struct names32 group_names[] = {
        {OFPG_ALL, "all"},
        {OFPG_ANY, "any"}
};

static struct names16 ext_header_names[] = {
        {OFPIEH_NONEXT, "no_next"},
        {OFPIEH_ESP,    "esp"},
        {OFPIEH_AUTH,   "auth"},
        {OFPIEH_DEST,   "dest"},
        {OFPIEH_FRAG,   "frag"},
        {OFPIEH_ROUTER, "router"},
        {OFPIEH_HOP,    "hop"},
        {OFPIEH_UNREP,  "unrep"},
        {OFPIEH_UNSEQ,  "unseq"}
};

static struct names8 group_type_names[] = {
        {OFPGT_ALL,      "all"},
        {OFPGT_SELECT,   "sel"},
        {OFPGT_INDIRECT, "ind"},
        {OFPGT_FF,       "ff"}
};

static struct names16 group_mod_cmd_names[] = {
        {OFPGC_ADD,    "add"},
        {OFPGC_MODIFY, "mod"},
        {OFPGC_DELETE, "del"}
};

static struct names16 meter_mod_cmd_names[] = {
        {OFPMC_ADD,    "add"},
        {OFPMC_MODIFY, "mod"},
        {OFPMC_DELETE, "del"}
};

static struct names8 table_names[] = {
        {0xff, "all"}
};

static struct names16 inst_names[] = {
        {OFPIT_GOTO_TABLE,     "goto"},
        {OFPIT_WRITE_METADATA, "meta"},
        {OFPIT_WRITE_ACTIONS,  "write"},
        {OFPIT_APPLY_ACTIONS,  "apply"},
        {OFPIT_CLEAR_ACTIONS,  "clear"},
        {OFPIT_METER,  "meter"}
};

static struct names8 flow_mod_cmd_names[] = {
        {OFPFC_ADD,           "add"},
        {OFPFC_MODIFY,        "mod"},
        {OFPFC_MODIFY_STRICT, "mods"},
        {OFPFC_DELETE,        "del"},
        {OFPFC_DELETE_STRICT, "dels"}
};

static struct names32 buffer_names[] = {
        {0xffffffff, "none"}
};

static struct names16 vlan_vid_names[] = {
        {OFPVID_PRESENT,  "any"},
        {OFPVID_NONE, "none"}
};


static struct names16 action_names[] = {
        {OFPAT_OUTPUT,         "output"},
        {OFPAT_COPY_TTL_OUT,   "ttl_out"},
        {OFPAT_COPY_TTL_IN,    "ttl_in"},
        {OFPAT_SET_MPLS_TTL,   "mpls_ttl"},
        {OFPAT_DEC_MPLS_TTL,   "mpls_dec"},
        {OFPAT_PUSH_VLAN,      "push_vlan"},
        {OFPAT_POP_VLAN,       "pop_vlan"},
        {OFPAT_PUSH_PBB,       "push_pbb"},
        {OFPAT_POP_PBB,        "pop_pbb"},
        {OFPAT_PUSH_MPLS,      "push_mpls"},
        {OFPAT_POP_MPLS,       "pop_mpls"},
        {OFPAT_SET_QUEUE,      "queue"},
        {OFPAT_GROUP,          "group"},
        {OFPAT_SET_NW_TTL,     "nw_ttl"},
        {OFPAT_DEC_NW_TTL,     "nw_dec"},
        {OFPAT_SET_FIELD,      "set_field"}
};

/* begin AR#exp */

#define ATN_EXP_ACTION_PUSH_L2_GRE "exp_push_l2_gre"
#define ATN_EXP_ACTION_POP_L2_GRE "exp_pop_l2_gre"

static struct names16 atn_action_names[] = {
        {ATN_OFPAT_PUSH_L2_GRE_HEADER,   ATN_EXP_ACTION_PUSH_L2_GRE},
        {ATN_OFPAT_POP_L2_GRE_HEADER,   ATN_EXP_ACTION_POP_L2_GRE}
};

/* For OFDPA2.0
 */
#define OFDPA_EXP_ACTION_PUSH_L2_HEADER         "ofdpa_push_l2hdr"
#define OFDPA_EXP_ACTION_POP_L2_HEADER          "ofdpa_pop_l2hdr"
#define OFDPA_EXP_ACTION_PUSH_CW                "ofdpa_push_cw"
#define OFDPA_EXP_ACTION_POP_CW                 "ofdpa_pop_cw"
#define OFDPA_EXP_ACTION_COPY_TC_IN             "ofdpa_copy_tc_in"
#define OFDPA_EXP_ACTION_COPY_TC_OUT            "ofdpa_copy_tc_out"
#define OFDPA_EXP_ACTION_SET_TC_FROM_TABLE      "ofdpa_set_tc_from_table"
#define OFDPA_EXP_ACTION_SET_DSCP_FROM_TABLE    "ofdpa_set_dscp_from_table"
#define OFDPA_EXP_ACTION_SET_PCP_DFI_FROM_TABLE "ofdpa_set_pcpdei_from_table"
#define OFDPA_EXP_ACTION_OAM_LM_RX_COUNT        "ofdpa_oam_lm_rx_count"
#define OFDPA_EXP_ACTION_OAM_LM_TX_COUNT        "ofdpa_oam_lm_tx_count"
#define OFDPA_EXP_ACTION_OAM_SET_COUNTER_FIELDS "ofdpa_set_counter_fields"
#define OFDPA_EXP_ACTION_DEC_TTL_MTU            "ofdpa_dec_ttl_mtu"
#define OFDPA_EXP_ACTION_CHECK_DROP_STATUS      "ofdpa_check_drop_status"
#define OFDPA_EXP_ACTION_SET_QOS_FROM_TABLE     "ofdpa_set_qos_from_table"

static struct names16 ofdpa_exp_action_names[] = {
    {OFDPA_ACT_PUSH_L2_HEADER,      OFDPA_EXP_ACTION_PUSH_L2_HEADER},
    {OFDPA_ACT_POP_L2_HEADER,       OFDPA_EXP_ACTION_POP_L2_HEADER},
    {OFDPA_ACT_PUSH_CW,             OFDPA_EXP_ACTION_PUSH_CW},
    {OFDPA_ACT_POP_CW,              OFDPA_EXP_ACTION_POP_CW},
    {OFDPA_ACT_COPY_TC_IN,          OFDPA_EXP_ACTION_COPY_TC_IN},
    {OFDPA_ACT_COPY_TC_OUT,         OFDPA_EXP_ACTION_COPY_TC_OUT},
    {OFDPA_ACT_SET_TC_FROM_TABLE,   OFDPA_EXP_ACTION_SET_TC_FROM_TABLE},
    {OFDPA_ACT_SET_DSCP_FROM_TABLE, OFDPA_EXP_ACTION_SET_DSCP_FROM_TABLE},
    {OFDPA_ACT_SET_PCP_DFI_FROM_TABLE,   OFDPA_EXP_ACTION_SET_PCP_DFI_FROM_TABLE},
    {OFDPA_ACT_OAM_LM_TX_COUNT,     OFDPA_EXP_ACTION_OAM_LM_TX_COUNT},
    {OFDPA_ACT_OAM_LM_RX_COUNT,     OFDPA_EXP_ACTION_OAM_LM_RX_COUNT},
    {OFDPA_ACT_OAM_SET_COUNTER_FIELDS,   OFDPA_EXP_ACTION_OAM_SET_COUNTER_FIELDS},
    {OFDPA_ACT_DEC_TTL_MTU,         OFDPA_EXP_ACTION_DEC_TTL_MTU},
    {OFDPA_ACT_CHECK_DROP_STATUS,   OFDPA_EXP_ACTION_CHECK_DROP_STATUS},
    {OFDPA_ACT_SET_QOS_FROM_TABLE,  OFDPA_EXP_ACTION_SET_QOS_FROM_TABLE}
};
/* End of OFDPA2.0
 */

/* end AR#exp */
static struct names16 band_names[] = {
    {OFPMBT_DROP, "drop"},
    {OFPMBT_DSCP_REMARK, "dscp_remark"},
    {OFPMBT_SET_COLOR, "set_color"},
    {OFPMBT_EXPERIMENTER, "exp"}
};

/**/
static struct names32 role_names[] = {
        {OFPCR_ROLE_EQUAL,        "equal"},
        {OFPCR_ROLE_MASTER,       "master"},
        {OFPCR_ROLE_NOCHANGE,     "nochange"},
        {OFPCR_ROLE_SLAVE,        "slave"},

};
/**/

#define FLOW_MOD_COMMAND       "cmd"
#define FLOW_MOD_COOKIE        "cookie"
#define FLOW_MOD_COOKIE_MASK   "cookie_mask"
#define FLOW_MOD_TABLE_ID      "table"
#define FLOW_MOD_IDLE          "idle"
#define FLOW_MOD_HARD          "hard"
#define FLOW_MOD_PRIO          "prio"
#define FLOW_MOD_BUFFER        "buffer"
#define FLOW_MOD_OUT_PORT      "out_port"
#define FLOW_MOD_OUT_GROUP     "out_group"
#define FLOW_MOD_FLAGS         "flags"
#define FLOW_MOD_MATCH         "match"


#define MATCH_IN_PORT        "in_port"
#define MATCH_IN_PHY_PORT    "in_phy_port"
#define MATCH_DL_SRC         "eth_src"
#define MATCH_DL_SRC_MASK    "eth_src_mask"
#define MATCH_DL_DST         "eth_dst"
#define MATCH_DL_DST_MASK    "eth_dst_mask"
#define MATCH_DL_VLAN        "vlan_vid"
#define MATCH_IP_DSCP        "ip_dscp"
#define MATCH_IP_ECN         "ip_ecn"
#define MATCH_DL_VLAN_PCP    "vlan_pcp"
#define MATCH_DL_TYPE        "eth_type"
#define MATCH_NW_PROTO       "ip_proto"
#define MATCH_NW_SRC         "ip_src"
#define MATCH_NW_SRC_MASK    "nw_src_mask"
#define MATCH_NW_DST         "ip_dst"
#define MATCH_NW_DST_MASK    "ipv4_dst_mask"
#define MATCH_TP_SRC         "tcp_src"
#define MATCH_TP_DST         "tcp_dst"
#define MATCH_UDP_SRC        "udp_src"
#define MATCH_UDP_DST        "udp_dst"
#define MATCH_SCTP_SRC       "sctp_src"
#define MATCH_SCTP_DST       "sctp_dst"
#define MATCH_ICMPV4_CODE    "icmp_code"
#define MATCH_ICMPV4_TYPE    "icmp_type"
#define MATCH_ARP_OP         "arp_op"
#define MATCH_ARP_SHA        "arp_sha"
#define MATCH_ARP_THA        "arp_tha"
#define MATCH_ARP_SPA        "arp_spa"
#define MATCH_ARP_TPA        "arp_tpa"
#define MATCH_NW_SRC_IPV6    "ipv6_src"
#define MATCH_NW_DST_IPV6    "ipv6_dst"
#define MATCH_ICMPV6_CODE    "icmpv6_code"
#define MATCH_ICMPV6_TYPE    "icmpv6_type"
#define MATCH_IPV6_FLABEL    "ipv6_flabel"
#define MATCH_IPV6_ND_TARGET "ipv6_nd_target"
#define MATCH_IPV6_ND_SLL    "ipv6_nd_sll"
#define MATCH_IPV6_ND_TLL    "ipv6_nd_tll"
#define MATCH_MPLS_LABEL     "mpls_label"
#define MATCH_MPLS_TC        "mpls_tc"
#define MATCH_MPLS_BOS       "mpls_bos"
#define MATCH_METADATA       "meta"
#define MATCH_METADATA_MASK  "meta_mask"
#define MATCH_PBB_ISID       "pbb_isid"
#define MATCH_TUNNEL_ID      "tunn_id"
#define MATCH_EXT_HDR        "ext_hdr"

/* begin AR#exp */
#define ATN_MATCH_EXP_INNER_ETH_DST       "exp_inner_eth_dst"
#define ATN_MATCH_EXP_INNER_ETH_SRC       "exp_inner_eth_src"
#define ATN_MATCH_EXP_INNER_VLAN_VID      "exp_inner_vlan_vid"
/* end AR#exp */

/* For OFDPA2.0
 */
#define MATCH_OFDPA_VRF "ofdpa_vrf"
#define MATCH_OFDPA_TRAFFIC_CLASS "ofdpa_tc"
#define MATCH_OFDPA_COLOR "ofdpa_color"
#define MATCH_OFDPA_DEI "ofdpa_dei"
#define MATCH_OFDPA_QOS_INDEX "ofdpa_qos_index"
#define MATCH_OFDPA_LMEP_ID "ofdpa_lmep_id"
#define MATCH_OFDPA_MPLS_TTL "ofdpa_mpls_ttl"
#define MATCH_OFDPA_MPLS_L2_PORT "ofdpa_mpls_l2_port"
#define MATCH_OFDPA_OVID "ofdpa_ovid"
#define MATCH_OFDPA_MPLS_DATA_FIRST_NIBBLE "ofdpa_mpls_data_first_nibble"
#define MATCH_OFDPA_MPLS_ACH_CHANNEL "ofdpa_mpls_ach_channel"
#define MATCH_OFDPA_MPLS_NEXT_LABEL_IS_GAL "ofdpa_mpls_next_label_is_gal"
#define MATCH_OFDPA_OAM_Y1731_MDL "ofdpa_oam_y1731_mdl"
#define MATCH_OFDPA_OAM_Y1731_OPCODE "ofdpa_oam_y1731_opcode"
#define MATCH_OFDPA_COLOR_ACTIONS_INDEX "ofdpa_color_actions_index"
#define MATCH_OFDPA_TXFCL "ofdpa_txfcl"
#define MATCH_OFDPA_RXFCL "ofdpa_rxfcl"
#define MATCH_OFDPA_RX_TIMESTAMP "ofdpa_rx_timestamp"
#define MATCH_OFDPA_PROTECTION_INDEX "ofdpa_protection_index"  /* not used */
#define MATCH_OFDPA_ACTSET_OUTPUT "ofdpa_actset_output"

#define OFDPA_EXPERIMENTER_ID 0x1018
/* End of OFDPA2.0
 */


#define GROUP_MOD_COMMAND "cmd"
#define GROUP_MOD_TYPE    "type"
#define GROUP_MOD_GROUP   "group"

#define BUCKET_WEIGHT       "weight"
#define BUCKET_WATCH_PORT   "port"
#define BUCKET_WATCH_GROUP  "group"

#define METER_MOD_COMMAND "cmd"
#define METER_MOD_FLAGS   "flags"
#define METER_MOD_METER   "meter"

#define BAND_RATE "rate"
#define BAND_BURST_SIZE "burst"
#define BAND_PREC_LEVEL "prec_level"

#define BAND_EXP_ID "exp_id"
#define BAND_EXP_TYPE "exp_type"
#define BAND_EXP_MODE "mode"
#define BAND_EXP_COLOR_AWARE "color_aware"
#define BAND_EXP_COLOR "color"

#define CONFIG_FLAGS "flags"
#define CONFIG_MISS  "miss"


#define PORT_MOD_PORT      "port"
#define PORT_MOD_HW_ADDR   "addr"
#define PORT_MOD_HW_CONFIG "conf"
#define PORT_MOD_MASK      "mask"
#define PORT_MOD_ADVERTISE "adv"


#define TABLE_MOD_TABLE  "table"
#define TABLE_MOD_CONFIG "conf"

/**/
#define ROLE_MOD "role"
#define ROLE_MOD_GENERATION_ID "gen_id"
#define V_BITMAP "versionbitmap"


#define PACKET_OUT_BUFID    "buf"
#define PACKET_OUT_INPORT   "port"

#define DATA_ETH_SRC  "eth_src"
#define DATA_ETH_DST  "eth_dst"
#define DATA_ETH_TYPE "type"
#define DATA_SIZE     "size"
#define DATA_FILE     "file"

/* begin AR#set-async */
#define PACKET_IN_MASK      "packet_in_mask"
#define PORT_STATUS_MASK    "port_status_mask"
#define FLOW_REMOVED_MASK   "flow_removed_mask"
/* end AR#set-async */

#define KEY_VAL    "="
#define KEY_VAL2   ":"
#define KEY_SEP    ","
/* begin AR#exp */
#define KEY_PLUS   "+"
/* end AR#exp */
#define MASK_SEP   "/"

#define ADD   "+"
#define WILDCARD_SUB   '-'



#define NUM_ELEMS( x )   (sizeof(x) / sizeof(x[0]))


#endif /* DPCTL_H */
