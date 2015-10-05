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

#include <inttypes.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include "ofl-exp.h"
//#include "ofl-exp-nicira.h"
#include "ofl-exp-openflow.h"
#include "../oflib/ofl-messages.h"
#include "../oflib/ofl-log.h"
#include "openflow/openflow.h"
//#include "openflow/nicira-ext.h"
#include "openflow/openflow-ext.h"

#define LOG_MODULE ofl_exp
OFL_LOG_INIT(LOG_MODULE)

/* begin AR#exp */
#define OUI_FMT                                                    \
    "%02"PRIx8":%02"PRIx8":%02"PRIx8
#define OUI_ARGS(ea)                                   \
    (ea)[2], (ea)[1], (ea)[0]
/* end AR#exp */


int
ofl_exp_msg_pack(struct ofl_msg_experimenter *msg, uint8_t **buf, size_t *buf_len) {
    switch (msg->experimenter_id) {
        case (OPENFLOW_VENDOR_ID): {
            return ofl_exp_openflow_msg_pack(msg, buf, buf_len);
        }
        default: {
            OFL_LOG_WARN(LOG_MODULE, "Trying to pack unknown EXPERIMENTER message (%u).", msg->experimenter_id);
            return -1;
        }
    }
}

ofl_err
ofl_exp_msg_unpack(struct ofp_header *oh, size_t *len, struct ofl_msg_experimenter **msg) {
    struct ofp_experimenter_header *exp;

    if (*len < sizeof(struct ofp_experimenter_header)) {
        OFL_LOG_WARN(LOG_MODULE, "Received EXPERIMENTER message is shorter than ofp_experimenter_header.");
        return ofl_error(OFPET_BAD_REQUEST, OFPBRC_BAD_LEN);
    }

    exp = (struct ofp_experimenter_header *)oh;

    switch (htonl(exp->experimenter)) {
        case (OPENFLOW_VENDOR_ID): {
            return ofl_exp_openflow_msg_unpack(oh, len, msg);
        }
        default: {
            OFL_LOG_WARN(LOG_MODULE, "Trying to unpack unknown EXPERIMENTER message (%u).", htonl(exp->experimenter));
            return ofl_error(OFPET_BAD_REQUEST, OFPBRC_BAD_EXPERIMENTER);
        }
    }
}

int
ofl_exp_msg_free(struct ofl_msg_experimenter *msg) {
    switch (msg->experimenter_id) {
        case (OPENFLOW_VENDOR_ID): {
            return ofl_exp_openflow_msg_free(msg);
        }
        default: {
            OFL_LOG_WARN(LOG_MODULE, "Trying to free unknown EXPERIMENTER message (%u).", msg->experimenter_id);
            free(msg);
            return -1;
        }
    }
}

char *
ofl_exp_msg_to_string(struct ofl_msg_experimenter *msg) {
    switch (msg->experimenter_id) {
        case (OPENFLOW_VENDOR_ID): {
            return ofl_exp_openflow_msg_to_string(msg);
        }
        default: {
            char *str;
            size_t str_size;
            FILE *stream = open_memstream(&str, &str_size);
            OFL_LOG_WARN(LOG_MODULE, "Trying to convert to string unknown EXPERIMENTER message (%u).", msg->experimenter_id);
            fprintf(stream, "exp{id=\"0x%"PRIx32"\"}", msg->experimenter_id);
            fclose(stream);
            return str;
        }
    }
}

int
ATN_ofl_exp_action_pack (struct ofl_action_header *src, struct ofp_action_header *dst) {
    struct ATN_ofl_action_exp *sa = (struct ATN_ofl_action_exp *)src;
    struct ATN_ofp_action_exp *da = (struct ATN_ofp_action_exp *)dst;

    switch (sa->exp_type) {
        case ATN_OFPAT_PUSH_L2_GRE_HEADER: {
            da->header.len              = htons(sizeof(struct ATN_ofp_action_exp));
            da->header.experimenter     = htonl(sa->experimenter);
            da->exp_type                = htonl(sa->exp_type);
            memset(da->pad, 0x00, 4);
            return sizeof(struct ATN_ofp_action_exp);
        }
        case ATN_OFPAT_POP_L2_GRE_HEADER:{
            da->header.len              = htons(sizeof(struct ATN_ofp_action_exp));
            da->header.experimenter     = htonl(sa->experimenter);
            da->exp_type                = htonl(sa->exp_type);
            memset(da->pad, 0x00, 4);
            return sizeof(struct ATN_ofp_action_exp);
        }
    }

    return 0;
}

