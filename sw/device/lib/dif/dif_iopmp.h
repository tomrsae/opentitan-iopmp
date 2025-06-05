// Copyright lowRISC contributors (OpenTitan project).
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0



#ifndef OPENTITAN_SW_DEVICE_LIB_DIF_DIF_IOPMP_H_
#define OPENTITAN_SW_DEVICE_LIB_DIF_DIF_IOPMP_H_

/**
 * @file
 * @brief <a href="/book/hw/ip/iopmp/">IOPMP</a> Device Interface Functions
 */

#include <stdint.h>

#include "sw/device/lib/dif/autogen/dif_iopmp_autogen.h"

// INFO registers
#define IOPMP_VERSION_REG_OFFSET 0x0000
#define IOPMP_IMPLEMENTATION_REG_OFFSET 0x0004
#define IOPMP_HWCFG0_REG_OFFSET 0x0008
  // add value bitfields for hwcfg0 as necessary
#define IOPMP_HWCFG1_REG_OFFSET 0x000C
  // add value bitfields for hwcfg1 as necessary
#define IOPMP_HWCFG2_REG_OFFSET 0x0010
  // add value bitfields for hwcfg2 as necessary
#define IOPMP_ENTRYOFFSET_REG_OFFSET 0x0014

// SRCMD table registers
#define IOPMP_SRCMD_EN_REG_OFFSET 0x1000
#define IOPMP_SRCMD_ENTRY_SIZE 32

// MDCFG table registers
#define IOPMP_MDCFG_REG_OFFSET 0x0800
#define IOPMP_MDCFG_ENTRY_SIZE 4
#define IOPMP_MDCFG_VAL_T_MASK 0xffffu
#define IOPMP_MDCFG_VAL_T_OFFSET 0
#define IOPMP_MDCFG_VAL_T_FIELD \
  ((bitfield_field32_t) { .mask = IOPMP_MDCFG_VAL_T_MASK, .index = IOPMP_MDCFG_VAL_T_OFFSET })

// Entry array registers
// uses "rel" offsets because base offsets are unknown at compile-time
#define IOPMP_ENTRY_ADDRH_REL_REG_OFFSET 0x4
#define IOPMP_ENTRY_CFG_REL_REG_OFFSET 0x8
#define IOPMP_ENTRY_ENTRY_SIZE 16
#define IOPMP_ENTRY_CFG_VAL_R_OFFSET 0
#define IOPMP_ENTRY_CFG_VAL_R_FIELD ((bitfield_bit32_index_t) IOPMP_ENTRY_CFG_VAL_R_OFFSET)
#define IOPMP_ENTRY_CFG_VAL_W_OFFSET 1
#define IOPMP_ENTRY_CFG_VAL_W_FIELD ((bitfield_bit32_index_t) IOPMP_ENTRY_CFG_VAL_W_OFFSET)
#define IOPMP_ENTRY_CFG_VAL_X_OFFSET 2
#define IOPMP_ENTRY_CFG_VAL_X_FIELD ((bitfield_bit32_index_t) IOPMP_ENTRY_CFG_VAL_X_OFFSET)
#define IOPMP_ENTRY_CFG_VAL_A_OFFSET 3
#define IOPMP_ENTRY_CFG_VAL_A_MASK 0x3u
#define IOPMP_ENTRY_CFG_VAL_A_FIELD \
  ((bitfield_field32_t) { .mask = IOPMP_ENTRY_CFG_VAL_A_MASK, .index = IOPMP_ENTRY_CFG_VAL_A_OFFSET })
#define IOPMP_ENTRY_CFG_VAL_SIRE_OFFSET 5
#define IOPMP_ENTRY_CFG_VAL_SIRE_FIELD ((bitfield_bit32_index_t) IOPMP_ENTRY_CFG_VAL_SIRE_OFFSET)
#define IOPMP_ENTRY_CFG_VAL_SIWE_OFFSET 6
#define IOPMP_ENTRY_CFG_VAL_SIWE_FIELD ((bitfield_bit32_index_t) IOPMP_ENTRY_CFG_VAL_SIWE_OFFSET)
#define IOPMP_ENTRY_CFG_VAL_SIXE_OFFSET 7
#define IOPMP_ENTRY_CFG_VAL_SIXE_FIELD ((bitfield_bit32_index_t) IOPMP_ENTRY_CFG_VAL_SIXE_OFFSET)
#define IOPMP_ENTRY_CFG_VAL_SERE_OFFSET 8
#define IOPMP_ENTRY_CFG_VAL_SERE_FIELD ((bitfield_bit32_index_t) IOPMP_ENTRY_CFG_VAL_SERE_OFFSET)
#define IOPMP_ENTRY_CFG_VAL_SEWE_OFFSET 9
#define IOPMP_ENTRY_CFG_VAL_SEWE_FIELD ((bitfield_bit32_index_t) IOPMP_ENTRY_CFG_VAL_SEWE_OFFSET)
#define IOPMP_ENTRY_CFG_VAL_SEXE_OFFSET 10
#define IOPMP_ENTRY_CFG_VAL_SEXE_FIELD ((bitfield_bit32_index_t) IOPMP_ENTRY_CFG_VAL_SEXE_OFFSET)

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