ofl_err
ATN_ofl_exp_action_unpack (struct ofp_action_header *src, size_t *len, struct ofl_action_header **dst) {
    struct ATN_ofp_action_exp *sa = (struct ATN_ofp_action_exp *)src;
    struct ATN_ofl_action_exp *da = malloc(sizeof(struct ATN_ofl_action_exp));

    if (*len < sizeof(struct ATN_ofp_action_exp)) {
        OFL_LOG_WARN(LOG_MODULE, "Received EXPERIMENTER message has invalid length (%zu).", *len);
        return ofl_error(OFPET_BAD_REQUEST, OFPBRC_BAD_LEN);
    }

    switch (ntohl(sa->exp_type)) {
        case ATN_OFPAT_PUSH_L2_GRE_HEADER: {
            da->experimenter        = ntohl(sa->header.experimenter);
            da->exp_type            = ntohl(sa->exp_type);
            break;
        }
        case ATN_OFPAT_POP_L2_GRE_HEADER:{
			da->experimenter            = ntohl(sa->header.experimenter);
            da->exp_type                = ntohl(sa->exp_type);
			break;
        }
    }

    *len -= sizeof(struct ATN_ofp_action_exp);
    *dst = (struct ofl_action_header*) da;
    return 0;
}

 int
ATN_ofl_exp_action_free (struct ofl_action_header *act) {
    struct ATN_ofl_action_exp *da = (struct ATN_ofl_action_exp*) act;
    free(da);
    return 0;
}

size_t
ATN_ofl_exp_action_ofp_len (struct ofl_action_header *act) {

    return sizeof(struct ATN_ofp_action_exp);
}

char*
ATN_ofl_exp_action_to_string (struct ofl_action_header *act) {

    char* msg;
    struct ATN_ofl_action_exp *act_exp = (struct ATN_ofl_action_exp *)act;

    msg = malloc(sizeof(char)*256);

    switch (act_exp->exp_type) {
        case ATN_OFPAT_PUSH_L2_GRE_HEADER: {
            sprintf(msg, ":ATN_OFPAT_PUSH_L2_GRE_HEADER: \""OUI_FMT"\"", OUI_ARGS((uint8_t*)&act_exp->experimenter));
			break;

        }
        case ATN_OFPAT_POP_L2_GRE_HEADER:{
            sprintf(msg, ":ATN_OFPAT_POP_L2_GRE_HEADER: \""OUI_FMT"\"", OUI_ARGS((uint8_t*)&act_exp->experimenter));
			break;
        }
    }

    return msg;
}

/* For OFDPA2.0
 */
int OFDPA_ofl_exp_action_pack(struct ofl_action_header *src, struct ofp_action_header *dst)
{
    struct OFDPA_ofl_action_exp *sa = (struct OFDPA_ofl_action_exp *)src;

    switch(sa->exp_type)
    {
        case OFDPA_ACT_PUSH_L2_HEADER:
        case OFDPA_ACT_POP_L2_HEADER:
        case OFDPA_ACT_PUSH_CW:
        case OFDPA_ACT_POP_CW:
        case OFDPA_ACT_COPY_TC_IN:
        case OFDPA_ACT_COPY_TC_OUT:
        case OFDPA_ACT_DEC_TTL_MTU:
        {
            struct OFDPA_ofp_action_exp *da = (struct OFDPA_ofp_action_exp *)dst;

            da->header.len = htons(sizeof(struct OFDPA_ofp_action_exp));
            da->header.experimenter = htonl(sa->experimenter);
            da->exp_type = htons(sa->exp_type);
            memset(da->pad, 0x00, sizeof(da->pad));
            return sizeof(struct OFDPA_ofp_action_exp);
            break;
        }

        case OFDPA_ACT_SET_TC_FROM_TABLE:
        case OFDPA_ACT_SET_DSCP_FROM_TABLE:
        case OFDPA_ACT_SET_PCP_DFI_FROM_TABLE:
        case OFDPA_ACT_SET_QOS_FROM_TABLE:
        {
            struct OFDPA_ofl_action_exp_set_u8 *tmp_sa_p = (struct OFDPA_ofl_action_exp_set_u8 *)src;
            struct OFDPA_ofp_action_exp_set_u8 *da = (struct OFDPA_ofp_action_exp_set_u8 *)dst;

            da->header.len = htons(sizeof(struct OFDPA_ofp_action_exp_set_u8));
            da->header.experimenter = htonl(tmp_sa_p->experimenter);
            da->exp_type = htons(tmp_sa_p->exp_type);
            da->value = tmp_sa_p->value;
            memset(da->pad, 0x00, sizeof(da->pad));
            return sizeof(struct OFDPA_ofp_action_exp_set_u8);
            break;
        }

        case OFDPA_ACT_OAM_LM_RX_COUNT:
        case OFDPA_ACT_OAM_LM_TX_COUNT:
        case OFDPA_ACT_OAM_SET_COUNTER_FIELDS:
        {
            struct OFDPA_ofl_action_exp_set_u32 *tmp_sa_p = (struct OFDPA_ofl_action_exp_set_u32 *)src;
            struct OFDPA_ofp_action_exp_set_u32 *da = (struct OFDPA_ofp_action_exp_set_u32 *)dst;

            da->header.len = htons(sizeof(struct OFDPA_ofp_action_exp_set_u32));
            da->header.experimenter = htonl(tmp_sa_p->experimenter);
            da->exp_type = htons(tmp_sa_p->exp_type);
            da->value = htonl(tmp_sa_p->value);
            memset(da->pad, 0x00, sizeof(da->pad));
            return sizeof(struct OFDPA_ofp_action_exp_set_u32);
            break;
        }

        case OFDPA_ACT_CHECK_DROP_STATUS:
        {
            struct OFDPA_ofl_action_exp_drop_status *tmp_sa_p = (struct OFDPA_ofl_action_exp_drop_status *)src;
            struct OFDPA_ofp_action_exp_drop_status *da = (struct OFDPA_ofp_action_exp_drop_status *)dst;

            da->header.len = htons(sizeof(struct OFDPA_ofp_action_exp_drop_status));
            da->header.experimenter = htonl(tmp_sa_p->experimenter);
            da->exp_type = htons(tmp_sa_p->exp_type);
            da->drop_index = htonl(tmp_sa_p->drop_index);
            da->drop_type = tmp_sa_p->drop_type;
            memset(da->pad, 0x00, sizeof(da->pad));
            return sizeof(struct OFDPA_ofp_action_exp_drop_status);
            break;
        }
    }

    return sizeof(struct OFDPA_ofp_action_exp);
}