/**
 * Runtime configuration for IOPMP.
 *
 * This struct describes (SOFTWARE) runtime information for one-time
 * configuration of the hardware.
 */
typedef struct dif_iopmp_config {
  int32_t entryoffset;
} dif_iopmp_config_t;


/**
 * Parameters for a IOPMP transaction.
 */
typedef struct dif_iopmp_transaction {
  uint8_t unused;
} dif_iopmp_transaction_t;

/**
 * An output location for a IOPMP transaction.
 */
typedef struct dif_iopmp_output {
  uint8_t unused;
} dif_iopmp_output_t;

// /**
//  * Configures IOPMP with runtime information.
//  *
//  * This function should only need to be called once for the lifetime of
//  * `handle`.
//  *
//  * @param iopmp A IOPMP handle.
//  * @param config Runtime configuration parameters.
//  * @return The result of the operation.
//  */
// OT_WARN_UNUSED_RESULT
// dif_result_t dif_iopmp_configure(
//   const dif_iopmp_t *iopmp,
//   dif_iopmp_config_t config);

/**
 * Begins a IOPMP transaction.
 *
 * Each call to this function should be sequenced with a call to
 * `dif_iopmp_end()`.
 *
 * @param iopmp A IOPMP handle.
 * @param transaction Transaction configuration parameters.
 * @return The result of the operation.
 */
OT_WARN_UNUSED_RESULT
dif_result_t dif_iopmp_start(
  const dif_iopmp_t *iopmp,
  dif_iopmp_transaction_t transaction);

/** Ends a IOPMP transaction, writing the results to the given output.
 *
 * @param iopmp A IOPMP handle.
 * @param output Transaction output parameters.
 * @return The result of the operation.
 */
OT_WARN_UNUSED_RESULT
dif_result_t dif_iopmp_end(
  const dif_iopmp_t *iopmp,
  dif_iopmp_output_t output);

/**
 * Locks out IOPMP functionality.
 *
 * This function is reentrant: calling it while functionality is locked will
 * have no effect and return `kDifOk`.
 *
 * @param iopmp A IOPMP handle.
 * @return The result of the operation.
 */
OT_WARN_UNUSED_RESULT
dif_result_t dif_iopmp_lock(
  const dif_iopmp_t *iopmp);

/**
 * Checks whether this IOPMP is locked.
 *
 * @param iopmp A IOPMP handle.
 * @param[out] is_locked Out-param for the locked state.
 * @return The result of the operation.
 */
OT_WARN_UNUSED_RESULT
dif_result_t dif_iopmp_is_locked(
  const dif_iopmp_t *iopmp,
  bool *is_locked);

void dif_iopmp_get_config(dif_iopmp_t* iopmp, dif_iopmp_config_t* config);

// ERR_CFG.ie
// (for local, per-entry, ENTRY_CFG for each entry WANNA re-read 2.7 before impl)
// ERR_CFG.rsv1 & ERR_CFG.rsv2 must be 0 on write 
void dif_iopmp_enable_global_irq_error_reaction(dif_iopmp_t* iopmp);

typedef enum dif_iopmp_entry_addr_mode {
  kDifIopmpEntryAddrModeOff,
  kDifIopmpEntryAddrModeTor,
  kDifIopmpEntryAddrModeNa4,
  kDifIopmpEntryAddrModeNapot
} dif_iopmp_entry_addr_mode_t;

typedef struct dif_iopmp_entry_cfg {
  dif_toggle_t r;
  dif_toggle_t w;
  dif_toggle_t x;
  dif_iopmp_entry_addr_mode_t a;
  dif_toggle_t sire;
  dif_toggle_t siwe;
  dif_toggle_t sixe;
  dif_toggle_t sere;
  dif_toggle_t sewe;
  dif_toggle_t sexe;
} dif_iopmp_entry_cfg_t;

void dif_iopmp_set_md_mask_for_rrid(dif_iopmp_t* iopmp, uint32_t rrid, uint32_t md_mask, bool lock);

void dif_iopmp_get_md_mask_for_rrid(dif_iopmp_t* iopmp, uint32_t rrid, uint32_t* md_mask, bool* is_locked);

void dif_iopmp_add_entry(dif_iopmp_t* iopmp, const dif_iopmp_config_t* iopmp_cfg, uint32_t entry_addr, const dif_iopmp_entry_cfg_t* entry_cfg);

void dif_iopmp_get_entry(dif_iopmp_t* iopmp, const dif_iopmp_config_t* iopmp_cfg, int entry, uint32_t* entry_addr, dif_iopmp_entry_cfg_t* entry_cfg);

void dif_iopmp_mdcfg_set_top_range(dif_iopmp_t* iopmp, uint32_t md, uint32_t top_range);

void dif_iopmp_mdcfg_get_top_range(dif_iopmp_t* iopmp, uint32_t md, uint32_t* top_range);

bool dif_iopmp_cmp_entry_cfg(const dif_iopmp_entry_cfg_t* self, const dif_iopmp_entry_cfg_t* other);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  // OPENTITAN_SW_DEVICE_LIB_DIF_DIF_IOPMP_H_