ofl_err OFDPA_ofl_exp_action_unpack(struct ofp_action_header *src, size_t *len, struct ofl_action_header **dst)
{
    struct OFDPA_ofp_action_exp *sa = (struct OFDPA_ofp_action_exp *)src;

    switch(ntohs(sa->exp_type))
    {
        case OFDPA_ACT_PUSH_L2_HEADER:
        case OFDPA_ACT_POP_L2_HEADER:
        case OFDPA_ACT_PUSH_CW:
        case OFDPA_ACT_POP_CW:
        case OFDPA_ACT_COPY_TC_IN:
        case OFDPA_ACT_COPY_TC_OUT:
        case OFDPA_ACT_DEC_TTL_MTU:
        {
            struct OFDPA_ofl_action_exp *da = malloc(sizeof(struct OFDPA_ofl_action_exp));

            if (*len < sizeof(struct OFDPA_ofp_action_exp))
            {
                OFL_LOG_WARN(LOG_MODULE, "Received EXPERIMENTER message has invalid length (%zu).", *len);
                return ofl_error(OFPET_BAD_REQUEST, OFPBRC_BAD_LEN);
            }

            da->experimenter = ntohl(sa->header.experimenter);
            da->exp_type = ntohs(sa->exp_type);
            *len -= sizeof(struct OFDPA_ofp_action_exp);
            *dst = (struct ofl_action_header*) da;
            break;
        }

        case OFDPA_ACT_SET_TC_FROM_TABLE:
        case OFDPA_ACT_SET_DSCP_FROM_TABLE:
        case OFDPA_ACT_SET_PCP_DFI_FROM_TABLE:
        case OFDPA_ACT_SET_QOS_FROM_TABLE:
        {
            struct OFDPA_ofp_action_exp_set_u8 *tmp_sa_p = (struct OFDPA_ofp_action_exp_set_u8 *)src;
            struct OFDPA_ofl_action_exp_set_u8 *da = malloc(sizeof(struct OFDPA_ofl_action_exp_set_u8));

            if (*len < sizeof(struct OFDPA_ofp_action_exp_set_u8))
            {
                OFL_LOG_WARN(LOG_MODULE, "Received EXPERIMENTER message has invalid length (%zu).", *len);
                return ofl_error(OFPET_BAD_REQUEST, OFPBRC_BAD_LEN);
            }

            da->value = tmp_sa_p->value;
            da->experimenter = ntohl(tmp_sa_p->header.experimenter);
            da->exp_type = ntohs(tmp_sa_p->exp_type);
            *len -= sizeof(struct OFDPA_ofp_action_exp_set_u8);
            *dst = (struct ofl_action_header*) da;
            break;
        }

        case OFDPA_ACT_OAM_LM_RX_COUNT:
        case OFDPA_ACT_OAM_LM_TX_COUNT:
        case OFDPA_ACT_OAM_SET_COUNTER_FIELDS:
        {
            struct OFDPA_ofp_action_exp_set_u32 *tmp_sa_p = (struct OFDPA_ofp_action_exp_set_u32 *)src;
            struct OFDPA_ofl_action_exp_set_u32 *da = malloc(sizeof(struct OFDPA_ofl_action_exp_set_u32));

            if (*len < sizeof(struct OFDPA_ofp_action_exp_set_u32))
            {
                OFL_LOG_WARN(LOG_MODULE, "Received EXPERIMENTER message has invalid length (%zu).", *len);
                return ofl_error(OFPET_BAD_REQUEST, OFPBRC_BAD_LEN);
            }

            da->value = ntohl(tmp_sa_p->value);
            da->experimenter = ntohl(tmp_sa_p->header.experimenter);
            da->exp_type = ntohs(tmp_sa_p->exp_type);
            *len -= sizeof(struct OFDPA_ofp_action_exp_set_u32);
            *dst = (struct ofl_action_header*) da;
            break;
        }

        case OFDPA_ACT_CHECK_DROP_STATUS:
        {
            struct OFDPA_ofp_action_exp_drop_status *tmp_sa_p = (struct OFDPA_ofp_action_exp_drop_status *)src;
            struct OFDPA_ofl_action_exp_drop_status *da = malloc(sizeof(struct OFDPA_ofl_action_exp_drop_status));

            if (*len < sizeof(struct OFDPA_ofp_action_exp_drop_status))
            {
                OFL_LOG_WARN(LOG_MODULE, "Received EXPERIMENTER message has invalid length (%zu).", *len);
                return ofl_error(OFPET_BAD_REQUEST, OFPBRC_BAD_LEN);
            }

            da->drop_index = ntohl(tmp_sa_p->drop_index);
            da->drop_type = tmp_sa_p->drop_type;
            da->experimenter = ntohl(tmp_sa_p->header.experimenter);
            da->exp_type = ntohs(tmp_sa_p->exp_type);
            *len -= sizeof(struct OFDPA_ofp_action_exp_drop_status);
            *dst = (struct ofl_action_header*) da;
            break;
        }
    }

    return 0;
}

int OFDPA_ofl_exp_action_free (struct ofl_action_header *act)
{
    struct OFDPA_ofl_action_exp *da = (struct OFDPA_ofl_action_exp*) act;

    switch(da->exp_type)
    {
        case OFDPA_ACT_PUSH_L2_HEADER:
        case OFDPA_ACT_POP_L2_HEADER:
        case OFDPA_ACT_PUSH_CW:
        case OFDPA_ACT_POP_CW:
        case OFDPA_ACT_COPY_TC_IN:
        case OFDPA_ACT_COPY_TC_OUT:
        case OFDPA_ACT_DEC_TTL_MTU:
        {
            struct OFDPA_ofl_action_exp *tmp_da_p = (struct OFDPA_ofl_action_exp*) act;

            free(tmp_da_p);
            break;
        }

        case OFDPA_ACT_SET_TC_FROM_TABLE:
        case OFDPA_ACT_SET_DSCP_FROM_TABLE:
        case OFDPA_ACT_SET_PCP_DFI_FROM_TABLE:
        case OFDPA_ACT_SET_QOS_FROM_TABLE:
        {
            struct OFDPA_ofl_action_exp_set_u8 *tmp_da_p = (struct OFDPA_ofl_action_exp_set_u8*) act;

            free(tmp_da_p);
            break;
        }

        case OFDPA_ACT_OAM_LM_RX_COUNT:
        case OFDPA_ACT_OAM_LM_TX_COUNT:
        case OFDPA_ACT_OAM_SET_COUNTER_FIELDS:
        {
            struct OFDPA_ofl_action_exp_set_u32 *tmp_da_p = (struct OFDPA_ofl_action_exp_set_u32*) act;

            free(tmp_da_p);
            break;
        }

        case OFDPA_ACT_CHECK_DROP_STATUS:
        {
            struct OFDPA_ofl_action_exp_drop_status *tmp_da_p = (struct OFDPA_ofl_action_exp_drop_status*) act;

            free(tmp_da_p);
            break;
        }
    }

    return 0;
}

size_t OFDPA_ofl_exp_action_ofp_len (struct ofl_action_header *act)
{
    struct OFDPA_ofl_action_exp *da = (struct OFDPA_ofl_action_exp*) act;

    switch(da->exp_type)
    {
        case OFDPA_ACT_PUSH_L2_HEADER:
        case OFDPA_ACT_POP_L2_HEADER:
        case OFDPA_ACT_PUSH_CW:
        case OFDPA_ACT_POP_CW:
        case OFDPA_ACT_COPY_TC_IN:
        case OFDPA_ACT_COPY_TC_OUT:
        case OFDPA_ACT_DEC_TTL_MTU:
            return sizeof(struct OFDPA_ofp_action_exp);
            break;

        case OFDPA_ACT_SET_TC_FROM_TABLE:
        case OFDPA_ACT_SET_DSCP_FROM_TABLE:
        case OFDPA_ACT_SET_PCP_DFI_FROM_TABLE:
        case OFDPA_ACT_SET_QOS_FROM_TABLE:
            return sizeof(struct OFDPA_ofp_action_exp_set_u8);
            break;

        case OFDPA_ACT_OAM_LM_RX_COUNT:
        case OFDPA_ACT_OAM_LM_TX_COUNT:
        case OFDPA_ACT_OAM_SET_COUNTER_FIELDS:
            return sizeof(struct OFDPA_ofp_action_exp_set_u32);
            break;

        case OFDPA_ACT_CHECK_DROP_STATUS:
            return sizeof(struct OFDPA_ofp_action_exp_drop_status);
            break;
    }

    return sizeof(struct OFDPA_ofp_action_exp);
}

char* OFDPA_ofl_exp_action_to_string(struct ofl_action_header *act)
{
    char* msg;
    struct OFDPA_ofl_action_exp *act_exp = (struct OFDPA_ofl_action_exp *)act;

    msg = malloc(sizeof(char)*256);

    switch(act_exp->exp_type)
    {
        case OFDPA_ACT_PUSH_L2_HEADER:
            sprintf(msg, ",[\"%s\"]", "OFDPA_ACT_PUSH_L2_HEADER");
            break;

        case OFDPA_ACT_POP_L2_HEADER:
            sprintf(msg, ",[\"%s\"]", "OFDPA_ACT_POP_L2_HEADER");
            break;

        case OFDPA_ACT_PUSH_CW:
            sprintf(msg, ",[\"%s\"]", "OFDPA_ACT_PUSH_CW");
            break;

        case OFDPA_ACT_POP_CW:
            sprintf(msg, ",[\"%s\"]", "OFDPA_ACT_POP_CW");
            break;

        case OFDPA_ACT_COPY_TC_IN:
            sprintf(msg, ",[\"%s\"]", "OFDPA_ACT_COPY_TC_IN");
            break;

        case OFDPA_ACT_COPY_TC_OUT:
            sprintf(msg, ",[\"%s\"]", "OFDPA_ACT_COPY_TC_OUT");
            break;

        case OFDPA_ACT_DEC_TTL_MTU:
            sprintf(msg, ",[\"%s\"]", "OFDPA_ACT_DEC_TTL_MTU");
            break;

        case OFDPA_ACT_SET_TC_FROM_TABLE:
        {
            struct OFDPA_ofl_action_exp_set_u8 *tmp_act_exp_p = (struct OFDPA_ofl_action_exp_set_u8*) act;

            sprintf(msg, ",{\"%s\":%d}", "OFDPA_ACT_SET_TC_FROM_TABLE", tmp_act_exp_p->value);
            break;
        }

        case OFDPA_ACT_SET_DSCP_FROM_TABLE:
        {
            struct OFDPA_ofl_action_exp_set_u8 *tmp_act_exp_p = (struct OFDPA_ofl_action_exp_set_u8*) act;

            sprintf(msg, ",{\"%s\":%d}", "OFDPA_ACT_SET_DSCP_FROM_TABLE", tmp_act_exp_p->value);
            break;
        }

        case OFDPA_ACT_SET_PCP_DFI_FROM_TABLE:
        {
            struct OFDPA_ofl_action_exp_set_u8 *tmp_act_exp_p = (struct OFDPA_ofl_action_exp_set_u8*) act;

            sprintf(msg, ",{\"%s\":%d}", "OFDPA_ACT_SET_PCP_DFI_FROM_TABLE", tmp_act_exp_p->value);
            break;
        }

        case OFDPA_ACT_SET_QOS_FROM_TABLE:
        {
            struct OFDPA_ofl_action_exp_set_u8 *tmp_act_exp_p = (struct OFDPA_ofl_action_exp_set_u8*) act;

            sprintf(msg, ",{\"%s\":%d}", "OFDPA_ACT_SET_QOS_FROM_TABLE", tmp_act_exp_p->value);
            break;
        }

        case OFDPA_ACT_OAM_LM_RX_COUNT:
        {
            struct OFDPA_ofl_action_exp_set_u32 *tmp_act_exp_p = (struct OFDPA_ofl_action_exp_set_u32*) act;

            sprintf(msg, ",{\"%s\":%ld}", "OFDPA_ACT_OAM_LM_RX_COUNT", tmp_act_exp_p->value);
            break;
        }

        case OFDPA_ACT_OAM_LM_TX_COUNT:
        {
            struct OFDPA_ofl_action_exp_set_u32 *tmp_act_exp_p = (struct OFDPA_ofl_action_exp_set_u32*) act;

            sprintf(msg, ",{\"%s\":%ld}", "OFDPA_ACT_OAM_LM_TX_COUNT", tmp_act_exp_p->value);
            break;
        }

        case OFDPA_ACT_OAM_SET_COUNTER_FIELDS:
        {
            struct OFDPA_ofl_action_exp_set_u32 *tmp_act_exp_p = (struct OFDPA_ofl_action_exp_set_u32*) act;

            sprintf(msg, ",{\"%s\":%ld}", "OFDPA_ACT_OAM_SET_COUNTER_FIELDS", tmp_act_exp_p->value);
            break;
        }

        case OFDPA_ACT_CHECK_DROP_STATUS:
        {
            struct OFDPA_ofl_action_exp_drop_status *tmp_act_exp_p = (struct OFDPA_ofl_action_exp_drop_status*) act;

            sprintf(msg, ",{\"%s\":\"index %ld & type %d\"", "OFDPA_ACT_CHECK_DROP_STATUS", tmp_act_exp_p->drop_index, tmp_act_exp_p->drop_type);
            break;
        }
    }

    return msg;
}
/* End of OFDPA2.0
 */
